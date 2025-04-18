template<typename T,int B=sizeof(T)*8>
class DynamicWaveletMatrix{
  using U=typename make_unsigned<T>::type;
  static U encode(T v){ return U(v) ^ (U(1)<<(B-1)); }
  static T decode(U u){ return T(u ^ (U(1)<<(B-1))); }

  struct SeqNode{ SeqNode*l,*r; int pr,sz; T val,sum,mn,mx;
    SeqNode(T v):l(nullptr),r(nullptr),pr(rand()),sz(1),val(v),sum(v),mn(v),mx(v){}
  };
  struct BitNode{ BitNode*l,*r; int pr,sz,ones; bool bit;
    BitNode(bool b):l(nullptr),r(nullptr),pr(rand()),sz(1),ones(b),bit(b){}
  };
  SeqNode* seqRoot;
  array<BitNode*,B> bitRoots;

  static int sz(SeqNode* x){ return x?x->sz:0; }
  static T sum(SeqNode* x){ return x?x->sum:0; }
  static T mn(SeqNode* x){ return x?x->mn:numeric_limits<T>::max(); }
  static T mx(SeqNode* x){ return x?x->mx:numeric_limits<T>::lowest(); }
  static SeqNode* pull(SeqNode* x){ x->sz=1+sz(x->l)+sz(x->r);
    x->sum=x->val+sum(x->l)+sum(x->r);
    x->mn=min(x->val,min(mn(x->l),mn(x->r)));
    x->mx=max(x->val,max(mx(x->l),mx(x->r)));
    return x;
  }
  static void split(SeqNode* t,int k,SeqNode*& a,SeqNode*& b){
    if(!t){a=b=nullptr;return;}
    if(sz(t->l)>=k) split(t->l,k,a,t->l), b=pull(t);
    else split(t->r,k-sz(t->l)-1,t->r,b), a=pull(t);
  }
  static SeqNode* merge(SeqNode* a,SeqNode* b){
    if(!a||!b) return a?a:b;
    if(a->pr<b->pr) a->r=merge(a->r,b), pull(a);
    else b->l=merge(a,b->l), pull(b);
    return a->pr<b->pr?a:b;
  }
  static int sz(BitNode* x){ return x?x->sz:0; }
  static int ones(BitNode* x){ return x?x->ones:0; }
  static BitNode* pull(BitNode* x){ x->sz=1+sz(x->l)+sz(x->r);
    x->ones=x->bit+ones(x->l)+ones(x->r); return x;
  }
  static void split(BitNode* t,int k,BitNode*& a,BitNode*& b){
    if(!t){a=b=nullptr;return;}
    if(sz(t->l)>=k) split(t->l,k,a,t->l), b=pull(t);
    else split(t->r,k-sz(t->l)-1,t->r,b), a=pull(t);
  }
  static BitNode* merge(BitNode* a,BitNode* b){
    if(!a||!b) return a?a:b;
    if(a->pr<b->pr) a->r=merge(a->r,b), pull(a);
    else b->l=merge(a,b->l), pull(b);
    return a->pr<b->pr?a:b;
  }
  static int rank1(BitNode* t,int k){ if(!t||k<=0) return 0;
    if(k>=sz(t)) return ones(t);
    int ls=sz(t->l);
    if(k<=ls) return rank1(t->l,k);
    return ones(t->l)+(t->bit?1:0)+rank1(t->r,k-ls-1);
  }
  static bool at(BitNode* t,int k){ while(t){int ls=sz(t->l);
      if(k<ls) t=t->l;
      else if(k==ls) return t->bit;
      else k-=ls+1, t=t->r;
    }
    return false;
  }
  static T seqAt(SeqNode* t,int k){ int ls=sz(t->l);
    if(k<ls) return seqAt(t->l,k);
    if(k==ls) return t->val;
    return seqAt(t->r,k-ls-1);
  }
public:
  DynamicWaveletMatrix(){ seqRoot=nullptr; bitRoots.fill(nullptr); srand(0); }
  int size() const{ return sz(seqRoot); }
  T operator[](int idx) const{ if(idx<0||idx>=size()) throw out_of_range("idx"); return seqAt(seqRoot,idx); }
  void insert(int pos,T v){ SeqNode *a,*b; split(seqRoot,pos,a,b);
    seqRoot=merge(merge(a,new SeqNode(v)),b);
    U uv=encode(v);
    for(int d=0;d<B;d++){
      auto &r=bitRoots[d];
      int c1=rank1(r,pos),z0=pos-c1,all0=sz(r)-ones(r);
      bool bit=(uv>>(B-1-d))&1;
      int npos=bit?all0+c1:z0;
      BitNode *L,*R; split(r,pos,L,R);
      r=merge(merge(L,new BitNode(bit)),R);
      pos=npos;
    }
  }
  void erase(int pos){ SeqNode *a,*m,*b; split(seqRoot,pos,a,m);
    split(m,1,m,b); delete m; seqRoot=merge(a,b);
    for(int d=0;d<B;d++){
      auto &r=bitRoots[d];
      int c1=rank1(r,pos),z0=pos-c1,all0=sz(r)-ones(r);
      bool bit=at(r,pos);
      int npos=bit?all0+c1:z0;
      BitNode *L,*R,*M; split(r,pos,L,R);
      split(R,1,M,R); delete M; r=merge(L,R);
      pos=npos;
    }
  }
  void updateValue(int p,T v){ erase(p); insert(p,v); }
  T rangeSum(int l,int r){ SeqNode *a,*m,*b; split(seqRoot,l,a,m);
    split(m,r-l,m,b);
    T res=sum(m);
    seqRoot=merge(a,merge(m,b));
    return res;
  }
  T rangeMin(int l,int r){ SeqNode *a,*m,*b; split(seqRoot,l,a,m); split(m,r-l,m,b);
    T res=mn(m); seqRoot=merge(a,merge(m,b)); return res;
  }
  T rangeMax(int l,int r){ SeqNode *a,*m,*b; split(seqRoot,l,a,m); split(m,r-l,m,b);
    T res=mx(m); seqRoot=merge(a,merge(m,b)); return res;
  }
  int rangeLessEqual(int l,int r,T v){ U kv=encode(v);
    if(kv==numeric_limits<U>::max()) return r-l; kv++;
    int cnt=0;
    for(int d=0;d<B;d++){
      auto *root=bitRoots[d];
      int c1l=rank1(root,l),c1r=rank1(root,r);
      int z0l=l-c1l,z0r=r-c1r;
      bool bit=(kv>>(B-1-d))&1;
      if(bit){ cnt+=z0r-z0l; int all0=sz(root)-ones(root);
        l=all0+c1l; r=all0+c1r;
      } else { l=z0l; r=z0r; }
    }
    return cnt;
  }
  T kthSmallest(int l,int r,int k){ U res=0;
    for(int d=0;d<B;d++){
      auto *root=bitRoots[d];
      int c1l=rank1(root,l),c1r=rank1(root,r);
      int z0l=l-c1l,z0r=r-c1r;
      int tot0=z0r-z0l;
      if(k<=tot0) { l=z0l; r=z0r; }
      else {
        res|=(U(1)<<(B-1-d)); k-=tot0;
        int all0=sz(root)-ones(root);
        l=all0+c1l; r=all0+c1r;
      }
    }
    return decode(res);
  }
};
