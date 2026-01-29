/*
    castle_squire.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

void
create_kalad_monster()
{
    set_name("squire");
    set_adj("stout");
    set_race_name("human");
    set_short("stout squire");
    set_long("This young man seems proud to be a servant of the "+
        "great knights of the High-Lord. He does his Master's every "+
        "wish with a smile.\n");

    set_alignment(500);
    set_knight_prestige(-300);
    add_speak("I am proud to serve my Master-Knight!\n");
    set_stats(({80,85,78,55,67,65}));
    set_skill(SS_WEP_SWORD,50);
    set_skill(SS_DEFENSE,60);
    set_skill(SS_AWARENESS,30);
    set_skill(SS_PARRY,40);
    set_act_time(5);

    add_act("emote tends to his sword.");
    add_act("emote studies a small scroll.");
    add_act("say I must get to my Master-Knight!");
    add_act("say My Master is the best knight in these realms!");
    add_act("say My Master once slew a dragon!");
    set_cact_time(3);

    add_cact("say HELP!");
    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_equipment(({
        NOBLE + "arm/dusty_cloak",
        NOBLE + "arm/cotton_tunic",
        NOBLE + "arm/leather_pants",
        NOBLE + "wep/steel_shortsword",
        }));

    MONEY_MAKE_CC(random(35))->move(TO);
}
