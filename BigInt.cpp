/*
	固定長多倍長
	0 <= x < 10^N_

	一桁10^6 (掛け算した時に繰り上がりを後回しにしてもllに収まるように)

	add / compare : O(N)
	prod : O(AB) (桁数で抑えている)

	TODO :
		引き算/負数
		FFT掛け算
		割り算
		可変長
		base 2冪?

*/

typedef long long ll;
constexpr ll TEN(int n) {return (n==0)?1:10*TEN(n-1);};

template<int N_>
struct BigInt{
	using ll = long long;

	constexpr static int B = TEN(6);

	constexpr static int N = (N_+5)/6;
	array<ll,N> v;

	BigInt(){
		fill(all(v),0);
	}
	BigInt(ll x){
		fill(all(v),0);
		for(int i=0;x>0;i++){
			assert(i<N);
			v[i] = x%B;
			x /= B;
		}
	}
	BigInt(array<ll,N> v):v(v){}

	BigInt(string s){
		fill(all(v),0);
		int L = s.size();
		rep(i,L/6){
			v[i] = stoi(s.substr(L-(i+1)*6,6));
		}
		if(L%6){
			v[L/6] = stoi(s.substr(0,L%6));
		}
	}

	int sz() const {
		for(int i = N-1;i>=0;i--){
			if(v[i]!=0) return i+1;
		}
		return 0;
	}

	explicit operator bool() const {
		rep(i,N) if(v[i]!=0) return true;
		return false;
	}

	BigInt& operator+=(const BigInt& r){
		rep(i,N){
			v[i] += r.v[i];
			if(v[i] >= B){
				v[i] -= B;
				v[i+1]++;
			}
		}
		return *this;
	}
	BigInt operator+(const BigInt& r) const {return BigInt(*this)+=r;}

	BigInt operator*(const BigInt& r) const {
		array<ll,N> res;
		fill(all(res),0);

		int X = sz();
		int Y = r.sz();
		assert(X+Y-2 < N);

		rep(i,X){
			rep(j,Y){
				res[i+j] += v[i] * r.v[j];
			}
		}
		rep(i,N){
			res[i+1] += res[i]/B;
			res[i] %= B;
		}
		return BigInt(res);
	}
	BigInt& operator*=(const BigInt& r){ return *this=*this*r;}

	bool operator==(const BigInt& r) const { return v==r.v;}
	bool operator!=(const BigInt& r) const { return v!=r.v;}
	bool operator<(const BigInt& r) const {
		for(int i=N-1;i>=0;i--) if(v[i] != r.v[i]) return v[i] < r.v[i];
		return 0;
	}
	bool operator>(const BigInt& r) const {
		for(int i=N-1;i>=0;i--) if(v[i] != r.v[i]) return v[i] > r.v[i];
		return 0;
	}
	bool operator<=(const BigInt& r) const {
		for(int i=N-1;i>=0;i--) if(v[i] != r.v[i]) return v[i] < r.v[i];
		return 1;
	}
	bool operator>=(const BigInt& r) const {
		for(int i=N-1;i>=0;i--) if(v[i] != r.v[i]) return v[i] > r.v[i];
		return 1;
	}


	string to_str() const {
		string s;
		bool is = 0;
		for(int i=N-1;i>=0;i--){
			if(!is && v[i]==0) continue;
			else if(!is){
				is = 1;
				s += to_string(v[i]);
			}else{
				string t = to_string(v[i]);
				s += string(6-(int)t.size(),'0') + t;
			}
		}
		if(s=="") s = "0";
		return s;
	}
	
	friend istream& operator>>(istream &i,BigInt& x){
		string s;
		i>>s;
		x = BigInt(s);
		return i;
	}
	friend ostream& operator<<(ostream &o,const BigInt& x){
		return o<<x.to_str();
	}

};

using Int = BigInt<1010>;
