/*
 * dcamp5x1.c
 *
 * Draconian camp  -  05 x 01
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "local.h"

inherit CAMPBASE;

// G L O B A L   V A R S

// P R O T O T Y P E S
public int descend_path();

object drac1, drac2, drac3, drac4;

#define DRAC "/d/Krynn/std/sivak"

void
reset_kurinost_room()
{
     if (!objectp(drac1)) 
     {
         drac1 = clone_object(DRAC);
         drac1->set_color("green");
         drac1->move(TO, 1);
     }

     if (!objectp(drac2)) 
     {
         drac2 = clone_object(DRAC);
         drac2->set_color("green");
         drac2->move(TO, 1);
     }

     if (!objectp(drac4)) 
     {
         drac4 = clone_object("/d/Krynn/std/bozak");
         drac4->set_skill(SS_AWARENESS, 75);
         drac4->set_color("green");
         drac4->move(TO, 1);
     }

     if (!objectp(drac3)) 
     { 
         drac3 = clone_object(RSLIVING + "sivak_leader");
         drac3->set_color("green");
         drac3->move(TO, 1);
     }

}

/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    // Set up basic camp descriptions.
    generate_camp(DCAMP_BROKENPATH, "");

    // Set up descriptions about the paved path.
    generate_path("south into the fortified encampment, " +
        "and upwards into a shadowy pass in the cliffs to your " +
        "northwest.");

    set_short("Before a fortified encampment guarding the pass into " +
        "the elven kingdom of Silvanesti");
    set_long("You stand before a fortified encampment, guarding " +
        "the northern pass into the forest kingdom of the Silvanesti " +
        "elves. Nestled beneath the cliffs in eternal shade, the " +
        "camp huddles close to a slender white tower that is tall enough " +
        "to catch the " + show_tower_light() + ". The camp is circled by " +
        "a crude palisade, with smoke from a few scattered " +
        "campfires rising from within it into the " + show_season_air() + 
        " air.\n");

    add_exit(RSROOMS + "dcamp5x2", "south", descend_path, 3);
    add_exit(RSROOMS + "rs2x6", "northwest");

    setup_tells();
    KURINOSTMAP;

    reset_kurinost_room();
}

/*
 *  FUNCTION : descend_path
 *  Arguments: none
 *  Returns  : int - 0, always allow move.
 * 
 *  Called when you walk down the path. Show additional description
 *  of the path.
 *
 */
public int
descend_path()
{
    if(objectp(drac4) && CAN_SEE(drac4, TP))
    {
       drac4->command("emote blocks the way into the encampment.");
       return 1;
    }

    write("You pass through the palisade and into the dragonarmy " +
        "encampment.\n");
    return 0;
}


