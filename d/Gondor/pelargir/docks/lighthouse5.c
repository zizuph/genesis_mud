/*
 * /d/Gondor/pelargir/docks/lighthouse5.c
 *
 * Copyright (C) April 27, 1998 by Ron Miller (Tyr)
 *
 * This is a new fourth landing in the lighthouse in Pelargir for the 
 * creation of a quest to restore the warning beacon.
 * 
 * Revision History:
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"


int
closed_for_repairs ()
{
  write("The lamproom is closed for repairs right now.\n");
  return 1;
}

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("On the lighthouse stairs");

    set_long(BSN("The top of the stairs is in sight, yet they "+
        "continue both up and down. The window on this landing "+
        "faces west toward the city of Pelargir."));

    add_item( ({ "top", "top of stairs", "sight" }) , BSN("The stairs "+
        "appear to end at the next level up."));

    add_item( ({ "next level", "level up" }) , BSN("The top of the "+
        "lighthouse is now in sight."));

    add_item("window", BSN("This window is actually in fairly "+
        "good condition. It faces the city of Pelargir."));

    add_item( ({ "city", "pelargir", "city of pelargir", "view", "west",
        "direction", "outdoors", "place" }) , BSN("The view from this "+
        "window is to the west. The houses in that direction are mostly "+
        "simple dwellings, save one which has all the aspects of a "+
        "mansion."));

    add_item( ({ "house", "houses", "dwelling", "dwellings", "neighborhood",
        "simple dwellings", "others", "community" }) , BSN("There is "+
        "nothing special about these rather plain little houses. "+
        "However the one farthest to the west is larger than the "+
        "others."));

    add_item( ({ "large house", "larger house", "west house", "last house",
        "mansion", "one" }) , BSN("A rather large house, which appears "+
        "oddly out of place in a neighborhood of relatively simple "+
        "dwellings. The owner must surely be a very important person "+
        "in this community."));

    add_item( ({ "owner", "person" }) , BSN("The owner of the mansion is "+
        "not outdoors at the moment."));

    add_item( ({ "lighthouse", "structure" }) , BSN("This tall granite "+
        "tower was most likely constructed to warn passing ships of "+
        "some nearby danger."));

    add_item( ({ "tower", "granite tower" }) , BSN("A sturdy old structure, "+
        "this tower appears able to withstand even the fiercest of "+
        "storms."));

    add_item("floor", BSN("Large irregularly shaped slabs of flat "+
        "granite have been pieced together here to form the stairs "+
        "and floor of the landing. There are old footprints "+
        "in the dust here.  Maybe someone does occasionally come "+
        "up here after all."));

    add_item( ({ "ceiling", "underside" }) , BSN("As with all spiral "+
        "staircases, the ceiling here is actually the underside of "+
        "the next level up."));

    add_item( ({ "landing", "fourth landing", "platform", "area" }) , 
        BSN("This small platform has stairs leading farther up on one "+
        "end, and down on the other."));

    add_item("here", BSN("This is the fourth landing of the Pelargir "+
        "lighthouse."));

    add_item( ({ "end", "up" }) , BSN("The stairs at one end of this "+
        "landing continue to spiral upward toward the top of the "+
        "lighthouse."));   

    add_item( ({ "other", "other end", "down" }) , BSN("The stairs at one "+
        "end of the landing spiral downward out of sight."));

    add_item( ({ "granite", "pieces", "stone", "stones", "flagstone",
        "flagstones", "slab", "slabs", "block", "blocks" }) , BSN("The grainy "+
        "gray stone used in the construction this lighthouse appears to "+
        "have been chosen more for its hardness and durability than its "+
        "aesthetic appeal."));

    add_item("stonework", BSN("The tower of the lighthouse is built "+
        "almost entirely of stone."));

    add_item( ({ "stairs", "stone stairs", "staircase", "spiral",
        "spiral staircase", "climb", "grueling climb" }) , BSN("These "+
        "winding stone stairs make for a long and grueling climb."));

    add_item( ({ "tower wall", "tower walls" }) , BSN("The walls of the "+
        "tower have been built of rough hewn blocks of granite from "+
        "some nearby quarry. Wall-mounted torches provide what meager "+
        "light there is here."));

    add_item( ({ "torch", "torches", "light" }) , BSN("Oil-burning torches "+
        "are mounted intermittently along the walls of the staircase. "+
        "Some appear to have gone out long ago. The few that still "+
        "flicker barely provide enough light to continue the climb."));    

    add_item( ({ "storm", "storms", "weather", "rainstorm", "rainstorms" }) ,
        BSN("Though the weather is fair at the moment, it would be "+
        "dangerous to underestimate the power of the fierce storms "+
        "that sometimes rage against this lighthouse."));

    add_item("quarry", BSN("The quarry from which the stones of this "+
        "tower were cut is not visible from the port area."));

    add_item( ({ "south", "port", "port area", "area", "harbour", "ships",
        "danger", "nearby danger", "port of pelargir", "pelargir harbour" }) , 
        BSN("The port of Pelargir lies to the south, but is not "+
        "visible when facing this direction."));

    add_exit("lamproom", "up", 0, 4);
    add_exit("lighthouse4", "down", 0, 4);
} /* end create_gondor */
