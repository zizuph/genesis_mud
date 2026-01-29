// file name:     zigg_overseer.c
// creator(s):    Lilith   09/26/97
// purpose:       Flag down sedan chairs
/*
 * Revisions:
 * 	Lucius, Sep 2017: Changed to use base overseer.
 */
#pragma strict_types

#include "/d/Avenir/include/paths.h"
inherit (CITY + "mon/overseer");

/* Create the npc */
public void
create_monster(void)
{
    loc_str = "leaving the Ziggurat";
    chair_path = CITY + "mon/zigg_chair";

    ::create_monster();

    add_act("say Are you ready to leave?");
    add_act("say The Ziggurat awaits...");
    add_act("say The Ziggurat entrance is up those stairs.");
}
