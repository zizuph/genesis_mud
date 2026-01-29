/* File         : /d/Khalakhor/std/room.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 1st 1999
 * Purpose      : Khalakhor standard room, to be inherited by 
 *                all domain rooms
 * Related Files: /std/room.c
 * Comments     :
 * Modifications:
 *   Added Wizard Tourist Logging code. - Tomas  June 2000
 *   Added room_tell (thanks Lucius!)  - Tomas  July 2000
 *   Stripped weather code - Teth December 2001
 *   Added Khalakhor Clock back to the domain.  Igneous Aug 2004
 *   Removed Wizard Tourist Logging code - Damaris 01/2005
 *   Added auto_fail() to exits by inheriting /lib/move
 *     (created by Lucius) - Damaris 02/2005
 *   Added add_door_exit() (created by Shiva) Added by Damaris 08/2006
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Khalakhor/sys/time.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Khalakhor/sys/properties.h"
#include "/d/Khalakhor/sys/paths.h"
#include <files.h>
#include <std.h>


inherit "/std/room";
inherit "/d/Khalakhor/std/room_tell";
inherit "/d/Khalakhor/lib/move";

// Global Vars
static mapping gNo_exit_msg = ([]);

/* Function name: create_khalakhor_room
 * Description  : The actual room constructor function
 */
void create_khalakhor_room() {}

/* Function name: create_room
 * Description  : The standard room constructor... we add our domain
 *                wide code in here and mask it so you can't overide
 *                anything placed in here.
 */
nomask void
create_room()
{
    set_terrain(TERRAIN_OUTSIDE | TERRAIN_NATURAL);
    remove_prop(ROOM_I_INSIDE);          /* Default room has heaven above */
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);  /* Default is a room */
    create_khalakhor_room();
}

/* Function name:  set_no_exit_msg
 * Description:    This function is used in your create_* function for
 *                 your room to set up alternate messages for when a
 *                 player attempts to go in a non-existant direction.
 * Arguments:      mixed dirs:  The directions we want to set the
 *                              non-standard message for.
 *                 string msg:  The message we want to print when a player
 *                              goes in one fo the dirs have it set for.
 */
public void
set_no_exit_msg(mixed dirs, string msg)
{
    int i;

    if (!pointerp(dirs))
    {
        if (dirs == "all")
        {
            dirs = ({"north", "northeast", "east", "southeast", "south",
              "southwest", "west", "northwest", "up", "down"});
        }
        else
            dirs = ({dirs});
    }
    i = -1;
    while (++i < sizeof(dirs))
        gNo_exit_msg[dirs[i]] = msg;

}

/* Function name:  unq_no_move (MASKED)
 * Description:    This function prints out the message when a player
 *                 attempts to use a non-existant exit.
 * Arguments:      string str:  The direction the player tried to go.
 * Returns:        A failure message and 0
 */
// public int
// unq_no_move(string str)
// {
//     string vb = query_verb();
// 
//     if (gNo_exit_msg[vb])
//         notify_fail(gNo_exit_msg[vb] + "\n");
//     else
//         notify_fail("There is no obvious exit "+ vb +".\n");
// 
//     return 0;
// }


int
check_time(string str)
{
    notify_fail("Check what? The time?\n");
    if (str == "time" || str == "the time")
    {
        notify_fail("You are unable to check the time "+
                    "from here.\n");
        say(QCTNAME(this_player()) + " checks the time.\n");
        return CLOCK->describe_the_time(this_object());
    }
    return 0;
}

/*
 * Function name: get_door
 * Description:   Clone a new door object.  This can be used to provide a
 *                default door object for exits created via add_door_exit().
 * Arguments:     1. (string) The path to the room on the other side of
 *                            the door.
 * Returns:       (object) A door object
 */
public varargs object
get_door(string dest)
{
    setuid();
    seteuid(getuid());
    return clone_object("/d/Khalakhor/std/door");
}

/*
 * Function name: add_door_exit
 * Description:   A handy function that automates a lot of the annoying
 *                configuration required for doors.  It creates an exit
 *                and adds a door to it all at once.
 * Arguments:     1. (object) A door object
 *                   (string) The filename of a door to be cloned
 *                    0       Use the default door, as given by get_door()
 */
public varargs void
add_door_exit(mixed door, mixed dest, string cmd, mixed block, mixed tired,
    mixed noshow)
{
    int i;

    add_exit(dest, cmd, block, tired, noshow);

    /* add_exit() will accept relative pathnames, but we want the
     * fully qualified version.  We can either evaluate the relative
     * path ourselves or let add_exit() do it and grab the result of
     * that.  I've chosen the latter.
     */
    i = member_array(cmd, query_exit_cmds());
    dest = query_exit_rooms()[i];

    setuid();
    seteuid(getuid());

    if (stringp(door))
    {
        setuid();
        seteuid(getuid());
        door = clone_object(door);
    }
    else if (!door)
    {
        door = get_door(dest);
    }

    door->set_door_exit_direction(cmd);
    door->set_door_id(dest);
    door->set_other_room(dest);
    door->move(this_object(), 1);
}

/*
 * Function name: describe_door
 * Description:   Produce a description for a door
 * Arguments:     1. (object) The door to describe
 *                2. (object) The person who should see the description
 */
public void
describe_door(object door, object for_obj)
{
    for_obj->catch_tell(
        capitalize(LANG_ADDART(door->query_door_desc(for_obj)) + ".\n"));
}

/*
 * Function name: describe_contents
 * Description:   This is called when someone looks at the room.  It is
 *                responsible for generating messages describing the items
 *                present.
 * Arguments:     1. (object)   The object (living) who is to receive the
 *                              message.
 *                2. (object *) The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    object *lv, *dd;
    string item;
    object *doors;

    for_obj->catch_tell(show_sublocs(for_obj));

    obarr -= ({ for_obj });

    lv = FILTER_LIVE(obarr);
    dd = obarr - lv;

    /* Describe doors separately */
    if (sizeof(doors = query_prop(ROOM_AO_DOOROB)))
    {
        dd -= doors;
    //    map(doors, &describe_door(, for_obj));
    }

    item = COMPOSITE_FILE->desc_dead(dd, 1);
    if (stringp(item))
    {
	for_obj->catch_tell(capitalize(item) + ".\n");
    }

    item = COMPOSITE_FILE->desc_live(lv, 1);
    if (stringp(item))
    {
	for_obj->catch_tell(capitalize(item) + ".\n");
    }
}

void
init()
{
    ::init();
    add_action(check_time, "check");
}
