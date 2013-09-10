#include <iostream>
#include <cstdio>
#include <vector>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <cstring>
#include <errno.h>   // to inform which error you are facing now
using namespace std;

char *destinateDir="/home/peanut/desktop/store";
char *currentDir="/home/peanut";
char * notDeal[]={"dosdevices","drive_c",".wine32","wine32",".wine",".wine32-backup",".wine-backup"};
bool copyFile(char *);
bool reachDir(char *);
bool dealWithDir(char *);
bool dealWithFile(char *);
bool match(char *dst,char *src);
bool notDealWith(char *);
bool from_to_(char *,char*);
bool sameName(char *,char *);

int main(){
char *directory=currentDir;
reachDir(directory);
return 0;
}

bool reachDir(char* dir_name = NULL){
    DIR* Entry=NULL;
    if(dir_name==NULL){
        dir_name = currentDir;
    }
    if(!(Entry=opendir(dir_name))){
        cout<<endl<<"Error open dir :  "<<dir_name<<endl;
        // Why the error appear
        switch(errno){
//            case EMFILE: cout<<"too much file for process!"<<endl;break;
//            case ENFILE: cout<<"too much file for system!"<<endl;break;
//            case ENOTDIR: cout<<"not true directory!"<<endl;break;
//            case ENOENT: cout<<"no such Directory!"<<endl;break;
//            case ENOMEM: cout<<"no enough memory!"<<endl;break;
            default: cout<<strerror(errno)<<endl;
        }  
        return false;
    }
    char temp[1000];
    strcpy(temp,dir_name);
    char* pstr=temp + strlen(dir_name);
    *pstr = '/';
    pstr++;
    struct stat buf;
    struct dirent* p=NULL;
    while(p=readdir(Entry)){
//        if( strcmp(p->d_name,".")!=0 && strcmp(p->d_name,"..")!=0 ){
//            cout<<p->d_name<<endl;
//        }
        if( notDealWith(p->d_name) ) continue; // some directory we do not handle
        strcpy(pstr,p->d_name);

//       stat
        memset(&buf,0,sizeof(buf));
        stat(temp,&buf);
        if(buf.st_mode & S_IFDIR){ if(!(buf.st_mode & S_IFLNK)) dealWithDir(temp); 
        }
        else if(buf.st_mode & S_IFREG) dealWithFile(temp);
    }
    closedir(Entry);
    return true;
}

bool dealWithDir(char *dir_name){
    char *p = dir_name;
    while(*p != '\0'){  p++;  }
    if(*(--p)=='.' && (*(--p)=='/'||*p=='.'&&*(--p)=='/'))    
    {
        return true;  // not deal with "." or ".."
    }
    cout<<"Dir : "<<dir_name<<endl;
    reachDir(dir_name);
    return true;
}

bool dealWithFile(char *file_name){
    
    cout<<"File: "<<file_name<<endl;
    if(match(file_name,".png")||match(file_name,".jpg")||match(file_name,".bmp")){
        copyFile(file_name);
    }
    return true;
}

bool copyFile(char *file_name){
    char *p=file_name;
    while(*p!='\0') p++;
    while(*p!='/') p--;
    p++;   // match the filename but without the directory

    char dstFile[500]={0};
    strcpy(dstFile, destinateDir);
    char *q = dstFile + strlen(dstFile);
    *q = '/';
    q++;
    strcpy(q,p);   // set the destination file name

    if(from_to_(dstFile,file_name))    
        cout<< " copy:  " <<file_name<<endl<<" to  :   "<<dstFile<<endl;
    return true;
}

bool match(char *dst, char *src){
    // only to judge the end of the filename 
    char *p=dst + strlen(dst) - strlen(src);
    if(!strcmp(p,src)) return true;
    return false;
}

bool notDealWith(char *dir_name){
    for(int i=0;i<sizeof(notDeal)/sizeof(char*);i++){
        if(strcmp(dir_name, notDeal[i])==0) return true;
    }
    return false;
}


bool from_to_(char* dst,char* src){
if(strcmp(dst,src)==0) return false;
FILE* d,*s;
if(s=fopen(src,"rb")){

if(d=fopen(dst,"wb")){
unsigned char t[10]={0};
int count;
while((count=fread(t,1,10,s))==10){
fwrite(t,1,10,d);
}
if(count!=0&&count<=10){ fwrite(t,1,count,d); }
cout<<"copy Successful !"<<endl;
}
else{ cout<<"unable to create file : "<<dst<<endl; fclose(s); return false; }
}
else{ cout<<"unable to open file : "<<src<<endl; return false; }
fclose(d);
fclose(s);
return true;
}


bool sameName(char *a ,char*b){
char *p=a,*q=b;
while(*p) p++;
while(*q) q++;
while(*p!='/' && p>=a) p--;  // get the name without path
while(*q!='/' && q>=b) q--;  // get the name without path
if(strcmp(++p,++q)==0) return true;
return false;
}
