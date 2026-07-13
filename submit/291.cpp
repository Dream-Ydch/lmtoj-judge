<?php
session_start();
error_reporting(E_ALL);
ini_set('display_errors', 1);
date_default_timezone_set('Asia/Shanghai');

require_once 'visit_log.php';
header("Content-Type:text/html;charset=utf-8");
require_once __DIR__ . '/database.php';
$conn = db();
$conn->set_charset("utf8");

$login_uid = isset($_SESSION['uid']) ? (int)$_SESSION['uid'] : 0;
if ($login_uid <= 0) {
    header("Location: login.php");
    exit;
}

if (isset($_GET['logout'])) {
    session_destroy();
    header("Location: login.php");
    exit;
}

$is_admin = 0;
$adminRes = $conn->query("SELECT admin FROM users WHERE uid = {$login_uid} LIMIT 1");
if ($adminRes && $adminRes->num_rows > 0) {
    $is_admin = (int)$adminRes->fetch_assoc()['admin'];
}

$userName = $_SESSION['name'] ?? '用户';

$page = isset($_GET['page']) ? max(1, (int)$_GET['page']) : 1;
$perPage = 20;
$offset = ($page - 1) * $perPage;

$problemFilter = isset($_GET['problem_id']) ? (int)$_GET['problem_id'] : 0;
$resultFilter = isset($_GET['result']) ? trim($_GET['result']) : '';
$uidFilter = isset($_GET['uid']) ? (int)$_GET['uid'] : 0;

if (!$is_admin) {
    $uidFilter = 0;
}

$where = "WHERE 1=1";
if (!$is_admin) {
    $where .= " AND s.uid = $login_uid";
}
if ($problemFilter > 0) {
    $where .= " AND s.problem_id = $problemFilter";
}
if (!empty($resultFilter)) {
    $where .= " AND s.result = '" . $conn->real_escape_string($resultFilter) . "'";
}
if ($uidFilter > 0 && $is_admin) {
    $where .= " AND s.uid = $uidFilter";
}

$countQuery = "SELECT COUNT(*) AS total FROM submissions s $where";
$countResult = $conn->query($countQuery);
$totalRecords = $countResult ? (int)$countResult->fetch_assoc()['total'] : 0;
$totalPages = ceil($totalRecords / $perPage);

$query = "SELECT s.*, p.name as problem_name, u.name as username
          FROM submissions s
          LEFT JOIN problem_desc p ON s.problem_id = p.id
          LEFT JOIN users u ON s.uid = u.uid
          $where
          ORDER BY s.id DESC
          LIMIT $offset, $perPage";
$submissions = $conn->query($query);

$problems = $conn->query("SELECT id, name FROM problem_desc ORDER BY id");

$pendingCount = 0;
if ($is_admin) {
    $pendingQuery = $conn->query("SELECT COUNT(*) AS cnt FROM submissions WHERE result = 'Pending'");
    $pendingCount = $pendingQuery ? (int)$pendingQuery->fetch_assoc()['cnt'] : 0;
}

function getResultClass($result) {
    $map = [
        'AC' => 'result-ac',
        'WA' => 'result-wa',
        'TLE' => 'result-tle',
        'RE' => 'result-re',
        'CE' => 'result-ce',
        'Pending' => 'result-pending',
        'Running' => 'result-running',
        'SystemError' => 'result-system',
        'UKE' => 'result-unknown'
    ];
    return $map[$result] ?? 'result-unknown';
}

function getResultText($result) {
    $map = [
        'AC' => 'Accepted',
        'WA' => 'Wrong Answer',
        'TLE' => 'Time Limit Exceeded',
        'RE' => 'Runtime Error',
        'CE' => 'Compile Error',
        'Pending' => 'Pending',
        'Running' => 'Running',
        'SystemError' => 'System Error',
        'UKE' => 'Unknown Error'
    ];
    return $map[$result] ?? $result;
}

// 从本地 results 目录读取评测结果（如果本地有的话）
function getResultFromLocal($judgeId) {
    $filePath = __DIR__ . "/results/{$judgeId}.json";
    if (file_exists($filePath)) {
        $content = file_get_contents($filePath);
        $data = json_decode($content, true);
        if ($data && isset($data['result'])) {
            return $data;
        }
    }
    return null;
}

