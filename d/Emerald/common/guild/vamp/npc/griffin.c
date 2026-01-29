/*
 * /d/Emerald/common/guild/vamp/npc/griffin.c"
 * 
 * A poor lost soul wandering in the mists outside of the
 * Vampire guild in Emerald.
 *
 * Copyright (c) October 2000, by Cooper Sherry (Gorboth)
 */

#pragma strict_types

inherit "/d/Emerald/common/guild/vamp/npc/lost_player.c";

#include <const.h>
#include <ss_types.h>
#include <stdproperties.h>


/* prototypes */
public void        create_lost_player();


/*
 * Function name:        create_lost_player()
 * Description  :        set up the npc
 */
public void
create_lost_player()
{
    set_name("griffin");
    set_living_name("griffin");
    add_name( ({ "jon", "john", "nite" }) );
    set_race_name("human");
    set_gender(G_MALE);
    set_adj( ({ "long-necked", "nasal" }) );

    set_stats(({80+random(50), 80+random(50), 100+random(30),
                50+random(50), 40+random(50), 70+random(50)}));
    set_alignment(random(500));
    set_title("of Nite, Calian Warrior");

    remove_prop(LIVE_I_NEVERKNOWN);
} /* create_lost_player */
