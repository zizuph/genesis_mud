#include "defs.h"

inherit M1_IN_BASE;

#include <stdproperties.h>

public void
reset_room()
{
    remove_exit("west");
}

void
create_m1_room()
{
     add_exit("m1_41", "south");

     add_prop(OBJ_S_SEARCH_FUN, "search_me");
}
 
public string
search_me(object searcher, string what)
{
    if (what != "shelves")
    {
        return 0;
    }

    if (member_array("west", query_exit_cmds()) >= 0)
    {
        return 0;
    }

    add_exit("m1_32", "west");
    return "As you search the shelves, an opening appears " +
        "to the west!\n";
}
