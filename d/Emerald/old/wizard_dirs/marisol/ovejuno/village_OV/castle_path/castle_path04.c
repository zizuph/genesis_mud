/* Path to the Lord's manor IIII
 * Coded by Marisol (06/13/98)
 * Modify by Marisol (07/10/98) for the Castle's path in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#pragma strict_types
#include "defs.h"
inherit CASTLE_PATH;

#include <stdproperties.h>

void
create_cpath_room()
{

    set_em_long("@@special_long@@"+
        "Green grass cover this part of the meadow. The path continues "+
        "a little further to an enclosed garden that rises in front of "+
        "the castle. In the distance, you can see a field of wheat. The "+
        "smells of smoke and pine are in the brisk air creating a "+
        "pleasant combination for the senses. High in the sky, a "+
        "dark-looking bird flies in circle over the castle.");

    add_item(({"meadow", "wheat field", "field"}),
        "A long meadow extends on one side of the path. Part of the "+
        "meadow is covered with golden wheat that sway soothingly "+
        "on the field.\n");                                                                       

    add_item("bird",
        "Seems that a huge vulture-like bird is hovering over the "+        
        "old mansion.\n");

    add_item(({"garden", "enclosed garden"}),
        "From here is hard to see what the garden look like inside "+
        "its green walls. A old gate covered with ivy seems the only "+
        "entrance to the garden.\n");

    add_item("gate",
        "A tall gate covered with ivy. It is hard to see from here its "+
        "details.\n");

    add_item("castle",
        "An old castle rises high and forbidden. It looms "+
        "darkly over the garden, like a huge spider looking at its "+
        "prey. There is an air of foreboding that enclosed the "+
        "structure, like hundred eyes looking down on you.\n");

    add_exit("castle_path03.c", "south");
    add_exit("castle_path05.c", "north");
    

}             

string
special_long()
{
    object last_room = this_player()->query_prop(LIVE_O_LAST_ROOM);
    string filename;

    if (!last_room)
    {
        return "As you finish to climb the path, the castle's dark "+
        "shape rises ominously. The trees line stops here. ";
    }

    filename = file_name(last_room);

    if (filename == (OV_PATH + "castle_path03"))
    {
    return "As you finish to climb the path, the castle's dark "+
           "shape rises ominously. The trees line stops here. ";
    }

    if (filename == (OV_PATH + "castle_path05"))
    {
    return "As you start climbing down the hill, the castle is left "+
    "behind. The trees line starts here. ";
    }

    return "As you start climb down the hill, the castle is left "+
    "behind. The trees line starts here. ";
}
