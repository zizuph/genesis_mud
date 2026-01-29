


inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>


create_monster() {
   set_name("dwarf");
   set_short("small dwarf");
   set_race_name("dwarf");

   set_alignment(-1000);
   set_long(
      "He is dressed in tattered clothes. He looks like he's been\n"+
      "on the run for a while.\n");
   add_prop(CONT_I_WEIGHT, 300*1000);
   add_prop(CONT_I_HEIGHT, 400);
    set_stats(({36,30,45,67,25,80}));
   set_hp(1000);

   set_skill(SS_UNARM_COMBAT, 40);
   set_skill(SS_WEP_CLUB,     40);
   set_skill(SS_DEFENCE,      45);
   set_skill(SS_PARRY,        40);
   set_pick_up(43);
   set_aggressive(1);
   set_attack_chance(87);

   set_alignment(-20);
   set_act_time(6);
   add_act("smirk");
   add_act("finger all");
   add_act(({"fume", "stomp"}));

   set_cact_time(7);
    add_cact("scream");
   add_cact("fume");

}


