inherit "/std/room";

#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <language.h>

#include "defs.h"
#include "event_defs.h"
#include "func.h"

#define DATA_OBJ SCHEDULER_DIR+"winners"
#define SHOW 1
#define CLAIM 2
#define LIVE_I_CUR_EVENT "_live_i_cur_event"
#define HEADER "-- Item Claimer -- (l d <num> c <num> q ! ?) -- "
#define ERRMSG "No such command. Do '?' for help, 'q' to quit.\n"
#define HELP "\nAvailable commands:\n\n"+\
             "l(ist)             List all available items\n"+\
             "d(escribe) <num>   Describe item <num>\n"+\
             "c(laim) <num>      Claim item <num>\n"+\
             "q(quit)            Quit Item Claimer\n"+\
             "!<command>         Perform <command>\n"+\
             "?                  This help page\n\n"
#define WRITE_LOG(x) write_file(REWARD_LOG,x+"\n")
#define SECS_IN_WEEK 7*24*60*60

mapping winners;     // Winners of events
//  ([ event_name: ({ winner,date,reward_type,reward,real_date }) ])

void save() {save_object(DATA_OBJ);}

void create_room()
{
 winners=([ ]);
 restore_object(DATA_OBJ);

 set_short("Events hall of fame");
 set_long("Stretching out before you is a massive hall.  A soft, "
+"warming light seems to emanate from the ceiling, "
+"giving the room a strange unearthly glow.  Smooth, "
+"slick, marble slabs cover the floor, almost seeming "
+"to echo the strange glow that comes from the ceiling.  "
+"Above your head giant rafters made of polished redwood "
+"support the enormous roof.  Every so often, you think "
+"you spot something move in the rafters, but when you "
+"look again, there is nothing there.  Lining the polished "
+"stone walls you see many numerous display cases that "
+"apparently contain some sort of items on display.  There "
+"is a large sign hanging on the wall to your left that "
+"seems to have some instructions on it.\n");
add_item("ceiling","It is high overhead and radiating a strange "
+"soft light which illuminates the entire hall.\n");
add_item("slabs","These smooth, highly polished pieces of marble "
+"cover the floor completely and perfectly.\n");
add_item("rafters","These massive beams made of hardened redwood "
+"support the incredible weight of the gigantic ceiling "
+"above your head.  Each of the rafters is at least four "
+"feet in diameter and thirty feet long.  It must have "
+"taken either a giant or divine assistance to build this "
+"place.\n");
add_item("walls","They are made of the same material as the floor "
+"here and in their polished surfaces, the diffuse light "
+"from the ceiling is reflected out in all directions.\n");
add_item("sign","Bordered by what appears to be a living, moving "
+"frame, the sign has some instructions on it.  It is "
+"somewhat hard to read unless you really focus since "
+"the vines and other images on the frame seem to be "
+"growing and writhing.\n");

 add_prop(ROOM_I_INSIDE,1);

 add_cmd_item("sign","read","@@read_sign");

 add_exit("/d/Genesis/start/human/town/tfloor4","down");

 setuid();
 seteuid(getuid());
 clone_object(SCHEDULER_DIR+"board.c")->move(TO);
}

void init()
{
 ::init();
 add_action("list","list");
 add_action("desc","desc");
 add_action("history","history");
 add_action("check","check");
 add_action("reward","reward");
}

string read_sign()
{
 return 
  " 'list events'         - See what events are planned\n"+
  " 'desc <name>'         - Show information about planned event\n"+
  " 'history'             - See list of all occured events\n"+
  " 'history date1-date2' - See list of events that occured\n"+
  "                            between date1 and date2\n"+
  "    e.g history 10/10/2005-10/11/2005\n"+
  "        history -01/01/2003\n"+
  "        history 27/02/1999-\n"+
  " 'history <name>'      - See information about occured event\n"+
  " 'check wins'          - Check what events you have won and\n"+
  "                           a nice reward waiting for you\n"+
  " 'reward <name>'       - Request reward for event you won\n";
}

void add_winner(string event,string name,int date,int rw_type,
                mixed *reward)
{
 if(member_array(event,m_indexes(winners))!=-1) return;

 winners+=([ event : ({ name,date,rw_type,reward,time() }) ]);
 save();
}

mapping query_winners() {return winners;}

int list(string str)
{
 string *names;

 NF("List what?\n");
 if(!str || !strlen(str)) return 0;
 if(str!="events") return 0;

 names=(SCHEDULER)->filter_events(({P_STATUS}),({ST_PENDING}));
 (SCHEDULER)->show_event_table(names);

 say(QCTNAME(TP)+" inquires about planned events.\n");

 return 1;
}

