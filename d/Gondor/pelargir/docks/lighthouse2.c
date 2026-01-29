/*
 * /d/Gondor/pelargir/docks/lighthouse2.c
 *
 * Copyright (C) 1998 by Ron Miller (Tyr)
 *
 * This is a rewrite of the first landing in the lighthouse in Pelargir 
 * at the creation of a quest to restore the warning beacon.
 * 
 * Revision History:
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
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

    set_long(BSN("The very long and tiring circular staircase inside "+
        "the lighthouse has its first landing here. There is little of "+
        "interest here except a small window overlooking the harbour."));

    add_prop(ROOM_I_INSIDE,1);

    add_item( ({ "lighthouse", "structure" }) , BSN("This tall granite "+
        "tower was most likely constructed to warn passing ships of "+
        "some nearby danger."));

    add_item( ({ "tower", "granite tower" }) , BSN("A sturdy old structure, "+
        "this tower appears able to withstand even the fiercest of "+
        "storms."));

    add_item("floor", BSN("Large irregularly shaped slabs of flat "+
        "granite have been pieced together here to form the stairs "+
        "and floor of the landing. The humid river air coming in "+
        "through the broken window makes them moist and slippery."));

    add_item( ({ "ceiling", "underside" }) , BSN("As with all spiral "+
        "staircases, the ceiling here is actually the underside of "+
        "the next level up."));

    add_item( ({ "landing", "first landing", "platform", "area" }) , BSN("This "+
        "small platform has stairs leading farther up on one end, and "+
        "down on the other. The damp flagstones of the floor in this "+
        "area make for slippery footing."));

    add_item( ({ "granite", "pieces", "stone", "stones", "flagstone",
        "flagstones", "slab", "slabs", "block", "blocks" }) , BSN("The grainy "+
        "gray rock used in the construction this lighthouse appears to "+
        "have been chosen more for its hardness and durability than its "+
        "aesthetic appeal."));

    add_item( ({ "rock", "stonework" }) , BSN("The tower of the lighthouse "+
        "is built almost totally of stone."));

    add_item( ({ "stairs", "staircase", "spiral", "spiral staircase", "climb",
        "here" }) , BSN("These winding stone stairs make for a long and "+
        "grueling climb."));

    add_item( ({ "wall", "walls" }) , BSN("The walls of the tower have "+
        "been built of rough hewn blocks of granite from some nearby "+
        "quarry. Wall-mounted torches provide what meager light "+
        "there is here."));

    add_item( ({ "torch", "torches", "light" }) , BSN("Oil-burning torches "+
        "are mounted intermittently along the walls of the staircase. "+
        "Some appear to have gone out long ago. The few that still "+
        "flicker barely provide enough light to continue the climb."));

    add_item("window", BSN("Actually more of a tall vertical gap in "+
        "the stonework of the tower, this crude opening has neither "+
        "a casement nor glazing. The view is to the south, overlooking "+
        "the panorama of the harbour."));

    add_item( ({ "gap", "opening", "space" }) , BSN("The space between two "+
        "stones in the wall of the landing once held a window, which "+
        "has long since been broken and remains unrepaired."));

    add_item( ({ "casement", "frame" }) , BSN("All that remains of the "+
        "window that was once here is a splintered wooden frame and "+
        "a few slivers of broken glass."));

    add_item( ({ "glazing", "sliver", "slivers", "glass", "pane" }) , BSN("A "+
        "few slivers of broken glass lying in the opening are the only "+
        "evidence that there was ever a pane in this window."));

    add_item( ({ "harbour", "pelargir", "pelargir harbour", "panorama",
        "view", "port", "south" }) , BSN("This vantage point offers an "+
        "excellent view of the bustling port of Pelargir. Several "+
        "ships are preparing to dock, while others are clearly "+
        "preparing to set sail."));

    add_item( ({ "ship", "ships" }) , BSN("Though many of the ships in "+
        "the harbour carry the emblem of Gondor on their mainsails, "+
        "some are of unfamiliar construction and bear the markings "+
        "of foreign lands."));

    add_item( ({ "markings", "design" }) , BSN("Most of the ships bear a "+
        "distinctive design, denoting the country of their home "+
        "port."));

    add_item( ({ "tree", "large tree", "large white tree", "white tree",
        "tall tree", "symbol", "symbol of gondor", "emblem",
        "emblem of gondor" }) , BSN("The most widely recognized symbol "+
        "of Gondor, a tall white tree, surrounded by seven stars is "+
        "set on a field of black."));

    add_item("stars", BSN("There are seven stars encircling a White "+
        "Tree in the emblem of Gondor."));

    add_item( ({ "field", "field of black", "background" }) , BSN("The "+
        "background of the emblem of Gondor is a simple field of solid "+
        "black."));

    add_item( ({ "sail", "sails", "mainsail" }) , BSN("The primary sail of "+
        "every Gondorian vessel is decorated with the symbol of the "+
        "White Tree."));

    add_item("danger", BSN("The the harbour appears tranquil at the "+
        "moment. Perhaps the view in a different direction might "+
        "show the reason this lighthouse was built."));

    add_item( ({ "storm", "storms" }) , BSN("Though the weather is fair "+
        "at the moment, it would be dangerous to underestimate the "+
        "power of the fierce storms that sometimes rage against this "+
        "lighthouse."));

    add_item("quarry", BSN("The quarry from which the stones of this "+
        "tower were cut is not visible from the port area."));

    add_item( ({ "river", "anduin", "river anduin" }) , BSN("The Great "+
        "River, Anduin, lies to the east of the port, but is not "+
        "visible when facing this direction."));

    add_exit("lighthouse3", "up", 0, 4);
    add_exit("lighthouse1", "down", 0, 4);
} /* end create_gondor */
