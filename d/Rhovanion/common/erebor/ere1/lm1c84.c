
/* Taken from the example /doc/examples/ by Mercade (I think)
   -- Dubilex. */

inherit "/d/Rhovanion/common/erebor/caves.c";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
    set_rock_type("cold grey granite");
    set_cave_name("the Lonely Mountain");
    set_region("northern");
    set_cave("Erebor");
    set_cave_type(8);
    set_long("Sitting around tables and at the bar you see many different people "
	+ "sitting with theire friends and drinking alot. From some of the "
        + "tables you hear singing and from others loud snoring. "
        + "There is a greasy menu at the bar where you can see what the Pub "
        + "offers to its customers.");
    
    add_item("bar", "Its a greasy bar, really disgusting.\n");
    add_item("menu", "It has some readable words on it.\n");
    add_item("chairs",
	"They are made out dark wood, obviously from outside Lonely Mountain.\n"); 
    add_item("tables", "They are speckled with spots of puke and beer.\n");
    add_cmd_item("menu", "read", "@@read");

    add_drink( ({ "beer", "beers", "small", "small beer" }),
	"beer", "small", 100, 4, 12, 0, 0,
	"It's a small but refreshing beer.\n", 0);
    
    add_drink( ({ "beer", "beers", "large", "large beer" }),
	"beer", "large", 200, 50, 130, 0, 0,
	"It's a large strong dwarven beer.\n", 0);
    
    add_drink( ({ "wine", "wines", "sweet", "sweet wine" }),
	"wine", "sweet", 200, 20, 72, 0, 0,
	"It has a deep red colour and smells wonderful.\n", 0);
    
    add_drink( ({ "wine", "wines", "strong", "strong wine" }),
	"wine", "strong", 200, 30, 108, 0, 0,
	"It has a deep red colour and smells wonderful.\n", 0);
    
    add_exit(CAVE_DIR + "lm1c17","north",0,1);
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
	+ "   Small beer                  12 cc\n" 
	+ "   A Large Dwarven beer       130 cc\n"
	+ "   Some really sweet wine      72 cc\n" 
	+ "   Some really strong wine    108 cc\n"
	+ "\n" 
	+ "Try 'buy beer with gold' if you wanna specify what to\n" 
	+ "pay with, or 'test buy beer' to see what would happen\n" 
	+ "if you typed 'buy beer'. 'buy 10 beer' would get you\n" 
	+ "ten beers from the bar, but it takes a little while to\n" 
	+ "give them all to you.\n");
    return 1;
}

