/*
 * /d/Gondor/pelargir/docks/lamproom.c
 *
 * Copyright (C) August 13, 1998 by Ron Miller (Tyr)
 *
 * This is a revised version of the top room in the lighthouse in 
 * Pelargir for the creation of a quest to restore the warning beacon.
 *
 * Revision history:
 *    6/7/99: bracket content states added by Tyr
 *    27/6/11: Patched by Tapakah for quest reset
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/beacon_defs.h"


/* prototypes */
public void    create_gondor();
public void    reset_room();
public int     lantern_state();
public void    sunrise();
public void    sunset();

/* global variables */
static object    Lensbracket,
                 Mirrorbracket,
                 Lanternbracket,
                 Lumendil;

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    FIX_EUID;

    set_short("The lantern room");

    set_long(BSN("This is the lantern room of the lighthouse. "+
        "Windows totally surround a pedestal which is obviously the "+
        "focal point of this room. For the first time, you clearly "+
        "hear the sound of the river rushing across the shoals below. "+
        "The timbers here constantly creak under the ceaseless "+
        "buffeting of the wind. A large keg of lantern oil sits "+
        "beside the pedestal."));

    add_item( ({ "lamproom", "room" }) , BSN("The topmost floor of the "+
        "lighthouse, this room is intended to house the lantern used "+
        "to warn passing ships of any danger nearby."));

    add_item( ({ "pedestal", "focal point", "point", "support" }) , BSN("This "+
        "pedestal serves as the support for a rather elaborate "+
        "mechanism."));

    add_item( ({ "mechanism", "device" }) , BSN("Even to the untrained eye, "+
        "this device is clearly optical in nature. It consists of "+
        "three separate brackets mounted atop the central pedestal."));

    add_item("brackets", BSN("There are two diametrically opposite "+
        "brackets, with a third centered between them."));

    add_item( ({ "eye", "untrained eye", "reflection" }) , BSN("A mirror "+
        "would be required to see the reflection of your own eye."));

    add_item("wind", BSN("The wind blows almost constantly here."));
        
    add_item( ({ "timber", "timbers", "trees", "ancient trees" }) , 
        BSN("Ancient trees were shaped and crafted to brace the "+
        "structure here against the most severe storms."));

    add_item( ({ "window", "windows", "wall", "walls", "top" }) , BSN("The "+
        "walls here are actually windows offering commanding views of "+
        "everything below."));

    add_item( ({ "views", "everything", "below", "everything below",
        "elevation", "outdoors" }) , BSN("The harbour lies to the south, "+
        "the Anduin River to the east, Pelargir itself lies to the "+
        "west, and the rolling countryside of Gondor stretches toward "+
        "the north."));
    
    add_item( ({ "harbour", "pelargir harbour", "south", "port", "surface" }) , 
        BSN("This view of the Pelargir harbour is rather breathtaking. "+
        "From this height, the ships below look like miniatures bobbing "+
        "on the surface in the harbour."));

    add_item( ({ "ship", "ships", "miniatures", "flags", "home port flags" }) , 
        BSN("From this height it is impossible to discern the home "+
        "port flags on the ships below."));

    add_item( ({ "river", "anduin", "river anduin", "mighty anduin", "east" }) , 
        BSN("From this vantage point there is a clear view of the "+
        "mighty Anduin River as it flows past. On either side of the "+
        "harbour entrance are dangerous looking shoals, probably the "+
        "very reason for the existence of this lighthouse."));

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

    add_item( ({ "shipping", "shipping traffic", "traffic" }) , BSN("Ships "+
        "from far and near carefully negotiate the entrance to the "+
        "Pelargir harbour."));

    add_item( ({ "city", "pelargir", "city of pelargir", "west", "town" }) , 
        BSN("The city of Pelargir is spreads toward the west.  The "+
        "houses in that direction are mostly simple dwellings, save "+
        "one, which has all the aspects of a mansion."));

    add_item( ({ "house", "houses", "dwelling", "dwellings", "community" }) , 
        BSN("There is nothing special about these rather plain little "+
        "houses. However the one farthest to the west is larger than "+
        "the others."));

    add_item( ({ "large house", "larger house", "west house", "last house",
        "mansion" }) , BSN("A rather large house, which appears oddly "+
        "out of place in a neighborhood of relatively simple "+
        "dwellings.  The owner must surely be a very important "+
        "person in this community."));

    add_item( ({ "owner", "person" }) , BSN("The owner of the mansion is "+
        "not outdoors at the moment."));

    add_item( ({ "countryside", "gondor", "north" }) , BSN("From here it "+
        "is easy to see over the walls of the city below.  The main "+
        "road seems to head toward the northeast after it leaves "+
        "the city gates.  There appears to be a small hut east of "+
        "the main road not too far outside of the town."));

    add_item( ({ "hut", "small hut", "blur" }) , BSN("The tiny hut so distant "+
        "that it is only a blur."));

    add_item( ({ "city wall", "city walls" }) , BSN("The landward "+
        "perimeter of Pelargir is protected by a tall stone wall."));

    add_item( ({ "gate", "gates", "city gate", "city gates" }) , BSN("There "+
        "are gates in the wall on the north and south sides of the "+
        "city, allowing land travellers access to this port city."));

    add_item( ({ "lighthouse", "structure" }) , BSN("This tall granite "+
        "tower was most likely constructed to warn passing ships of "+
        "some nearby danger."));

    add_item( ({ "tower", "granite tower", "here", "room" }) , BSN("A sturdy "+
        "old structure, this tower appears able to withstand even the "+
        "fiercest of storms."));

    add_item( ({ "granite", "pieces", "stone", "stones", "flagstone",
        "flagstones", "slab", "slabs", "block", "blocks" }) , BSN("The grainy "+
        "gray rock used in the construction this lighthouse appears to "+
        "have been chosen more for its hardness and durability than its "+
        "aesthetic appeal."));

    add_item( ({ "rock", "stonework" }) , BSN("The tower of the lighthouse "+
        "is built almost totally of stone."));

    add_item( ({ "stairs", "staircase", "spiral", "spiral staircase" }) , 
        BSN("These winding stone stairs make for a long and grueling "+
        "climb."));

    add_item("floor", BSN("Large irregularly shaped slabs of flat "+
        "granite have been pieced together here to form the stairs "+
        "and floor of the lamproom."));

    add_item( ({ "ceiling", "surface", "metallic surface", "polished surface",
        "polished metallic surface" }) , BSN("The ceiling here is some "+
        "polished metallic surface designed to reflect as much light "+
        "as possible."));

    add_item("light", BSN("Most of the light here comes in through "+
        "the windows which form the walls, except when the beacon "+
        "lantern is lit."));

    add_item( ({ "tower wall", "tower walls" }) , BSN("The walls of the "+
        "tower have been built of rough hewn blocks of granite from "+
        "some nearby quarry."));

    add_item( ({ "storm", "storms", "weather", "rainstorm", "rainstorms" }) ,
        BSN("Though the weather is fair at the moment, it would be "+
        "dangerous to underestimate the power of the fierce storms "+
        "that sometimes rage against this lighthouse."));

    add_item("quarry", BSN("The quarry from which the stones of this "+
        "tower were cut is not visible from the port area."));

    add_item( ({ "gondor", "wilds", "wilds of gondor", "direction", "north" }) , 
        BSN("This tower is up high enough to afford a view over the "+
        "northern wall of the city. The main road seems to head toward "+
        "the northeast after it leaves the city. There also appears to "+
        "be a small hut east of the main road not too far outside of "+
        "the town."));

    add_item( ({ "city wall", "city walls", "northern wall", "perimeter",
        "stone wall" }) , BSN("The landward perimeter of Pelargir is "+
        "protected by a tall stone wall."));

    add_item( ({ "northeast", "road", "main road", "breaks" }) , 
        BSN("Occasionally visible in breaks between the trees, the road "+
        "makes its way toward the northeast."));

    add_item( ({ "tree", "trees", "countryside" }) , BSN("Trees cover the "+
        "countryside beyond the northern city walls."));

    add_item( ({ "keg", "large keg", "oilkeg" }) , BSN("This is a very large "+
	"wooden keg, designed to hold a large supply of lamp oil."));

    add_exit("lighthouse5", "down", 0, 4);

    reset_room();
}         /* end create_gondor() */

