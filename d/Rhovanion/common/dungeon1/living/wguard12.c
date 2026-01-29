inherit "/std/monster";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <macros.h>
#include <money.h>
#include <language.h>
void
create_monster() {
   set_name("goraaz");
   set_race_name("wyrmman");
   set_adj("blue-skinned");
   set_adj("dark");
   set_long("This formidable creature is over seven feet " +
      "tall and by the looks of him...  Very strong!  He " +
      "peers out at you from behind solid white eyes.\n");
   set_title("the Second of the Master and Knightbane of the Realm");
   set_gender(0);
   set_aggressive(0);
   set_alignment(-500);
   set_hp(500);
   set_stats(({ 90, 100, 90, 75, 85, 70 }));
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 65);
   set_skill(SS_UNARM_COMBAT, 50);
   set_skill(SS_WEP_SWORD, 75);
   set_skill(SS_2H_COMBAT, 75);
   trig_new("%s 'attacks' %s","part_fight");
   trig_new("%s 'introduces' %s","intro_me");
   set_alarm(0.0,0.0,"get_stuff");
}
part_fight() {
   command("emote narrows his white eyes mercilessly.");
   set_aggressive(1);
   return 1;
}
intro_me(){
   set_alarm(1.0,0.0,"intro_me2");
   return 1;
}
intro_me2() {
   command("introduce myself");
   return 1;
}
get_stuff() {
   object ob1;
   object ob2;
   seteuid(geteuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/warmour3.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wbuckler2.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wbelt.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wboots.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/whelmet.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wnecklace.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wsword4.c")
   ->move(TO);
   ob1 = MONEY_MAKE(25, "silver")->move(TO);
   ob2 = MONEY_MAKE( 2, "gold")->Move(TO);
   command("wear all");
   command("wield all");
   return 1;
}
