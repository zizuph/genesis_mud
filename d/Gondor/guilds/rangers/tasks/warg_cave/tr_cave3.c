/* /d/Gondor/guilds/rangers/warg_cave/tr_cave3.c
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

string forward = "west";
string back = "south";
object troll1, troll2, troll3;

void
reset_room()
{
    // reset warg tracks
    set_tracks(forward, "troll");
    if (!objectp(troll1))
    {
        troll1 = clone_object(NPC_DIR + "hilltroll");
        troll1->move(TO, 1);
        troll1->command("emote ambles in.");
    }
    if (!objectp(troll2))
    {
        troll2 = clone_object(NPC_DIR + "hilltroll2");
        troll2->move(TO, 1);
        troll2->command("emote stumbles in.");
    }
    if (!objectp(troll3))
    {
        troll3 = clone_object(NPC_DIR + "hilltroll3");
        troll3->move(TO, 1);
        troll3->command("emote staggers in.");
    }
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
    add_exit(CAVE_PATH + "tr_cave4", forward, &find_path(forward), 0, 1);
    add_exit(CAVE_PATH + "tr_cave2", back, &find_path(back), 0, 1);
    reset_room();
}

