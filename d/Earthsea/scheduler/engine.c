inherit "/std/room";

#define DELTA 30.0
#define DEBUG(x) find_player("ged")->catch_msg(x+"\n")

#include <std.h>

#include "defs.h"
#include "event_defs.h"
#include "func.h"

int hndl;

void tellall(int level,string text)
{
 int i;
 object *all=users();

 for(i=0;i<sizeof(all);i++)
   if((SECURITY)->query_wiz_rank(all[i]->query_real_name())>=level)
     all[i]->catch_msg(text);
}

string *filter_events(string *props,string *values)
{
 return (SCHEDULER)->filter_events(props,values);
}

mixed query_prop_value(string name,string prop) 
{
 return (SCHEDULER)->query_prop_value(name,prop);
}

void check_events()
{
 string *name,start,end;
 int i,ann;

 name=filter_events(({P_DATE,P_STATUS}),({get_date(now()),ST_PENDING}));

 for(i=0;i<sizeof(name);i++)
  {
   ann=(SCHEDULER)->query_prop_value(name[i],P_ANNOUNCE_MINS);
   start=query_prop_value(name[i],P_START);
   if(compare_datetime(modify_datetime(now(),ann),start)!=2)
     (SCHEDULER)->event_start(name[i]);
  }

 name=filter_events(({P_STATUS}),({ST_RUNNING}));
 for(i=0;i<sizeof(name);i++) 
  {
   end=(SCHEDULER)->query_prop_value(name[i],P_END);
   if(compare_datetime(now(),end)!=2)
     present("handler",TO)->finish_event();
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
 set_short("Events clock room");
 set_long("You are in a great hall, you can barely see the ceiling. "+
   "Here all events around Exodus are handled. You feel presence "+
   "of a great magic in the air.\n");

 hndl=-1;
 restart_clock();
}

void enter_inv(object ob, object from)
{
 if(ob->get_event())
   tell_room(TO,"New event handler suddenly appears!\n");

 ::enter_inv(ob,from);
}

void leave_inv(object ob, object to)
{
 if(ob->get_event())
   tell_room(TO,"One of event handlers suddenly disappears with a "+
     "loud POP!\n");

 ::leave_inv(ob,to);
}


