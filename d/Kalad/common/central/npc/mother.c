inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("anni");
   add_name("housewife");
   set_race_name("human");
   set_adj("calm");
   add_adj("sensible");
   set_gender(G_FEMALE);
   set_short("housewife");
   set_long("This woman is the busy homebody of this house. Like many of "+
      "the other Kaladian women she usually stays at home and takes care of "+
      "the children as well as cooking for her husband.\n");
   set_stats(({30,50,30,40,40,30}));
   set_alignment(400);
   set_skill(SS_AWARENESS,100);
   set_act_time(6);
   add_act("emote dusts the room.");
   add_act("smile");
   add_act("say Hello there!");
   add_act("pat child");
   add_act("say Don't wander off now honey.");
   add_speak("My my, all these chores to do.\n");
   set_knight_prestige(-4);
   MONEY_MAKE_SC(random(15))->move(TO,1);
   trig_new("%w 'arrives.' %s", "react_arrive");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("gasp");
      command("say Goodness gracious!");
      command("say You beast! Leave my child alone!");
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
      command("say Greetings " + obj->query_nonmet_name() + ".");
      command("bow " + lower_case(obj->query_real_name()));
   }
}