/*
 * villa1/terrace_e.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"
#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit V1 +"housebase";

#define SEE_EAST    ({ V1 +"garden" })
#define SEE_WEST    ({ V1 +"beach_access", V1 + "terrace_w" })
#define SEE_SOUTH   ({ V1 +"living" })
#define SEE_NORTH   ({ V1 +"pool" })

public string
north_view(void)
{
    string str; 
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";
    if (sizeof(live) > 1)
	str = "are";
    else str = "is";
    return " that "+ COMPOSITE_LIVE(live) + " "+ str +" soaking in";
}

public string
east_view(void)
{
    string str;

    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return " with a mixture of herbs and flowers";
    if (sizeof(live) > 1)
	str = "seem";
    else str = "seems";

    return " where "+ COMPOSITE_LIVE(live) + " "+ str +" to be enjoying";
}

public string
west_view(void)
{
    object *live = get_view(SEE_WEST);

    if (!sizeof(live))
	return " with a much better view";
    else 
	return ", where "+ COMPOSITE_LIVE(live) + " can be seen enjoying "+
	"an even better view than this one";
}

public string
south_view(void)
{

    object *live = get_view(SEE_SOUTH);

    if (!sizeof(live))
	return "";
    else 
	return " where you can see "+ COMPOSITE_LIVE(live);    
}



/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    add_exit("garden", "northeast");
    add_exit("pool", "pool");
    add_exit("terrace_w", "northwest");
    add_exit("living", "south");

    set_short("main terrace of the villa");
    set_long("This is the main terrace at the center of the villa. "+
      "The view of the pool@@north_view@@, and the Sea of "+
      "Sybarus beyond it, is stunning. The light of the Source "+
      "glitters on the waves as they roll onto shore. The limestone "+
      "underfoot is unpolished, with a soft, chamois-like texture. "+
      "Northwest is a terrace with seating and a firepit@@west_view@@. "+
      "There is a fruit tree of some sort to the northeast, in a "+
      "garden@@east_view@@. "+
      "South is a lounging area@@south_view@@."+
      "\n");

    add_help_topic("here",  "/d/Avenir/houses/help/general");
    add_help_topic("room",  "/d/Avenir/houses/help/general");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    add_item(({"east"}), "The garden lies northeast of here.\n");
    add_item(({"west"}), "There is a seating area to the northwest.\n");
    add_item(({"north"}), "You see the sea of Sybarus and some of "+
      "the islands.\n");
    add_item(({"south"}), "The main living room is there.\n");


}
