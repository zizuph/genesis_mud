/*
 * A test of a monster that can find the shortest path to a certain room.
 *
 * Does only handle normal exits
 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

#define DEBUG(x)        find_player("ashlar")->catch_msg("PATHFINDER: " + (x) + "\n")

inherit AM_FILE

string target_room;
int find_alarm;

object *room_array;
int *parent_array;
string *cmd_array;

int current_check, max_check;

void
create_krynn_monster()
{
    set_name("pathfinder");
    add_name("pf");
}

void
stop_search()
{
    if (find_alarm)
        remove_alarm(find_alarm);
    find_alarm = 0;
}

void
clear_search()
{
    room_array =        ({ });
    parent_array =      ({ });
    cmd_array =         ({ });

    current_check = 0;
    max_check = 0;
}

varargs void
add_to_search(object room_obj, int parent_idx = -1, string cmd = "")
{
    if (!room_obj)
        return;
        
    if (member_array(room_obj, room_array) >= 0)
        return;

    room_array += ({ room_obj });
    parent_array += ({ parent_idx });
    cmd_array += ({ cmd });

    max_check++;

    if (max_check > 500)
    {
    	DEBUG("Sanity check, aborting because max_check > 500");
    	stop_search();
    }
}

void
pathfinder_fail()
{
    DEBUG("No path to target found.");
    stop_search();
}

void
pathfinder_succeed()
{
    DEBUG("Path found. Call query_found_path to retrieve it.");
    DEBUG("current_check = " + current_check + ", max_check = " + max_check);
    stop_search();
}

void
do_search()
{
    int i,j;
    string *exit_rooms, *exit_cmds;
    object tem;
	
    setuid();
    seteuid(getuid());

    for (i=0; i<10; i++)
    {
        object ob;
    	
    	if (current_check >= max_check)
    	{
    	    pathfinder_fail();
    	    return;
    	}

    	ob = room_array[current_check];

    	if (file_name(ob) == target_room)
    	{
    	    pathfinder_succeed();
    	    return;
    	}

    	exit_rooms = ob->query_exit_rooms();
    	exit_cmds = ob->query_exit_cmds();
    	tem = clone_object(NOBJ + "drink/ale1");
        for(j=0; j<sizeof(exit_rooms); j++)
        {
            catch(tem->move(exit_rooms[j]));
            add_to_search(E(tem),current_check,exit_cmds[j]);
        }
        tem->remove_object();

        current_check++;
    }
}

void
set_target_room(string tar)
{
    target_room = tar;
}

string
query_target_room()
{
    return target_room;
}

string *
recursive_find_path(int idx)
{
    if (parent_array[idx] == -1)
        return ({ });
    else
        return recursive_find_path(parent_array[idx]) + ({ cmd_array[idx] });
}

/*
 * Returns the path of commands needed to reach the target
 */
string *
query_found_path()
{
    return recursive_find_path(current_check);
}

int
start_pathfinder()
{
    if (!stringp(target_room))
        return 0;

    if (!environment())
        return 0;

    if (find_alarm)
        return 0;

    clear_search();
    add_to_search(environment());

    find_alarm = set_alarm(0.0, 2.0, do_search);

    return find_alarm;
}
