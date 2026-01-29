inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
void
create_monster()
{
   int i;
   set_name("ninja");
   set_living_name("hyper-combat closetninja");
   set_long("This is Mute's deadly ninja assassin.  He is very tough"+
      " and likes to karate chop his enemies! \n");
   set_race_name("human");
   set_adj("hyper-combat");
   set_adj("closet");
   set_gender(0);
   set_all_hitloc_unarmed(5);
   set_all_attack_unarmed(10, 10);
   set_alignment(0);
   set_aggressive(1);
   set_stats(({ 50, 100, 50, 25, 25, 50 }));
   set_hp(2500);
   set_skill(SS_WEP_SWORD, 80);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_UNARM_COMBAT, 75);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 65);
   add_prop(CONT_I_WEIGHT, 85000);
   add_prop(CONT_I_HEIGHT, 1830);
   add_prop(CONT_I_VOLUME, 84000);
   set_act_time(0);
   add_act("say Oh, yaso hiro noto kamika!");
   add_act(({"say Wasohirotachi!", "emote does a ninja flip", "bow all"}));
   set_alarm(1.0, 0.0, "get_sword");
}

get_sword()
{
   seteuid(getuid());
   clone_object("/d/Rhovanion/mute/ninja-to.c")->move(this_object());
   command("wield all");
}
