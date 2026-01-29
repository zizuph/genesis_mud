#define YR_MNT_DAYS ({31,28,31,30,31,30,31,31,30,31,30,31})
#define LEAP_YR_MNT_DAYS ({31,29,31,30,31,30,31,31,30,31,30,31})
#define IS_LEAP_YEAR(y) !(y%4)
#define MNTH_DAYS(y,m) (IS_LEAP_YEAR(y) ? LEAP_YR_MNT_DAYS[m-1] :\
  YR_MNT_DAYS[m-1])
#define YR_DAYS(y) (IS_LEAP_YEAR(y) ? 366 : 365)
#define ITOA(x) sprintf("%d",x)
#define ADD_ZERO(x) (x<10 ? 0+ITOA(x) : ITOA(x))
#define DAYS_OF_WEEK ({"Sun","Mon","Tue","Wed","Thu","Fri","Sat"})

#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")
#define MAIL(subject,sender,recipient,text) "/secure/mail_reader"->\
create_mail(subject,sender,LC(recipient),LC(recipient),text+"\n")

static mapping MONTHES=(["Jan":"01","Feb":"02","Mar":"03","Apr":"04",
  "May":"05","Jun":"06","Jul":"07","Aug":"08","Sep":"09","Oct":"10",
  "Nov":"11","Dec":"12"]);

int is_digit(int char)
{
 return ((char<48 || char>57) ? 0 : 1);
}

int is_number(string str)
{
 int i;

 if(!str || !strlen(str)) return 0;

 for(i=0;i<strlen(str);i++) if(!is_digit(str[i])) return 0;
 return 1;
}

mixed *is_valid_datetime(string str)
{
 string s_day,s_month,s_year,s_hrs,s_mins;
 int day,month,year,hrs,mins;
 int i,tot_days=0;

 if(sscanf(str,"%s/%s/%s %s:%s",s_day,s_month,s_year,s_hrs,s_mins)!=5) 
   return 0;

 if(strlen(s_day)!=2 || strlen(s_month)!=2 || strlen(s_year)!=4 || 
   strlen(s_hrs)!=2 || strlen(s_mins)!=2) return 0;

 if(!is_number(s_day) || !is_number(s_day) || !is_number(s_day) || 
   !is_number(s_day) || !is_number(s_day) || !is_number(s_day))
     return 0;

 year=atoi(s_year);
 month=atoi(s_month);
 day=atoi(s_day);
 hrs=atoi(s_hrs);
 mins=atoi(s_mins);

 if(year<1970) return 0;
 if(month<1 || month>12) return 0;
 if(day<1 || day>MNTH_DAYS(year,month)) return 0;
 if(hrs<0 || hrs>23) return 0;
 if(mins<0 || mins>59) return 0;

 return ({year,month,day,hrs,mins}); 
}

int compare_datetime(string dt1,string dt2)
{
 mixed *d1,*d2;

 d1=is_valid_datetime(dt1);
 d2=is_valid_datetime(dt2);

 if(!d1 || !d2) return -1;

 if(d1[0]>d2[0]) return 1;
 if(d1[0]<d2[0]) return 2;
 if(d1[1]>d2[1]) return 1;
 if(d1[1]<d2[1]) return 2;
 if(d1[2]>d2[2]) return 1;
 if(d1[2]<d2[2]) return 2;
 if(d1[3]>d2[3]) return 1;
 if(d1[3]<d2[3]) return 2;
 if(d1[4]>d2[4]) return 1;
 if(d1[4]<d2[4]) return 2;

 return 0;
}

string dupl_char(string str,int n)
{
 int i;
 string res="";

 if(!n) return "";
 for(i=0;i<n;i++) res+=str;
 return res;
}

string to_datetime(string dt)
{
 string *tm,*tm1;
 int i,cnt;
 string year,mnth,day,hrs,mins;

 tm=explode(dt," ");
 cnt=0;
 for(i=0;i<sizeof(tm);i++)
  {
   if(tm[i]=="") continue;
   cnt++;
   switch(cnt)
    {
     case 2: 
       mnth=MONTHES[tm[i]]; 
       break;
     case 3: 
       day=tm[i];
       if(strlen(day)==1) day="0"+day;
       break;
     case 4:
       tm1=explode(tm[i],":");
       hrs=tm1[0]; mins=tm1[1];
       break;
     case 5:
       year=tm[i];
       break;
    }
  }

 return day+"/"+mnth+"/"+year+" "+hrs+":"+mins;
}

string now() {return to_datetime(ctime(time()));}

string fix_file(string name)
{
 int i;
 string nm=name;

 if(!name || name=="") return "";

 for(i=0;i<strlen(nm);i++) if(nm[i]!=32) break;
 if(i!=strlen(nm)) nm=extract(nm,i,strlen(nm)-1);
 for(i=strlen(nm)-1;i>=0;i--) if(nm[i]!=32) break;
 if(i!=0) nm=extract(nm,0,i);

 if(extract(nm,strlen(nm)-2,strlen(nm)-1)!=".c") 
   return nm+".c";
 return nm;
}

int file_exists(string name)
{
 return (file_size(name)<0 ? 0 : 1);
}

int domain_exists(string dom)
{
 return (member_array(dom,(SECURITY)->query_domain_list())==-1 ? 0 : 1);
}

string get_date(string dt)
{
 return extract(dt,0,9);
}

string get_time(string dt)
{
 return extract(dt,11,15);
}