int desc(string str)
{
 string *names;

 NF("Desc what?\n");
 if(!str || !strlen(str)) return 0;

 names=(SCHEDULER)->filter_events(({P_STATUS}),({ST_PENDING}));

 NF("No such event is planned.\n");
 if(member_array(str,names)==-1) return 0;

 write((SCHEDULER)->desc_event(str)+"\n");
 say(QCTNAME(TP)+" inquires about event: "+str+".\n");

 return 1;
}

int history(string str)
{
 string *names,from,to;

 if(!str || !strlen(str))
  {
   names=(SCHEDULER)->filter_history(0,0);
   (SCHEDULER)->show_history_table(names);
   say(QCTNAME(TP)+" inquires about events history.\n");
   return 1;
  }

 if(sscanf(str,"%s-%s",from,to)==2)
  {
   if(!strlen(from)) from=0;
   if(!strlen(to)) to=0;
   NF("Invalid date: "+from+"\n");
   if(from && !is_valid_datetime(from+" 00:00")) return 0;
   NF("Invalid date: "+to+"\n");
   if(to && !is_valid_datetime(to+" 00:00")) return 0;

   names=(SCHEDULER)->filter_history(from,to);
   (SCHEDULER)->show_history_table(names);
   say(QCTNAME(TP)+" inquires about events history.\n");
   return 1;
  }

 NF("No such event occured: "+str+"\n");
 if(!(SCHEDULER)->history_exists(str)) return 0;

 write(read_file(HISTORY_LOG_DIR+str+".log"));
 say(QCTNAME(TP)+" inquires about event: "+str+".\n");

 return 1;
}

void clear()
{
 winners=([ ]);
 save();
}

mixed *query_events_won(string name)
{
 string *ind;
 mixed *res;
 int i;

 ind=m_indexes(winners); res=({ });
 for(i=0;i<sizeof(ind);i++)
   if(winners[ind[i]][W_WINNER]==name) 
     res+=({ ({ind[i],winners[ind[i]][W_RW_TYPE]}) });

 return res;
}

mixed *query_winner_data(string event)
{
 if(member_array(event,m_indexes(winners))==-1) return 0;

 return ({ winners[event][W_WINNER],winners[event][W_RW_TYPE],
           winners[event][W_RW_AMNT] });
}

int check(string str)
{
 int i;
 mixed *won;

 NF("Check wins maybe?\n");

 if(!str || !strlen(str)) return 0;
 if(str!="wins") return 0;

 won=query_events_won(TP->query_name());

 NF("You havn't won any events yet!\n");
 if(!sizeof(won)) return 0;

 for(i=0;i<sizeof(won);i++)
   write(C(RW_DESC[won[i][1]]+" awaits you for winning an event: "+
     won[i][0]+"\n"));
 say(QCTNAME(TP)+" inquires about events "+PRO(TP)+" won.\n");
 
 return 1;
}

void remove_winner(string event)
{
 winners=m_delete(winners,event);
 save();
}

int check_expired(string event)
{
 return (time()-winners[event][W_REAL_DATE]>SECS_IN_WEEK);
}

int reward(string str)
{
 mixed *data;
 object rw;

 NF("No such event occured: "+str+"\n");
 if(!(SCHEDULER)->history_exists(str)) return 0;

 data=query_winner_data(str);

 NF("There is no reward for you on this event.\n");
 if(!data) return 0;

 NF("No no no. You did not win this event.\n");
 if(data[0]!=TP->query_name()) return 0;

 NF("Time for claiming reward for this event has expired!\n");
 if(check_expired(str)) 
  {
   WRITE_LOG(TP->query_name()+" tried to claim reward for winning "+
     "event: "+str+" at "+ctime(time())+", but time for claiming has "+
     "expired.");
   remove_winner(str);
   return 0;
  }

 switch(data[1])
  {
   case RW_NONE:
     rw=0;
     write("No reward was assigned to this event!\n");
     WRITE_LOG(TP->query_name()+" tried to claim reward for winning "+
       "event: "+str+" at "+ctime(time())+", but it was no reward "+
       "assigned to this event.");
     break;
   case RW_COINS:
     rw=MONEY_MAKE_PC(data[2]);
     write(C(LANG_WNUM(data[2])+" platinum coins suddenly appear in "+
       "your inventory!\n"));
     WRITE_LOG(TP->query_name()+" claimed "+data[2]+
       " platinum coins at "+ctime(time())+" as a reward for "+
       "winning event: "+str);
     break;
   case RW_QXP:
     TP->add_exp_quest(data[2]);
     write("You feel quest experience floating into you.\n");
     WRITE_LOG(TP->query_name()+" claimed "+data[2]+" points of "+
       "quest experience at "+ctime(time())+" as a reward for "+
       "winning event: "+str);
     break;
   case RW_CXP:
     TP->add_exp_combat(data[2]);
     write("You feel combat experience floating into you.\n");
     WRITE_LOG(TP->query_name()+" claimed "+data[2]+" points of "+
       "combat experience at "+ctime(time())+" as a reward for "+
       "winning event: "+str);
     break;
   case RW_GXP:
     TP->add_exp_general(data[2]);
     write("You feel general experience floating into you.\n");
     WRITE_LOG(TP->query_name()+" claimed "+data[2]+" points of "+
       "general experience at "+ctime(time())+" as a reward for "+
       "winning event: "+str);
     break;
   case RW_ITEM:
     TP->add_prop(LIVE_I_CUR_EVENT,str);
     write("Entering item claimer. Type '?' for help.\n");
     write(HEADER);
     input_to("get_command");
     return 1;
  }

 if(data[1]!=RW_NONE)
     say(QCTNAME(TP)+" claims his reward for winning an event: "+
       str+"!\n");     

 if(rw)
  {
   if(rw->move(TP))
    {
     write("You cannot carry your reward. Dropping it on the ground.\n");
     rw->move(ENV(TP));
    }
  }

 remove_winner(str);
 return 1;
}

