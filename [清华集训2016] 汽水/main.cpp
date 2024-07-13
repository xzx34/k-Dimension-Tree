//这是一份多年前的考场代码
//参考https://www.luogu.com.cn/article/5yejxp1x 
 
#include <bits/stdc++.h>
#define re register int 
#define FOR(i,a,b) for(re i=a;i<=b;i++)
#define ROF(i,a,b) for(re i=a;i>=b;i--)
#define db long double   
#define il inline
#define int long long 
using namespace std;
il void gmx(db &x,db y){x<y&&(x=y);}
il void gmn(db &x,db y){x>y&&(x=y);}
il void gmx(int &x,int y){x<y&&(x=y);}
il void gmn(int &x,int y){x>y&&(x=y);}
il int read(){
	char c=getchar();int z=0,f=1;
	while(c!='-'&&(c>'9'||c<'0')) c=getchar();
	if(c=='-') f=-1,c=getchar();
	while(c>='0'&&c<='9') z=z*10+c-'0',c=getchar();
	return z*f;
}
const int N=1e5+6,inf=1e15;
int n,k,to[N<<1],nex[N<<1],cnt=1,head[N];
int w[N<<1];
il void add(int x,int y,int z){
	to[++cnt]=y;nex[cnt]=head[x];w[cnt]=z;head[x]=cnt;
	to[++cnt]=x;nex[cnt]=head[y];w[cnt]=z;head[y]=cnt;
}
db ans=inf;
namespace KDT{
	const double alph=0.7;
	int wd,tot,num;
	struct P{
		int x[2];
		il void clear(){x[1]=x[0]=0;}
	}a[N],mx[N],mn[N],tag[N],b[N];
	int ch[N][2],siz[N];
	#define lc ch[o][0]
	#define rc ch[o][1]
	#define mid (l+r>>1)
	vector<int> rub;
	il void del(int o){rub.push_back(o);lc=rc=siz[o]=0;a[o].clear();mn[o].clear();mx[o].clear();tag[o].clear();}
	bool operator < (P x,P y){return x.x[wd]<y.x[wd];}
	il void upd(int o){
		mn[o]=mx[o]=a[o];
		siz[o]=siz[lc]+siz[rc]+1;
		FOR(i,0,1){
			if(lc) gmx(mx[o].x[i],mx[lc].x[i]),gmn(mn[o].x[i],mn[lc].x[i]);
			if(rc) gmx(mx[o].x[i],mx[rc].x[i]),gmn(mn[o].x[i],mn[rc].x[i]);
		}
	}
	il void psd(int o,int d=0){
		FOR(i,0,1) if(d=tag[o].x[i]){
			if(lc) tag[lc].x[i]+=d,a[lc].x[i]+=d,mx[lc].x[i]+=d,mn[lc].x[i]+=d;
			if(rc) tag[rc].x[i]+=d,a[rc].x[i]+=d,mx[rc].x[i]+=d,mn[rc].x[i]+=d;
			tag[o].x[i]=0;
		}
	}
	il void jia(int &o){
		if(rub.empty()) o=++tot;
		else o=rub.back(),rub.pop_back();
	}
	il int build(int l,int r,int dep){
		if(l>r) return 0;
		int o;jia(o);
		wd=dep&1;
		nth_element(b+l,b+mid,b+r+1);
		a[o]=b[mid];
		lc=build(l,mid-1,dep+1);rc=build(mid+1,r,dep+1);
		return upd(o),o;
	}
	il void pia(int o){
		psd(o);
		if(lc) pia(lc);
		if(rc) pia(rc);
		b[++num]=a[o];del(o);
	}
	il void check(int &o,int dep){if(siz[o]*alph<siz[lc]||siz[o]*alph<siz[rc]) num=0,pia(o),o=build(1,num,dep);}
	il void ins(int &o,int dep,P x){
		if(!o) return jia(o),a[o]=mx[o]=mn[o]=x,siz[o]=1,void();
		psd(o);
		int son=x.x[dep&1]>a[o].x[dep&1];
		ins(ch[o][son],dep+1,x);
		upd(o);check(o,dep);
	}
	vector<int> vec;
	il void getp(int o){ 
		if(!o) return ;
		psd(o),getp(lc),getp(rc),vec.push_back(o);
	}
	il db getans(P x,P y){return fabs(1.0*(x.x[1]+y.x[1])/(x.x[0]+y.x[0]));}
	il void ask(int o,P y){
		if(o) gmn(ans,getans(a[o],y));
		if(!lc&&!rc) return ;
		psd(o);
		db a1=inf,a2=inf;
		if(lc){
			if(mn[lc].x[1]+y.x[1]<=0&&0<=mx[lc].x[1]+y.x[1]) ask(lc,y);
			else a1=min(getans(y,mx[lc]),getans(y,(P){mx[lc].x[0],mn[lc].x[1]}));
		}
		if(rc){
			if(mn[rc].x[1]+y.x[1]<=0&&0<=mx[rc].x[1]+y.x[1]) ask(rc,y);
			else a2=min(getans(y,mx[rc]),getans(y,(P){mx[rc].x[0],mn[rc].x[1]}));
		}
		if(a1<a2) {
			if(a1<ans) ask(lc,y);
			if(a2<ans) ask(rc,y);
		}
		else {
			if(a2<ans) ask(rc,y);
			if(a1<ans) ask(lc,y);
		}
	}
};
using namespace KDT;
int rt[N];
il void dp(int x,int fa){
	for(re i=head[x];i;i=nex[i]){
		if(to[i]==fa) continue;
		dp(to[i],x);
		int o=rt[to[i]];
		tag[o].x[0]+=1,mn[o].x[0]+=1,mx[o].x[0]+=1,a[o].x[0]+=1;
		tag[o].x[1]+=w[i],mn[o].x[1]+=w[i],mx[o].x[1]+=w[i],a[o].x[1]+=w[i];
		ask(o,(P){0,0});
		if(siz[o]>siz[rt[x]]) swap(o,rt[x]);
		getp(o);
		for(auto y:vec) ask(rt[x],a[y]);
		for(auto y:vec) ins(rt[x],1,a[y]); 
		for(auto y:vec) del(y);
		vec.clear();
	}
	if(x!=1) ins(rt[x],1,(P){0,0});
}
signed main (){
	n=read();k=read();
	FOR(i,1,n-1){
		int x=read(),y=read(),z=read()-k;
		add(x,y,z);
	}
	dp(1,0);
	ask(rt[1],(P){0,0});
	cout<<(long long)ans;
	return 0;
}
