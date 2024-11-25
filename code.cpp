#include<bits/stdc++.h>
using namespace std;
const long long INF=1e9;
inline int IntLen(long long p)
{
	int l=1;
	if(p<0)
	{
		p*=-1;
		++l;
	}
	p/=10;
	while(p)
	{
		++l;
		p/=10;
	}
	return l;
}
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
	inline int Len()
	{
		if(b==1)
		{
			return IntLen(a);
		}
		return IntLen(a)+IntLen(b)+1;
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
const Number ZERO(0);
class Simplex
{
	int m;
	int n;
	int rule;
	string z;
	vector<string>nam;
	vector<int>base;
	vector<vector<Number>>a;
	vector<Number>b;
	set<vector<int>>se;
	inline bool Check()
	{
		for(auto p:a[m])
		{
			if(p>ZERO)
			{
				return 0;
			}
		}
		return 1;
	}
	inline void Space(const int len,const char ch=' ')
	{
		for(int i=0;i<len;++i)
		{
			cout<<ch;
		}
	}
	inline bool Find(const int i)
	{
		for(int j=0;j<m;++j)
		{
			if(a[j][i]>ZERO)
			{
				return 1;
			}
		}
		return 0;
	}
public:
	inline void Print()
	{
		vector<int>len(n+2);
		for(auto i:base)
		{
			len[0]=max(len[0],(int)nam[i].size());
		}
		for(int i=0;i<n;++i)
		{
			len[i+1]=nam[i].size();
			for(int j=0;j<=m;++j)
			{
				len[i+1]=max(len[i+1],a[j][i].Len());
			}
		}
		len.back()=3;
		for(int j=0;j<=m;++j)
		{
			len.back()=max(len.back(),b[j].Len());
		}
		Space(len[0]);
		for(int i=0;i<n;++i)
		{
			cout<<"|";
			cout<<nam[i];
			Space(len[i+1]-nam[i].size());
		}
		cout<<"|RHS"<<endl;
		for(int i=0;i<=m;++i)
		{
			Space(len[0],'-');
			for(int j=1;j<len.size();++j)
			{
				cout<<"+";
				Space(len[j],'-');
			}
			cout<<endl;
			if(i<m)
			{
				cout<<nam[base[i]];
				Space(len[0]-nam[base[i]].size());
			}
			else
			{
				cout<<z;
				Space(len[0]-1);
			}
			for(int j=0;j<n;++j)
			{
				cout<<"|";
				a[i][j].W();
				Space(len[j+1]-a[i][j].Len());
			}
			cout<<"|";
			b[i].W();
			cout<<endl;
		}
		cout<<endl;
	}
	inline void Calc()
	{
		while(!Check())
		{
			int index=-1;
			for(int i=0;i<n;++i)
			{
				if(rule==0)
				{
					if(a[m][i]>0&&(index==-1||a[m][index]<a[m][i]))
					{
						if(Find(i))
						{
							index=i;
						}
					}
				}
				if(rule==1)
				{
					if(a[m][i]>0&&index==-1)
					{
						if(Find(i))
						{
							index=i;
						}
					}
				}
			}
			if(index==-1)
			{
				break;
			}
			int index2=-1;
			Number mi(INF);
			for(int i=0;i<m;++i)
			{
				if(a[i][index]>ZERO)
				{
					Number aa=b[i]/a[i][index];
					if(aa<mi)
					{
						index2=i;
						mi=aa;
					}
				}
			}
			if(index2==-1)
			{
				puts("min is -infty");
				break;
			}
			cout<<nam[index]<<"->"<<nam[base[index2]]<<endl;
			base[index2]=index;
			Number di=a[index2][index];
			if(se.find(base)!=se.end())
			{
				puts("... ...");
				break;
			}
			se.insert(base);
			for(int i=0;i<n;++i)
			{
				a[index2][i]=a[index2][i]/di;
			}
			b[index2]=b[index2]/di;
			for(int i=0;i<=m;++i)
			{
				if(i==index2)
				{
					continue;
				}
				Number cut=a[i][index];
				for(int j=0;j<n;++j)
				{
					a[i][j]=a[i][j]-cut*a[index2][j];
				}
				b[i]=b[i]-cut*b[index2];
			}
			Print();
		}
		if(Check())
		{
			cout<<"min:";
			b[m].W();
			cout<<endl;
			vector<Number>answer(n);
			for(int i=0;i<m;++i)
			{
				answer[base[i]]=b[i];
			}
			for(int i=0;i<n;++i)
			{
				cout<<nam[i]<<"=";
				answer[i].W();
				cout<<endl;
			}
		}
	}
	inline void Init()
	{
		vector<bool>vis(n);
		for(int i=0;i<m;++i)
		{
			for(int k=m;k<=m;++k)
			{
				if(i==k)
				{
					continue;
				}
				Number cut=a[k][base[i]];
				for(int j=0;j<n;++j)
				{
					a[k][j]=a[k][j]-cut*a[i][j];
				}
				b[k]=b[k]-cut*b[i];
			}
		}
	}
	inline void Test()
	{
		cin>>rule;
		cin>>n>>m;
		nam.resize(n+m);
		a.resize(m+1);
		b.resize(m+1);
		base.resize(m+1);
		for(int i=0;i<n;++i)
		{
			cin>>nam[i];
		}
		n+=m;
		for(int i=n-m;i<n;++i)
		{
			nam[i]="add"+to_string(i-(n-m)+1);
		}
		for(int i=0;i<m;++i)
		{
			a[i].resize(n);
			for(int j=0;j<n-m;++j)
			{
				cin>>a[i][j].a>>a[i][j].b;
				a[i][j]();
			}
			a[i][n-m+i]=Number(1);
			cin>>b[i].a>>b[i].b;
			base[i]=n-m+i;
			b[i]();
			if(b[i]<ZERO)
			{
				for(int j=0;j<n-m;++j)
				{
					a[i][j]=a[i][j]*Number(-1);
				}
				b[i]=b[i]*Number(-1);
			}
		}
		a[m].resize(n);
		for(int i=n-m;i<n;++i)
		{
			a[m][i]=Number(-1);
		}
		z="g";
		Print();
		Init();
		Print();
		Calc();
		if(b[m]>ZERO)
		{
			puts("No solution.");
			return;
		}
		n-=m;
		for(int i=0;i<m;++i)
		{
			a[i].resize(n);
		}
		int mm=0;
		for(int i=0;i<m;++i)
		{
			if(base[i]<n)
			{
				a[mm]=a[i];
				b[mm]=b[i];
				base[mm]=base[i];
				++mm;
			}
		}
		m=mm;
		a.resize(m+1);
		a[m].resize(n);
		for(int j=0;j<n;++j)
		{
			cin>>a[m][j].a>>a[m][j].b;
			a[m][j].a*=-1;
			a[m][j]();
		}
		b[m]=ZERO;
		z="z";
		Init();
		Print();
		Calc();
	}
}a;
int main()
{
	// freopen("input_.txt","r",stdin);
	// freopen("output.txt","w",stdout);
	a.Test();
	return 0;
}