void show_items(string event)
{
 mixed *data;
 string *item,desc;
 int i;

 data=query_winner_data(event);
 item=data[2];

 write("\nNum   Item\n"+
       "-------------------------------------------------\n");
 for(i=0;i<sizeof(item);i++)
  {
   if(!file_exists(item[i])) 
     desc="This item no longer exists. Please contact AoE.";
   else
     desc=C(LANG_ADDART((item[i])->short()));
   write(sprintf("[%-2d]  %s\n",i+1,desc));
  }
 write("\n");
}

int do_item(string event,string num,int action)
{
 int ind;
 mixed *data;
 string *item;
 object rw;

 data=query_winner_data(event);
 item=data[2];

 sscanf(num,"%d",ind);
 if(ind<1 || ind>sizeof(item))
  {
   write(sprintf("Please specify a number between 1 and %d.\n",
     sizeof(item)));
   return 0;
  }

 if(!file_exists(item[ind-1])) 
  {
   write("This item no longer exists. Please contact AoE.\n");
   return 0;
  }

 switch(action)
  {
   case SHOW:
     write("\nYou study the "+(item[ind-1])->short()+" carefully.\n");
       (item[ind-1])->appraise_object();
     write("\n");
     break;
   case CLAIM:
     write("You claim "+LANG_ADDART((item[ind-1])->short())+" as your "+
       "reward.\n");
     say(QCTNAME(TP)+" claims his reward for winning an event: "+
       event+"!\n");     
     rw=clone_object(item[ind-1]);
     if(rw->move(TP))
      {
       write("You cannot carry your reward. Dropping it on the "+
         "ground.\n");
       rw->move(ENV(TP));
      }
     WRITE_LOG(TP->query_name()+" claimed "+LANG_ADDART(rw->short())+
       "("+MASTER_OB(rw)+") at "+ctime(time())+" as a reward for "+
       "winning event: "+event);
     remove_winner(event);
     break;
  }

 return 1;
}

void get_command(string str)
{
 string *params,cmd;

 if(!str || !strlen(str))
  {
   write(HEADER);
   input_to("get_command");
   return;
  }

 params=explode(str," ");
 cmd=params[0];
 params=params[1..];

 switch(cmd)
  {
   case "q": case "quit":
     TP->remove_prop(LIVE_I_CUR_EVENT);
     write("Quitting Item Claimer. No item claimed.\n");
     return;

   case "?":
     write(HELP);
     break;

   case "l": case "list":
     show_items(TP->query_prop(LIVE_I_CUR_EVENT));
     break;

   case "d": case "describe":
     if(sizeof(params)!=1)
      {
       write("Describe what item? Please specify a number.\n");
       break;
      }
     if(!is_number(params[0]))
      {
       write("Please, specify a valid number of an item.\n");
       break;
      }
     do_item(TP->query_prop(LIVE_I_CUR_EVENT),params[0],SHOW);
     break;
   
   case "c": case "claim":
     if(sizeof(params)!=1)
      {
       write("Claim what item? Please specify a number.\n");
       break;
      }
     if(!is_number(params[0]))
      {
       write("Please, specify a valid number of an item.\n");
       break;
      }
     if(do_item(TP->query_prop(LIVE_I_CUR_EVENT),params[0],CLAIM))
       return;
     break;

   default: 
     write(ERRMSG);
  }

 write(HEADER);
 input_to("get_command");
}

