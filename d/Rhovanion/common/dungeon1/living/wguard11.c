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
   set_name("guard");
   set_race_name("wyrmman");
   set_adj("reptilian");
   set_adj("solemn");
   set_long("These beast-like men are standing perfectly " +
      "still blocking passage east down the corridor.\n");
   set_gender(2);
   set_aggressive(0);
   set_alignment(-150);
   set_stats(({ 60, 90, 60, 60, 60, 65 }));
   set_hp(200);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_PARRY, 30);
   set_skill(SS_UNARM_COMBAT, 40);
   set_skill(SS_WEP_POLEARM, 60);
   trig_new("%s 'attacks' %s","part_fight");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   seteuid(geteuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/warmour1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/whelmet.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wboots.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wspear.c")
   ->move(TO);
   command("wield all");
   command("wear all");
   return 1;
}
part_fight() {
   command("emote narrows its eyes.");
   set_aggressive(1);
   return 1;
}
