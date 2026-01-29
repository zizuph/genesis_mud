/*
 * /d/Sparkle/area/city/bank/room/garage_hole.c
 *
 * This is the hole in the wall behind the garage
 * of the Gnomes of Genesis in Sparkle.
 * It is the location of the hammer for the hammer quest.
 *
 * Modification Log:
 *      Created Feb 2009, by Aeg (Matthew Morin)
 *      Finwe, April 2019 - Updated descriptions and made nest searchable.
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"

inherit BANK_ROOM + "bank_standard"; /* inherit basic bank file */


// sets up nest search
object scout;			/* npc */
object hammer;			/* quest item */
object joint;			/* junk item */
object dowel_s;			/* junk item */
object chronometer;		/* junk item */

int nest_searched = 0;  /* if nest was seardhed or not */

/*
 * Function name:           create_bank_room
 * Description  :           Creates a room with bank settings
 */
public void
create_bank_room()
{
    set_short("A dark hole");
    set_long("This is a dark, terrible looking hole that has been dug " +
        "into the wall. It is dark and dusty. The floor is at a slight " +
        "upward slope and the walls are made of dark stone. A nest has " +
        "been built here.\n");

	add_item( ({ "room", "hole", "here", "hole in the wall" }),
		 "This is a dead-end hole in the wall. It is dirty and unadorned. " +
        "Crawling out through the hole is the only way out of here.\n");
	add_item( ({ "decor" }),
		"This is an unadorned hole in the wall. It is round shaped, " +
        "and dark and dusty.\n");
	add_item( ({ "floor", "ground" }),
		"The floor is made of cold, dusty stone. Besides the clutter, " +
        "it is not noteworthy.\n");
	add_item( ({ "walls" }),
		"The walls are made of a dark stone. It looks roughly carved.\n");
    add_item( ({"dark stone"}),
        "The dark stone is plain looking. It is roughly cut and makes " +
        "up the walls, floor, and ceiling of the hole.\n");
	add_item( ({ "slope", "upward slope" }),
		"The floor slopes up toward a wall and down to the garage.\n");
	add_item( ({ "dust" }),
		"It is fine powder and dirt, and covers the dark hole.\n");
	add_item( ({ "clutter", "junk", "nest", "owlrat nest" }),
		"Owlrats have taken residence of this hole. They scavenge around " +
        "the building for any piece of trash they can find and bring " +
        "it here.\n");

    add_cmd_item(({"hole", "in the hole", "in hole", "through the hole", 
				"through hole", "into hole", "out" }),
                 	"crawl", "@@crawl");
	
	/* General tells */

	stop_room_tells();
	add_tell("Airflow from the hole blows some dust around.\n");

// this sets up the search routine to find something in the log
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN,"my_search");

    /* Exits */

    /* Properties */
    add_prop(ROOM_I_LIGHT, 0); /* Unlit tunnel */


} /* create_bank_room */

public int
crawl()
{
    write("You crawl into the dark hole.\n");
    this_player()->move_living("crawling through the dark hole",
               "/d/Sparkle/area/city/bank/room/garage" );
    return 1;
} /* crawl */


/*
 * Function name:        reset_room
 * Description  :        Override the standard reset_room to bring in
 *                       objects that should be here.
 * Arguments    :        none
 * Returns      :        nothing
 */
public void
reset_room()
{
    nest_searched = 0;

} /* reset_room */


mixed
my_search(object searcher, string str)
{
    if(str=="nest" || str=="owlrat nest")
    {
        if(nest_searched == 1)
        
        {
            return "You found nothing in the nest.\n";
        }
        else
        {
        // hammer
            seteuid(getuid(TO));
            hammer = clone_object("/d/Sparkle/area/city/bank/obj/quest_hammer");
            hammer->move(searcher,1);

        // joint            
            seteuid(getuid(TO));
            joint = clone_object("/d/Sparkle/area/city/bank/obj/joint");
            joint->move(searcher, 1);
            
        // clone 3 dowels    
            for (int i = 0; i < 3; ++i)
            {
                seteuid(getuid(TO));
                dowel_s = clone_object("/d/Sparkle/area/city/bank/obj/dowel_s");
                dowel_s->move(searcher,1);
            }

        // chronometer
            seteuid(getuid(TO));
            chronometer = clone_object("/d/Sparkle/area/city/bank/obj/chronometer");
            chronometer->move(searcher,1);
        }

            nest_searched = 1;
            return "You found some items in the nest log.\n";
        }

    return "You found nothing inside the nest.\n";
}
