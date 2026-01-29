#include "default.h"
inherit "/d/Kalad/std/monster";

#define A_BITE 0
#define H_BODY 0

void
create_kalad_monster()
{
    set_name("bug");
    set_race_name("termite");
    set_adj("large");
    set_long("A gigantic termite, the size of this bug is almost "+
      "unbelievable. It must be as large as your fist!\n");
    set_gender(G_NEUTER);
    set_stats(({5, 10, 5, 6, 6, 8}));
    set_skill(SS_DEFENCE, 10);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_M_NO_INS, 1);
    set_aggressive(1);
    set_random_move(10);
    set_act_time(9);
    add_act("emote munches on some wood.");
    add_act("emote scuttles around the room.");
    set_attack_unarmed(A_BITE, 5, 5, W_IMPALE, 100, "pincers");
    set_hitloc_unarmed(H_BODY, ({ 5, 5, 6 }), 100, "body");
}
