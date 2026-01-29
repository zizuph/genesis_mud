#include "default.h"
inherit "/d/Kalad/std/monster";

void
create_kalad_monster()
{
    set_name("servant");
    set_race_name("human");
    set_adj("servile");
    set_long("A skinny-looking individual that looks like he needs "+
      "several good meals. He is diligently cleaning his surroundings.\n");
    set_stats(({20, 30, 20, 20, 20, 15}));
    set_alignment(500);
    set_skill(SS_WEP_CLUB, 30);
    set_act_time(6);
    add_act("emote sweeps the floor.");
    add_act("emote wipes the sweat from his brow.");
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_speak("The master expects every room to be clean.\n");
    set_knight_prestige(-5);

    equip(({ ARM + "tcsshirt", WEP + "tcsbroom" }));
    
    MONEY_MAKE_CC(random(10))->move(TO);
}

