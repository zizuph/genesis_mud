#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("slave");
    set_race_name("human");
    set_adj("downtrodden");
    set_long("A filthy-looking human being that looks like he has had the "+
      "very life sucked out of him. Even as you examine him, it doesn't seem "+
      "to register within him that you are here, so out of sync is he with "+
      "the world.\n");
    set_stats(({60, 50, 60, 50, 50, 40}));
    set_alignment(-250);

    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_DEFENCE, 50);
    set_skill(SS_PARRY, 50);
    set_skill(SS_SNEAK, 70);

    add_leftover("/std/leftover", "skull", 1, 0, 1, 1);

    set_act_time(6);
    add_act("stare");
    add_act("groan");
    add_act("sniff");
    add_act(({"sneak down", "wield knife"}));
    add_act(({"unwield knife", "up"}));

    set_knight_prestige(250);
    set_alarm(1.0, 0.0, "arm_me");
}

void
arm_me()
{
    object wep;
    seteuid(getuid(this_object()));
    wep = clone_object(WEP + "bhsknife");
    wep->move(this_object());
}
