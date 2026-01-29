/*
 * villa1/beach_access.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"
#include <stdproperties.h>

inherit V1 +"housebase";

#include <composite.h>

#define SEE_EAST    ({ V1 + "terrace_w", V1 +"pool" })

public string
east_view(void)
{
    object *live = get_view(SEE_EAST);

    if (!sizeof(live))
	return "";

    return ", where you can see "+
    COMPOSITE_LIVE(live) + " enjoying the sea air";
}

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */

void 
create_house_room()
{
    add_exit("terrace_w", "east");
    add_exit("kitchen", "southeast");
    // down to beach stairs. They will end with a jump down and no way back up.

    set_items_outdoor();
    set_items_stone();

    set_short("top of stairs to beach");
    set_long("This is the far western corner of the villa grounds. " +
      "From here you can see the dark waters of the sea rolling " +
      "against the shoreline below. "+
      "To the west you can make out the flames of the dark fortress "+
      "which stands between the Underdark and the civiliation "+
      "of Sybarus. "+
      "East of here is a large terrace and a pool@@east_view@@. " +
      "South is a door that opens into the kitchen, where " +
      "it smells like something is cooking. " +
      "There is a set of stairs spiralling down toward the beach. " +
      "\n");

    add_help_topic("here",  "/d/Avenir/houses/help/general");
    add_help_topic("room",  "/d/Avenir/houses/help/general");

    add_item(({"door", "south door", "kitchen door"}),
      "A wide door that allows access between the kitchen " +
      "and the terrace.\n");
    add_item(({"garden", "small garden"}), "There is a small garden at "+ 
      "the far east side of the villa grounds, past the pool.\n"); 
    add_item(({"stairs"}), "A set of stairs spirals down into the "+
      "living stone of the cavern wall.\n");	
    add_item(({"east"}), "There is a terrace with a firepit and "+
      "some chairs west of here.\n");
    add_item(({"west"}), "There is nothing but natural stone there.\n");
    add_item(({"north"}), "You see the sea of Sybarus and some of "+
      "the islands.\n");
    add_item(({"south"}), "The kitchen is south of here.\n");


}
