#include<bits/stdc++.h>
#define out(a) cout<<#a""<<':'<<a<<'\n'
using namespace std;
typedef long long ll;
class gjd{//高精度
private:
	vector<int>dig;//存储数字，低位在前
	bool is_fs;//是否为负数
	//去除前导零
	void trim(){
		while(dig.size()>1&&dig.back()==0) dig.pop_back();
		if(dig.size()==1&&dig[0]==0) is_fs=0;
	}
	//比较绝对值大小
	int cmp_abs(const gjd& oth)const{
		if(dig.size()!=oth.dig.size()) return dig.size()<oth.dig.size()?-1:1;
		for(int i=dig.size()-1;i>=0;i--)
			if(dig[i]!=oth.dig[i])
				return dig[i]<oth.dig[i]?-1:1;
		return 0;
	}
public:
	//构造函数
	gjd():is_fs(0){dig.push_back(0);}
	gjd(const string& s){
		int start=0;
		if(s[0]=='-'){
			is_fs=1;
			start=1;
		}else is_fs=0;
		for (int i=s.size()-1;i>=start;i--) dig.push_back(s[i]-'0');
		trim();
	}
	gjd(ll num){
		if(num<0){
			is_fs=1;
			num=-num;
		}else is_fs=0;
		if(num==0) dig.push_back(0);
		else{
			while(num>0){
				dig.push_back(num%10);
				num/=10;
			}
		}
	}
	// 转换为字符串
	string toString()const{
		string res;
		if(is_fs) res+='-';
		for (int i=dig.size()-1;i>=0;i--) res+=to_string(dig[i]);
		return res;
	}
	// 比较运算符
	bool operator<(const gjd& oth)const{
		if(is_fs!=oth.is_fs) return is_fs;
		if(is_fs) return cmp_abs(oth)>0;
		else return cmp_abs(oth)<0;
	}
	bool operator>(const gjd& oth)const{return oth<*this;}
	bool operator<=(const gjd& oth)const{return !(*this>oth);}
	bool operator>=(const gjd& oth)const{return !(*this<oth);}
	bool operator==(const gjd& oth)const{return is_fs==oth.is_fs&&dig==oth.dig;}
	bool operator!=(const gjd& oth)const{return !(*this==oth);}
	// 算术运算符
	gjd operator-()const{
		gjd res=*this;
		res.is_fs=!is_fs;
		res.trim();
		return res;
	}
	gjd operator+(const gjd& oth)const{
		if(is_fs==oth.is_fs){
			gjd res;
			res.is_fs=is_fs;
			res.dig.clear();
			int cr=0,maxl=max(dig.size(),oth.dig.size());
			for(int i=0;i<maxl||cr;i++){
				int sum=cr;
				if(i<(int)dig.size()) sum+=dig[i];
				if(i<(int)oth.dig.size()) sum+=oth.dig[i];
				res.dig.push_back(sum % 10);
				cr=sum/10;
			}
			res.trim();
			return res;
		}else{
			if(is_fs) return oth-(-*this);
			else return *this-(-oth);
		}
	}
	gjd operator-(const gjd& oth)const{
		if(is_fs!=oth.is_fs) return *this+(-oth);
		if(cmp_abs(oth)>=0){
			gjd res;
			res.is_fs=is_fs;
			res.dig.clear();
			int br=0;
			for(int i=0;i<(int)dig.size();i++){
				int diff=dig[i]-br;
				if(i<(int)oth.dig.size()) diff-=oth.dig[i];
				if(diff<0){
					diff+=10;
					br=1;
				}else br=0;
				res.dig.push_back(diff);
			}
			res.trim();
			return res;
		}else return -(oth-*this);
	}
	gjd operator*(const gjd& oth)const{
		gjd res;
		res.dig.resize(dig.size()+oth.dig.size(),0);
		res.is_fs=is_fs!=oth.is_fs;
		for(int i=0;i<(int)dig.size();i++){
			int cr=0;
			for(int j=0;j<(int)oth.dig.size()||cr;j++){
				ll prd=res.dig[i+j]+cr;
				if(j<(int)oth.dig.size()) prd+=dig[i]*oth.dig[j];
				res.dig[i+j]=prd%10;
				cr=prd/10;
			}
		}
		res.trim();
		return res;
	}
	gjd operator/(const gjd& oth)const{
		if(oth==gjd(0)) throw runtime_error("Division by zero");
		gjd divd=*this;
		gjd divs=oth;
		divd.is_fs=0;
		divs.is_fs=0;
		if(divd<divs) return gjd(0);
		gjd res;
		res.dig.resize(divd.dig.size(),0);
		res.is_fs=is_fs!=oth.is_fs;
		gjd crt;
		for(int i=divd.dig.size()-1;i>=0;i--){
			crt.dig.insert(crt.dig.begin(),divd.dig[i]);
			crt.trim();
			int x=0,l=0,r=9;
			while(l<=r){
				int mid=(l+r)/2;
				if(divs*gjd(mid)<=crt){
					x=mid;
					l=mid+1;
				}else r=mid-1;
			}
			res.dig[i]=x;
			crt=crt-divs*gjd(x);
		}
		res.trim();
		return res;
	}
	gjd operator%(const gjd& oth)const{return *this-(*this/oth)*oth;}
	gjd& operator+=(const gjd& oth){*this=*this+oth;return *this;}
	gjd& operator-=(const gjd& oth){*this=*this-oth;return *this;}
	gjd& operator*=(const gjd& oth){*this=*this*oth;return *this;}
	gjd& operator/=(const gjd& oth){*this=*this/oth;return *this;}
	gjd& operator%=(const gjd& oth){*this=*this%oth;return *this;}
	friend istream& operator>>(istream& is,gjd& num){
		string s;
		is>>s;
		num=gjd(s);
		return is;
	}
	friend ostream& operator<<(ostream& os,const gjd& num){
		os<<num.toString();
		return os;
	}
};
int main(){
	string s1,s2;
	cin>>s1>>s2;
	gjd a(s1),b(s2);
	cout<<a+b;
	return 0;
}