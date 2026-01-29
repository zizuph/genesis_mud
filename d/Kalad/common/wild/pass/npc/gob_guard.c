/* 
 * /d/Kalad/common/wild/pass/npc/gob_guard.c
 * Purpose    : A goblin guard
 * Located    : /d/Kalad/common/wild/pass/goblin/
 * Created By : Antharanos ??.??.??
 * Modified By: 
 */ 

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
#include "/d/Kalad/defs.h"
string
random_extra()
{
   int i;
   i = random(7);
   if(i < 1)
      return "sneaky";
   else if(i < 2)
      return "brutal";
   else if(i < 3)
      return "malicious";
   else if(i < 4)
      return "demonic";
   else if(i < 5)
      return "savage";
   else if(i < 6)
      return "malevolent";
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
   set_name("goblin");
   set_race_name("goblin");
   set_adj(extra);
   set_long("A filthy, scabberous goblin. It glares at you with an "+
      "unnerving amount of intelligence in its beady red eyes, giving you the "+
      "impression that perhaps goblins aren't as stupid as most people "+
      "portray them to be.\n");
   for(i = 0; i < 3; i++)
   set_base_stat(i, 50 + random(50));
   set_base_stat(3, 50);
   set_base_stat(4, 50);
   set_base_stat(5, 40);
   set_alignment(-500);
   set_knight_prestige(500);
   set_skill(SS_WEP_SWORD,80);
   set_skill(SS_WEP_CLUB,80);
   set_skill(SS_DEFENCE,60);
   set_skill(SS_PARRY,70);
   set_skill(SS_AWARENESS,40);
   set_skill(SS_2H_COMBAT,50);
   set_act_time(6);
   add_act(({"say Let's kill some more humans!","kill human"}));
   add_act("growl");
   add_act("tackle all");
   add_act("grin");
   add_act("fart");
   add_act("get all from corpse");
   set_cact_time(6);
   add_cact("snarl all");
   add_cact("say I'll feed ya to my stomach!");
   add_cact("laugh evil");
   add_prop(LIVE_I_SEE_DARK,5);
   set_alarm(1.0,0.0,"my_stuff");
   trig_new("%w 'drops' %s","react_drop");
}
void
my_stuff()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object("/d/Kalad/common/wild/pass/arm/gg_mail");
   item -> move(TO);
   item = clone_object("/d/Kalad/common/wild/pass/arm/gg_boots");
   item -> move(TO);
   item = clone_object("/d/Kalad/common/wild/pass/arm/gg_helm");
   item -> move(TO);
   command("wear all");
   item = clone_object("/d/Kalad/common/wild/pass/wep/gg_sword");
   item -> move(TO);
   item = clone_object("/d/Kalad/common/wild/pass/wep/gg_club");
   item -> move(TO);
   command("wield all");
   MONEY_MAKE_SC(random(25))->move(TO,1);
}
void
help_friend(object ob)
{
   if(ob && !query_attack() && present(ob, environment()))
      {
      command("say Ye stupid " + TP->query_nonmet_name() + "!");
      command("say Looks like it's " + TP->query_race_name() + " fer dinner!");
      command("kill " + (ob->query_real_name()));
   }
}
public void
introduce_me(string who)
{
    object obj;

    if(!(obj = present(who, environment()))) return;
    command("spit");
    command("say I don't give a damn who you are, ya stupid "+obj->query_race_name()+"!!");
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
      command("grin greed");
   }
}
