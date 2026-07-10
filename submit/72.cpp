name: 代码评测

on:
  push:
    paths:
      - 'submit/**'
  workflow_dispatch:
    inputs:
      judge_id:
        description: '评测ID (对应 submit/{judge_id}.cpp)'
        required: true
        type: string
      problem_id:
        description: '题目ID (对应 testdata/{problem_id}/)'
        required: true
        type: string

jobs:
  judge:
    runs-on: ubuntu-latest

    steps:
      - name: 检出代码
        uses: actions/checkout@v4
        with:
          fetch-depth: 0

      - name: 获取评测ID和题目ID
        id: get_id
        run: |
          JUDGE_ID="${{ github.event.inputs.judge_id }}"
          PROBLEM_ID="${{ github.event.inputs.problem_id }}"
          
          if [ -z "$JUDGE_ID" ]; then
            COMMIT_MSG=$(git log -1 --pretty=%B)
            JUDGE_ID=$(echo "$COMMIT_MSG" | grep -oP '#\K\d+' | head -1)
            PROBLEM_ID=$(echo "$COMMIT_MSG" | grep -oP '题目 \K\d+' | head -1)
          fi
          
          echo "JUDGE_ID=$JUDGE_ID" >> $GITHUB_ENV
          echo "PROBLEM_ID=$PROBLEM_ID" >> $GITHUB_ENV

      - name: 显示参数
        run: |
          echo "评测ID: ${{ env.JUDGE_ID }}"
          echo "题目ID: ${{ env.PROBLEM_ID }}"

      - name: 编译
        run: |
          if [ ! -f "submit/${{ env.JUDGE_ID }}.cpp" ]; then
            echo "代码文件 submit/${{ env.JUDGE_ID }}.cpp 不存在"
            exit 1
          fi
          cp "submit/${{ env.JUDGE_ID }}.cpp" main.cpp
          if g++ -std=c++17 -O2 -o program main.cpp 2> compile_error.txt; then
            echo "编译成功"
          else
            echo "编译失败"
            cat compile_error.txt
            mkdir -p results
            echo "{\"judge_id\": ${{ env.JUDGE_ID }}, \"result\": \"CE\", \"passed\": 0, \"total\": 0}" > results/${{ env.JUDGE_ID }}.json
            exit 1
          fi

      - name: 评测
        run: |
          data_dir="testdata/${{ env.PROBLEM_ID }}"
          if [ ! -d "$data_dir" ]; then
            data_dir="${{ env.PROBLEM_ID }}"
          fi
          if [ ! -d "$data_dir" ]; then
            echo "错误：找不到题目 ${{ env.PROBLEM_ID }} 的测试数据目录"
            exit 1
          fi

          passed=0
          total=0

          for input in "$data_dir"/*.in; do
            if [ ! -f "$input" ]; then continue; fi
            total=$((total + 1))
            base=$(basename "$input" .in)
            output_file="$data_dir/$base.out"
            ans_file="$data_dir/$base.ans"

            if [ -f "$output_file" ]; then
              answer_file="$output_file"
            elif [ -f "$ans_file" ]; then
              answer_file="$ans_file"
            else
              echo "测试点 $base: SKIP"
              continue
            fi

            timeout 5 ./program < "$input" > output.txt 2>&1
            exit_code=$?

            if [ $exit_code -eq 124 ]; then
              echo "测试点 $base: TLE"
            elif [ $exit_code -ne 0 ]; then
              echo "测试点 $base: RE"
            else
              if diff -q output.txt "$answer_file" > /dev/null 2>&1; then
                echo "测试点 $base: AC"
                passed=$((passed + 1))
              else
                echo "测试点 $base: WA"
              fi
            fi
          done

          echo ""
          echo "通过: $passed / $total"

          if [ $passed -eq $total ] && [ $total -gt 0 ]; then
            RESULT="AC"
          elif [ $total -eq 0 ]; then
            RESULT="NoData"
          else
            RESULT="WA"
          fi

          mkdir -p results
          echo "{\"judge_id\": ${{ env.JUDGE_ID }}, \"result\": \"$RESULT\", \"passed\": $passed, \"total\": $total}" > results/${{ env.JUDGE_ID }}.json

      - name: 提交结果到仓库
        if: always()
        run: |
          mkdir -p results
          if [ ! -f "results/${{ env.JUDGE_ID }}.json" ]; then
            echo "{\"judge_id\": ${{ env.JUDGE_ID }}, \"result\": \"SystemError\", \"passed\": 0, \"total\": 0}" > results/${{ env.JUDGE_ID }}.json
          fi

          git config --global user.name "github-actions[bot]"
          git config --global user.email "github-actions[bot]@users.noreply.github.com"

          git pull --rebase origin main || true
          git add results/
          git commit -m "评测结果 #${{ env.JUDGE_ID }}" || true
          git push origin main || true