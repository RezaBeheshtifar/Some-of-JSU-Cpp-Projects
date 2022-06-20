short isBinary(string str)
{
    int n=str.size();
    for(int i=0 ; i<n ; i++)
        if(str.at(i)!='0' && str.at(i)!='1')
            return 0;
    return 1;
}

short isDecimal(string str)
{
    int n=str.size();
    for(int i=0 ; i<n ; i++)
    {
    	int c=str.at(i);
    	if(c!='0' && c!='1' && c!='2' && c!='3' && c!='4' && c!='5' && c!='6' && c!='7' && c!='8' && c!='9')
            return 0;
    } 
    return 1;
}

short isZero(string str)
{
    int n=str.size();
    for(int i=0 ; i<n ; i++)
        if(str.at(i)!='0')
            return 0;
    return 1;
}

string normalizeBinary(string str)
{
	// Example: 0000001101100 --> 1101100
    int i=0, n=str.size();
    if(n==0 || isZero(str))
        return "0";  // if n=0 --> str=NULL --> return "0"
                     // if (isZero=1) --> return "0"
    if(n==1)
        return str;  // if n=1 --> str.at(0)='0' OR str.at(0)='1' --> return str
    for( ; i<n ; i++)
        if(str.at(i)!='0')
            break;
    return str.substr(i,n-i);
}

int equalSize(string& a, string& b)
{
    int n1=a.size(), n2=b.size();
    int n=n1-n2;
    if(n>0)
    {
        for(int i=0 ; i<n ; i++)
            b='0'+b;
        return n1;
    }
    if(n<0)
    {
        for(int i=0 ; i<-n ; i++)
            a='0'+a;
        return n2;
    }
    return n1;
}

void FA(char carryIn, char x, char y, char &carryOut, char &s)
{
    short a=x-'0', b=y-'0', c=carryIn-'0';
    s=(a^b^c)+'0';
    carryOut=((a&b)|(b&c)|(a&c))+'0';
}

string addString(string a, string b)
{
    string result;
    int length=equalSize(a, b);
    char carry='0', s;
    for(int i=length-1 ; i>=0 ; i--)
    {
        FA(carry,a.at(i),b.at(i),carry,s);
        result = s + result;
    }
    if(carry=='1')
        result = '1' + result;
    return normalizeBinary(result);
}

string subString(string a, string b)
{
    string result;
    int length=equalSize(a, b);
    char carry='1', s;
    for(int i=length-1 ; i>=0 ; i--)
    {
        FA(carry,a.at(i),(b.at(i)=='0')?'1':'0',carry,s);
        result = s + result;
    }
    if(carry=='1')
        ;
    return normalizeBinary(result);
}

string shlString(string str, int m)
{
    int n=str.size();
    for(int i=0 ; i<m ; i++)
        str=str+'0';
    return str;
}

string FM(char a, char b)
{
    if(a=='0' || b=='0')
        return "0";
    return "1";
}

string multiply(string U, string V)
{
    int n=equalSize(U,V);
    if(n==0)
        return "0";
    if(n==1)
        return FM(U.at(0),V.at(0));

    int m=n/2;
    int h=(n-m);

    string X=U.substr(0,m);
    string Y=U.substr(m,h);
    string W=V.substr(0,m);
    string Z=V.substr(m,h);

    string P=multiply(X,W);
    string Q=multiply(Y,Z);
    string R=multiply(addString(X,Y),addString(W,Z));

    return normalizeBinary(addString(addString(shlString(P,2*h),shlString((subString(subString(R,P),Q)),h)),Q));
}
// W(n)=3W(n/2)+teta(n) --> W(n)=teta(n^1.58)

string power2bin_first(int n)
{
    if(n<0)
        return "ERROR";
    if(n==0)
        return "1";
    if(n==1)
        return "1010";
    int m=n/2;
    return normalizeBinary(multiply(power2bin_first(m),power2bin_first(n-m)));
}
// W(n)=2W(n/2)+teta(n^1.58) --> W(n)=teta(n^1.58)

string power2bin_second(int n)
{
    if(n<0)
        return "ERROR";
    if(n==0)
        return "1";
    if(n==1)
        return "1010";
    short flagOdd=0;
    if(n%2)
    {
        flagOdd=1;
        n--;
    }
    string s="1010";
    for(int i=0 ; i<n-1 ; i++)
        s=multiply(s,"1010");
    if(flagOdd)
        s=multiply(s,"1010");
    return normalizeBinary(s);
}

string dec2bin_oneDigit(char c)
{
	if(c=='0') return "0";
	if(c=='1') return "1";
	if(c=='2') return "10";
	if(c=='3') return "11";
	if(c=='4') return "100";
	if(c=='5') return "101";
	if(c=='6') return "110";
	if(c=='7') return "111";
	if(c=='8') return "1000";
	if(c=='9') return "1001";
	return "ERROR"; 
}

string decimal2bin(string dec)
{
	int n=dec.size();
	if(n==0)
        return "0";
    if(n==1)
        return dec2bin_oneDigit(dec.at(0));
    string remain=dec.substr(1,n-1);                                           // teta(n)
    string current=multiply(dec2bin_oneDigit(dec.at(0)),power2bin_first(n-1)); // teta(n^1.58)+teta(n^1.58)
    return addString(current,decimal2bin(remain));                             // W(n-1)+teta(n)
}
// W(n)=W(n-1)+2teta(n^1.58)+2teta(n) --> W(n)=W(n-1)+teta(n^1.58) --> W(n)=teta(n^2)
