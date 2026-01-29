// file name:        /d/Avenir/common/bazaar/admin/admin_base.c
// creator(s):       Lilith, Sept '97
// revisions: 
// purpose:          
// note:             This file is to be inherited in all admin rooms.  
//                   The more frequent add_items should be entered 
//                   here.		     
// bug(s):           
// to-do:            

#pragma strict_types

/* Inherit the standard room object */
inherit "/d/Avenir/inherit/room";

/* Include the local area defines, etc */
#include "/d/Avenir/common/bazaar/admin/admin.h"

/* Prototypes */
/* These are the add_items and add_cmd_items for the cave rooms 
 * (see below)
 */
void add_bridge();
void add_courtyard();
void add_fountain();
void add_gate();
void add_tribunal();
void add_inquis();
void add_ngate();
void add_sgate();
void add_stones();
void add_source();
void add_outside();

/*
 * Function name: create_admin_room
 * Description:   This function should be used for creating cave rooms.
 */
void create_admin_room() { }

/*
 * Function name: reset_admin_room
 * Description:   This function should be used for for reseting cave rooms.
 */
void reset_admin_room() { }

/*
 * Function name: create_domain_room
 * Description:   This function creates a SMIS-enabled room.
 */

public void create_domain_room()
{
    set_area("baz_adminp");

    /* If an add_item will be in every room, add it here */

    LIGHT;
    IN;

    create_admin_room();
    reset_admin_room();
}

/* These are the add_items and add_cmd_items for the cave rooms 
 * (Those used more than once in the area)
 */
void add_bridge()
{
    add_source();
    add_item(({"bar", "bars"}), "These bars, while appearing to be "+
        "made of gold, are not nearly so soft as that metal. Some "+
        "mysterious method of metal-smithing has produced vast quantities "+
        "of bars as thick around as your wrist and as hard as steel.\n");
    add_item(({"wire", "wires"}), "A brilliant form of passive defence, "+
        "these strands of wire have been spun so fine that you fear "+
        "to fall against them lest you slice yourself to the bone on "+
        "them.\n");
    add_item(({"wood", "planks", "kesoit"}), "Wood is precious in "+
        "Sybarus, and kesoit most precious of all, as it grows on just "+
        "a few islands in Sybarus and nowhere else.  The wood is "+
        "naturally very dark, with a very fine blood-red grain. "+
        "It is aesthetically pleasing not only to the eye, but also "+
        "to the nose, for it has a distinctly appealing scent.\n");
    add_cmd_item(({"wire", "wires", "strand", "strands"}), 
        ({"touch", "feel"}), "Ouch!\nYou jerk away from the woven "+
        "stands of gilded wire, sucking on the fine cut on your "+
        "finger. You decide to try to stand in the very center of "+
        "the bridge, as far away from the wires as possible.\n");
}

void add_courtyard()
{
    add_item(({"courtyard", "broad courtyard", "square", "tribunal "+
        "square", "Tribunal Square"}),
        "This courtyard, known to Sybarites as Tribunal Square, "+
        "is paved in large slabs of stone. It "+
        "runs north-south, with a long, low green marble building "+
        "along the west side, and a stately red-gold building "+
        "due south.\n");
}
void add_fountain()
{
    add_item(({"fountain", "fount", "pool", "golden fountain" }),
        "It is a large circular pool made of purest alabaster. "+
        "Rising above it are three rings connected to form a "+
        "trefoil. Each ring is crafted from pure gold, thick as "+
        "a man's arm, and tall as an elf. Water spouts from the "+
        "junctions of the circles and falls into the pool with "+
        "a relaxing rush and patter.\n");
    add_item("water", "The water is pure and clear.\n");
    add_item(({"trefoil", "circles", "connected circles", "rings",
        "ring", "circle", "gold rings", "gold trefoil"}),
        "It is the symbol of Sybarus. Cast from purest gold, "+   
        "it stands in the center of the pool and is washed "+
        "continually by clear water.\n");
}    
void add_gate()
{
    add_item(({"gate", "third gate", "Third Gate", "archway", "wood",
        "high arch", "arched gate", "arch", "doors", "wooden doors"}),
        "The gate dominates this courtyard, easily visible from all "+
        "sections. It is made of wood from the kesoit tree, which "+
        "is both very dark and highly fire-resistant. It is made "+
        "of two half-doors cut to fit perfectly into the archway "+
        "leading toward the Forbidden City. It is known as the "+
        "Third Gate.\n");
}

void add_inquis()
{
    add_item(({"marble building", "green building", "low building",
        "green-marble building", "green marble", "kestares", "Kestares"}),
        "A beautifully-constructed, yet somewhat menacing building "+
        "made of black-veined green marble. It has two entrances, "+
        "one at the north end, the other at the south. It is known "+
        "locally as the Kestares, the Questioning Place.\n");
}
void add_inside_inquis()
{
    add_item(({"walls", "blocks", "marble block", "green stone" }),
        "Each block is the twice the length of your forearm. There "+
        "are black veins snaking through each one.\n");
    add_item(({"floor", "floors"}),
        "The floor is dark and smooth, and immaculately clean.\n");
    add_item(({"table"}),
        "The table gleams darkly in the low light of the room. "+
        "It is smooth and bare.\n");
    add_item(({"chair", "chairs"}),
        "Both chairs are made of the same dark wood as the table. "+
        "They look hard and uncomfortable.\n");
    IN_IN;
}
void add_ngate()
{
    add_item(({"gatehouse", "north gatehouse"}),
        "This gate house is twin to the one on the south side of "+
        "the Third Gate. It is rather small, with a single door "+
        "and some regularly-placed rectangular slits at eye-level.\n");
}
void add_sgate()
{
    add_item(({"gatehouse", "south gatehouse"}),
        "This gate house is twin to the one on the north side of "+
        "the Third Gate. It is rather small, with a single door "+
        "and some regularly-placed rectangular slits at eye-level.\n");
}
void add_stones()
{
    add_item(({"path", "stones", "stone path", "slabs"}),
        "The stones of the courtyard look like they are made of slabs "+
        "of flawed semi-precious stones such as jasper and carnelian.\n");
    add_item(({"ground", "floor", "cobbles"}), "The ground is paved "+
	    "with cobbles cut from slabs of gorgeous, if flawed, stone.\n");
}
void add_source()
{
    add_item(({"Source", "source", "light", "illumination", "skein", 
        "glow", "above", "sky"}),
        "High above, in the ceiling of this great cavern, is "+
        "a glowing skein of mineral that emits light.\n");
}   
void add_tribunal()
{
    add_item(({"tribunal", "stately building", "red-gold building",
        "red-gold stone" }),
        "This collonaded building rises above the courtyard. Its "+
        "red carnelian stone is veined with gold that reflects the "+
        "light of the Source. It is known locally as the Tribunal.\n");
}
void add_inside_tribunal()
{
    add_item(({"wall", "walls", "stone", "stones", "floor", "floors"}),
        "The stones are a gleaming red, with veins of gold snaking "+
        "through them.\n");
    add_item(({"chair", "throne", "throne-like chair" }),
        "An over-large chair, ornately carved from kesoit wood.\n");
    add_item(({"post", "whipping post"}),
        "A sturdy post running from floor to ceiling. Prisoners are "+
        "chained to it while awaiting sentencing.\n");
    IN_IN;
}    
void add_outside()
{
    add_courtyard();
    add_fountain();
    add_gate();
    add_inquis();
    add_stones();
    add_tribunal();
    add_source();
}
/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
