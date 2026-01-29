#include <macros.h>

#include "defs.h"

#define TIME_OUT 120.0

void priest_act(int stage);
void accept_trickster();
void leave_guild(object who);

int ritual=0;
int alarm_h,alarm2_h;
int stg=0;
int stage2_stg=0;
object priest,player,leave;

void init_ritual()
{
 add_action("kneel","kneel");
 add_action("rise","rise");
 add_action("rise","arise");
 add_action("swear","swear");
}

void start_ritual(object who)
{
 setuid();
 seteuid(getuid());

 if(who->query_invis())
  {
   who->catch_msg("You cannot go through ritual invisable!\n");
   return;
  }

 ritual=1;
 player=who;
 priest=clone_object(TRICKSTERS+"npc/priest");
 priest->move(TO);
 tell_room(TO,QCTNAME(priest)+" silently enters the room.\n");
 priest_act(1);
}

void cancel_ritual()
{
 remove_alarm(alarm_h);
 remove_alarm(alarm2_h);
 tell_room(TO,QCTNAME(priest)+" silently leaves the room.\n");
 priest->remove_object();
 priest=0;
 player=0;
 ritual=0;
 stg=0;
 stage2_stg=0;
}

void not_ready()
{
 priest->SAY_TO(player,"Apparently you are not ready , mortal...");
 priest->command("tlaugh "+player->query_real_name());
 cancel_ritual();
}

void stage2()
{
 if(ENV(player)!=ENV(priest)) 
  {
   cancel_ritual();
   return;
  }

 stage2_stg++;
 
 switch(stage2_stg)
  {
   case 1: priest->command("emote closes his eyes and concentrates.");
           break;
   case 2: priest->command("tpray"); break;
   case 3: priest->command("hiss"); break;
   case 4: player->catch_msg(QTN(priest,player)+" takes you arm and "+
             "stabs it with dagger.\n"+
             "You feel weakness in whole body.\n");
           tell_room(TO,QCTNAME(priest)+" takes "+QTPNAME(player)+
             " arm and stabs it with dagger.\n",player);
           player->heal_hp(-1000);
           break;
   case 5: player->catch_msg("As your blood starts trickling on altar "+
             "runes start to glow with unholy red light!\n");
           tell_room(TO,QCTPNAME(player)+" blood starts trickling on "+
             "altar and runes start to glow with unholy red light!\n",
           player);
           break;
   case 6: priest->command("tpray"); break;
   case 7: priest->emote("opens his eyes , you see unholy glimpse in "+
             "his eyes.");
           priest->SAY_TO(player,"You may now rise..."); 
           break;
  }

 if(stage2_stg==7) 
  {
   stg=3;
   remove_alarm(alarm2_h);
   alarm_h=set_alarm(TIME_OUT,0.0,&not_ready());
  }
}

void priest_act(int stage)
{
 if(ENV(player)!=ENV(priest)) 
  {
   cancel_ritual();
   return;
  }

 switch(stage)
  {
   case 1:
     stg=1;
     priest->command("tgrin "+player->query_real_name());
     priest->command("say The ritual begins...");
     priest->SAY_TO(player,"Kneel before altar , mortal soul...");
     alarm_h=set_alarm(TIME_OUT,0.0,&not_ready());
     break;

   case 2:
     stg=2;
     priest->command("tlaugh");
     priest->say("say I will now pray to Kina to accept you into "+
       "our dark Order...");
     priest->SAY_TO(player,"And stay on your knees , mortal...");
     stage2_stg=0;
     alarm2_h=set_alarm(1.0,5.0,&stage2());
     break;

   case 4:
     stg=4;
     priest->SAY_TO(player,"Now swear with your life and honour to "+
       "serve Kina...");
     priest->command("tgrin "+player->query_real_name());
     alarm_h=set_alarm(TIME_OUT,0.0,&not_ready());
     break;

   case 6:
     stg=6;
     priest->SAY_TO(player,"By the power given me by Kina I accept "+
       "you into Tricksters.");
     priest->command("meet "+player->query_real_name());
     player->catch_msg("You recieve a stick , a kit and a rumel from "+
       QtN(priest,player)+".\n");
     tell_room(TO,QCTNAME(player)+" recieves a stick , a kit and a "+
       "rumel from "+QCTNAME(priest)+".\n",player);
     accept_trickster();
     cancel_ritual();
     break;
  }
}

int kneel(string what)
{
 if(!ritual || stg!=1) return 0;

 if(ritual && TP!=player)
  {
   write("There is ritual already going on! You will have to wait.\n");
   return 1;
  }

 if(!what || what!="before altar") 
  {
   write("Kneel before alter mayhaps??\n");   
   return 1;
  }

 write("You kneel before altar.\n");
 say(QCTNAME(TP)+" kneels before altar.\n");

 remove_alarm(alarm_h);
 priest_act(2);

 return 1;
}

int rise(string what)
{
 if(!ritual || stg!=3) return 0;

 NF("There is ritual already going on! You will have to wait.\n");
 if(ritual && TP!=player) return 0;

 NF("Maybe simply "+query_verb()+"?\n");
 if(what) return 0;

 write("You "+query_verb()+" from altar.\n");
 say(QCTNAME(TP)+" "+query_verb()+"s from altar.\n");
 tell_room(TO,"Runes on altar seem to fade.\n");

 remove_alarm(alarm_h);
 priest_act(4);

 return 1;
}

int swear(string what)
{
 if(!ritual || stg!=4) return 0;

 NF("There is ritual already going on! You will have to wait.\n");
 if(ritual && TP!=player) return 0;
 
 NF("Maybe simply "+query_verb()+"?\n");
 if(what) return 0;

 write("You swear with your life , honour to server Kina blindly.\n");
 say(QCTNAME(TP)+" swears to server Kina.\n");

 remove_alarm(alarm_h);
 priest_act(6);

 return 1;
}

void priest_act_leave(object who)
{
 priest->SAY_TO(who,"You wish to leave , so be it! Begone and don't "+
   "ever return!\n");
 who->catch_msg(QTN(priest,who)+" takes stick , kit and rumel from "+
   "you.\n");
 tell_room(TO,QCTPNAME(who)+" kit stick , kit and rumel are taked "+
   "by "+QTNAME(priest)+".\n",who);
 present(STICK_DESC,priest)->outfit();
 priest->command("tcackle");
 priest->command("stinksplash "+who->query_real_name());

 tell_room(TO,QCTNAME(priest)+" silently leaves the room.\n");
 priest->remove_object();
 priest=0;
 ritual=0;
 leave=0;
}

void leave_guild(object who)
{
 setuid();
 seteuid(getuid());

 leave=who;
 ritual=1;
 priest=clone_object(TRICKSTERS+"npc/priest");
 priest->move(TO);
 tell_room(TO,QCTNAME(priest)+" silently enters the room.\n");

 set_alarm(2.0,0.0,&priest_act_leave(who));
}

