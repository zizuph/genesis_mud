/* Path to the Lord's manor I
 * Coded by Marisol (06/4/98)
 * Modify by Marisol (07/10/98) to be used as the Castle's path
 * in the village of Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_PATH;

#include <stdproperties.h>

void
create_cpath_room()
{

    set_em_long("@@special_long@@To one side of the path you can see "+
        "trees spreading up and down the hill. To the other side, a "+
        "long meadow extends along the path. In the distance "+
        "you can see a golden wheat field. The smells of "+
        "smoke and pine are in the brisk air creating a pleasant "+
        "combination. High in the sky a proud hawk flies "+
        "freely in the blue sky.");

    add_item("hawk",
        "A brown and white hawk flies silently in the blue sky.\n");

    add_item(({"meadow", "wheat field", "field"}),
        "A long meadow extends on one side of the path. Part of the "+
        "meadow is covered with golden wheat that sway soothingly "+
        "on the field.\n");

add_exit("../village_ov01", "south");
add_exit("castle_path02.c", "north");

}                       

string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you climb the path, the village is left behind. ";
    }

    filename = file_name(last_room);

    if (filename == (OV_DIR_VIL + "village_ov01"))
    {
    return "As you climb the path, the village is left behind. ";
    }

    if (filename == (OV_PATH + "castle_path02"))
    {
    return "The path slowly climb down the hill leaving the castle "+
    "behind. ";
    }

    return "The path slowly climb down the hill, leaving the castle "+
    "behind. ";
}
