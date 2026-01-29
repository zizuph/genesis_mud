/*
 * Rack room base room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L2_BASE_ROOM;

string get_rack_loc();

/*
 * Function name:        create_room
 * Description  :        creates room
 */
void
create_room()
{
    ::create_room();

    set_short("Rack room");
    set_long("You have squeezed yourself into a rather tiny and featureless " +
        "cave. There is what appears to be a rack for holding weapons " +
        "standing on the " + get_rack_loc() + " side of the cave. Aside " +
        "from the rack, all you can see are the two small torches, burning " +
        "brightly on the roughly chiseled walls and illuminating the rocky " +
        "ceiling, broken only by the irregular opening in the wall which " +
        "leads back out to the larger cavern and the underground lake.\n\n");


    add_item(({"armoury", "racking", "weapon rack", "rack"}),
        "The only thing you can really see in this tiny " +
        "cave is the rack resting up agains the " + get_rack_loc() + 
        "end of the room. You could examine the rack more closely if you " +
        "wanted to.\n");
    add_item(({"opening", "irregular opening"}),
        "There is an irregular shaped opening in the wall which leads back " +
        "out into the larger cavern you came from originally.\n");
    add_item(({"lake", "underground lake", "wide lake"}),
        "Barely visible through the opening in the northern wall is " +
        "the wide underground lake which fills the middle of the " +
        "cavern outside.\n");
    add_item(({"cavern", "large cavern", "larger cavern"}),
        "When you look through the opening in the north wall, you can " +
        "see a large cavern with a wide lake in the middle of it.\n");
    add_item(({"caves", "caverns"}),
        "You are in a large series of caves and caverns that tunnel " +
        "deep beneath the mountains.\n");
    add_item(({"floor", "down"}),
        "The grey, stone floor here is uneven, but has been worn " +
        "smooth over what you suspect is many years of use.\n");
    add_item(({"wall", "walls"}),
        "The walls here are made of the same grey stone as everything " +
        "else in these caves. Two torches have been mounted here to " +
        "provide some light. \n");
    add_item(({"ceiling", "up"}),
        "The dull grey stone of the ceiling has been roughly chiseled, " +
        "obviously worked by hand to expand what was probably a " +
        "naturally existing cave at first.\n");
    add_item(({"torch", "torches"}),
        "There are a two torches mounted on the walls here, burning " +
        "brightly and keeping this cave well lit.\n");
    add_item(({"stone", "grey stone", "granite"}),
        "This dull grey stone is the very bones of the mountains you are " +
        "currently beneath. This granite is very hard, but in many places " +
        "it appears that several industrious goblins have chiseled away " +
        "at the walls and ceilings to make these caves more habitable.\n");
             
    room_add_object(OBJS_DIR + "l2_rack");

    add_npc(NPCS_DIR + "goblin2_rguard", 2, &->arm_me());
    

} /* create_room */


/*
 * Function name:        get_rack_loc
 * Description  :        blank function to override to return location of rack
 */
string
get_rack_loc()
{
    return "wrong";
} /* get_rack_loc */

/*
 * Function name:        reset_room
 * Description  :        resets contents of rack
 */
void 
reset_room()
{
    ::reset_room();
    object rack = present("rack", this_object());
    rack->reset_container();
} /* reset_room */