// 从 GitHub results 目录读取评测结果
function getResultFromGitHub($judgeId) {
    // 先尝试从本地读取
    $localResult = getResultFromLocal($judgeId);
    if ($localResult) {
        return $localResult;
    }
    
    // 如果本地没有，从 GitHub 读取
    $url = "https://raw.githubusercontent.com/Dream-Ydch/lmtoj-judge/main/results/{$judgeId}.json";
    
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, $url);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_TIMEOUT, 3);
    curl_setopt($ch, CURLOPT_USERAGENT, 'lmtOJ/1.0');
    curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
    
    $response = curl_exec($ch);
    $httpCode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
    curl_close($ch);
    
    if ($httpCode == 200 && $response) {
        $data = json_decode($response, true);
        if ($data && isset($data['result'])) {
            return $data;
        }
    }
    
    return null;
}

// 获取分数显示的函数
function getScoreDisplay($result, $score) {
    if ($result == 'AC') {
        // AC 时显示实际分数，如果没有分数则显示 100
        return $score !== null && $score !== '' ? (int)$score : 100;
    }
    elseif ($result == 'Pending' || $result == 'Running') {
        return '—';
    }
    elseif (in_array($result, ['CE', 'RE', 'TLE', 'WA', 'SystemError', 'UKE'])) {
        return 0;
    }
    else {
        return '—';
    }
}
?>
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <title>评测记录 - lmtOJ</title>
    <link rel="preconnect" href="https://cdn.jsdelivr.net">
    <style>
        :root {
            --bg: #f9f7f4;
            --card-bg: #ffffff;
            --nav-bg: #3d3a37;
            --nav-text: #f0ece6;
            --text: #2c2a28;
            --text-secondary: #7a736b;
            --text-muted: #a0988e;
            --border: #e6e1da;
            --border-light: #f0ece6;
            --accent: #6b8a74;
            --accent-hover: #55735e;
            --accent-light: #eef4ef;
            --shadow: 0 2px 10px rgba(0,0,0,0.05);
            --shadow-md: 0 4px 16px rgba(0,0,0,0.06);
            --radius: 10px;
            --radius-sm: 6px;
            --transition: 0.18s ease;
            --font: 'Segoe UI', 'PingFang SC', 'Microsoft YaHei', 'Noto Sans SC', system-ui, sans-serif;
        }
        * { margin:0; padding:0; box-sizing:border-box; }
        body { background:var(--bg); font-family:var(--font); color:var(--text); line-height:1.6; -webkit-font-smoothing:antialiased; }
        .navbar {
            background:var(--nav-bg); height:54px; display:flex; align-items:center;
            justify-content:space-between; padding:0 28px; color:var(--nav-text);
            position:sticky; top:0; z-index:100; box-shadow:0 1px 4px rgba(0,0,0,0.08);
        }
        .navbar h1 { font-size:17px; font-weight:600; color:#f0ece6; letter-spacing:0.4px; }
        .navbar h1 a { color:#f0ece6; text-decoration:none; }
        .user-info { display:flex; align-items:center; gap:6px; }
        .user-info a {
            color:#e0dbd3; text-decoration:none; font-size:13.5px; padding:7px 13px;
            border-radius:20px; transition:var(--transition); font-weight:500;
        }
        .user-info a:hover { background:rgba(255,255,255,0.1); color:#fff; }
        .user-info a.admin-link { color:#f5d76e; font-weight:600; }
        .main { max-width:1100px; margin:28px auto 40px; display:flex; gap:22px; padding:0 20px; align-items:flex-start; }
        .sidebar {
            background:var(--card-bg); border-radius:var(--radius); box-shadow:var(--shadow);
            width:fit-content; min-width:110px; overflow:hidden; position:sticky; top:80px; flex-shrink:0;
        }
        .sidebar a {
            display:block; padding:13px 22px; text-align:center; background:var(--card-bg);
            color:var(--text); text-decoration:none; font-size:14.5px; font-weight:500;
            transition:var(--transition); border-left:3px solid transparent; letter-spacing:0.3px;
        }
        .sidebar a:hover { background:#f5f2ed; border-left-color:var(--accent); color:var(--accent); }
        .sidebar a.active { border-left-color:var(--accent); background:var(--accent-light); }
        .content { flex:1; min-width:0; }
        .card {
            background:var(--card-bg); border-radius:var(--radius); padding:26px 28px;
            margin-bottom:18px; box-shadow:var(--shadow);
        }
        .card h2 { font-size:18px; font-weight:600; margin-bottom:16px; }
        .filter-bar {
            display: flex; flex-wrap: wrap; gap: 12px; align-items: center; margin-bottom: 0;
        }
        .filter-bar label { font-size: 13px; font-weight: 500; color: var(--text-secondary); }
        .filter-bar select, .filter-bar input {
            padding: 7px 14px; border: 1.5px solid var(--border); border-radius: var(--radius-sm);
            font-size: 13px; background: #fff; outline: none; font-family: var(--font); transition: var(--transition); min-width: 120px;
        }
        .filter-bar select:focus, .filter-bar input:focus {
            border-color: var(--accent); box-shadow: 0 0 0 3px rgba(107,138,116,0.1);
        }
        .btn {
            padding: 7px 20px; background: var(--accent); color: #fff; border: none;
            border-radius: 20px; cursor: pointer; font-size: 13px; font-weight: 500; transition: var(--transition); font-family: var(--font);
        }
        .btn:hover { background: var(--accent-hover); box-shadow:0 2px 8px rgba(107,138,116,0.25); }
        .btn-reset { background: var(--border); color: var(--text-secondary); }
        .btn-reset:hover { background: #d5d0c8; }
        .btn-sm { padding: 4px 12px; font-size: 12px; border-radius: 12px; text-decoration: none; display: inline-block; }
        .table-wrap { overflow-x: auto; margin-top: 16px; }
        table { width: 100%; border-collapse: collapse; }
        thead { background: #f8f7f4; border-bottom: 2px solid var(--border); }
        th {
            text-align: left; padding: 12px 16px; font-size: 12px; font-weight: 600;
            text-transform: uppercase; letter-spacing: 0.5px; color: var(--text-secondary);
        }
        td { padding: 12px 16px; border-bottom: 1px solid var(--border-light); font-size: 14px; vertical-align: middle; }
        tr:hover td { background: #fafaf8; }
        tr:last-child td { border-bottom: none; }
        .result-badge {
            display: inline-block; padding: 2px 12px; border-radius: 12px; font-size: 12px; font-weight: 600; letter-spacing: 0.3px;
        }
        .result-ac { background: #d4edda; color: #155724; }
        .result-wa { background: #f8d7da; color: #721c24; }
        .result-tle { background: #fff3cd; color: #856404; }
        .result-re { background: #e8d5f5; color: #6c3483; }
        .result-ce { background: #fff3cd; color: #856404; }
        .result-pending { background: #cce5ff; color: #004085; }
        .result-running { background: #e8f5e9; color: #1b5e20; }
        .result-system { background: #e2e3e5; color: #383d41; }
        .result-unknown { background: #e2e3e5; color: #383d41; }
        .problem-link { color: var(--accent); font-weight: 500; }
        .problem-link:hover { text-decoration: underline; }
        .user-link { color: var(--text-secondary); text-decoration: none; }
        .user-link:hover { color: var(--accent); text-decoration: underline; }
        .time-text { font-size: 13px; color: var(--text-muted); }
        .empty-state { text-align: center; padding: 60px 20px; color: var(--text-muted); }
        .empty-state .icon { font-size: 48px; margin-bottom: 12px; }
        .pagination {
            display: flex; justify-content: center; gap: 6px; padding: 20px 0 10px; flex-wrap: wrap;
        }
        .pagination a, .pagination span {
            padding: 6px 14px; border-radius: 20px; font-size: 14px; font-weight: 500;
            color: var(--text-secondary); text-decoration: none; transition: var(--transition); border: 1.5px solid var(--border);
        }
        .pagination a:hover { background: var(--accent-light); color: var(--accent); border-color: var(--accent); }
        .pagination .active { background: var(--accent); color: #fff; border-color: var(--accent); }
        .pagination .disabled { opacity: 0.4; cursor: default; }
        .pagination .ellipsis { border: none; color: var(--text-muted); }
        .admin-toolbar {
            display: flex; gap: 12px; align-items: center; flex-wrap: wrap;
            padding: 12px 20px; background: #fef9e7; border: 1px solid #f9e79f;
            border-radius: var(--radius); margin-bottom: 18px;
        }
        .admin-toolbar .label { font-size: 13px; font-weight: 600; color: #7d6608; }
        .admin-toolbar .badge { background: #f39c12; color: #fff; padding: 2px 10px; border-radius: 12px; font-size: 12px; font-weight: 600; }

        /* 管理员内联编辑样式 */
        .admin-edit-cell { display: inline-flex; align-items: center; gap: 4px; }
        .admin-edit-icon {
            font-size: 14px; color: #999; cursor: pointer; user-select: none; transition: color 0.2s;
        }
        .admin-edit-icon:hover { color: #333; }
        .admin-result-select {
            padding: 2px 6px; border: 1.5px solid var(--border); border-radius: var(--radius-sm);
            font-size: 12px; font-weight: 500; background: #fff; outline: none; display: none;
        }
        .admin-result-select:focus { border-color: var(--accent); }

        /* 得分样式 */
        .score-ac { color: #27ae60; font-weight: 600; }
        .score-fail { color: #e74c3c; font-weight: 500; }
        .score-pending { color: #3498db; font-weight: 500; }
        .score-unknown { color: var(--text-muted); }

        @media (max-width:768px) {
            .main { flex-direction:column; padding:0 12px; margin:18px auto 30px; }
            .sidebar { width:100%; position:static; display:flex; flex-wrap:wrap; }
            .sidebar a { flex:1 1 auto; padding:11px 10px; font-size:13px; border-left:none; border-bottom:2px solid transparent; }
            .sidebar a:hover { border-left-color:transparent; border-bottom-color:var(--accent); }
            .navbar { padding:0 14px; height:48px; }
            .card { padding:18px 14px; }
            .filter-bar { flex-direction: column; align-items: stretch; }
            .filter-bar select, .filter-bar input { min-width: auto; }
            th, td { padding: 8px 10px; font-size: 13px; }
            .admin-toolbar { flex-direction: column; align-items: stretch; }
        }
    </style>
</head>
<body>

<?php include __DIR__ . '/navbar.php'; ?>

<div class="main">
    <?php include 'sidebar.php'; ?>

    <div class="content">
        <div style="display:flex; justify-content:space-between; align-items:center; margin-bottom:16px; flex-wrap:wrap; gap:8px;">
            <h2 style="font-size:20px; font-weight:700;">📊 评测记录</h2>
            <span style="font-size:14px; color:var(--text-muted);">共 <?= $totalRecords ?> 条记录</span>
        </div>

        <div class="card">
            <form method="GET" class="filter-bar">
                <label for="problem_id">题目</label>
                <select name="problem_id" id="problem_id">
                    <option value="0">全部题目</option>
                    <?php while ($p = $problems->fetch_assoc()): ?>
                        <option value="<?= $p['id'] ?>" <?= $problemFilter == $p['id'] ? 'selected' : '' ?>>
                            #<?= $p['id'] ?> <?= htmlspecialchars($p['name'] ?? '') ?>
                        </option>
                    <?php endwhile; ?>
                </select>

                <label for="result">结果</label>
                <select name="result" id="result">
                    <option value="">全部结果</option>
                    <option value="AC" <?= $resultFilter == 'AC' ? 'selected' : '' ?>>AC</option>
                    <option value="WA" <?= $resultFilter == 'WA' ? 'selected' : '' ?>>WA</option>
                    <option value="TLE" <?= $resultFilter == 'TLE' ? 'selected' : '' ?>>TLE</option>
                    <option value="RE" <?= $resultFilter == 'RE' ? 'selected' : '' ?>>RE</option>
                    <option value="CE" <?= $resultFilter == 'CE' ? 'selected' : '' ?>>CE</option>
                    <option value="Pending" <?= $resultFilter == 'Pending' ? 'selected' : '' ?>>Pending</option>
                    <option value="Running" <?= $resultFilter == 'Running' ? 'selected' : '' ?>>Running</option>
                    <option value="SystemError" <?= $resultFilter == 'SystemError' ? 'selected' : '' ?>>System Error</option>
                    <option value="UKE" <?= $resultFilter == 'UKE' ? 'selected' : '' ?>>UKE</option>
                </select>

                <?php if ($is_admin): ?>
                    <label for="uid">用户ID</label>
                    <input type="number" name="uid" id="uid" value="<?= $uidFilter > 0 ? $uidFilter : '' ?>" placeholder="输入用户ID" style="min-width:100px;">
                <?php endif; ?>

                <button type="submit" class="btn">筛选</button>
                <a href="record.php" class="btn btn-reset" style="text-decoration:none;">重置</a>
            </form>
        </div>

        <div class="card" style="padding:0; overflow:hidden;">
            <div class="table-wrap">
                <?php if ($submissions && $submissions->num_rows > 0): ?>
                <table>
                    <thead>
                        <tr>
                            <th style="width:70px;">ID</th>
                            <th style="width:80px;">题目</th>
                            <th>用户</th>
                            <th style="width:180px;">结果</th>
                            <th style="width:100px;">得分</th>
                            <th style="width:150px;">提交时间</th>
                        </tr>
                    </thead>
                    <tbody>
                        <?php while ($row = $submissions->fetch_assoc()): ?>
                        <?php 
                            // 从 GitHub 获取最新结果
                            $githubResult = getResultFromGitHub($row['id']);
                            
                            if ($githubResult) {
                                $displayResult = $githubResult['result'];
                                // 如果 JSON 中有 score 字段，使用它，否则使用数据库中的
                                $displayScore = isset($githubResult['score']) ? $githubResult['score'] : $row['score'];
                            } else {
                                $displayResult = $row['result'];
                                $displayScore = $row['score'];
                            }
                            
                            // 如果是 AC 但分数为 0 或 null，设置为 100
                            if ($displayResult == 'AC' && ($displayScore === null || $displayScore === '' || $displayScore == 0)) {
                                $displayScore = 100;
                            }
                            
                            $scoreDisplay = getScoreDisplay($displayResult, $displayScore);
                            $scoreClass = '';
                            if ($displayResult == 'AC') {
                                $scoreClass = 'score-ac';
                            } elseif (in_array($displayResult, ['CE', 'RE', 'TLE', 'WA', 'SystemError', 'UKE'])) {
                                $scoreClass = 'score-fail';
                            } elseif ($displayResult == 'Pending' || $displayResult == 'Running') {
                                $scoreClass = 'score-pending';
                            } else {
                                $scoreClass = 'score-unknown';
                            }
                        ?>
                        <tr>
                            <td><strong>#<?= $row['id'] ?></strong></td>
                            <td>
                                <a href="problem_view.php?id=<?= $row['problem_id'] ?>" class="problem-link">
                                    #<?= $row['problem_id'] ?>
                                </a>
                            </td>
                            <td>
                                <a href="user.php?uid=<?= $row['uid'] ?>" class="user-link">
                                    <?= htmlspecialchars($row['username'] ?? '用户#' . $row['uid']) ?>
                                </a>
                            </td>
                            <td>
                                <?php if ($is_admin): ?>
                                <span class="admin-edit-cell" data-id="<?= $row['id'] ?>" data-result="<?= $displayResult ?>">
                                    <select class="admin-result-select">
                                        <option value="AC" <?= $displayResult=='AC'?'selected':'' ?>>AC</option>
                                        <option value="WA" <?= $displayResult=='WA'?'selected':'' ?>>WA</option>
                                        <option value="TLE" <?= $displayResult=='TLE'?'selected':'' ?>>TLE</option>
                                        <option value="RE" <?= $displayResult=='RE'?'selected':'' ?>>RE</option>
                                        <option value="CE" <?= $displayResult=='CE'?'selected':'' ?>>CE</option>
                                        <option value="Pending" <?= $displayResult=='Pending'?'selected':'' ?>>Pending</option>
                                        <option value="Running" <?= $displayResult=='Running'?'selected':'' ?>>Running</option>
                                        <option value="SystemError" <?= $displayResult=='SystemError'?'selected':'' ?>>System Error</option>
                                        <option value="UKE" <?= $displayResult=='UKE'?'selected':'' ?>>UKE</option>
                                    </select>
                                    <span class="result-badge <?= getResultClass($displayResult) ?>"><?= getResultText($displayResult) ?></span>
                                    <span class="admin-edit-icon" title="修改评测状态"> ✎</span>
                                </span>
                                <?php else: ?>
                                <span class="result-badge <?= getResultClass($displayResult) ?>"><?= getResultText($displayResult) ?></span>
                                <?php endif; ?>
                            </td>
                            <td>
                                <span class="<?= $scoreClass ?>">
                                    <?= $scoreDisplay ?>
                                </span>
                            </td>
                            <td class="time-text"><?= date('Y-m-d H:i', strtotime($row['created_at'])+15*3600) ?></td>
                        </tr>
                        <?php endwhile; ?>
                    </tbody>
                </table>
                <?php else: ?>
                <div class="empty-state">
                    <div class="icon">📭</div>
                    <p>暂无评测记录</p>
                </div>
                <?php endif; ?>
            </div>
        </div>

        <?php if ($totalPages > 1): ?>
        <div class="pagination">
            <?php
            $queryParams = "problem_id={$problemFilter}&result=" . urlencode($resultFilter);
            $uidParam = ($is_admin && $uidFilter > 0) ? "&uid={$uidFilter}" : "";
            ?>
            <?php if ($page > 1): ?>
                <a href="?page=<?= $page-1 ?>&<?= $queryParams ?><?= $uidParam ?>">‹ 上一页</a>
            <?php else: ?>
                <span class="disabled">‹ 上一页</span>
            <?php endif; ?>

            <?php $start = max(1, $page - 2); $end = min($totalPages, $page + 2); if ($start > 1): ?>
                <a href="?page=1&<?= $queryParams ?><?= $uidParam ?>">1</a>
                <?php if ($start > 2): ?><span class="ellipsis">…</span><?php endif; ?>
            <?php endif; ?>

            <?php for ($i = $start; $i <= $end; $i++): ?>
                <?php if ($i == $page): ?>
                    <span class="active"><?= $i ?></span>
                <?php else: ?>
                    <a href="?page=<?= $i ?>&<?= $queryParams ?><?= $uidParam ?>"><?= $i ?></a>
                <?php endif; ?>
            <?php endfor; ?>

            <?php if ($end < $totalPages): ?>
                <?php if ($end < $totalPages - 1): ?><span class="ellipsis">…</span><?php endif; ?>
                <a href="?page=<?= $totalPages ?>&<?= $queryParams ?><?= $uidParam ?>"><?= $totalPages ?></a>
            <?php endif; ?>

            <?php if ($page < $totalPages): ?>
                <a href="?page=<?= $page+1 ?>&<?= $queryParams ?><?= $uidParam ?>">下一页 ›</a>
            <?php else: ?>
                <span class="disabled">下一页 ›</span>
            <?php endif; ?>
        </div>
        <?php endif; ?>
    </div>
</div>

<?php include __DIR__ . '/footer.php'; ?>

<?php if ($is_admin): ?>
<script>
(function() {
    // 内联编辑逻辑：点击铅笔切换为下拉框，修改后自动保存
    function initAdminEdit() {
        document.querySelectorAll('.admin-edit-cell').forEach(cell => {
            const select = cell.querySelector('.admin-result-select');
            const badge = cell.querySelector('.result-badge');
            const icon = cell.querySelector('.admin-edit-icon');
            const submissionId = cell.dataset.id;
            const currentResult = cell.dataset.result;

            // 点击铅笔：隐藏徽章和铅笔，显示下拉框并聚焦
            icon.addEventListener('click', function(e) {
                e.stopPropagation();
                e.preventDefault();
                badge.style.display = 'none';
                icon.style.display = 'none';
                select.style.display = 'inline-block';
                select.focus();
            });

            // 下拉框值改变时自动保存
            select.addEventListener('change', function() {
                const newResult = select.value;
                // 发送 AJAX 更新
                fetch('record_update.php', {
                    method: 'POST',
                    headers: {'Content-Type': 'application/x-www-form-urlencoded'},
                    body: 'id=' + encodeURIComponent(submissionId) + '&result=' + encodeURIComponent(newResult)
                })
                .then(res => res.json())
                .then(data => {
                    if (data.success) {
                        // 更新徽章样式和文字
                        badge.textContent = select.options[select.selectedIndex].text;
                        badge.className = 'result-badge ' + getResultClass(newResult);
                        // 更新 data-result
                        cell.dataset.result = newResult;
                        // 恢复显示
                        badge.style.display = '';
                        icon.style.display = '';
                        select.style.display = 'none';
                    } else {
                        alert('修改失败: ' + (data.error || '未知错误'));
                        // 恢复原选择值
                        select.value = currentResult;
                        badge.style.display = '';
                        icon.style.display = '';
                        select.style.display = 'none';
                    }
                })
                .catch(err => {
                    alert('请求失败: ' + err);
                    badge.style.display = '';
                    icon.style.display = '';
                    select.style.display = 'none';
                });
            });

            // 点击下拉框外部时取消编辑
            document.addEventListener('click', function(e) {
                if (!cell.contains(e.target)) {
                    badge.style.display = '';
                    icon.style.display = '';
                    select.style.display = 'none';
                }
            });
        });
    }

    // 辅助函数：将结果代码转为 CSS 类名
    function getResultClass(result) {
        const map = {
            'AC': 'result-ac',
            'WA': 'result-wa',
            'TLE': 'result-tle',
            'RE': 'result-re',
            'CE': 'result-ce',
            'Pending': 'result-pending',
            'Running': 'result-running',
            'SystemError': 'result-system',
            'UKE': 'result-unknown'
        };
        return map[result] || 'result-unknown';
    }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', initAdminEdit);
    } else {
        initAdminEdit();
    }
})();
</script>
<?php endif; ?>
</body>
</html>