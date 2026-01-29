/*
 * villa1/front_hall.c
 *
 * Lilith, Nov 2021
 *
 */

#pragma strict_types

#include "villa1.h"
#include <stdproperties.h>

inherit V1 +"housebase";

object table;

#include <composite.h>

#define SEE_NORTH	({ V1 + "living" })
#define SEE_SOUTH	({ V1 + "w_garden" })

public string
north_view(void)
{
    object *live = get_view(SEE_NORTH);

    if (!sizeof(live))
	return "";

    return " where you can see "+
    COMPOSITE_LIVE(live) + ",";
}

public string
south_view(void)
{
    object *live = get_view(SEE_SOUTH);

    if (!sizeof(live))
	return "";

    return ", where "+
    COMPOSITE_LIVE(live) + " seems to be enjoying a quiet moment";
}


public string
table_inv(void)
{
    if (!table) return "";
    return table->describe_table();
}

/*
 * Function name:        create_house_room()
 * Description  :        Creates a house room from from the base file
 *                       "housebase.c"
 */
void 
create_house_room()
{
    table = clone_object(HOBJ +"table_v1_front");	
    table->move(this_object());

    set_short("front hall");
    set_long("This is the front hall of the villa. It opens "+
      "north onto a covered terrace that is the main lounging "+
      "area,@@north_view@@ and south toward the water garden and the "+
      "private entrance@@south_view@@. Two wings extend to the east "+
      "and west, one being the owner's suite and the other, "+
      "the kitchen and dining area. @@table_inv@@ "+
      "The creamy limestone floors "+
      "flow toward white onyx walls that glow faintly in "+
      "the light of the Source.\n");

    add_exit("w_garden", "south");
    add_exit("living", "north");
    add_exit("bedroom", "east");
    add_exit("kitchen", "west");

    add_help_topic("here",  "/d/Avenir/houses/help/general");
    add_help_topic("room",  "/d/Avenir/houses/help/general");

    set_items_stone();
    add_item(({"ceiling", "glass", "panes", "glass panes", "up"}),
      "Panes of clear glass are fitted between blocks of stone that "+
      "arch above your head to form a ceiling that gives a light and "+
      "airy feeling to the room.\n");
    add_item(({"hall", "front hall", "main hall"}),
      "This is the front hall of one of the private villas in Sybarus. "+
      "It is mostly made of stone and glass.\n");
    add_item(({"east"}), "The bedroom suite lies to the east.\n");
    add_item(({"west"}), "The kitchen lies is the west.\n");
    add_item(({"north"}), "The living areas of the villa are to "+
      "the north.\n");
    add_item(({"south"}), "The water garden and the entrance to the "+
      "villa are south of here.\n");

}
