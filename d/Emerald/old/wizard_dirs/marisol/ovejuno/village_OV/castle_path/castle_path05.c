/* Path to the Lord's manor V
 * Coded by Marisol (06/15/98)
 * Modified by Marisol (07/10/98) for the Castle's path in Emerald.
 * Copyright (c) Marisol Ramos 1998 */

#include "defs.h"
inherit CASTLE_PATH;

#include <macros.h>

int block_garden();


void
create_cpath_room()
{

    set_short("A gate that closes a green-walled garden.");
    set_long("A gate rises here guarding the entrance of a "+
        "green-walled garden. The gate is all covered with ivy, "+
        "so is impossible to see the garden beyond. The castle "+
        "looms over the garden, dark and forbidden, even though "+ 
        "the bright day. High in the sky, a dark-looking "+
        "bird flies in circle over the castle. A stone-hewn "+
        "path veers northwest to the castle proper.\n");


    add_item("bird",
        "Seems that a huge vulture-like bird is hovering over the "+
        "old castle.\n");

    add_item(({"garden", "green-walled garden"}),
        "From here is hard to see what the garden look like inside "+
        "its green walls. A old gate covered with ivy seems the only "+
        "entrance to the garden.\n");

        add_item("gate",
        "A baroque, rusty, iron gate adorned with a complicated "+
        "design of flowers and leaves. Vines and ivy cover it, "+
        "making almost impossible to see through it. There seems "+
        "to be a small apperture between the vines, ivy and bars. "+
        "Maybe you can wriggle in through it.\n");

    add_item("castle",
        "An old castle rises high and forbidden. Its looms "+
        "darkly over the garden, like a huge spider looking at its "+
        "prey. There is an air of foreboding that enclosed the "+
        "structure, like a hundred eyes looking down on you.\n");          

    add_item(({"path", "ground"}),
        "This part of the path is still hard-packed earth. But this "+
        "changes as the path veers to the northwest. The path goes "+
        "from earth to square stones.\n");


    add_exit("/d/Emerald/marisol/ovejuno/garden/manor_garden01", "north",
    block_garden, 5, 1);
    add_exit("castle_path04.c", "south");
    add_exit("castle_path06.c", "northwest");


}

int
block_garden()
{
    string str;
    if (this_player()->query_average_stat()<30)
    { 
     str = " somehow manages to wriggle through the apperture.\n";
     write("You manage to wriggle through the apperture.\n");
     tell_room(this_object(), ({METNAME + str, NONMETNAME + str, ""}),
     this_player());

     return 0;
    }

    write("You can't wriggle through the apperture. You are too big.\n");
    return 1;
}

int
do_wriggle(string str)
{
    if(!strlen(str) || !parse_command(str,({}),"'through' 'apperture'"))
    {
    notify_fail(capitalize(query_verb()) + " where?\n");
    return 0;
    }

    this_player()->command("$north");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_wriggle, "wriggle");
}    
