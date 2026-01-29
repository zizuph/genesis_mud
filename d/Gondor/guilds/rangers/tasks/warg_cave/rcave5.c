/* /d/Gondor/guilds/rangers/warg_cave/rcave5.c
 * Coded by Tigerlily, 2004-10-29
 * Caves where white_warg lives--last task for
 * Ranger apprentices is to kill the warg in team with
 * exactly one full ranger  Rangers must track warg
 * in order to find path.
 */
#pragma strict_types

#include "cave_defs.h"

inherit CAVE_ROOM;

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string forward = "northeast";
string back = "down";

void
reset_room()
{
    // reset warg tracks
    set_tracks(forward, "warg");
}

public void
create_cave()
{
    string path_dirs;
   
    set_short("A network of caves under the White Mountains");
    path_dirs = "\n";
    set_long(&set_cave_long(path_dirs));
    add_cave_items();
    set_wandering_msg();
    add_prop(ROOM_I_LIGHT, -1); 
    add_exit(CAVE_PATH + "rcave6", forward, &find_path(forward), 0, 1);
    add_exit(CAVE_PATH + "rcave4", back, &find_path(back), 0, 1);
    add_exit(CAVE_PATH + "tr_cave8", "northwest", &find_path("northwest"), 0, 1);

    reset_room();
}

