/*
 * /d/Emerald/std/room.c
 * 
 * All rooms in Emerald should inherit this file.
 *
 * Added functionality:
 * - Easier handling of clone handler objects through set_clone_handler()
 * - Automatic formatting of long descriptions through set_em_long()
 * - Support for regions through set_region_manager()
 * - Easier creation of doors through add_door_exit()
 * - Support for "persistent objects"  
 * - Set_no_exit_msg for unique no obvious exit messages (Gorboth, 11.02)
 * - Added try_item() to assist with add_item overlap (Gorboth, 4.03)
 */

inherit "/std/room";

#include "/d/Emerald/sys/macros.h"
#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/sys/properties.h"
#include "/d/Emerald/sys/pom.h"
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <language.h>

static string clone_handler;
static string region_manager = "";
public int loading_pobs = 0;
static mapping  No_exit_msg = ([]);     /* custom no-exit msgs          */

public void load_persistent_objects();

public void     set_no_exit_msg(mixed dir, string msg);
/*
 * Function name: create_emerald_room
 * Description:   Constructor for Emerald rooms.  Redefine this to
 *                configure your room.
 */
public void
create_emerald_room()
{
}

/*
 * Function name: get_default_region_manager
 * Description:   It is assumed that a room's region manager is called
 *                "region.c".  This function checks for the presence of such
 *                a region manager in the specified directory.
 * Arguments:     1. (string) The directory in which to look for the region
 *                            manager.
 * Returns:       (string) The full path to the region manager or an empty
 *                         string if none is found.
 */
public string
get_default_region_manager(string dir)
{
    string mngr, tmp_mngr;

    mngr = tmp_mngr = dir + "/region";

    if (file_size(mngr + ".c") > 0)
    {
        while (strlen(tmp_mngr = tmp_mngr->redirect_region_manager()))
        {
            mngr = tmp_mngr;
        }

        return mngr;
    }

    return "";
}

/*
 * Function name: create_room
 * Description:   Constructor for standard rooms.
 */
void
create_room()
{
    /* See if we can find the region manager on our own */
    string this_dir = implode(explode(file_name(this_object()), "/")[..-2], "/");
    catch(region_manager = get_default_region_manager(this_dir));

    load_persistent_objects();

    create_emerald_room();

    /* If there is a region manager and no terrain type is set, use the
     * default as given by the manager.
     */
    if (strlen(region_manager) && !query_prop(ROOM_I_TERRAIN_TYPE))
    {
        add_prop(ROOM_I_TERRAIN_TYPE, region_manager->query_terrain());
    }

    // There is no actual sunlight in Emerald, however the type of light
    // that is there always counts as sunlight (indoors or out)
    if (member_array(ROOM_I_SUNLIGHT, query_props()) == -1)
    {
        add_prop(ROOM_I_SUNLIGHT, max(0, query_prop(ROOM_I_LIGHT) * 3));
    }
}

/* 
 * Function name: set_clone_handler
 * Description:   If this room should load a clone handler, use this
 *                function to set the path to the clone handler.
 * Arguments:     string path - The path to the clone handler
 */
void
set_clone_handler(string path)
{
    clone_handler = path;
}

/*
 * Function name: set_em_long
 * Description:   Use this rather than set_long() to get the special
 *                Emerald formatting for room long descriptions.
 * Arguments:     string s - the room's long description
 */
void
set_em_long(string s)
{
    set_long(s + "\n");
}

/*
 * Function name: set_region_manager
 * Description:   Designate the path to the region manager for this
 *                room.
 * Arguments:     string s - the path to the region manager
 */
void
set_region_manager(string s)
{
    region_manager = s;
}

string
query_region_manager()
{
    return region_manager;
}

/*
 * Function name: init
 * Description:   Called when a living encounters (enters) the room.
 */
