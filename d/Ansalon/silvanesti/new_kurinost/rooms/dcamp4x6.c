/*
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
public int ascend_path();

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
         drac4->set_skill(SS_AWARENESS, 60);
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
    generate_path("up north into the fortified encampment, " +
        "and southeast down a trail leading towards a great forest.");

    set_short("Before a fortified encampment overlooking " +
        "the elven kingdom of Silvanesti");
    set_long("You stand in front of a fortified encampment that overlooks " +
        "the fabled forest kingdom of the Silvanesti " +
        "elves. The encampment to your north is nestled beneath the cliffs in " +
        "eternal shade and surrounded by a crude palisade, with a slender white " +
        "tower the only structure tall enough to rise above it and the shade to " +
        "catch the " + show_tower_light() + ". A path leads down from here " +
        "towards the edge of the forest to your southeast.\n");

    add_item(({"path", "dirt path"}),
        "A dirt path leads from the encampment here down to the edge of the " +
        "forest kingdom of the Silvanesti elves.\n");

    add_exit(RSROOMS + "dcamp4x5", "north", ascend_path, 3);
    add_exit(RSROOMS + "forest_path1", "southeast");

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
ascend_path()
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


