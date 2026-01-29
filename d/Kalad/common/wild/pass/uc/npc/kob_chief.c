inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(7);
   if(i < 1)
      return "conniving";
   else if(i < 2)
      return "treacherous";
   else if(i < 3)
      return "disgusting";
   else if(i < 4)
      return "demented";
   else if(i < 5)
      return "snivelling";
   else if(i < 6)
      return "defiant";
   else
      return "filthy";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   string extra;
   extra = random_extra();
   set_name("kobold");
   add_name("chieftain");
   set_race_name("kobold");
   set_adj("large");
   add_adj(extra);
   set_long("A reptilian-like being, it stands nearly four feet in "+
      "height. Protruding from its sloping brow are a pair of small, "+
      "twisted horns. Two, beady red eyes stare out at you from a face "+
      "that possesses a flattened nose and large mouth. Its scaly "+
      "hide is the color of rusty metal and from its rear protrudes a "+
      "long, rat-like tail.\n");
   set_gender(G_NEUTER);
   for(i = 0; i < 3; i++)
   set_base_stat(i, 50 + random(40));
   set_base_stat(3, 35);
   set_base_stat(4, 35);
   set_base_stat(5, 30);
   set_alignment(-400);
   set_knight_prestige(400);
   set_skill(SS_WEP_SWORD,75);
   set_skill(SS_WEP_AXE,75);
   set_skill(SS_DEFENCE,50);
   set_skill(SS_PARRY,50);
   set_skill(SS_AWARENESS,40);
   set_skill(SS_2H_COMBAT,50);
   set_act_time(6);
   add_act("growl");
   add_act("tackle all");
   add_act("grin");
   add_act("get all from corpse");
   add_act("stand on the boulder");
   add_act("sit in the throne");
   set_cact_time(6);
   add_cact("snarl all");
   add_cact("laugh evil");
   add_cact("grin vic");
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(LIVE_I_NEVERKNOWN,1);
   trig_new("%w 'drops' %s","react_drop");
}
void
arm_me()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(uc/arm/kob_c_arm));
   item -> move(TO);
   command("wear all");
   item = clone_object(CPASS(uc/wep/kob_l_sword));
   item -> move(TO);
   item = clone_object(CPASS(uc/wep/kob_l_axe));
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_GC(random(5))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("scream");
      command("kill " + (ob->query_real_name()));
   }
}
int
react_drop(string who, string dummy){
   if(who){
      who = lower_case(who);
      set_alarm(2.0,0.0,"return_drop",who);
      return 1;
   }
}
void
return_drop(string who){
   object obj;
   int ran;
   if(obj = present(who, environment())){
      command("get all coins");
      command("smile dev");
   }
}
