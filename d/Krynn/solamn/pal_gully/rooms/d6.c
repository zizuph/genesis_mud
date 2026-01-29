/* 
 * Living Quarters of the Dewar Caverns
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_DEWAR_BASE; 

object dwarf1;
object dwarf2;
object dwarf3;

/*
 * Function name: reset_pal_dewar_room
 * Description  : Resets the room
 */
void
reset_pal_dewar_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "dewar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "dewar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "dewar");
        dwarf3->move(TO);
    }
}

/*
 * Function name: create_pal_dewar_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_dewar_room()
{
    set_short("Living Quarters");
    set_long("The home of the Dewar Dwarves. "
    +"The walls of the caverns are smooth and well "
    +"carved. Living quarters of the Dewar "
    +"dwarves. There are bunks attached to the walls "
    +"where the Dewar can take their rest. There "
    +"are small trunks at the end of the bunks "
    +"and shelves built into the walls in between "
    +"the rows. Weapons, macabre items, and "
    +"bloody trophies are visible on some of the "
    +"shelves. This room is lit by oil lanterns "
    +"attached to the walls.\n");
    
     add_item(({"items", "macabre", "macabre items", "bloody trophies",
	"shelf", "shelves","trophies","rows", "row"}),
	"Placed haphazardly upon the rows of shelves are trophies that the "
	+"Dewar have collected and decided to keep. Skulls of small animals, "
	+"bloody furs, eyeballs in jars and other "
	+"disgusting items are on the shelves.\n");
	add_item(({"bunk", "bunks","bed", "beds"}), 
	"Bunk beds line either side of the room. "
	+"The bunks are crudely made from wood and linen but appear solid.\n");
	add_item(({"trunk", "trunks"}), "Made from wood and iron, these trunks "
	+"are where the Dewar store their clothing while they rest.\n");
    add_item(({"weapons", "weapon"}), "Axes, the favoured item "
    +"of the Dewar are lodged into the ground for use in slaughter.\n");
	add_item(({"skull", "small animal", "skulls"}), "Cleaned and preserved "
    +"skulls of small animals, like rats and rabbits, are on display in a "
	+"gruesome manner.\n");
	add_item(({"fur", "bloody furs", "furs"}), "The furs of the animals "
	+"whose skulls are on display have been put on display as well. "
	+"Blood drips from them and the smell is sickening.\n");
	add_item(({"eyeballs", "eyeball", "jars", "jar", "eyeballs in jars"}),
	"Plucked from the skulls of small animals and brined, for some reason, "
	+"in jars.\n");
	add_item(({"clothes", "clothing","pant", "pants", "shirt", "shirts"}),
	"Tossed into the trunks are dirty "
	+"shirts and pants.  They are stained with blood and other filth from "
	+"a day of committing evil acts.\n");
	
    add_exit(RDIR + "d7","south",0);
    add_exit(RDIR + "d8","northwest",0);
    add_exit(RDIR + "d5", "east", 0);
    reset_room();
    
}