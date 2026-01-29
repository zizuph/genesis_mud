/* 
 * /d/Kalad/common/wild/pass/npc/bed_wom.c
 * Purpose    : A bedellin woman in the camp
 * Located    : /d/Kalad/common/wild/pass/desert/camp
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include "/sys/ss_types.h"
#include "/sys/money.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("woman");
   set_race_name("human");
   set_adj("demure");
   add_adj("bedellin");
   set_gender(G_FEMALE);
   set_short("demure bedellin woman");
   set_long("A typical Bedellin woman, she is swathed from head to toe "+
      "in a concealing aba that hides everything but her hands and eyes "+
      "from view. She walks around with her eyes downcast, and mouth silent.\n");
   set_stats(({35,50,35,40,40,35}));
   set_alignment(400);
   set_skill(SS_AWARENESS,50);
   set_act_time(6);
   add_act("emote makes not a sound as she moves about.");
   add_act("emote casts her eyes downward.");
   set_knight_prestige(-4);
   MONEY_MAKE_SC(random(10))->move(TO,1);
   trig_new("%w 'arrives.' %s", "react_arrive");
}
int
react_arrive(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("emote lowers her eyes meekly.");
      command("bow " + lower_case(obj->query_real_name()));
   }
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob,environment()))
      {
      command("scream");
      command("kill " + (ob->query_real_name()));
   }
}
void
my_stuff()
{
   object it;
   seteuid(getuid(TO));
   it = clone_object("/d/Kalad/common/wild/pass/arm/bed_waba");
   it -> move(TO);
   command("wear all");
}
