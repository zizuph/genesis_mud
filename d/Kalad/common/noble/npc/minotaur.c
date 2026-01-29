/*
    minotaur.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    set_name("minotaur");
    set_adj("brutish");
    add_adj("furious");
    set_race_name("minotaur");
    set_long("This raging creature has the head of a bull, but the body "+
        "of a muscled giant. It roars with fury, and swings its axe at anything "+
        "that moves. It smells putrid, and flies buzz around its fur.\n");

    set_alignment(-400);
    set_knight_prestige(-200);

    set_stats(({120,100,130,60,60,100}));

    set_aggressive(1);

    set_skill(SS_WEP_AXE,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,70);
    set_skill(SS_PARRY,100);

    set_cact_time(3);
    add_cact("emote snorts.");
    add_cact("roar");
    add_cact("emote grunts.");
    add_cact("glare all");

    add_prop(LIVE_I_NEVERKNOWN,1);

    set_hitloc_unarmed(0,40,20,"head");
    set_hitloc_unarmed(1,50,40,"body");
    set_hitloc_unarmed(2,40,30,"legs");
    set_hitloc_unarmed(3,40,5,"right arm");
    set_hitloc_unarmed(4,40,5,"left arm");

    add_equipment(({
        NOBLE + "wep/lochaber_axe",
        }));
}
