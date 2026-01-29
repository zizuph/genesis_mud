// file name: d/Avenir/common/outpost/fort8.c
// creator(s): Lilith June 2004
// last update:

#pragma strict_types
#include "/d/Avenir/common/outpost/outpost.h"
inherit OUTPOST +"fort_base";

void create_fort_room()
{
    set_short("a vestibule with stairs leading up and down");
    set_long("This room has been cut from the stone of the cavern wall. "+
        "Some crystal and copper wall lamps gently illuminate the "+
        "emptiness of the space. "+
		"Two wrought-iron doors have been swung aside to allow "+
        "access, but when swung closed, would interlock to create "+
        "an impassible barrier to the north. "+
        "Along the west wall, a set of stairs rises up toward steady "+
        "brightness. "+ 
        "To the south, another set of stairs leads downward into "+
        "flickering darkness. "+		
		"There is a sign with an arrow pointing upward alongside "+
        "the word 'VOLODA' and another word 'FORGE' with an arrow "+
        "pointing down."+      
        "\n");
       
    add_exit("fort5",      "north",0);
    add_exit("paint_shop", "up",0);
    add_exit("smithy",     "down", 0);
	
	add_exit_views();
    add_fort_room();
	
    add_item(({"sign", "signs"}),
        "There is a sign hanging from the ceiling. The sign shows "+
        "an 'up' arrow next to the word 'VOLODA' and a 'down' "+
        "arrow next to the word 'FORGE'.\n");
    add_cmd_item(({"sign", "signs"}), "read",
        "There is a sign hanging from the ceiling. The sign shows "+
        "an 'up' arrow next to the word 'VOLODA' and a 'down' "+
        "arrow next to the word 'FORGE'.\n");
    add_item(({"up sign", "up arrow", "voloda"}),
        "There is a sign hanging from the ceiling. The sign shows "+
        "an 'up' arrow next to the word 'VOLODA'.\n");
    add_item(({"down sign", "down arrow", "forge"}),
        "There is a sign hanging from the ceiling. The sign shows "+
        "a 'down' arrow next to the word 'FORGE'.\n");
    add_item(({"stairs", "up stairs", "down stairs"}),
        "There are two sets of stairs here, one going up, the other "+
        "going down.\n");
    add_item(({"door", "doors", "wrought iron", "wrought-iron", 
	    "wrought-iron doors", "wrought-iron door" }),	
        "Two doors made of wrought-iron have been swung back on "+
        "either side of the north doorway. When closed, it looks "+
        "like they interlock to create a formidable barrier.\n");
    add_cmd_item(({"door", "doors", "wrought iron", "wrought-iron", 
	    "wrought-iron doors", "wrought-iron door" }),
        ({"swing", "close"}), "You can't seem to do that.\n");
   
} // create_room()

