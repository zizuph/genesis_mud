#include <macros.h>

string blocked_exit;

int guarded()
{
 int i;

 for(i=0;i<sizeof(guards);i++)
   if(guards[i]) return 1;

 return 0;
}

string get_long()
{
 string res;

 res="You are in rather small corridor. ";

 if(guarded()) return res+"Tough guards guard the passage to "+
   blocked_exit+". They won't be too glad if you try pass them by.\n";

 return res+"You see some beds here , apparently some guards were "+
   "supposed to be here , but somehow they are not here.\n";
}

int block()
{
 int i;
 object grd=0;

 if(TP->query_real_name()=="karg") return 0;

 for(i=0;i<sizeof(guards);i++)
   if(guards[i]) grd=guards[i];

 if(!grd) return 0;

 if(!TP->query_prop("_was_warned_by_karg"))
  {
   grd->command("say Halt , "+TP->query_nonmet_name()+"!");
   grd->command("say I'm warning you, stay out of here!");
   say(QCTNAME(TP)+" was brutally stoped by guards.\n");
   TP->add_prop("_was_warned_by_karg",1);
   return 1;
  }

 if(TP->query_prop("_was_warned_by_karg")==1)
  {
   grd->command("say Halt , "+TP->query_nonmet_name()+"!");
   grd->command("say You've been warned! Leave or you will die!");
   say(QCTNAME(TP)+" was brutally stoped by guards.\n");
   TP->add_prop("_was_warned_by_karg",2);
   return 1;
  }

 (SERVER)->add_enemy(TP->query_real_name());
 grd->command("say You've been warned twice , "+
   TP->query_nonmet_name()+", now you die!");
 grd->command("shout Guards , attack!!!");
 for(i=0;i<sizeof(guards);i++)
   guards[i]->command("kill "+TP->query_real_name());
 return 1;
}

