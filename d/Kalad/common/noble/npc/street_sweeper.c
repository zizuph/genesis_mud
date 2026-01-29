/*
    street_sweeper.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("street-sweeper");
    set_adj("poor");
    add_adj("skinny");
    set_race_name("human");
    set_short("poor skinny street-sweeper");
    set_long("This poor man looks like a slave. He roams the roads "+
        "of the noble district sweeping up the streets and throwing trash "+
        "away. He is skinny and looks tired.\nHe is holding a broom.\n");

    set_alignment(200);
    set_knight_prestige(-60);

    add_speak("I don't get much food these days, I need to work harder "+
        "they say...\n");
    set_stats(({40,50,30,20,20,10}));
    set_skill(SS_DEFENSE,30);

    set_random_move(1);

    set_act_time(4);
    add_act("emote sweeps the street with his broom.");
    add_act("emote bends down and picks up some trash.");
    add_act("emote dusts the road carefully.");

    add_prop(LIVE_I_NEVERKNOWN,1);

    add_equipment(({
        NOBLE + "arm/torn_tunic",
        }));
}