/*
 * Function name:    reset_room
 * Description:      resets the room -- restores lumendil and 
 *		     adds brackets to hold the components of the 
 *                   mechanism. These are the brackets which hold the
 *                   components of the warning beacon in the lamproom of
 *                   the Pelargir lighthouse.
 */
public void
reset_room()
{
  object *lantern_contents, *lens_contents, *mirror_contents;
  ::reset_room();

    Lumendil = clone_npc(Lumendil, LUMENDIL_FILE);

    if (!objectp(Mirrorbracket))
    {
        Mirrorbracket = clone_object(MIRRORBRACKET_FILE);
        Mirrorbracket->move(TO);
    }

    if (!objectp(Lensbracket))
    {
        Lensbracket = clone_object(LENSBRACKET_FILE);
        Lensbracket->move(TO);
    }

    if (!objectp(Lanternbracket))
    {
       Lanternbracket = clone_object(LANTERNBRACKET_FILE);
       Lanternbracket->move(TO);
    }
	if (lantern_state() != NONE_HERE) {
	  all_inventory(Lensbracket)->remove_object();
	  all_inventory(Mirrorbracket)->remove_object();
	  all_inventory(Lanternbracket)->remove_object();
	}
}   /* end reset_room()  */

/*
 * Function name:        lantern_state
 * Description  :        this tells us how many of the pieces of
 *                       the lantern have been returned and replaced
 * Arguments    :        none
 * Returns      :        int -- one of the states #defined above
 */
public int
lantern_state()
{
    int     state;

    if (present(LANTERN_NAME, Lanternbracket))
    {
        state += LANTERN_HERE;
    }

    if (present(MIRROR_NAME, Mirrorbracket))
    {
        state += MIRROR_HERE;
    }

    if (present(LENS_NAME, Lensbracket))
    {
        state += LENS_HERE;
    }

    return state;
} /* end lantern_state */


/*
 * Function name:	sunrise
 * Description	:	called from gondor master clock at sunrise.
 *			if lumendil is present, call sunrise() in
 *			him to extinguish the beacon.
 */
public void
sunrise()
{
    if (objectp(Lumendil) &&
	ENV(Lumendil) == TO)
    {
	Lumendil->sunrise();
    }
} /* end sunrise */

/*
 * Function name:	sunset
 * Description	:	called from gondor master clock at sunset.
 *			if lumendil is present, call sunset() in
 *			him to light the beacon.
 */
public void
sunset()
{
    if (objectp(Lumendil) &&
	ENV(Lumendil) == TO)
    {
	Lumendil->sunset();
    }
} /* end sunset */
