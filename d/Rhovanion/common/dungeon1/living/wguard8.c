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
   set_adj("muscle-bound");
   set_adj("gigantic");
   set_long("This eight foot tall monstrosity is bulging " +
      "with muscles.  He looks ready to tear you apart!\n");
   set_gender(2);
   set_alignment(-90);
   set_aggressive(0);
   set_stats(({ 100, 35, 110, 30, 60, 55 }));
   set_hp(100);
   set_skill(SS_WEP_CLUB, 55);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 40);
   set_skill(SS_UNARM_COMBAT, 50);
   set_act_time(5);
   add_act("emote flexes its muscles in front of your face!");
   add_act("emote whirls its weighted iron chain by your " +
      "and laughs!");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   seteuid(getuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/wchain.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/whelmet.c")
   ->move(TO);
   command("wear all");
   command("wield all");
   return 1;
}
