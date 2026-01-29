inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
/* by antharanos */
create_monster()
{
   ::create_monster();
   set_name("edward");
   add_name("child");
   set_race_name("human");
   set_adj("young");
   set_short("young child");
   set_long("A young human child, he looks like he's having quite a good time "+
      "playing and jumping around the room.\n");
   set_stats(({10,15,12,5,5,10}));
   set_alignment(600);
   set_act_time(9);
   add_act("smile cheer");
   add_act("emote jumps around the room happily.");
   add_act("tickle all");
   add_act("say Ahm onwy thwee yeaws old.");
   add_act("giggle");
   add_act("emote sucks his thumb.");
   set_knight_prestige(-6);
   add_speak("Thwee pwus two is five.\n");
   add_prop(LIVE_I_NEVERKNOWN,1);
   trig_new("%w 'arrives.' %s", "react_arrive");
   trig_new("%w 'pats' 'you' %s", "react_pat");
}


void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("gasp");
      command("say Leave my mommy alone!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
int
react_arrive(string who, string dummy){
   if(who){
      who = lower_case(who);
   set_alarm(3.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("say Why look! Its a nice " + obj->query_nonmet_name() + ".");
      command("ask " + (obj->query_real_name()) + " Wanna play with me?");
   }
}
int
react_pat(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_pat",who);
      return 1;
   }
}
void
return_pat(string who){
   {
      command("smile shyly");
   }
}
