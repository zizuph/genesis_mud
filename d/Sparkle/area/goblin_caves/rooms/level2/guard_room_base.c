/*
 * Guard room base room
 * Boreaulam, August 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

string get_add_room_long();

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("small guard room");
    set_long("This small room appears to have been carved out to accomodate " +
        "some guards who keep watch on these caves. Each of the roughly " +
        "chiseled walls have a torch mounted, keeping the room well lit. A " +
        "large, wooden table sits in the middle of the room, surrounded by " +
        "a handful of poorly constructed chairs. Against the southern " +
        "wall, a handful of rusty weapons and old uniforms sit on a thick " +
        "stone slab, suggesting that this room is intended for use by " +
        "the local guards. In the middle of the north wall, an irregular " +
        "opening leads back out into the larger cavern. \n\n");
    
    add_item(({"table", "large table", "wooden table"}),
             "This table is rather large, and it appears to be made entirely " +
             "of wood. Full of chips and splinters, this table has quite " +
             "obviously seen better days. A few of bottles of wine, " +
             "accompanied by several half-full glasses sit in the middle " +
             "of the table.\n");
    add_item(({"chair", "chairs"}),
             "There are many chairs here, but you have difficulty finding " +
             "one that you would feel comfortable sitting in, as they all " +
             "look like they are ready to fall apart.\n");
    add_item(({"wine", "bottles", "wine bottles", "bottle", "wine bottle"}),
             "There are a few bottles of wine, all of them open and " +
             "half-empty, sitting on top of the large, wooden table.\n");
    add_item(({"glass", "glasses"}),
             "These glasses are heavy and crudely made, not to mention " +
             "rather dirty. Judging by the large collection sitting here " +
             "on the table, the guards here must really enjoy their wine.\n");
    add_item(({"torch", "torches"}),
             "There are five torches mounted on the wall here, one on " +
             "every wall, and two flanking the opening on the north wall. " +
             "The torches are burning bright, showering this small cave " +
             "with plenty of light.\n");
    add_item(({"slab", "stone slab", "thick slab"}),
             "This thick slab of stone sits up tight against the southern " +
             "wall and appears to be used as a place to leave old or " +
             "unused equipment for the guards here.\n");
    add_item(({"equipment", "uniform", "old uniform", "uniforms", 
                "heap", "pile", "old uniforms"}),
             "Although heavily stained and ripped, these heaps of cloth are " +
             "still recognizable as old uniforms for the guards who serve " +
             "in these caves. It appears that the guards are content to " +
             "leave them sitting on a stone slab at the south end of the " +
             "room.\n");
    add_item(({"weapon", "weapons", "rusty weapon", "rusty weapons"}),
             "A handful of rusty weapons have been abandoned on top of the " +
             "stone slab at the southern end of this cave. Upon closer " +
             "inspection, you can see that these weapons are worthless and " +
             "almost certainly unusable.\n");
    add_item(({"opening", "irregular opening"}),
             "This opening in the northern wall leads back out into the " +
             "larger cavern you came from originally.\n");
    add_item(({"floor", "down"}),
             "The grey, stone floor here is uneven, but has been worn " +
             "smooth over what you suspect is many years of use.\n");
    add_item(({"wall", "walls"}),
             "Which wall did you want to examine? The north wall? The " +
             "south wall?\n");
    add_item(({"ceiling", "up"}),
             "The dull grey stone of the ceiling has been roughly chiseled, " +
             "obviously worked by hand to expand what was probably a " +
             "naturally existing cave at first.\n");
    add_item(({"south wall", "southern wall"}),
             "The southern wall is made from the same dull, grey stone as " +
             "the rest of the cave. A single torch has been mounted in the " +
             "middle, helping to keep this cave well lit. However, a thick " +
             "stone slab has been pressed up against it.\n");
    add_item(({"east wall", "eastern wall"}),
             "The eastern wall is made from the same dull, grey stone as " +
             "the rest of the cave. A single torch has been mounted in the " +
             "middle, helping to keep this cave well lit.\n");
    add_item(({"west wall", "western wall"}),
             "The western wall is made from the same dull, grey stone as " +
             "the rest of the cave. A single torch has been mounted in the " +
             "middle, helping to keep this cave well lit.\n");
    add_item(({"north wall", "northern wall"}),
             "The northern wall is made from the same dull, grey stone as " +
             "the rest of the cave. Two small torches have been mounted on " +
             "either side of the irregular opening which leads back out to " +
             "the larger cavern and the lake outside.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
             "Barely visible through the opening in the northern wall is " +
             "the wide underground lake which fills the middle of the " +
             "cavern outside.\n");
    add_item(({"cave", "room", "guard room", "here"}),
             "This small room appears to have been carved out to accomodate " +
            "some guards who keep watch on these caves. Each of the roughly " +
            "chiseled walls have a torch mounted, keeping the room well lit. " +
            "A large, wooden table sits in the middle of the room, " +
            "surrounded by a handful of poorly constructed chairs. Against " +
            "the southern wall, a handful of rusty weapons and old uniforms " +
            "sit on a thick stone slab, suggesting that this room is " +
            "intended for use by the local guards. In the middle of the " +
            "north wall, an irregular opening leads back out into the larger " +
            "cavern.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
             "When you look through the opening in the north wall, you can " +
             "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
             "You are in a large series of caves and caverns that tunnel " +
             "deep beneath the mountains.\n");
    add_item(({"chips", "splinters"}),
             "The wooden table looks to be in bad shape, as there are many " +
             "chips and splinters missing from heavy use over the years.\n");
    add_item(({"stone", "grey stone", "granite"}),
             "This dull grey stone is the very bones of the mountains you " + 
             "are currently beneath. This granite is very hard, but in many " + 
             "places it appears that several industrious goblins have " + 
             "chiseled away at the walls and ceilings to make these caves " + 
             "more habitable.\n");

    add_npc(NPCS_DIR + "goblin2_1", 4, &->arm_me());
} /* create_room */

/*
 * Function name:        get_add_room_long
 * Description  :        blank function to override to return additional long 
 *                       description
 */
string 
get_add_room_long()
{
    return "wrong game description";
} /* get_add_room_long */
