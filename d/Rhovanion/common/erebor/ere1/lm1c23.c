/*
 * Example inn with the new pub.c
 */
inherit "/d/Rhovanion/common/erebor/caves.c";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"


/*
 * Function name: create_room
 * Description:   Set up default trade and cofigure it if wanted.
 */

create_cave()
{
    set_rock_type("cold grey granite");
    set_cave_name("the Lonely Mountain");
    set_region("northern");
    set_cave("Erebor");
    set_cave_type(8);
    set_long("'Welcome to the Shield and Hammer' you hear the bartender shout " 
	+ "as you enter this magnificient Pub. Sitting at nice clean tables " 
	+ "and at the long oak bar you spot many smiling dwarves whos sitting " 
	+ "around and drinking ale happily. At the eastern wall you see a  "
	+ "large fireplace, with a burning hot fire inside. On the bar you see "
	+ "a small sign, with a menu stamped onto it.");
    
    add_item("bar", "A nice clean long oak bar.\n");
    add_item(({"menu","sign"}), "It has some readable words on it.\n");
    add_item("chairs",
	"They are made out dark wood, obviously from outside Lonely Mountain.\n"); 
    add_item("tables", "They are speckled with spots of beer.\n");
    add_cmd_item("menu", "sign", "read", "@@read");

    add_drink( ({ "beer", "beers", "small", "small beer" }),
	"beer", "small", 100, 4, 12, 0, 0,
	"It's a small but refreshing beer.\n", 0);
    
    add_drink( ({ "beer", "beers", "large", "large beer" }),
	"beer", "large", 200, 50, 36, 0, 0,
	"It's a large strong dwarven beer.\n", 0);
    
    add_drink( ({ "wine", "wines", "sweet", "sweet wine" }),
	"wine", "sweet", 200, 20, 72, 0, 0,
	"It has a deep red colour and smells wonderful.\n", 0);

    add_exit(CAVE_DIR + "lm1c16","south",0,1);
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

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write(" " 
        + "\n" 
	+ "   Small beer                 12 cc\n" 
	+ "   A Large Dwarven beer       36 cc\n"
	+ "   Some really sweet wine     72 cc\n" 
	+"\n" 
	+ "Try 'buy beer with gold' if you wanna specify what to\n" 
	+ "pay with, or 'test buy beer' to see what would happen\n" 
	+ "if you typed 'buy beer'. 'buy 10 beer' would get you\n" 
	+ "ten beers from the bar, but it takes a little while to\n" 
	+ "give them all to you.\n");
    return 1;
}

