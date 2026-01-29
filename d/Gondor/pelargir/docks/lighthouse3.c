/*
 * /d/Gondor/pelargir/docks/lighthouse3.c
 *
 * Copyright (C) April 22, 1998 by Ron Miller (Tyr)
 *
 * This is a new second landing in the lighthouse in Pelargir for the 
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

    set_long(BSN("The stairs wind both up and down from this landing. "+
        "A window on this side looks east toward the mighty Anduin."));

    add_prop(ROOM_I_INSIDE,1);

    add_item( ({ "lighthouse", "structure" }) , BSN("This tall granite "+
        "tower was most likely constructed to warn passing ships of "+
        "some nearby danger."));

    add_item( ({ "tower", "granite tower" }) , BSN("A sturdy old structure, "+
        "this tower appears able to withstand even the fiercest of "+
        "storms."));

    add_item("floor", BSN("Large irregularly shaped slabs of flat "+
        "granite have been pieced together here to form the stairs "+
        "and floor of the landing. The wind blowing through the "+
        "window opening has begun to dry the flagstone floor here."));

    add_item( ({ "ceiling", "underside" }) , BSN("As with all spiral "+
        "staircases, the ceiling here is actually the underside of "+
        "the next level up."));

    add_item( ({ "landing", "second landing", "platform", "area" }) , 
        BSN("This small platform has stairs leading farther up on one "+
        "end, and down on the other."));

    add_item( ({ "elevation", "here" }) , BSN("This is the second landing "+
        "of the Pelargir lighthouse."));

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

    add_item( ({ "wall", "walls" }) , BSN("The walls of the tower have "+
        "been built of rough hewn blocks of granite from some nearby "+
        "quarry. Wall-mounted torches provide what meager light "+
        "there is here."));

    add_item( ({ "torch", "torches", "light" }) , BSN("Oil-burning torches "+
        "are mounted intermittently along the walls of the staircase. "+
        "Some appear to have gone out long ago. The few that still "+
        "flicker barely provide enough light to continue the climb."));    
    add_item( ({ "storm", "storms", "weather" }) , BSN("Though the weather "+
        "is fair at the moment, it would be dangerous to "+
        "underestimate the power of the fierce storms that sometimes "+
        "rage against this lighthouse."));

    add_item("quarry", BSN("The quarry from which the stones of this "+
        "tower were cut is not visible from the port area."));

    add_item( ({ "south", "port", "port area", "area", "harbour",
        "port of pelargir", "pelargir harbour" }) , BSN("The port of "+
        "Pelargir lies to the south, but is not visible in this "+
        "direction."));

    add_item( ({ "pelargir", "city", "city of pelargir" }) , BSN("The city "+
        "of Pelargir lies to the southwest, but is not visible when "+
        "looking this direction."));

    add_item( ({ "window", "it", "opening", "broken window" }) , 
        BSN("Though it might once have actually been a real window, "+
        "all that is left now are a few broken shards of glass "+
        "clinging to the perimeter of the sash. The Great River, "+
        "Anduin, is visible through the resulting opening."));

    add_item( ({ "shard", "shards", "shards of glass", "glass",
        "broken glass", "sliver", "slivers", "pane" }) , BSN("A few "+
        "slivers of broken glass lying in the opening are the only "+
        "evidence that there was ever a pane in this window."));

    add_item( ({ "perimeter", "sash", "perimeter of sash", "evidence",
        "frame", "wooden frame", "splintered wooden frame" }) , BSN("All "+
        "that remains of the window that was once here is a "+
        "splintered wooden frame and a few slivers of broken glass."));

    add_item( ({ "wind", "breeze" }) , BSN("A gentle breeze blows in "+
        "through the broken window."));

    add_item( ({ "river", "anduin", "great river", "great river anduin",
        "view", "side", "east", "mighty anduin", "current", "direction",
        "this direction", "river current" }) , BSN("From this elevation "+
        "there is a clear view of the mighty Anduin river as it flows "+
        "swiftly past. On either side of the harbour entrance are "+
        "dangerous looking shoals, probably the very reason for the "+
        "existence of this lighthouse."));

    add_item( ({ "side", "either side", "harbour entrance", "entrance" }) , 
        BSN("To the east, the port of Pelargir opens into the mighty "+
        "Anduin River."));

    add_item( ({ "danger", "dangers", "nearby danger", "pile", "piles",
        "tip", "tips", "hint", "beneath", "shoal", "shoals", "rock",
        "rocks", "reason" }) , BSN("There are shallows in the river near "+
        "the harbour entrance where the riverbed has banked up into "+
        "several sizeable sandbars. Only the tips of a few protruding "+
        "rocks give a hint of the dangers to shipping that lie hidden "+
        "beneath."));

    add_item("shallows", BSN("The river looks particularly shallow "+
        "on either side of the harbour entrance."));

    add_item( ({ "riverbed", "channel" }) , BSN("The channel of the river "+
        "bends westward here, approaching the entrance to the Pelargir "+
        "harbour."));

    add_item( ({ "sandbar", "sandbars", "sand" }) , BSN("The river current "+
        "has mounded sand into clearly visible piles near the entrance "+
        "to the harbour."));

    add_item( ({ "ship", "ships", "shipping" }) , BSN("Ships from far and "+
        "near carefully negotiate the entrance to the Pelargir "+ 
        "harbour."));

    add_exit("lighthouse4", "up", 0, 4);
    add_exit("lighthouse2", "down", 0, 4);
} /* end create_gondor */
