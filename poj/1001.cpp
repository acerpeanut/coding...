#include <iostream>
#include <string>
using namespace std;
void multiply(string& a,string& b,string& c){
	int al=a.length();
	int bl=b.length();
	int *s=new int[al+bl-1];
	c.clear();
	c.insert(0,al+bl-1,'0');
	for(int i=0;i<al+bl-1;i++) s[i]=0;
	for(int i=0;i<a.length();i++){
		for(int j=0;j<b.length();j++){
			s[i+j]+=(a[i]-'0')*(b[j]-'0');
		}
	}
	for(int i=al+bl-2;i>0;i--){
		s[i-1]+=s[i]/10;
		c[i]=s[i]%10+'0';
	}
	while(s[0]>9){
		c[0]=s[0]%10+'0';
		s[0]=s[0]/10;
		c.insert(0,1,0);
	}
	c[0]=s[0]+'0';
	delete [] s;
}
void point(string& a,int c){
	if(c!=-1){
		while(c>a.length()){
			a.insert(0,1,'0');
			c--;
		}
		c=a.length()-c;

		a.insert(c,1,'.');
		for(int i=a.length()-1;i>0;i--){
			if(a[i]=='0' ){
				a.erase(i,1);
			}
			else if(a[i]=='.'){
				a.erase(i,1);
				break;
			}
			else{
				break;
			}
		}
	}
	for(int i=0;i<a.length();i++){
		if(a[0]=='0'){
			a.erase(0,1);
		}
		else{
			break;
		}
	}
	if(a.length()==0){
		a.insert(0,1,'0');
	}
}


int main(){
	string a;
	int b;
	while(cin>>a>>b){
		int i=0;
		int c=-1;
		string s;
		string t;
		string waiting[10];
		int waiting_count=0;
		while(a[i]!='\0'){
			if(a[i]!='.'){
				s.push_back(a[i]);
			}
			else{
				c=i;
			}
			i++;
		}
		if(c!=-1){
			c=a.length()-c-1;
			c=c*b;
		}
		t=s;
		string product=s;
		if(b==0){
			product="00000000001";
		}
		while(true){
			int tmp=(b>1?b%2:0);
			if(tmp==1){
				waiting[waiting_count++]=s;
			}
			b=b/2;
			if(b>0){
				multiply(s,t,product);
				s=product;
				t=product;
			}
			else break;
		}
		while(waiting_count-->0){
			s=product;
			multiply(s,waiting[waiting_count],product);
		}
		point(product,c);
		cout<<product<<endl;
	}
	return 0;
}
