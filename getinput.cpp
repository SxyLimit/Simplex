#include<bits/stdc++.h>
using namespace std;
class Number
{
	long long Gcd(const long long a,const long long b)
	{
		return b?Gcd(b,a%b):a;
	}
public:
	long long a,b;
	inline Number():a(0),b(1)
	{

	}
	inline Number(const long long a_,const long long b_=1)
	{
		a=a_/Gcd(abs(a_),abs(b_));
		b=b_/Gcd(abs(a_),abs(b_));
		if(b<0)
		{
			a*=-1;
			b*=-1;
		}
	}
	inline Number operator +(const Number &p)const
	{
		return Number(a*p.b+b*p.a,b*p.b);
	}
	inline Number operator -(const Number &p)const
	{
		return Number(a*p.b-b*p.a,b*p.b);
	}
	inline Number operator *(const Number &p)const
	{
		return Number(a*p.a,b*p.b);
	}
	inline Number operator /(const Number &p)const
	{
		return Number(a*p.b,b*p.a);
	}
	inline bool operator <(const Number &p)const
	{
		return a*p.b<p.a*b;
	}
	inline bool operator >(const Number &p)const
	{
		return a*p.b>p.a*b;
	}
	inline void operator ()()
	{
		long long g=Gcd(abs(a),abs(b));
		a/=g;
		b/=g;
		if(b<0)
		{
			a*=-1;
			b*=-1;
		}
	}
	inline void W()
	{
		if(b==1)
		{
			cout<<a;
		}
		else
		{
			cout<<a<<"/"<<b;
		}
	}
};
int n;
vector<string>a;
vector<string>nam;
set<string>se;
vector<map<string,Number>>p;
inline Number Get1Number(int &now,const string &s)
{
	while(now<s.size()&&(s[now]<'0'||s[now]>'9'))
	{
		++now;
	}
	Number a(0);
	while(now<s.size()&&'0'<=s[now]&&s[now]<='9')
	{
		a=a*Number(10)+Number(s[now]-'0');
		++now;
	}
	if(now==s.size())
	{
		return a;
	}
	if(s[now]=='.')
	{
		++now;
		Number b(1);
		while('0'<=s[now]&&s[now]<='9')
		{
			b=b*Number(10);
			a=a+Number(s[now]-'0')/b;
			++now;
		}
	}
	return a;
}
inline Number GetNumber(int &now,const string &s)
{
	int f=1;
	while(now<s.size()&&(s[now]<'0'||s[now]>'9'))
	{
		if(s[now]=='-')
		{
			f*=-1;
		}
		if(s[now]=='_'||('a'<=s[now]&&s[now]<='z')||('A'<=s[now]&&s[now]<='Z'))
		{
			return Number(f);
		}
		++now;
	}
	Number a=Number(f)*Get1Number(now,s);
	while(now<s.size()&&s[now]==' ')
	{
		++now;
	}
	if(now==s.size())
	{
		return a;
	}
	if(s[now]=='/')
	{
		Number b=Get1Number(now,s);
		a=a/b;
	}
	return a;
}
inline string GetName(int &now,const string &s)
{
	while(now<s.size()&&s[now]!='_'&&(s[now]<'a'||s[now]>'z')&&(s[now]<'A'||s[now]>'Z'))
	{
		++now;
	}
	string result="";
	while(now<s.size()&&s[now]=='_'||('a'<=s[now]&&s[now]<='z')||('A'<=s[now]&&s[now]<='Z')||('0'<=s[now]&&s[now]<='9'))
	{
		result+=s[now];
		++now;
	}
	return result;
}
inline void Init(const string &a,map<string,Number> &p,const int id)
{
	int now=0;
	p.clear();
	int opt=-1;
	while(now<a.size())
	{
		while(now<a.size()&&(a[now]==' '||a[now]=='<'||a[now]=='>'||a[now]=='\n'||a[now]=='\r'))
		{
			++now;
		}
		if(now==a.size())
		{
			break;
		}
		if(a[now]=='=')
		{
			opt=0;
			if(a[now-1]=='<')
			{
				opt=1;
			}
			if(a[now-1]=='>')
			{
				opt=2;
			}
			break;
		}
		Number num=GetNumber(now,a);
		string na=GetName(now,a);
		if(p.count(na))
		{
			p[na]=p[na]+num;
		}
		else
		{
			se.insert(na);
			p[na]=num;
		}
	}
	if(opt==-1)
	{
		return;
	}
	Number num=GetNumber(now,a);
	p["1_"]=num;
	if(opt==0)
	{
		return;
	}
	string na="y"+to_string(id);
	se.insert(na);
	if(opt==1)
	{
		p[na]=Number(1);
	}
	else
	{
		p[na]=Number(-1);
	}
}
map<string,int>toint;
vector<vector<Number>>aa;
string rule;
int main()
{
	// freopen("input.txt","r",stdin);
	// freopen("input_.txt","w",stdout);
	cin>>n;
	a.resize(n+1);
	p.resize(n+1);
	getline(cin,a[0]);
	for(int i=0;i<=n;++i)
	{
		getline(cin,a[i]);
		Init(a[i],p[i],i);
	}
	getline(cin,rule);
	if(rule=="Dantzig")
	{
		cout<<0<<endl;
	}
	else
	{
		if(rule=="Bland")
		{
			cout<<1<<endl;
		}
		else
		{
			cout<<0<<endl;
		}
	}
	int cnt=0;
	for(auto s:se)
	{
		toint[s]=cnt++;
	}
	toint["1_"]=cnt;
	aa.resize(n+1);
	cout<<cnt<<" "<<n<<endl;
	for(auto s:se)
	{
		cout<<s<<endl;
	}
	for(int i=0;i<=n;++i)
	{
		aa[i].resize(cnt+1);
		for(auto q:p[i])
		{
			aa[i][toint[q.first]]=q.second;
		}
		for(int j=0;j<cnt+(i<n);++j)
		{
			cout<<aa[i][j].a<<" "<<aa[i][j].b<<"  ";
		}
		cout<<endl;
	}
	return 0;
}
