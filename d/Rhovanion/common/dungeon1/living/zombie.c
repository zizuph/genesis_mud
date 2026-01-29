inherit "/std/monster";
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
void
create_monster() {
   set_name("zombie");
   add_name("giant");
   set_race_name("horror");
   set_adj("zombie");
   set_adj("giant");
   set_long("This twelve foot tall monstrous undead creature " +
      "is rotting everywhere on its body.  The smell is ungodly! " +
      "You feel oddly afraid as prepares to tear you limb from limb.\n");
   set_gender(2);
   set_alignment(-700);
   set_aggressive(1);
   set_stats(({ 125, 50, 80, 20, 50, 70 }));
   set_hp(500);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 50);
   set_skill(SS_WEP_CLUB, 50);
   set_skill(SS_UNARM_COMBAT, 30);
   add_prop(LIVE_I_SEE_DARK, 5);
   add_prop(CONT_I_WEIGHT, 130000);
   add_prop(CONT_I_HEIGHT, 2459);
   add_prop(CONT_I_VOLUME, 125000);
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   seteuid(getuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/zarm.c")
   ->move(TO);
   command("wield all");
}
