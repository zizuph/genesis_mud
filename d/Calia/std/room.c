/*
 * - /d/Calia/std/room.c
 *   
 * This is a standard room based on Raumdor's.
 * 
 */
#pragma no_clone
#pragma strict_types
#pragma save_binary


#include <stdproperties.h>
#include <language.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/std/room";

inherit "/d/Calia/lib/move";
inherit "/d/Calia/lib/room_tell";
inherit "/d/Calia/lib/clone_move";

static mixed obj_dlong,      /* Daytime long description */
             obj_nlong,      /* Nighttime long description */
             obj_nitems,     /* The items (pseudo look) of this object */
             obj_ditems;     /* The items (pseudo look) of this object */


static void
create_room()
{
//    ::create_room();
}

/*
 * This will setup room_tells if the room has any.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
	start_room_tells();
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
    return clone_object("/d/Calia/std/door");
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
