
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
    bigint(string argument){
        bool f=0;
         try{
            cin>>argument;
            for(auto ch:argument){
                if((ch>'9' || ch<'0') && ch!='-'){
                    throw invalid_argument("Please enter only integer values");
                }
            }
        }catch(invalid_argument& e){
            cerr<<e.what()<<endl;
            f=1;
        }
        if(!f)value=argument;
    }
    void readVal(){
        cout<<"Enter number:";
        string inputValue;
        try{
            cin>>inputValue;
            for(auto ch:inputValue){
                if((ch>'9' || ch<'0') && ch!='-'){
                    throw invalid_argument("Please enter only integer values");
                }
            }
        }catch(invalid_argument& e){
            cerr<<e.what()<<endl;
            this->readVal();
            return;
        }
        value=inputValue;
    }
    bool isnegative(string inputValue){
        if(inputValue[0]=='-') return 1;
        return 0;
    }

    bool isZero(string inputValue){
        if(isnegative(inputValue)) inputValue=inputValue.substr(1);
        int length=inputValue.size();
        for(int i=0;i<length;i++){
            if(inputValue[i]!='0' && inputValue[i]!='-') return 0;
        }
        return 1;
    }
    int comparehelper(string value1,string value2){
        int p1=value1.size();
        int p2=value2.size();
        if(p1>p2) return 1;
        if(p1<p2) return -1;
        int i=0,diff=0,bigger=0;
        do{
         diff=value1[i]-value2[i];
         if(diff>0) bigger=1;
         else if(diff<0) bigger=-1;
         ++i;
        }while(diff==0 && i<p1 && i<p2);
        return bigger;
    }
    int compareBigInt(bigInt B){
        string value1=value;
        string value2=B.value;
        if(isnegative(value1)) value1=value1.substr(1);
        if(isnegative(value2)) value2=value2.substr(1);
        return comparehelper(value1,value2);
    }

    string removeZeroes(string inputValue){
        int nonz=0,newlength=0,i=0;
        int length=inputValue.size()-1;
        for(nonz=0;nonz<inputValue.size();nonz++){
            if(inputValue[nonz]!='0') break;
        }
        if(nonz==0) return inputValue;
        inputValue=inputValue.substr(nonz);

        return inputValue;
    }

    string adderBigInt(bigInt B){
        string value1=this->value;
        string value2=B.value;
        int p1=value1.size()-1;
        int p2=value2.size()-1;
        int sum=0,carry=0,k=p1+1;
        string ans;
        for(int i=0;i<=k;i++) ans+='0';
        while(p2>=0){
            sum=value1[p1]+value2[p2]+carry-'0'-'0';
            ans[k]='0'+sum%10;
            carry=sum/10;
            p1--;
            p2--;
            k--;

        }
        while(p1>=0){
            sum=value1[p1]+carry-'0';
            ans[k]='0'+sum%10;
            carry=sum/10;
            p1--;
            k--;
        }
        if(carry){
            ans[k]='0'+carry;
        }
        ans=removeZeroes(ans);
        return  ans;
    }
    string multiplierBigInt(string inputValue1,string inputValue2){
        if(isnegative(inputValue1)) inputValue1=inputValue1.substr(1);
        if(isnegative(inputValue2)) inputValue2=inputValue2.substr(1);
        int l1=inputValue1.size();
        int l2=inputValue2.size();
        int sum=0,carry=0;
        int l3=l1+l2;
        int ptr1=0;
        int ptr2;
        int i;
        //error(a,b);
        string ans;
        for(int i=0;i<=l3;i++) ans+='0';
        for(i=l2-1;i>=0;i--){
            sum=0,carry=0;
            ptr2=l3-ptr1;
            for(int j=l1-1;j>=0;j--){
                sum=(inputValue1[j]-'0')*(inputValue2[i]-'0')+(ans[ptr2]-'0')+carry;
                ans[ptr2]='0'+sum%10;
              //  ////error(sum);
                carry=sum/10;
                --ptr2;

            }
            if(carry) ans[ptr2]+=carry;
        ++ptr1;
        }
        //cout<<res<<endl;
        ans=removeZeroes(ans);
        return ans;
}
string subtracterBigInt(bigInt B){
        string inputValue2=B.value;
        string inputValue1=this->value;
        int p=this->compareBigInt(B);
        if(p<0) {swap(inputValue1,inputValue2);
        p*=-1;}
        int p1=inputValue1.size()-1;
        int p2=inputValue2.size()-1;
        string ans;
        int taken=0,k=p1;
        for(int i=0;i<=p1;i++) ans+='0';
        while(p2>=0){
            int top=inputValue1[p1]-'0';
            int bottom=inputValue2[p2]-'0';
            if(taken>0){
                if(taken==1){
                    top-=1;
                }else{
                top=9+inputValue1[p1]-'0';
                }
                --taken;
            }
            if(top<bottom){
                do{
                    ++taken;
                }while(inputValue1[p1-taken]=='0' && (p1-taken)>0);
                top+=10;
            }
            ans[k]='0'+top-bottom;
            p1--;
            p2--;
            k--;

        }
        while(p1>=0){
            if(taken>0){
                ans[k]=inputValue1[p1]-1;
                if(inputValue1[p1]=='0')
                    ans[k]='9';
                --taken;

            }
                else{
                    ans[k]=inputValue1[p1];
                }
                --p1;
                --k;

        }
        //cout<<c<<endl;
        ans=removeZeroes(ans);
        return ans;
    }

    string multiplierBigInt(bigInt B){
        string inputValue2=B.value;
        string inputValue1=this->value;
        if(isnegative(inputValue1)) inputValue1=inputValue1.substr(1);
        if(isnegative(inputValue2)) inputValue2=inputValue2.substr(1);
        int l1=inputValue1.size();
        int l2=inputValue2.size();
        int sum=0,carry=0;
        int l3=l1+l2;
        int ptr1=0;
        int ptr2;
        int i;
        ////error(a,b);
        string ans;
        for(int i=0;i<=l3;i++) ans+='0';
        for(i=l2-1;i>=0;i--){
            sum=0,carry=0;
            ptr2=l3-ptr1;
            for(int j=l1-1;j>=0;j--){
                sum=(inputValue1[j]-'0')*(inputValue2[i]-'0')+(ans[ptr2]-'0')+carry;
                ans[ptr2]='0'+sum%10;
              //  ////error(sum);
                carry=sum/10;
                --ptr2;

            }
            if(carry) ans[ptr2]+=carry;
        ++ptr1;
        }
        //cout<<res<<endl;
        ans=removeZeroes(ans);
        return ans;
    }

    void subtractBigInt(bigInt B){
        string inputValue1=this->value;
        string inputValue2=B.value;
        bool f1=isnegative(inputValue1);
        bool f2=isnegative(inputValue2);
        int p=this->compareBigInt(B);
        if(isZero(inputValue1) && isZero(inputValue2)){
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
            if(f1) inputValue1=inputValue1.substr(1);
            if(f2) inputValue2=inputValue2.substr(1);
            bigInt C({inputValue1});
            bigInt D({inputValue2});
            string ans=C.subtracterBigInt(D);
            //error(a,b,res);
            if((!f2 && p<0)||(f1 && p>0)) ans='-'+ans;
            if(isZero(ans)) ans="0";
            this->value=ans;
            return;
        }
        else{
            //add
            if(f1) inputValue1=inputValue1.substr(1);
            else inputValue2=inputValue2.substr(1);
            if(p<0) swap(inputValue1,inputValue1);
            bigInt C({inputValue1});
            bigInt D({inputValue2});
           // error(C.value,D.value);
            string ans=C.adderBigInt(D);
            //error(res);
            if(f1) ans='-'+ans;
            value=ans;
            return;
            }


    }
    void addBigInt(bigInt B){
        string inputValue1=value;
        string inputValue2=B.value;
        int p=this->compareBigInt(B);
        bool f1=isnegative(inputValue1);
        bool f2=isnegative(inputValue2);
        if(isZero(inputValue1) && isZero(inputValue2)) {
            value="0";
            return;
        }
        if(f1^f2==1){
            int p2=this->compareBigInt(B);
            if(f1){
                inputValue1=inputValue1.substr(1);
                }
            else{
                inputValue2=inputValue2.substr(1);
                }
            if(p2<0) swap(inputValue1,inputValue2);
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
            bigInt C({inputValue1}),D({inputValue2});
            C.subtractBigInt(D);
            string ans=C.value;
            if((f1 && p2>0)||(f2&&p2<0)) ans='-'+ans;
            value=ans;
            return ;
        }
        else{
        string ans;
            if(f1){
                inputValue1=inputValue1.substr(1);
                inputValue2=inputValue2.substr(1);
             }
               bigInt C({inputValue2});
               bigInt D({inputValue1});

             if(p<0){
                    ans=C.adderBigInt(D);

                    }
                else{
                     ans=D.adderBigInt(C);
                }
             if(f1==1) ans='-'+ans;
        this->value=ans;
        return;
        }


    }
    void multBigInt(bigInt B){
    string inputValue1=this->value;
    string inputValue2=B.value;
    if(isZero(inputValue1)|| isZero(inputValue2)){
        this->value="0";
        return;
    }
    else {
            string ans;
            if(isnegative(inputValue1)^isnegative(inputValue2)){
                ans=multiplierBigInt(inputValue1,inputValue2);
                ans='-'+ans;
                this->value=ans;
                return;
            }
            else {
                    ans=multiplierBigInt(inputValue1,inputValue2);
                }

            this->value=ans;
            return ;

        }

    }


};
bigInt fib(int n){
    bigInt value1({"0"}),value2({"1"}),value3;
    for(int i=0;i<n-2;i++){
        value1.addBigInt(value2);
        value3.value=value1.value;
        value1.value=value2.value;
        value2.value=value3.value;
    }
    return value3;
}
bigInt fact(int n){
    bigInt value1({"1"}),ans({"1"}),incerement({"1"});
    bigInt value2({to_string(n)});
 //   cout<<b.value<<endl;
    while(value1.compareBigInt(value2)!=0){
        ans.multBigInt(value1);
        value1.addBigInt(incerement);
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
