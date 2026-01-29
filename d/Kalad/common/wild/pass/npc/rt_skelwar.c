/* 
 * /d/Kalad/common/wild/pass/npc/rt_skelwar.c
 * Purpose    : A skeleton warrior
 * Located    : /d/Kalad/common/wild/pass/desert/sand/r*
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_monster()
{
   ::create_monster();
   set_name("warrior");
   set_race_name("warrior");
   set_adj("skeletal");
   set_long("The animated skeletal remains of a human being. When this poor "+
      "soul was once a creature of the flesh, it must have been a warrior, "+
      "for now its skeleton is dressed in the arms and armour of a warrior. "+
      "A few scraps of flesh can be seen hanging from various parts of "+
      "its skeleton.\n");
   set_gender(G_NEUTER);
   set_knight_prestige(100);
   set_aggressive(1);
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
   wep = clone_object(CPASS(wep/rt_swsword));
   wep -> move(TO);
   command("wield all");
   arm = clone_object(CPASS(arm/rt_swchain));
   arm -> move(TO);
   arm = clone_object(CPASS(arm/rt_swshield));
   arm -> move(TO);
   command("wear all");
}
do_die(object killer)
{
   object bones;
   if (query_hp() > 0) return;
   bones = clone_object(CPASS(obj/rt_bones));
   bones -> move(environment(TO));
   ::do_die(killer);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote rattles quite noisily.");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
