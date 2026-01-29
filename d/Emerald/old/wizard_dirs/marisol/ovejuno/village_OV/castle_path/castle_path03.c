/* Path to the Lord's manor III
 * Coded by Marisol (06/11/98)
 * Modify by Marisol (07/10/98) for the Castle's path in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_PATH;

#include <stdproperties.h>

void
create_cpath_room()
{

    set_em_long("@@special_long@@On one side of the path, trees are "+
        "set in a straight line. On the other side, a long meadow "+
        "spreads along the path. The wind caresses playfully the high "+
        "stalks of a wheat field. The smells of smoke and pine are in "+
        "the brisk air creating a pleasant combination for the senses. "+
        "High in the sky, cotton-like clouds travel freely in the blue "+
        "sky.");

    add_item(({"meadow", "wheat field", "field"}),
        "A long meadow extends on one side of the path. Part of the "+
        "meadow is covered with golden wheat that sway soothingly "+
        "on the field.\n");


    add_item("clouds",
        "Cotton-like clouds trail lazily with the sea breeze. If you "+
        "look closely, you can see the silhouttes of huge ships "+
        "sailing in the blue sky.\n");                     

    add_exit("castle_path02.c", "south");
    add_exit("castle_path04.c", "north");


}                                        

string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you climb the path, you approach slowly the castle. ";
    }

    filename = file_name(last_room);

    if (filename == (OV_PATH + "castle_path02"))
    {
    return "As you climb the path, you approach slowly the castle. ";
    }

    if (filename == (OV_PATH + "castle_path04"))
    {
    return "The path slowly climb down the hill leaving the castle "+
    "behind. ";
    }

    return "The path slowly climb down the hill, leaving the castle "+
    "behind. ";
}
