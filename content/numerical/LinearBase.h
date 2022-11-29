/**
 * Author: Changxv
 * Date: 2021-08-19
 * License: CC0
 * Description: LinearBase.
 * Time: O(\log N)
 * Status: Check Library
 */

#pragma once

int n,m;
ll lb[63],bin[63];
vector<ll> ve;
vector<int> bit;

void Ins(ll x){
	for (int i = 62; ~i; --i) {
		if(!x)return ;
		if(~x&bin[i])continue;
		if(lb[i])x^=lb[i];
		else{
			for (int j = 0; j < i; ++j) if(x&bin[j])x^=lb[j];
			for (int j = i + 1; j < 63; ++j) if(lb[j]&bin[i])lb[j]^=x;
			lb[i]=x;
			return ;
		}
	}
}

ll Max(){
	ll ans=0;
	for (int i = 0; i < 63; ++i) if(lb[i])ans^=lb[i];
	return ans;
}

ll Kth(ll K){
	if((int)ve.size()!=n)--K;
	if(K>bin[ve.size()]-1)return -1;
	ll ans=0;
	for (int i = 0; i < sz(ve); ++i) if(K&bin[i])ans^=ve[i];
	return ans;
}

ll Rank(ll x){
	ll ans=0;
	for (int i = 0; i < sz(bit); ++i) if(x&bin[bit[i]])ans|=bin[i];
	return ans;
}
 
void Merge(ll b[]){
	for (int i = 0; i < 63; ++i) Ins(b[i]);
}

void solve() {
	bin[0]=1;
	for (int i = 0; i < 63; ++i) bin[i]=bin[i-1]<<1ll;
	// insert(xi)
	for (int i = 0; i < 63; ++i) 
		if(lb[i])ve.push_back(lb[i]),bit.push_back(i);
}
