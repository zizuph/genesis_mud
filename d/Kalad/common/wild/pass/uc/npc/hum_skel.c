inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("warrior");
   set_race_name("warrior");
   set_adj("skeletal");
   set_long("Judging by the size and shape of the bones, the animated "+
      "remains of a human being. When this poor and unfortunate "+
      "soul was once a creature of the flesh, it must have been a warrior, "+
      "for now its skeleton is dressed in the arms and armour of a warrior. "+
      "A few scraps of flesh can be seen hanging from various parts of "+
      "its body.\n");
   set_gender(G_NEUTER);
   set_knight_prestige(100);
   set_aggressive(1);
   set_attack_chance(75);
   set_stats(({50,50,50,1,1,50}));
   set_skill(SS_UNARM_COMBAT,25);
   set_skill(SS_BLIND_COMBAT,100);
   set_skill(SS_WEP_SWORD,50);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,50);
   add_prop(LIVE_I_SEE_DARK,100);
   add_prop(LIVE_I_UNDEAD,15);
   add_prop(LIVE_I_NO_CORPSE,1);
   add_prop(LIVE_I_NEVERKNOWN,1);
   set_act_time(3);
   add_act("emote rattles its bones together.");
   set_cact_time(3);
   add_cact("emote noisily rattles its bones together.");
}
void
arm_me()
{
   object wep,arm;
   seteuid(getuid(TO));
   wep = clone_object(CPASS(uc/wep/skel_sword));
   wep -> move(TO);
   command("wield all");
   arm = clone_object(CPASS(uc/arm/skel_chain));
   arm -> move(TO);
   arm = clone_object(CPASS(uc/arm/skel_shield));
   arm -> move(TO);
   command("wear all");
}
do_die(object killer)
{
   object bones;
   if (query_hp() > 0) return;
   bones = clone_object(CPASS(uc/obj/skel_bones));
   bones -> move(environment(TO));
   ::do_die(killer);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote opens its jaw in a silent scream for battle.");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
