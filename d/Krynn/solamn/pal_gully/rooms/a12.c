/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a12.c
 */


#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

object dwarf1;
object dwarf2;
object dwarf3;

string crawl_castle(string str);

/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "aghar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "aghar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "aghar");
        dwarf3->move(TO);
    }
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_gully_room()
{
    set_short("Play Area");
    set_long("This room is larger than the others. Still "
    +"filled with garbage and other refuse, this room has many "
    +"small structures built from boxes and scraps of metal and "
    +"wood that the Aghar have found. The room resembles "
    +"a small kingdom with little buildings to crawl in and "
    +"out of as well as little makeshift drawbridges and other "
    +"fun little items.\n");
    
    add_item(({"castle", "makeshift castle","kingdom", "kingdoms"}),
	"Made from refuse, boxes and little scraps of metal and wood, "
	+"this Castle is rather cute. Someone put a lot of effort into "
	+"constructing it. Putting parapets and spires on top, "
	+"a little drawbridge and enough space that you could probably "
	+"crawl inside!\n");
    add_item(({"drawbridge", "makeshift drawbridge", "drawbridges"}), "A little "
    +"drawbridge made from a plank of wood that goes over a garbage "
    +"moat.\n");
	add_item(({"moat", "garbage moat"}), "a small moat made from garbage "
	+"water flows around the kingdom.\n");
	add_item(({"plank", "plank of wood","wood plank", "wooden plank"}),
	"A small plank of wood that has likely been found cast aside within "
	+"the mine. The aghar have used it as a drawbridge to get over their "
	+"homemade garbage moat.\n");
	add_item(({"structure", "structures","box", "boxes", "parapets",
	"parapet"}),"Boxes have been used to construct the makeshift castle. "
	+"They have been stacked up on one another, cut to make shapes and "
	+"made into a cute little kingdom, parapets and all.\n");
    add_item(({"items", "fun items", "little items", "prince", "princess",
	"kender", "adventurer","adventurers" }), "Little characters, "
    +"a prince, princess, some adventurers and even a "
    +"little kender. These toys seem old and discarded. Someone has "
    +"gathered them up, cleaned them off, and built them this "
    +"little castle!\n");
     
    add_exit(RDIR + "a10","south",0);
    
    reset_pal_gully_room();
    
}


int
crawl_castle(string str)
{
    
    notify_fail("Crawl where?\n");
    if (str != "castle" && str != "through castle" && str != "in castle" 
    && str != "into castle" && str != "through the castle")
    return 0;
    
    else
    say((this_player()), QCTNAME(this_player()) +
    " crawls into the castle structure and out of sight.\n");
    write("You crawl out of the castle structure back into the room.\n\n");
    this_player()->move_living("M", RDIR+ "hidden2");
    say(QCTNAME(TP)+" arrives crawling into the castle structure.\n.");
    return 1;
}


public void
init()
{
    ::init();
    add_action(crawl_castle, "crawl");
}