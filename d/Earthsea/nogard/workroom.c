/* Last edited: Nogard,  04-29-1998 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Earthsea/nogard/defs.h"

void
create_room()
{
    set_short("A small, simple study");
    set_long("You are in a plain, simple study. Shimmering portals on "+
        "the walls seem to reach destinations all over the World.\n");

    add_item(({"portal","portals"}),("Examining each of them, you see "+
        "that they reach into different places.\nThey seem to sizzle "+
        "and shimmer with electricity.\n"));

    add_exit("/d/Earthsea/workroom.c", "Earthsea", "@@check_exit");
    add_exit("/d/Genesis/start/human/town/tower","sparkle","@@check_exit");
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_LIGHT,1);
}

int
check_exit()
{
    if(TP->query_wiz_level())
        return 0;
    write("Unseen forces prevent you from using the portals. You get the "+
        "feeling you could always go 'back' to where you came from.\n");
    return 1;
}

int
let_mortals_back(string s)
{
    string last_location;

    last_location = TP->query_prop("_player_transed_from");
    tell_room(last_location,QCTNAME(TP)+" enters from the beyond.\n");
    TP->move_living("back to whence they came", last_location);
    return 1;
}

int
query_prevent_snoop()
{
    return 1;
}

void
init()
{
    ::init();

    add_action("let_mortals_back","back");
}
