
#include<bits/stdc++.h>
using namespace std;
#define what_is(x) cerr << #x << " is " << x << endl;
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
#define rint1(x) ll  x; cin>>x;
#define rint2(x,y) ll  x,y; cin>>x>>y;
#define read(a,n) ll a[n]; for(int i=0;i<n;i++) cin>>a[i];

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}

template<typename T,typename... Args>
T sum(T a,Args... args) {return a+sum(args...);}

class bigInt{
    public:
        string value;
    bigint(string s){
        bool f=0;
         try{
            cin>>s;
            for(auto x:s){
                if((x>'9' || x<'0') && x!='-'){
                    throw invalid_argument("Please enter only integer values");
                }
            }
        }catch(invalid_argument& e){
            cerr<<e.what()<<endl;
            f=1;
        }
        if(!f)value=s;
    }
    void readVal(){
        cout<<"Enter number:";
        string s;
        try{
            cin>>s;
            for(auto x:s){
                if((x>'9' || x<'0') && x!='-'){
                    throw invalid_argument("Please enter only integer values");
                }
            }
        }catch(invalid_argument& e){
            cerr<<e.what()<<endl;
            this->readVal();
            return;
        }
        value=s;
    }
    bool isZero(string a){
        if(isnegative(a)) a=a.substr(1);
        int n=a.size();
        for(int i=0;i<n;i++){
            if(a[i]!='0' && a[i]!='-') return 0;
        }
        return 1;
    }
    bool isnegative(string s){
        if(s[0]=='-') return 1;
        return 0;
    }
    int comparehelper(string a,string b){
        int p1=a.size();
        int p2=b.size();
        if(p1>p2) return 1;
        if(p1<p2) return -1;
        int i=0,diff=0,bigger=0;
        do{
         diff=a[i]-b[i];
         if(diff>0) bigger=1;
         else if(diff<0) bigger=-1;
         ++i;
        }while(diff==0 && i<p1 && i<p2);
        return bigger;
    }
    int compareBigInt(bigInt B){
        string a=value;
        string b=B.value;
        if(isnegative(a)) a=a.substr(1);
        if(isnegative(b)) b=b.substr(1);
        return comparehelper(a,b);
    }

    string removeZeroes(string res){
        int nonz=0,newlen=0,i=0;
        int len=res.size()-1;
        for(nonz=0;nonz<res.size();nonz++){
            if(res[nonz]!='0') break;
        }
        if(nonz==0) return res;
        res=res.substr(nonz);

        return res;

    }

    string adderBigInt(bigInt B){
        string a=this->value;
        string b=B.value;
        int p1=a.size()-1;
        int p2=b.size()-1;
        int sum=0,carry=0,k=p1+1;
        string c;
        for(int i=0;i<=k;i++) c+='0';
        while(p2>=0){
            sum=a[p1]+b[p2]+carry-'0'-'0';
            c[k]='0'+sum%10;
            carry=sum/10;
            p1--;
            p2--;
            k--;

        }
        while(p1>=0){
            sum=a[p1]+carry-'0';
            c[k]='0'+sum%10;
            carry=sum/10;
            p1--;
            k--;
        }
        if(carry){
            c[k]='0'+carry;
        }
        c=removeZeroes(c);
        return c ;
    }
    string multiplierBigInt(string a,string b){
        if(isnegative(a)) a=a.substr(1);
        if(isnegative(b)) b=b.substr(1);
        int l1=a.size();
        int l2=b.size();
        int sum=0,carry=0;
        int l3=l1+l2;
        int ptr1=0;
        int ptr2;
        int i;
        //error(a,b);
        string res;
        for(int i=0;i<=l3;i++) res+='0';
        for(i=l2-1;i>=0;i--){
            sum=0,carry=0;
            ptr2=l3-ptr1;
            for(int j=l1-1;j>=0;j--){
                sum=(a[j]-'0')*(b[i]-'0')+(res[ptr2]-'0')+carry;
                res[ptr2]='0'+sum%10;
              //  ////error(sum);
                carry=sum/10;
                --ptr2;

            }
            if(carry) res[ptr2]+=carry;
        ++ptr1;
        }
        //cout<<res<<endl;
        res=removeZeroes(res);
        return res;
}
    string subtracterBigInt(bigInt B){
        string b=B.value;
        string a=this->value;
        int p=this->compareBigInt(B);
        if(p<0) {swap(a,b);
        p*=-1;}
        int p1=a.size()-1;
        int p2=b.size()-1;
        string c;
        int taken=0,k=p1;
        for(int i=0;i<=p1;i++) c+='0';
        while(p2>=0){
            int top=a[p1]-'0';
            int bottom=b[p2]-'0';
            if(taken>0){
                if(taken==1){
                    top-=1;
                }else{
                top=9+a[p1]-'0';
                }
                --taken;
            }
            if(top<bottom){
                do{
                    ++taken;
                }while(a[p1-taken]=='0' && (p1-taken)>0);
                top+=10;
            }
            c[k]='0'+top-bottom;
            p1--;
            p2--;
            k--;

        }
        while(p1>=0){
            if(taken>0){
                c[k]=a[p1]-1;
                if(a[p1]=='0')
                    c[k]='9';
                --taken;

            }
                else{
                    c[k]=a[p1];
                }
                --p1;
                --k;

        }
        //cout<<c<<endl;
        c=removeZeroes(c);
        return c;
    }
    string multiplierBigInt(bigInt B){
        string b=B.value;
        string a=this->value;
        if(isnegative(a)) a=a.substr(1);
        if(isnegative(b)) b=b.substr(1);
        int l1=a.size();
        int l2=b.size();
        int sum=0,carry=0;
        int l3=l1+l2;
        int ptr1=0;
        int ptr2;
        int i;
        ////error(a,b);
        string res;
        for(int i=0;i<=l3;i++) res+='0';
        for(i=l2-1;i>=0;i--){
            sum=0,carry=0;
            ptr2=l3-ptr1;
            for(int j=l1-1;j>=0;j--){
                sum=(a[j]-'0')*(b[i]-'0')+(res[ptr2]-'0')+carry;
                res[ptr2]='0'+sum%10;
              //  ////error(sum);
                carry=sum/10;
                --ptr2;

            }
            if(carry) res[ptr2]+=carry;
        ++ptr1;
        }
        //cout<<res<<endl;
        res=removeZeroes(res);
        return res;
    }

