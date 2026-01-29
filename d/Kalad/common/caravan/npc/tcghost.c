#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("ghost");
    set_race_name("ghost");
    set_adj("wandering");
    set_long("All you see is a strange figure dressed in tattered robes "+
      "that is slowly wandering up and down these halls.\n");
    set_stats(({50, 75, 50, 75, 75, 50}));
    set_alignment(-1200);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_BLIND_COMBAT, 50);
    add_prop(OBJ_I_INVIS, 1);
    set_act_time(3);
    add_act("moan");
    add_act("groan");
    add_act("chuckle evilly");
    add_act("laugh evilly");
    add_act("say I shall kill you slowly...ever so slowly...");
    set_knight_prestige(900);
    set_random_move(10);
}
