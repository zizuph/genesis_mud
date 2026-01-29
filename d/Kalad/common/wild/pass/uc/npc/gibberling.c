inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(7);
   if(i < 1)
      return "sneaky";
   else if(i < 2)
      return "treacherous";
   else if(i < 3)
      return "malicious";
   else if(i < 4)
      return "demonic";
   else if(i < 5)
      return "savage";
   else if(i < 6)
      return "defiant";
   else
      return "cunning";
}
/* by Antharanos */
void
create_monster()
{
   int i;
   string extra;
   extra = random_extra();
   set_name("gibberling");
   set_race_name("gibberling");
   set_adj(extra);
   set_long("A writhing mass of dark brown fur, the creature resembles a "+
      "wolf, given its long maw and canine-like ears. A pair of strong, "+
      "muscled arms reach down almost to the bottom of its four and a half foot "+
      "height. A large black mane, akin to that of a lion's, surrounds its "+
      "head, a study in hideousness. "+
      "Eyes that are as black as these caves stare back at you with a "+
      "maniacal intensity.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 20 + random(20));
   set_base_stat(3, 15);
   set_base_stat(4, 15);
   set_base_stat(5, 20);
   set_aggressive(1);
   set_attack_chance(50);
   set_knight_prestige(100);
   set_skill(SS_WEP_SWORD,50);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_PARRY,30);
   set_skill(SS_AWARENESS,50);
   set_act_time(6);
   add_act("emote gibbers incoherently.");
   add_act("growl all");
   add_act("snarl all");
   add_act("grin maniac");
   add_act("get all from corpse");
   add_act("get all coins");
   set_cact_time(6);
   add_cact("scream");
   add_cact("emote screams something incoherently.");
   add_prop(LIVE_I_SEE_DARK,5);
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(NPC_I_NO_RUN_AWAY,1);
   trig_new("%w 'drops' %s","react_drop");
}
void
arm_me()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object(CPASS(uc/wep/gibb_sword));
   item -> move(TO);
   command("wield all");
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("emote screams furiously, spittle flying everywhere.");
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
      command("cackle maniac");
   }
}