    void subtractBigInt(bigInt B){
        string a=this->value;
        string b=B.value;
        bool f1=isnegative(a);
        bool f2=isnegative(b);
        int p=this->compareBigInt(B);
        if(isZero(a) && isZero(b)){
            value="0";
            return ;
        }
        //if(p==0) {value="0"; return;}
        /*
        -+=-(add two)
        +-=+(add two)
        --=-(subtract two)
        ++=-(subtract two)
        */
        if(f1==f2){
            //subtract
            if(f1) a=a.substr(1);
            if(f2) b=b.substr(1);
            bigInt C({a});
            bigInt D({b});
            string res=C.subtracterBigInt(D);
            //error(a,b,res);
            if((!f2 && p<0)||(f1 && p>0)) res='-'+res;
            if(isZero(res)) res="0";
            this->value=res;
            return;
        }
        else{
            //add
            if(f1) a=a.substr(1);
            else b=b.substr(1);
            if(p<0) swap(a,b);
            bigInt C({a});
            bigInt D({b});
           // error(C.value,D.value);
            string res=C.adderBigInt(D);
            //error(res);
            if(f1) res='-'+res;
            value=res;
            return;
            }


    }
    void addBigInt(bigInt B){
        string a=value;
        string b=B.value;
        int p=this->compareBigInt(B);
        bool f1=isnegative(a);
        bool f2=isnegative(b);
        if(isZero(a) && isZero(b)) {
            value="0";
            return;
        }
        if(f1^f2==1){
            int p2=this->compareBigInt(B);
            if(f1){
                a=a.substr(1);
                }
            else{
                b=b.substr(1);
                }
            if(p2<0) swap(a,b);
            /*
            subtract
            +-{
                + ans+
                - ans-
            }
            -+
                +  ans+
                -  ans-
            */
            bigInt C({a}),D({b});
            C.subtractBigInt(D);
            string res=C.value;
            if((f1 && p2>0)||(f2&&p2<0)) res='-'+res;
            value=res;
            return ;
        }
        else{
        string res;
            if(f1){
                a=a.substr(1);
                b=b.substr(1);
             }
               bigInt C({b});
               bigInt D({a});

             if(p<0){
                    res=C.adderBigInt(D);

                    }
                else{
                     res=D.adderBigInt(C);
                }
             if(f1==1) res='-'+res;
        this->value=res;
        return;
        }


    }
    void multBigInt(bigInt B){
    string a=this->value;
    string b=B.value;
    if(isZero(a)|| isZero(b)){
        this->value="0";
        return;
    }
    else {
            string res;
            if(isnegative(a)^isnegative(b)){
                res=multiplierBigInt(a,b);
                res='-'+res;
                this->value=res;
                return;
            }
            else {
                    res=multiplierBigInt(a,b);
                }

            this->value=res;
            return ;

        }

    }


};
bigInt fib(int n){
    bigInt a({"0"}),b({"1"}),c;
    for(int i=0;i<n-2;i++){
        a.addBigInt(b);
        c.value=a.value;
        a.value=b.value;
        b.value=c.value;
    }
    return c;
}
bigInt fact(int n){
    bigInt a({"1"}),ans({"1"}),incerement({"1"});
    bigInt b({to_string(n)});
 //   cout<<b.value<<endl;
    while(a.compareBigInt(b)!=0){
        ans.multBigInt(a);
        a.addBigInt(incerement);
    }
    return ans;
}
int main(){
    int n=50000;
    cin>>n;

   /* for(int i=0;i<n;i++){
        bigInt a,b,c,d;

        a.readVal();
        b.readVal();
        c.value=a.value;
        d.value=b.value;
        c.addBigInt(d);
        cout<<"sum: "<<c.value<<endl;
        c.value=a.value;
        d.value=b.value;
        c.subtractBigInt(d);
        cout<<"diff: "<<c.value<<endl;
        c.value=a.value;
        d.value=b.value;
        c.multBigInt(d);
        cout<<"mult: "<<c.value<<endl;

    }*/
      // auto z=fact(n+1);
   // cout<<z.value<<endl;
    //cout<<z.value.size()<<endl;
 //   bigInt a({"1s23"});
    cout<<fib(n).value<<endl;
}
//fib
//2e4 in 0.701 seconds,4180 digits
//5e4 in 5.5s ,10449 digits
// 1e5 in 21 s, 20899 digits

//fact
//1e3 in 0.081 second ,2568 digits
//1e4 in 9.747 second ,35660 digits
//1e3 in 0.081 second ,2568 digits
//
