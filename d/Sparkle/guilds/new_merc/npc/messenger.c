/*
 *  /d/Sparkle/guilds/new_merc/npc/cook.c
 *
 *  This is Harold, the cook who works the kitchens of the Mercenary
 *  Guild. 
 *
 *  Created September 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/npc/sparkle_npc";
inherit "/d/Genesis/lib/intro";

#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>

#include "../merc_defs.h"


/* Prototypes */
public void        create_monster();


/* 
 * Function name:       create_sparkle_npc
 * Description  :       This function overrides the one in the base class
 * Arguments    :       none
 * Returns      :       void/nothing
 */
public void
create_monster()
{
    set_living_name("feristam");
    set_name("feristam");
    set_race_name("human");
    add_adj( ({ "weathered", "dark-haired" }) );

    set_title("the Wanderer, Field Agend for the Dagarim Aran");

    set_short("weathered dark-haired human");
    set_long("There is a hidden strength apparent in this man's eyes.\n");

    set_stats( ({ 150, 150, 150, 150, 150, 150 }) );
    set_alignment(1200); /* A good-natured fellow. */

    remove_prop(LIVE_I_NEVERKNOWN);

    setuid();
    seteuid(getuid());
} /* create_monster */   
