inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "../defs.h"

int alarm_h;
int count=0;
int length=0;

void end_in(int t)
{
 count+=length-t;
}

void stink_action();

void set_length(int l)
{
 count=0;
 length=l;
}

void create_object()
{
 setuid();
 seteuid(getuid());
 set_name("_trickster_stink_object_");
 set_no_show_composite(1);
 add_prop(OBJ_I_NO_DROP,"");
}

void react_random(object who)
{
 int what;

 what=random(5);
 switch(what)
  {
   case 0:
     who->catch_msg("You wish you were upwind from "+
       TP->query_the_name(who)+", as you get a wiff of "+POS(TP)+
       " stinky odor.\n");
     who->command("cough");
     break;
   case 1:
     who->catch_msg("The stench coming from "+TP->query_the_name(who)+
       " causes you to lose your lunch!\n");
     who->command("puke");
     break;
   case 2:
     who->catch_msg(C(TP->query_the_name(who))+" smells so bad, you "+
       "kick "+OBJ(TP)+" in hopes that "+PRO(TP)+" will leave.\n");
     who->catch_msg("You kick "+TP->query_the_name(who)+
       " fanatically.\n");
     write(C(who->query_the_name(TP))+" kicks you fanatically.\n");
     say(C(QTNAME(who))+" kicks "+QTNAME(TP)+" fanatically.\n",
       ({who,TP}));
     break;
   case 3:
     who->catch_msg("The putrid smell coming from "+
       TP->query_the_name(who)+" causes you to choke on something.\n");
     who->command("choke");
     break;
   case 4:
     who->catch_msg("The horrid smell coming from "+
       TP->query_the_name(who)+" makes you want to throw up.\n");
     who->command("gag");
  }
}

void stink_action()
{
 object *all_here,*al,*mee;
 int i;

 count++;
 if(count==1)
  {
   write("You REALLY stink!\n");
   say(C(QTNAME(TP))+" starts to eminate a horrible odor!!\n");
   return;
  }

 if(count==length)
  {
   write("Whew...  that horrible smell has finally gone away.\n");
   say(C(QTNAME(TP))+" finally smells bearable again.\n");
   remove_alarm(alarm_h);
   remove_object();
   return;
  }

 mee=({TP});
 al=(ENV(TP))->subinventory();
 all_here=al-mee;
 say("A putrid smell assults your nose!\n");
 for(i=0;i<sizeof(all_here);i++) 
   if(living(all_here[i]))
     react_random(all_here[i]);
}

void start()
{
 set_this_player(ENV(TO));
 alarm_h=set_alarm(5.0,10.0,&stink_action());
}

