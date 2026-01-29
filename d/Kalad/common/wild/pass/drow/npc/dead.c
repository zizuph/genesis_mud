inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/extra_long";

#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(10);
   if(i < 1)
      return "cruel";
   else if (i < 2)
      return "vicious";
   else if (i < 3)
      return "sadistic";
   else if (i < 4)
      return "savage";
   else if (i < 5)
      return "brutal";
   else if (i < 6)
      return "malevolent";
   else if (i < 7)
      return "demonic";
   else if (i < 8)
      return "devilish";
   else if (i < 9)
      return "unholy";
   else 
      return "hateful";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   string extra;
   extra = random_extra();
   set_name("drow");
   add_name("warrior");
   set_race_name("drow");
   set_adj(extra);
   add_adj("undead");
   set_pshort(extra + " undead drow");
   set_long("A once-proud drow warrior, his formerly handsome features are now ravaged by "+
      "his existence as an undead warrior, a true servant to Lolth and her "+
      "foul priestesses. If nothing, the fire within his eyes seems to burn "+
      "brighter than before, for he is now wholly devoted to Lolth's cause.\n");
   set_extra_long("From the symbol of a black widow spider perched atop "+
      "two crossed halberds, it appears as if he belongs to House Noquar.\n");
   set_aggressive(1);
   set_stats(({100,100,100,25,25,75}));
   set_skill(SS_WEP_POLEARM,90);
   set_skill(SS_DEFENCE,75);
   set_skill(SS_PARRY,75);
   set_skill(SS_AWARENESS,60);
   set_skill(SS_BLIND_COMBAT,90);
   set_skill(SS_HIDE,50);
   set_skill(SS_SNEAK,50);
   set_act_time(6);
   add_act("moan");
   add_act("groan");
   add_act("emote stares at you with unblinking eyes.");
   set_cact_time(3);
   add_cact("emote moans: Elghinn plynn dos...");
   add_cact("moan");
   set_knight_prestige(500);
   add_prop(LIVE_I_SEE_DARK,10);
   add_prop(LIVE_I_SEE_INVIS,10);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   set_alarm(1.0,0.0,"arm_me");
}
void
arm_me()
{
   object wep, arm;
   seteuid(getuid(TO));
   arm = clone_object(CPASS(drow/arm/h8_war_armour));
   arm -> move(TO);
   command("wear all");
   wep = clone_object(CPASS(drow/wep/h8_war_halberd));
   wep -> move(TO);
   command("wield all");
}
void
help_friend(object ob)
{
   if (ob && !query_attack() && present(ob, environment()))
      {
      command("groan");
      command("kill " + lower_case(ob->query_real_name()));
   }
}
int
special_attack(object enemy)
{
   object me;
   mixed *hitresult;
   string how;
   me = TO;
   if(random(15))
      return 0;
   hitresult = enemy->hit_me(200 + random(200), W_IMPALE, me, -1);
   how = " with little success";
   if(hitresult[0] > 0)
      how == "";
   if(hitresult[0] > 5)
      how = " bruisingly";
   if(hitresult[0] > 10)
      how = " painfully";
   if(hitresult[0] > 15)
      how = " very painfully";
   if(hitresult[0] > 20)
      how = " painfully hard";
   if(hitresult[0] > 25)
      how = " incredibly hard";
   if(hitresult[0] > 30)
      how = " with devastating effectiveness";
   if(hitresult[0] > 35)
      how = " with a fatal blow";
   me -> catch_msg("You attempt to impale your opponent!\n"+
      capitalize(enemy->query_pronoun()) + " is hit"+
      how + ".\n");
   enemy -> catch_msg(QCTNAME(me) + " attempts to impale you with his weapon!\n"+
      "You are hit" + how + ".\n");
   tell_watcher(QCTNAME(me) + " attempts to impale " + QTNAME(enemy) + " with his weapon!\n"+
      capitalize(enemy->query_pronoun()) + " is hit" +
      how + ".\n", enemy);
   if(enemy->query_hp() <= 0)
      enemy->do_die(me);
   return 1;
}
