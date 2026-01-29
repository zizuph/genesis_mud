/*
 * /d/Gondor/pelargir/docks/lighthouse4.c
 *
 * Copyright (C) April 22, 1998 by Ron Miller (Tyr)
 *
 * This is a new third landing in the lighthouse in Pelargir for the 
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

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
void
create_gondor()
{
    set_short("A landing on the lighthouse stairs");

    set_long(BSN("The stairs seem to wind eternally. They continue "+
        "both up and down from this landing. A small window offers "+
        "a glimpse to the north, over the city walls into the wilds "+
        "of Gondor."));

    add_prop(ROOM_I_INSIDE,1);

    add_item("stairs", BSN("Stairs lead both up and down from this "+
        "landing."));

    add_item( ({ "lighthouse", "structure" }) , BSN("This tall granite "+
        "tower was most likely constructed to warn passing ships of "+
        "some nearby danger."));

    add_item( ({ "tower", "granite tower" }) , BSN("A sturdy old structure, "+
        "this tower appears able to withstand even the fiercest of "+
        "storms."));

    add_item("floor", BSN("Large irregularly shaped slabs of flat "+
        "granite have been pieced together here to form the stairs "+
        "and floor of the landing. There are old footprints "+
        "in the dust here. Maybe someone does occasionally come "+
        "up here after all."));

    add_item( ({ "ceiling", "underside" }) , BSN("As with all spiral "+
        "staircases, the ceiling here is actually the underside of "+
        "the next level up."));

    add_item( ({ "landing", "third landing", "platform", "area", "level" }) , 
        BSN("This small platform has stairs leading farther up on one "+
        "end, and down on the other."));

    add_item( ({ "wall", "walls" }) , BSN("The walls of the tower have "+
        "been built of rough hewn blocks of granite from some nearby "+
        "quarry."));

    add_item("here", BSN("This is the third landing of the Pelargir "+
        "lighthouse."));

    add_item( ({ "end", "up" }) , BSN("The stairs at one end of this "+
        "landing continue to spiral upward toward the top of the "+
        "lighthouse."));

    add_item( ({ "top", "top of lighthouse" }) , BSN("The spiral shape "+
        "of the staircase makes it impossible to see to the top of "+
        "the lighthouse."));

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

    add_item( ({ "pelargir", "city", "city of pelargir", "southwest", "town" }) , 
        BSN("The city of Pelargir lies to the southwest, but when "+
        "facing this direction, only the northern city wall is "+
        "visible."));

     add_item( ({ "window", "small window", "opening" }) , BSN("Incredibly, "+
        "there is actually still a pane in this window.  Between the "+
        "dried rain streaks it is possible to see beyond the city "+
        "walls."));

    add_item( ({ "pane", "glass" }) , BSN("Clearly neglected for years, "+
        "this window bears the streaks of many rainstorms, not to "+
        "mention a thick accumulation of dust."));

    add_item( ({ "footprint", "footprints" }) , BSN("Someone seems to have "+
        "left footprints in the dust here fairly recently."));

    add_item( ({ "someone", "whoever" }) , BSN("Whoever left these "+
        "footprints in the dust is no longer here."));

    add_item( ({ "dust", "layer", "everything" }) , BSN("A fine layer of "+
        "dust coats almost everything here."));

    add_item( ({ "streaks", "rain streaks", "grit" }) , BSN("The glass in "+
        "this window is smudged with the grit left behind by dozens of "+
        "rainstorms."));

    add_item( ({ "gondor", "wilds", "wilds of gondor", "direction", "glimpse",
        "view", "north" }) , BSN("This landing  is up high enough to "+
        "afford a view over the northern wall of the city. The main "+
        "road seems to head toward the northeast after it leaves the "+
        "city. There also appears to be a small hut east of the main "+
        "road not too far outside of the town."));

    add_item( ({ "city wall", "city walls", "northern wall", "perimeter",
        "stone wall" }) , BSN("The landward perimeter of Pelargir is "+
        "protected by a tall stone wall."));

    add_item( ({ "gate", "city gate", "city gates" }) , BSN("The gates "+
        "of the city are not visible from this side of the of the "+
        "lighthouse."));

    add_item( ({ "northeast", "road", "breaks" }) , BSN("Occasionally "+
        "visible in breaks between the trees, the road makes its way "+
        "toward the northeast."));

    add_item( ({ "tree", "trees", "countryside" }) , BSN("Trees cover the "+
        "countryside beyond the northern city walls."));

    add_item( ({ "hut", "small hut", "blur" }) , BSN("The tiny hut is so "+
        "distant that it is only a blur."));

    add_exit("lighthouse5", "up", 0, 4);
    add_exit("lighthouse3", "down", 0, 4);
} /* end create_gondor */
