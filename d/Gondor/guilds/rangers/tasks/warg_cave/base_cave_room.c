/*/d/Gondor/guilds/rangers/tasks/warg_cave/base_cave_room.c
 * Tigerlily, October, 2004
 * Base room for ranger caves
 * Rooms for apprentice task 8
 *  path to warg set by 'tracks'
 *  Other paths go to troll caves
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room.c"; 

#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
/*
 *  Global variables
 */

/*
 *  Prototypes
 */
public int    add_cave_items();
public string set_cave_long(string path_dirs);
void          set_wandering_msg();
public int    find_path(string dir);
public int    set_tracks(string dir, string race);

string
set_cave_long(string path_dirs = "")
{
    string desc;

    desc = "A network of caves and tunnels runs under the " +
        "mountains. There are no distinguishing features " +
        "or landmarks. The path is shrouded in a mysterious " +
        "dark fog so that it is difficult to get one's bearings. " +
        "Debris is scattered around the rocky " +
        "floor, and the walls are covered with some kind of " +
        "fungus. A foul smell permeates the air. ";
    desc += path_dirs;
    return desc;
}

void
add_cave_items()
{
    add_item(({"cave", "network of caves", "tunnels", "caves"}),
        "You are deep within a network of caves and tunnels that " +
        "extends under the White Mountains.\n");
    add_item(({"landmarks", "features"}), 
        "In the dark underworld of tunnels there is nothing " +
        "to distinguish one direction from another.\n");
    add_item(({"debris", "floor", "rocky floor"}),
        "The rocky floor has debris cluttering it. You " +
        "notice sticks, leaves, bones, and an occasional " +
        "partially eaten carcass of some animal.\n");
    add_item(({"walls", "fungus"}),
        "The rocky walls of the tunnel are covered in " +
        "some sort of fungus-like excretion.\n");
    add_item(({"fog", "dark fog", "mysterious dark fog", "bearings"}),
        "There is some sort of supernatural fog that shrouds " +
        "the path, preventing you from getting a sense of " +
        "your location and direction. It seems as though " +
        "there is some evil agency at work " +
        "to prevent progress in any direction.\n");
    add_item(({"path", "bearings"}),
        "The path you are standing on is " +
        "shrouded in a mysterious dark fog making it difficult " +
        "to see where it leads in any direction.\n");

}


void
set_wandering_msg()
{
    string *avail_exits = query_exit_cmds();
    string *all_exits = ({"north", "northeast",
        "east", "southeast", "south", "southwest",
        "west", "northwest", "up", "down" });
    string *non_exits = ({});

    non_exits = all_exits - avail_exits;
    set_no_exit_msg(non_exits, "You wander around lost but " +
        "manage to return to where you started.\n");
    return;
}
/*
 *
 *  Purpose:  Measures player's ability to find path 
 *
 */
int
find_path(string dir)
{
    object tp = this_player();

    if (tp->resolve_task(TASK_ROUTINE, ({TS_INT, SS_TRACKING, 
       SS_LOC_SENSE, SS_AWARENESS})) > 0)
    {
       write("You follow the path " + dir + ".\n");
       return 0; 
    }
    write("You wander around lost but manage to return to " +
        "where you started.\n");
    return 1;
}

public void
hook_smelled(string str)
{
    write("The foul stench of wild beasts mixed with the smell " +
        "of rotting carcasses assails your nostrils.\n");
    return;
}

public int
set_tracks(string dir, string race)
{
    add_prop(ROOM_S_DIR,({ dir, race }));
    return 1;
}

void
create_cave()
{
}

void
create_gondor()
{
    create_cave();
}

