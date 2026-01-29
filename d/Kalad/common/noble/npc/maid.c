/*
    maid.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"

void
create_kalad_monster()
{
    object arm;
    
    set_name("dotty");
    set_adj("happy");
    add_adj("bouncy");
    add_name("maid");
    set_race_name("human");
    set_short("happy bouncy maid");
    set_long("This beautiful slave girl is dressed as a maid. She does "+
        "her mundane chores with vigor. With cute short blonde hair, "+
        "adorable pouting lips, and a wonderful figure, you believe she "+
        "pleases her Master well.\n");
    set_stats(({50,50,50,40,50,40}));
    set_skill(SS_DEFENCE,30);
    set_alignment(600);
    set_knight_prestige(-300);
    set_act_time(5);
    add_act("emote dusts the bed.");
    add_act("giggle");
    add_act("emote polishes the table.");
    add_act("emote checks the candles.");
    add_act("say I hope Master is kind to me again today.");
    add_act("say I love my Master..");
    add_act("sigh");
    set_cact_time(3);

    add_cact("shout Help! Guards! Help!");
    set_gender(1);

    setuid();
    seteuid(getuid());

    arm = clone_object(NOBLE + "arm/cotton_skirt");
    arm->set_short("maid skirt");
    arm->move(TO);

    add_equipment(({
        NOBLE + "arm/cotton_tunic",
        }));
}
