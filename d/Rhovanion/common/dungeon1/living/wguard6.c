inherit "/std/monster";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
void
create_monster() {
   set_name("guard");
   set_race_name("wyrmman");
   set_adj("reptilian");
   set_adj("short");
   set_long("This short creature appears to be part " +
      "wyrm and perhaps part human.  Horns protrude from all " +
      "over its head and its skin is leathery and dark grey. " +
      "Claws extend from its hands and feet and its mouth is filled " +
      "with vicious white teeth.\n");
   set_gender(2);
   set_alignment(-90);
   set_aggressive(0);
   set_stats(({ 50, 30, 50, 50, 50, 35 }));
   set_hp(100);
   set_skill(SS_WEP_CLUB, 39);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_DEFENCE, 45);
   set_skill(SS_PARRY, 20);
   set_skill(SS_UNARM_COMBAT, 25);
   set_act_time(5);
   add_act("emote tosses its warhammer in the air and " +
      "catches it again with ease.");
   add_act("emote smiles slyly");
   set_cchat_time(10);
   add_cchat("emote goes Ha Ha HEEeee! as it flips its " +
      "warhammer over in its hand and charges at you!");
   add_cchat("emote slams into you with amazing ferocity!");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   ob1 = MONEY_MAKE(30, "copper")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wwarhammer.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wshirt.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wpants2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wboots.c")
   ->move(TO);
   command("wield all");
   command("wear all");
   return 1;
}