string sub_datetime(string dt,int mins)
{
 mixed *d;
 int i;

 d=is_valid_datetime(dt);
 if(!dt) return 0;

 for(i=1;i<=mins;i++)
  {
   d[4]--;
   if(d[4]<0) {d[4]=59; d[3]--;}
   if(d[3]<0) {d[3]=23; d[2]--;}
   if(d[2]<1) 
    {
     d[1]--;
     if(d[1]<1) {d[1]=12;d[0]--;}
     d[2]=MNTH_DAYS(d[0],d[1]);
    }
  }

 return ADD_ZERO(d[2])+"/"+ADD_ZERO(d[1])+"/"+d[0]+" "+
        ADD_ZERO(d[3])+":"+ADD_ZERO(d[4]);
}

string add_datetime(string dt,int mins)
{
 mixed *d;
 int i;

 d=is_valid_datetime(dt);
 if(!dt) return 0;

 for(i=1;i<=mins;i++)
  {
   d[4]++;
   if(d[4]>59) {d[4]=0; d[3]++;}
   if(d[3]>23) {d[3]=0; d[2]++;}
   if(d[2]>MNTH_DAYS(d[0],d[1])) {d[2]=1; d[1]++;}
   if(d[1]>12) {d[1]=1; d[0]++;}
  }

 return ADD_ZERO(d[2])+"/"+ADD_ZERO(d[1])+"/"+d[0]+" "+
        ADD_ZERO(d[3])+":"+ADD_ZERO(d[4]);
}

string modify_datetime(string dt,int mins)
{
 if(mins>0) return add_datetime(dt,mins);
 if(mins<0) return sub_datetime(dt,-mins);
 return dt;
}

mixed is_unique(mixed *arr)
{
 mixed *so_far=({ }),*repeat=({ });
 int i;

 for(i=0;i<sizeof(arr);i++)
  {
   if(member_array(arr[i],so_far)!=-1)
    {
     if(member_array(arr[i],repeat)==-1) repeat+=({ arr[i] });
    }
   else so_far+=({ arr[i] });
  }

 if(!sizeof(repeat)) return 1;
 return repeat;
}

string get_domain(string fl)
{
 string *dirs;

 dirs=explode(fl,"/")-({ "" });
 if(sizeof(dirs)<3) return 0;

 if(dirs[0]!="d") return 0;

 return dirs[1];
}

int between_date(string dt,string from,string to)
{
 string dt1,from1,to1;

 dt1=dt+" 00:01";

 if(!from && !to) return 1;

 if(!from && to)
  {
   to1=modify_datetime(to+" 23:59",1);
   return(compare_datetime(dt1,to1)==2);
  }

 if(from && !to)
  {
   from1=from+" 00:00";
   return(compare_datetime(dt1,from1)==1);
  }

 from1=from+" 00:00";
 to1=modify_datetime(to+" 23:59",1);

 return(compare_datetime(dt1,from1)==1 &&
        compare_datetime(dt1,to1)==2);
}

mixed *is_valid_time(string tm)
{
 int hrs,mins;
 string s_hrs,s_mins;

 if(sscanf(tm,"%s:%s",s_hrs,s_mins)!=2) return 0;

 if(!is_number(s_hrs) || !is_number(s_mins)) return 0;
 if(strlen(s_hrs)!=2) return 0;
 if(strlen(s_mins)!=2) return 0;
 sscanf(s_hrs,"%d",hrs); sscanf(s_mins,"%d",mins);

 if(hrs<0 || hrs>23) return 0;
 if(mins<0 || mins>59) return 0;

 return ({ hrs,mins });
}

int compare_time(string tm1,string tm2)
{
 mixed *t1,*t2;

 t1=is_valid_time(tm1); t2=is_valid_time(tm2);
 if(!t1 || !t2) return -1;

 if(t1[0]*60+t1[1]>t2[0]*60+t2[1]) return 1;
 if(t1[0]*60+t1[1]<t2[0]*60+t2[1]) return 2;

 return 0;
}

string mins_to_time(int mn)
{
 int hrs,mins;
 string s_hrs,s_mins;

 mins=mn%60; hrs=mn/60;
 s_mins=sprintf("%d",mins); s_hrs=sprintf("%d",hrs);
 if(strlen(s_mins)<2) s_mins="0"+s_mins;

 return s_hrs+":"+s_mins;
}

int time_to_mins(string tm)
{
 mixed *t;

 t=is_valid_time(tm);
 if(!t) return 0;

 return t[0]*60+t[1];
}

int mins_between(string t1,string t2)
{
 mixed *tm1,*tm2;
 int res;

 tm1=is_valid_time(t1); tm2=is_valid_time(t2);
 if(!tm1 || !tm2) return 0;

 res=tm1[0]*60+tm1[1]-tm2[0]*60-tm2[1];
 return (res<0 ? -res : res);
}

string add_time(string tm,int mins)
{
 return mins_to_time(time_to_mins(tm)+mins);
}

string sub_time(string tm,int mins)
{
 return mins_to_time(time_to_mins(tm)-mins);
}

string modify_time(string tm,int mins)
{
 if(mins>0) return add_time(tm,mins);
 if(mins<0) return sub_time(tm,-mins);
 return tm;
}

string replace_time(string dt,string tm)
{
 return dt[0..10]+tm;
}

string get_rand_time(string *tm)
{
 if(sizeof(tm)!=2) return 0;

 return modify_time(tm[0],random(mins_between(tm[0],tm[1]))+1);
}

int *get_random_days(int n)
{
 int *res=({1,2,3,4,5,6,7}),i;

 if(n>6) return res;

 for(i=0;i<7-n;i++) res-=({ RND(res) });
 return res;
}

int day_of_week(int tm)
{
 return member_array(ctime(tm)[0..2],DAYS_OF_WEEK);
}

void notify_player(string name,string msg)
{
 object pl;

 pl=find_player(name);
 if(pl) pl->catch_msg("\n\nEVENTMASTER TELLS YOU:\n"+msg+"\n\n");
   else MAIL("Notify message","Eventmaster",name,msg);
}

