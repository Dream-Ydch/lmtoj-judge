#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned int
#define N 1048576
int memory[N],pos;
string code[N]={

};
string readStr(int x,int y)	// 从 code[x][y] 开始读取一个字符串, 读到空格为止 
{
	pos=y;
	string ret="";
	int len=code[x].length();
	while(pos<len && code[x][pos]==' ')
	{
		++pos;
	}
	while(pos<len && code[x][pos]!=' ')
	{
		ret=ret+code[x][pos++];
	}
	return ret;
}
int readInt(int x,int y)	// 从 code[x][y] 开始读取一个整数, 读到非数字为止 
{
	pos=y;
	int ret=0, len=code[x].length();
	bool f=0;
	while(pos<len && !isdigit(code[x][pos]))
	{
		if(code[x][pos]=='-')
		{
			f=1;
		}
		++pos;
	}
	while(pos<len && isdigit(code[x][pos]))
	{
		ret=(ret<<3)+(ret<<1)+(code[x][pos++]^48);
	}
	return f?-ret:ret;
}
signed main()
{
	for(int i=0;;i=(i+1)%N)
	{
		string op=readStr(i,0);
		if(op=="input")
		{
			int x=readInt(i,pos);
			cin>>memory[x];
		}
		else if(op=="output")
		{
			string mode=readStr(i,pos);
			if(mode=="int")
			{
				int x=readInt(i,pos);
				cout<<memory[x];
			}
			else if(mode=="char")
			{
				int x=readInt(i,pos);
				cout<<char(memory[x]%128);
			}
			else
			{
				cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
				break;
			}
		}
		else if(op=="write")
		{
			int x=readInt(i,pos), y=readInt(i,pos);
			memory[x]=y;
		}
		else if(op=="copy")
		{
			int x=readInt(i,pos), y=readInt(i,pos);
			memory[y]=memory[x];
		}
		else if(op=="calc")	// and or not xor add sub mul div mod
		{
			string mode=readStr(i,pos);
			int x=readInt(i,pos), y=readInt(i,pos), z=(mode=="not" ? 0 : readInt(i,pos));
			x=memory[x], y=memory[y];
			if(mode=="and")
			{
				memory[z]=x&y;
			}
			else if(mode=="or")
			{
				memory[z]=x|y;
			}
			else if(mode=="not")
			{
				memory[y]=~x;
			}
			else if(mode=="xor")
			{
				memory[z]=x^y;
			}
			else if(mode=="add")
			{
				memory[z]=x+y;
			}
			else if(mode=="sub")
			{
				memory[z]=x-y;
			}
			else if(mode=="mul")
			{
				memory[z]=x*y;
			}
			else if(mode=="div")
			{
				if(y==0)
				{
					cout<<"\n\nError: Division by Zero\n\n";
					break;
				}
				memory[z]=x/y;
			}
			else if(mode=="mod")
			{
				memory[z]=x%y;
			}
			else
			{
				cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
				break;
			}
		}
		else if(op=="goto")
		{
			int x=readInt(i,pos);
			i=x-1;
		}
		else if(op=="if")	// < > == <= >= !=
		{
			string mode=readStr(i,pos);
			int x=readInt(i,pos), y=readInt(i,pos), z=readInt(i,pos);
			x=memory[x], y=memory[y];
			if(mode=="<")
			{
				if(x<y)
				{
					i=z-1;
				}
			}
			else if(mode==">")
			{
				if(x>y)
				{
					i=z-1;
				}
			}
			else if(mode=="==")
			{
				if(x==y)
				{
					i=z-1;
				}
			}
			else if(mode=="<=")
			{
				if(x<=y)
				{
					i=z-1;
				}
			}
			else if(mode==">=")
			{
				if(x>=y)
				{
					i=z-1;
				}
			}
			else if(mode=="!=")
			{
				if(x!=y)
				{
					i=z-1;
				}
			}
			else
			{
				cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
				break;
			}
		}
		else if(op=="++")
		{
			int x=readInt(i,pos);
			memory[x]++;
		}
		else if(op=="--")
		{
			int x=readInt(i,pos);
			memory[x]--;
		}
		else if(op=="exit")
		{
			break;
		}
		else
		{
			cout<<"\n\nError: Invalid Code at i = "<<i<<"\n\n";
			break;
		}
	}
	return 0;
}