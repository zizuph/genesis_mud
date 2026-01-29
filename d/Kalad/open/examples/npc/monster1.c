inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
create_monster()
{
   ::create_monster();
   set_name("monster");
   set_race_name("monster");
   set_adj("tall");
   set_long("A big, nasty monster.\n");
   set_stats(({20,30,20,5,5,15}));
   set_skill(SS_WEP_SWORD,30);
   set_skill(SS_DEFENCE,30);
   set_skill(SS_AWARENESS,20);
   set_act_time(6);
   add_act("say Hi! I'm a monster!");
   add_act("fart");
   set_cact_time(6);
   add_cact("say Why are you attacking me?");
   add_speak("I'm an example monster, what are you?\n");
   set_alarm(1.0,0.0,"my_equipment");
}
my_equipment()
{
   object item;
   seteuid(getuid(TO));
   item = clone_object("/d/Kalad/open/examples/wep/weapon1");
   item -> move(TO);
   command("wield all");
   item = clone_object("/d/Kalad/open/examples/arm/armour1");
   item -> move(TO);
   command("wear all");
   MONEY_MAKE_CC(random(50))->move(TO,1);
}
