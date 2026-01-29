/*
 * Entrance room
 * Boreaulam, April 2012
 */
#include "defs.h"
#pragma strict_types

inherit L1_BASE_ROOM;

/*
 * Function name:		create_room
 * Description  :		creates room
 */
void
create_room()
{
	::create_room();
    set_short("Cave entrance");
    set_long("You are standing on an entrance mat " +
         "just inside the goblin cave. " +
         "It is quite cool in here, and damp as well. " +
         "You feel fresh air coming from cave exit to the south. " +
         "The cave expands in all directions. " +
         "\n\n");

    add_item(({"mat", "entrance mat"}),
               "The entrance mat is pretty worn down but you can " +
               "see some words embroidered on it.\n");
    add_item(({"words", "writing", "embroidery"}),
               "@@show_writing");
    add_item(({"exit", "cave exit"}),
               "The exit is south from here. " +
               "Fresh air makes you breath easier.\n");
    add_cmd_item( ({"words", "writing", "embroidery"}),
                  "read",
                  "@@show_writing");

    add_exit ("roomb","north");
    add_exit ("roomd","west");
    add_exit ("roomf","east");
    add_exit ("/d/Genesis/start/human/wild2/top5","south");

    add_npc(NPCS_DIR + "goblin1_1", 2, &->arm_me());
} /* create_room */

/*
 * Function name:		show_writing
 * Description  :		shows written words on mat
 */
string
show_writing()
{
	return "\t\t\tGoblins - Welcome!\n " +
           "\t\t\tOthers - Not welcome!\n";
}	/* show_writing */

