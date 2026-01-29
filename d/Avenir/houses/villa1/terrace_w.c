/*
 * villa1/terrace_w.c
 *
 * Lilith, Feb 2022
 *
 */

#pragma strict_types

#include "villa1.h"

inherit V1 +"housebase";
inherit "/d/Gondor/open/fireplace/fireplace";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

#define SEE_EAST    ({ V1 +"pool" })
#define SEE_WEST    ({ V1 +"beach_access" })
#define SEE_SOUTH   ({ V1 +"living", V1 +"terrace_c" })


public string
east_view(void)
{
    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return "";

    return " with "+
    COMPOSITE_LIVE(live) + " soaking in it";
}


public string
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return "a stairwell lies west";
    else 
	return COMPOSITE_LIVE(live) + " is standing near a stairwell";
}

public string
south_view(void)
{
    object *live = get_view(SEE_SOUTH);

    if (!sizeof(live))
	return "";
    if (sizeof(live) > 1)
	return " where "+ COMPOSITE_LIVE(live) + " appear to be relaxing";
    else
	return " where "+ COMPOSITE_LIVE(live) + " appears to be relaxing";    

}


/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 
create_house_room()
{
    room_add_object(HOBJ + "chair_sling_e");
    room_add_object(HOBJ + "chair_sling_w");
    room_add_object(HOBJ + "bench_obsidian");

    add_exit("beach_access", "west");
    add_exit("kitchen", "south");
    add_exit("terrace_c", "southeast");
    add_exit("pool", "pool");

    set_items_outdoor();
    set_items_stone();
    set_fire_container("firepit");

    set_short("terrace seating area by the pool");
    set_long("This is a terrace with a spectacular view of the Sea "+
      "of Sybarus. Many meters below is a lovely white sand beach. "+
      "Two sling chairs and an obsidian bench provide seating around "+
      "a firepit that can provide warmth when the air is chilly. "+
      "The east edge of the terrace becomes a large hot spring pool"+
      "@@east_view@@, while @@west_view@@. " +
      "Beyond it you can make out the flames of the dark fortress "+
      "which stands guard between the Underdark and the civiliation "+
      "of Sybarus. Southeast is a terrace and beyond it, a "+
      "lounging area with luxury couches@@south_view@@. "+
      "A delicious aroma wafts over from the kitchen to the south" +
      "west.\n");

    add_help_topic("here",  "/d/Avenir/houses/help/terrace_help");
    add_help_topic("room",  "/d/Avenir/houses/help/terrace_help");	

    add_item( ({"door", "south door", "kitchen door"}),
      "A wide door that allows access between the kitchen " +
      "and the terrace.\n");
    add_item(({"garden", "small garden"}), "There is a small garden at "+ 
      "the far east side of the villa grounds, past the pool.\n"); 
    add_item(({"stairs"}), "A set of stairs spirals down into the "+
      "living stone of the cavern wall.\n");	
    add_item(({"pool", "hot spring pool", "bottom", "bottom of pool"}),
      "The bottom of the pool is tiled in lapis lazuli, "+
      "giving the warm water of the hot spring a stunning "+
      "azure blue color. Wisps of mist float here and there "+
      "along the surface of the water, evidence that it is "+
      "much warmer than the surrounding air.\n");		
    add_item(({"firepit", "fire"}),
      "A hollow has been carved into the limestone and wood "+
      "stacked inside for a fire.\n");
    add_item(({"east"}), "The pool lies east of here.\n");
    add_item(({"west"}), "There is a set of stairs leading down.\n");
    add_item(({"north"}), "You see the sea of Sybarus and some of "+
      "the islands.\n");
    add_item(({"south"}), "The kitchen is south of here.\n");


}

/*
 * init - use to add the commands to the room.
 */
void 
init()
{
    ::init();
    // add the fire-related commands from Gondor.
    ::init_fire();
}
