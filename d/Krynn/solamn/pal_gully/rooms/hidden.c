/* 
 * Inside a Castle in Aghar Newbie Zone
 * hidden.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

string crawl_castle(string str);

/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
	
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
public void 
create_pal_gully_room()
{
    set_short("Inside the Castle");
    set_long("Inside a tiny room that has been built inside "
    +"of the makeshift castle. There are scribbles on "
    +"the inside of the castle that show an Aghar Dwarf "
    +"rescuing a group of adventurers who are lost under "
    +"Pax Tharkas.\n");
    
    add_item(({"castle", "makeshift castle","kingdom", "kingdoms"}),
	"Made from refuse, boxes and little scraps of metal and wood, "
	+"this Castle is rather cute. Someone put a lot of effort into "
	+"constructing it. Putting parapets and spires on top, "
	+"a little drawbridge and all this space inside.\n");
    add_item(({"drawbridge", "makeshift drawbridge", "drawbridges"}), "A little "
    +"drawbridge made from a plank of wood that goes over a garbage "
    +"moat.\n");
	add_item(({"plank", "plank of wood","wood plank", "wooden plank"}),
	"A small plank of wood that has likely been found cast aside within "
	+"the mine. The aghar have used it as a drawbridge to get over their "
	+"homemade garbage moat.\n");
	add_item(({"structure", "structures","box", "boxes", "parapets",
	"parapet"}),"Boxes have been used to construct the makeshift castle. "
	+"They have been stacked up on one another, cut to make shapes and "
	+"made into a cute little kingdom, parapets and all.\n");
	add_item(({"moat", "garbage moat"}), "a small moat made from garbage "
	+"water flows around the kingdom.\n");
    add_item(({"items", "fun items", "little items", "prince", "princess",
	"kender", "adventurer","adventurers" }), "Little characters, "
    +"a prince, princess, some adventurers and even a "
    +"little kender. These toys seem old and discarded. Someone has "
    +"gathered them up, cleaned them off, and built them this "
    +"little castle!\n");
    
    reset_pal_gully_room();
    
}

int
crawl_castle(string str)
{
    
    notify_fail("Crawl where?\n");
    if (str != "castle" && str != "out of the castle" && str != "out of castle" 
    && str != "into room" && str != "through the castle" && str != "out")
    return 0;
    
    else
    say((this_player()), QCTNAME(this_player()) +
    " crawls out of the castle structure.\n");
    write("You crawl out of the castle structure back into the room.\n\n");
    this_player()->move_living("M", RDIR + "a11");
    say(QCTNAME(TP)+" arrives crawling from within the castle structure.\n.");
    return 1;
}


public void
init()
{
    ::init();
    add_action(crawl_castle, "crawl");
}


/*void
reset_room()
{
    if(!dewar)
    {
        dewar = clone_object(LIV + "dewar");
        dewar->move(TO);

        dewar2 = clone_object(LIV + "dewar");
        dewar2->move(TO);
        
        dewar3 = clone_object(LIV + "dewar");
        dewar3->move(TO);
    
    }
}*/