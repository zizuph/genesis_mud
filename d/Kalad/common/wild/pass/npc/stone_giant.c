/* 
 * /d/Kalad/common/wild/pass/npc/stone_giant.c
 * Purpose    : A stone giant
 * Located    : /d/kalad/common/wild/pass/desert/mount/g*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("giant");
   set_race_name("stone giant");
   set_adj("fierce");
   set_long("A gargantuan figure that stands well over eighteen feet in "+
      "height. His lean, muscular figure is comparable to the bodies of the "+
      "most fit of athletes. Despite his lean build, the rock-like texture "+
      "of his flesh indicates great strength. His gaunt features, coupled "+
      "with deep sunken eyes gives him a perpetually grim expression.\n");
   set_stats(({200,100,150,75,75,125}));
   set_all_hitloc_unarmed(40);
   set_skill(SS_WEP_CLUB,90);
   set_skill(SS_DEFENCE,90);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
   set_act_time(6);
   add_act("smile grim");
   add_act("emote says something in a strange language.");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("grin menacingly");
   add_cact("emote says something harshly at you in a strange tongue.");
   add_speak("Leave these mountains or you will die, little one.\n");
   add_prop(CONT_I_WEIGHT,4000000);
   add_prop(CONT_I_VOLUME,4000000);
   trig_new("%w 'arrives.' %s", "react_arrive");
}
void
arm_me()
{
   object wep;
   seteuid(getuid(TO));
   wep = clone_object(CPASS(wep/sg_club));
   wep -> move(TO);
   command("wield all");
   MONEY_MAKE_CC(random(50))->move(TO,1);
}
int
react_arrive(string who, string dummy)
{
   if(who)
      {
      who = lower_case(who);
      set_alarm(3.0,0.0,"return_arrive",who);
      return 1;
   }
}
void
return_arrive(string who)
{
   object obj;
   int ran;
   if(obj = present(who, environment()))
      {
      command("grin . " + (obj->query_real_name()));
   }
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote bellows out something in a strange tongue!");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
