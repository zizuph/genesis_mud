

inherit "/std/monster";

#include <macros.h>
#include <ss_types.h>
#include <language.h>
#include <stdproperties.h>

create_monster() {
   set_name(({"rogue","wild hippy human", "wild human","hippy human"}) );
   set_short("wild hippy human");
   set_race_name("human");
   set_long("He has very long hair and looks to be very dirty.\n");
   add_prop(CONT_I_WEIGHT, 300*1000);
   add_prop(CONT_I_HEIGHT, 400);
   set_stats(({200,60,200,1,1,1}));
   set_hp(1000);

   set_skill(SS_UNARM_COMBAT, 40);
   set_skill(SS_DEFENCE,      45);
   set_skill(SS_PARRY,        40);
   set_pick_up(43);
   set_aggressive(1);
   set_attack_chance(87);

   set_act_time(6);
   add_act("smirk");
   add_act("say F*ck off!!!");
   add_act(({"spit all","grin"}));

   set_cact_time(7);
   add_cact("gasp");
   add_cact("emote slaps your face hard!");
   add_cact("tremble");

}

