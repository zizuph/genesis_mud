inherit "/std/monster";
#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
#include <money.h>
void
create_monster() {
   set_name("skeleton");
   set_race_name("skeleton");
   set_adj(ONE_OF_LIST(({"human","dwarf","elf","hobbit",
               "gnome","orc","goblin","ogre","wyrmman"})));
   set_adj("animated");
   set_long("This filthy undead being is clothed " +
      "only in the tatters of the clothing it wore in " +
      "life.  Its eyes burn with hatred for the living.\n");
   set_gender(2);
   set_aggressive(1);
   set_alignment(-200);
   set_stats(({ 35, 30, 50, 10, 10, 35 }));
   set_skill(SS_DEFENCE, 40);
   set_skill(SS_PARRY, 45);
   set_skill(SS_WEP_SWORD, 35);
   set_skill(SS_WEP_POLEARM, 35);
   set_skill(SS_WEP_CLUB, 40);
   set_alarm(0.0,0.0,"get_stuff");
}
get_stuff() {
   clone_object(ONE_OF_LIST(({
               "/d/Rhovanion/mute/dungeon1/sksword.c",
               "/d/Rhovanion/mute/dungeon1/skspear.c",
               "/d/Rhovanion/mute/dungeon1/skclub.c"})))->move(TO);
   command("wield all");
   return 1;
}
