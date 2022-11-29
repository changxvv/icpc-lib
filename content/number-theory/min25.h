/**
 * Author: changxv
 * Date: 2021-08-14
 * License: CC0
 * Source: myself
 * Description: min25.
 * Time: O(n)
 * Status: Tested
 */

#pragma once

const int maxn=1e5+3,md=1e9+7,inv2=md+1>>1;

ll n;
int Sq,m,cnt;
int pr[maxn],h0[maxn<<1],h1[maxn<<1];
ll w[maxn<<1];

inline int Id(ll x){return x<=Sq?x:m-n/x+1;}
inline int inc(int x,int y){return x+y>=md?x+y-md:x+y;}
inline int dec(int x,int y){return x-y<0?x-y+md:x-y;}
inline int mul(int x,int y){return (ll)x*y%md;}
inline void cinc(int&x,int y){x=inc(x,y);}
inline void cdec(int&x,int y){x=dec(x,y);}

int Sum(ll x,int i){
	int ans=dec(h0[Id(x)],h0[pr[i]]);
	for(int j=i+1;(ll)pr[j]*pr[j]<=x;++j){
		ll y=x;
		for(int e=1;(y/=pr[j])>=pr[j];++e){
			cinc(ans,inc(pr[j]^(e+1),mul(pr[j]^e,Sum(y,j))));
		}
	}
	return ans;
}

int main(){
	cin>>n;
	Sq=sqrt(n);

	for(ll i=1;i<=n;i=w[m]+1){
		w[++m]=n/(n/i);
		int x=w[m]%md;
		h0[m]=dec(x,1);
		h1[m]=dec(mul(mul(inc(x,1),x),inv2),1);
	}

	For(i,2,Sq){
		if(h0[i]==h0[i-1])continue;
		pr[++cnt]=i;
		ll sqr=(ll)i*i;
		for(int j=m;w[j]>=sqr;--j){
			int id=Id(w[j]/i);
			cdec(h0[j],dec(h0[id],h0[i-1]));
			cdec(h1[j],mul(i,dec(h1[id],h1[i-1])));
		}
	}
	For(i,2,m)h0[i]=inc(dec(h1[i],h0[i]),2);

	pr[0]=1,pr[cnt+1]=Sq+1;
	cout<<inc(Sum(n,0),1)<<'\n';
	Rep(i,*pr,1){ //iteration
		ll sqr=(ll)pr[i]*pr[i];
		for(int j=m;w[j]>=sqr;--j){
			ll y=w[j];
			for(int e=1;(y/=pr[i])>=pr[i];++e){
				cinc(g[j],inc(pr[i]^(e+1),mul(pr[i]^e,dec(g[Id(y)],g[pr[i]]))));
			}
		}
	}
}
