/* 	forest1.c			Styles.   3 Mar 1993
 */
// modified 1999.05.19 Cirion: added entrance to monks guild section

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "wild.h"

void
create_room()
{
    set_short("Green forest");
    set_long("\n"+
             "You are standing in a luscious green forest listening to the\n"+
             "many birds in the air. A sense of ease and tranquillity rests\n"+
             "over this place. Between the trees to the far west, you\n"+
             "can see the mountains.\n"+
             "");

    add_exit(THIS_DIR + "slope","west");
    add_exit(THIS_DIR + "orc_road3","south");
    add_exit(THIS_DIR + "orc_road2f","southeast",0,1,1);
    add_exit(THIS_DIR + "orc_road4","southwest",0,1,1);
//    add_exit ("/d/Genesis/guilds/monks/room/path1", "north");

    add_item(({"mountains","trees","forest" }),
             "");
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_wide.txt");
}

/*
 * Called to verify that the player is a monk, used to shut down
 * the guild and prevent access if the Dragon Order is closed.
 */
int check_monk ()
    {
    if (!(this_player()->m_query_monk()))
        {
        write("The path is too overgrown, for now.\n");
        return 1;
        }

    return 0;
    }


