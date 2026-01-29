inherit "/std/room";

#define DELTA 10.0
#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")
#define DAYS_OF_WEEK ({"Sun","Mon","Tue","Wed","Thu","Fri","Sat"})

#include <std.h>

#include "defs.h"
#include "event_defs.h"
#include "func.h"

#define CEVENT_OBJ SCHEDULER_DIR+"cevent"

static int hndl;
mapping plan;
string last_plan_date;

void save()
{
 save_object(CEVENT_OBJ);
}

int check_new_sunday()
{
 return(ctime(time())[0..2]=="Sun" && 
   ctime(time())[8..9]!=last_plan_date[8..9]);
}

void generate_plan(string event)
{
 mixed *sch,days,*tm;
 int i,*rd;
 string *res,start;


 sch=(SCHEDULER)->get_schedule(event);
 start=to_datetime(last_plan_date);
 if(!sch) return 0;

 res=allocate(7);
 switch(sch[0])
  {
   case FR_DAY:
     for(i=0;i<7;i++)
      {
       if(stringp(sch[1])) res[i]=sch[1];
       else res[i]=get_rand_time(sch[1]);
      }
     break;

   case FR_WEEK:
     days=sch[1]; tm=sch[2];
     if(sizeof(days))
      {
       for(i=0;i<sizeof(days);i++)
        {
         if(stringp(tm[i])) res[days[i]-1]=tm[i];
         else res[days[i]-1]=get_rand_time(tm[i]);
        }
      }
     else
      {
       rd=get_random_days((int)days);
       for(i=0;i<sizeof(rd);i++)
        {
         if(stringp(tm[i])) res[rd[i]-1]=tm[i];
         else res[rd[i]-1]=get_rand_time(tm[i]);
        }
      }
     break;
  }

 plan[event]=res;
 save();
}

void generate_plans()
{
 string *ind;
 int i;

 last_plan_date=ctime(time());

 ind=m_indexes(plan);
 for(i=0;i<sizeof(ind);i++) generate_plan(ind[i]);
}

void launch_event(string event)
{
 string server,func,owner,msg;
 mixed res;

 server=(SCHEDULER)->get_server(event);
 func=(SCHEDULER)->get_function(event);
 owner=(SCHEDULER)->get_owner(event);
 msg="Failed to run event "+event+" on "+ctime(time())+".\n";
 
 if(!file_exists(server))
  {
   msg+="Server ("+server+") does not exists!";
   notify_player(owner,msg);
   return;
  }

 (server)->blabla();

 if(!function_exists(func,find_object(server)))
  {
   msg+="Function "+func+" does not exists in server "+server+"!";
   notify_player(owner,msg);
   return;
  }

 res=call_other(server,func);
 
 if(!floatp(res))
  {
   msg+="Function "+func+" of server "+server+" does not return float!";
   notify_player(owner,msg);
   return;
  }

 if(res==-1.0)
  {
   msg+="Aborted by server request.";
   notify_player(owner,msg);
   write_file(CEVENT_LOG,"Event "+event+" was aborted at "+
     ctime(time())+" by server request.\n");
   return;
  }

 if(res==0.0)
  {
   notify_player(owner,"Started event "+event+" at "+ctime(time()));
   write_file(CEVENT_LOG,"Started event "+event+" at "+
     ctime(time())+"\n");
   return;
  }

 set_alarm(res,0.0,&launch_event(event));
}

void check_events()
{
 int day,i;
 string *ind,dt;

 if(check_new_sunday()) generate_plans();

 day=day_of_week(time());
 ind=m_indexes(plan);
 for(i=0;i<sizeof(ind);i++)
  {
   if(!plan[ind[i]][day]) continue;
   dt=replace_time(now(),plan[ind[i]][day]);
   if(compare_datetime(now(),dt)==1) 
    {
     plan[ind[i]][day]=0;
     save();
     launch_event(ind[i]);
    }
  }
}

void restart_clock()
{
 if(hndl==-1) 
  {
   hndl=set_alarm(0.1,DELTA,&check_events());
   write("Clock started.\n");
   DEBUG(TP->query_name()+" has started the scheduler clock on "+
     ctime(time()));
  }
 else write("Clock is already running.\n");
}

void stop_clock()
{
 if(hndl!=-1) 
  {
   remove_alarm(hndl);
   hndl=-1;
   write("Clock stoped.\n");
   DEBUG(TP->query_name()+" has stoped the scheduler clock on "+
     ctime(time()));
  }
 else write("Clock is not running.\n");
}

void create_room()
{
 set_short("Custom events clock room");
 set_long("You are in a great hall, you can barely see the ceiling. "+
   "Here all the custom events around Exodus are handled. You feel "+
   "presence of a great magic in the air.\n");

 hndl=-1;
 plan=([ ]);
 restore_object(CEVENT_OBJ);

 restart_clock();
}

void set_last_plan_date(string dt) {last_plan_date=dt;}
string query_last_plan_date() {return last_plan_date;}

mapping query_plan() {return plan;}

void remove_plan(string event) 
{
 plan=m_delete(plan,event);
 save();
}

string get_event_plan(string name)
{
 int i;
 string res="This event is planned to run on following days:\n";

 for(i=0;i<7;i++)
   if(plan[name][i]) res+=DAYS_OF_WEEK[i]+" - "+plan[name][i]+"\n";

 return res;
}

