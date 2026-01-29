/*
 * Hallway in the Union guildhall
 *  Cirion 032096
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

public object door;

public void
union_room(void)
{
    set_short("eastern passage");
    set_long("The hall ends here before a magnificent door of "+
	"solid oak, adorned with images of waves and flames, "+
	"intertwining so they seem to go on forever.@@door_desc@@ "+
	"The passageway is lined with lustrous green stone walls "+
	"that extend back to the west.\n");

    add_item(({"floor","ground","basalt"}),
	"The floor is made from greyish basalt, expertly fitted "+
	"together so that no seams show.\n");
    add_item(({"seam","seams"}), "You cannot see them.\n");
    add_item(({"wall","walls"}), "The walls are made from "+
	"a smooth yellow-green stone that seems more like "+
	"gemstone than anything else.\n");
    add_item(({"roof","ceiling"}),
	"It is perfectly flat and unadorned.\n");

    add_cmd_item(({"wall","walls","stone"}),({"touch","feel"}),
	"The walls are smooth, almost silken.\n");

    add_exit("hall_ne2", "west");

    add_object(OBJ +"libdoorw");
}

public string
door_desc(void)
{
    if (!objectp(door))
	door = present("_union_door");

    if (door->query_open())
    {
	return " The door stands open, leading into a large "+
	    "room with high shelves.";
    }

    return " The door stands shut.";
}
