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
   set_adj("large");
   set_gender(2);
   set_alignment(-100);
   set_aggressive(0);
   set_stats(({ 70, 60, 80, 30, 50, 40 }));
   set_hp(500);
   set_skill(SS_DEFENCE, 50);
   set_skill(SS_2H_COMBAT, 45);
   set_skill(SS_WEP_KNIFE, 45);
   set_skill(SS_BLIND_COMBAT, 75);
   set_skill(SS_PARRY, 45);
   add_prop(CONT_I_WEIGHT, 99000);
   add_prop(CONT_I_HEIGHT, 2200);
   add_prop(CONT_I_VOLUME, 85000);
   set_act_time(5);
   add_act("emote smiles ever so slightly and narrows its eyes " +
      "at your approach.");
   add_act("emote clenches its fists and then relaxes them again.");
   add_act("emote clenches its fists and then relaxes them again.");
   set_alarm(1.0,0.0,"get_stuff");
}
get_stuff() {
   int i;
   object ob1;
   seteuid(getuid());
   clone_object("/d/Rhovanion/common/dungeon1/gear/lclaw.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/rclaw.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/warmour1.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/whelmet.c")
   ->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/gear/wboots.c")
   ->move(TO);
   ob1 = MONEY_MAKE(48, "silver")->move(TO);
   command("wield all");
   command("wear all");
   return 1;
}