void
init()
{
    ::init();
   
    /* Make sure the clone handler is loaded */
    if (strlen(clone_handler))
    {
        LOAD_CLONE_HANDLER(clone_handler);
    }
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
    return clone_object(EMERALD_DOOR_OBJ);
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
        map(doors, &describe_door(, for_obj));
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

/*
 * Function name: add_persistent_object
 * Description:   Registers a "persistent object" in this room.  A persistent
 *                object gets added to the room when it is loaded as if
 *                it had been added explicitly by the coder.
 * Arguments:     1. (mixed) The object or its filename
 */
public void
add_persistent_object(mixed persistent_object)
{
    setuid();
    seteuid(getuid());
    POM_ADD(persistent_object,
	    this_object(),
	    persistent_object->query_subloc());
}

/*
 * Function name: remove_persistent_object
 * Description:   Unregisters a "persistent object" in this room.  See
 *                add_persistent_object
 * Arguments:     1. (mixed) The object or its filename
 */
public void
remove_persistent_object(mixed persistent_object)
{
    setuid();
    seteuid(getuid());
    POM_REMOVE(POM_GET_ID(persistent_object), this_object());
}

/*
 * Function name: load_persistent_objects
 * Description:   Load, clone, and move persistent objects for this room.
 */
public void
load_persistent_objects()
{
    setuid();
    seteuid(getuid());

    // I hate using global flags like this, but I'm hard pressed to find
    // a better solution without overcomplicating matters.
    loading_pobs = 1;
    POM_LOAD(this_object());
    loading_pobs = 0;
}

/*
 * Function name: check_persistent_object
 * Description:   Determine whether the given object is a valid "persistent
 *                object" in this room.
 * Arguments:     1. (object) The object to test
 * Returns:       1/0 - Object is persistent/Object is not persistent
 */
public int
check_persistent_object(object ob)
{
    return 0;
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (loading_pobs || !check_persistent_object(ob))
    {
        return;
    }

    add_persistent_object(ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!check_persistent_object(ob))
    {            
        return;
    }

    remove_persistent_object(ob);
}


/*
 * From: /d/Gondor/std/room.c
 *
 * Function name:       set_no_exit_msg
 * Description  :       set the custom no-exit msg for direction(s)
 * Arguments    :       mixed dir -- either a string or an array of strings;
 *                                   each string is a direction for which
 *                                   this room does not have an exit.
 *                      string msg -- the msg for these directions
 *
 * So instead of "There is no obvious exit west.", you can tell
 * players "You wander west among the trees for a bit, then return
 * to the road."
 */
public void
set_no_exit_msg(mixed dir, string msg)
{
    int         i, n;

    if ( pointerp(dir) )
    {
        for ( i = 0, n = sizeof(dir); i < n; ++i )
            No_exit_msg[dir[i]] = msg;
    }
    else if ( stringp(dir) && strlen(dir) )
    {
        No_exit_msg[dir] = msg;
    }
} /* set_no_exit_msg */


/*
 * Function name: unq_no_move
 * Description  : mask parent to do custom msgs for 'normal' but
 *                nonexistant directions.  Here, 'normal'
 *                exits are north, southeast, down, etcetera.
 * Arguments    : string str - the command line argument.
 * Returns      : int 0 - always.
 */
public int
unq_no_move(string str)
{
    string      vb = query_verb();

    if ( strlen(No_exit_msg[vb]) )         /* custom msg */
        notify_fail(No_exit_msg[vb]);
    else                                /* oh, well */
        notify_fail("There is no obvious exit "+vb+".\n");
    return 0;
}


/*
 * Function name:       try_item
 * Description  :       checks to see if an item already exists
 *                      within a given object, and if it does not, it then
 *                      adds it as add_item() would.
 * Arguments    :       mixed names --  string or array of strings, the
 *                                      item name(s).
 *                      mixed desc -- string or function, the description.
 * Returns      :       int -- the number of items added
 */
public int
try_item(mixed names, mixed desc)
{
    int         i;
    string      *exists;

    if (pointerp(names)) 
    { 
        exists = ({});
        for (i = 0; i < sizeof(names); i++) 
        {
            if (item_id(names[i])) 
            {
                exists += ({ names[i] });
            }
        }
        names -= exists;
        if ((i = sizeof(names)))
        {
            add_item(names, desc);
        }
    } 
    else if (!TO->item_id(names))
    {
        add_item(names, desc);
        i = 1;
    }
    return i;   /* # of items added */
} /* try_item */
