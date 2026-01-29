/* 
   This is how a simple pub could look like
   This pub works quicker than the other example pub but you cannot
   choose what coins to pay with, but then again, speed is important

   Made by Nick

   Totally remade by Lugdush 1996-06-05
*/

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/pub";

#include "../defs.h"

string
menu()
{
    return "You can order the following drinks here:\n\n"+
        "Ale            - 12 cc\n"+
        "Beer           - 70 cc\n"+
        "Whiskey        - 72 cc\n"+
        "Cider          - 12 cc\n";
}

/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */
void
create_room()
{
    set_short("The staggering dwarf");
    set_long("You are in the middle of the Staggering Dwarf. It is the\n"+
	     "local pub of Dwarfheim and here the locals gather to\n"+
	     "drink and talk. There are a few tables here, and at one\n"+
	     "of the walls is a small bar, with a menu on it.\n");
	     
    add_item("bar", "It is long and very smooth, it looks to be made out "+
             "of mahogany.\n");
    add_item(({"wall", "walls"}), "They are carved from stone.\n");
    add_item("tables", "They are scattered about the room.\n");
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item("menu","@@menu");
    add_cmd_item("menu","read","@@menu");

    add_exit(LVL1 + "corr5","up");

    add_drink("beer", "beer", "strong", 540, 38, 70, 0, 0,
              "This is a pint of very strong beer.\n");
    add_drink("ale", "ale", "light", 100, 4, 12, 0, 0,
              "The ale looks very refreshing.\n");
    add_drink("whiskey", "whiskey", "malt", 62, 25, 72, 0, 0,
              "The malt whiskey is at least 12 years old.\n");
    add_drink("cider", "cider", "apple", 84, 4, 12, 0, 0,
              "The cider is cool and refreshing.\n");
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */

    init_pub();
}

