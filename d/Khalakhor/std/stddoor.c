/* 
 * door.c
 *
 * This is the standard door object.
 *
 * User function in this object:
 * -----------------------------
 *
 * Contructor: create_door()
 *
 * Arguments:	        s = string, i = integer, o = object, m = mixed
 *			*x = list of given type.
 *			** mandatory function. 
 *
 * All set functions has a corresponding query function defined.
 *
 *
** set_other_room(m)	- Call this function with the name of the room where
 *			  the other side of the door is.
 *
** set_door_id(m)	- Call this function with a unique name for the door,
 *			  this should really be something strange that no
 *			  other door in the same room can be called. "door"
 *			  is *not* a good choise...
 *
 * set_open(i)		- Call if 1 if open, 0 if closed.
 *
 * add_lock(m)          - Add a lock to the door.
 *
 * Don't forget to set the special door properties if the standard
 * settings aren't what you want. 
 *
 * The standard door is open, has no locks, weighs 60 kg and has a volume of
 * 80 liters. The height of the standard door is 3 meters.
 *
 * There are a number of message hooks that can be redefined to alter some
 * of the default messages.  These are:
 *
 * Function hook                        Describes
 *=======================================================================
 * closed_door_fail_pass_hook        Trying to pass through a closed door
 * locked_door_fail_open_hook        Trying to open a locked door
 * open_door_fail_open_hook          Trying to open an open door
 * door_open_hook                    Opening the door
 * closed_door_fail_close_hook       Trying to close a closed door
 * door_close_hook                   Closing the door
 * open_door_fail_lock_hook          Trying to lock an open door
 * open_door_fail_unlock_hook        Trying to unlock an open door
 * open_door_fail_pick_hook          Trying to pick an open door
 * door_knock_hook                   Knocking on the door
 *
 * In addition, there are several functions that can be redefined to prevent
 * several door actions from occuring.  These are:
 *
 * prevent_pass_door
 * prevent_open_door
 * prevent_close_door
 * prevent_lock_door
 * prevent_unlock_door
 * prevent_pick_door
 * prevent_knock_door
 *
 * Any of these functions which return a value of 1 will block the related
 * actions.  You will need to print your own failure messages.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <cmdparse.h>
#include <language.h>

#ifndef LOCK_OBJECT
#define LOCK_OBJECT "/d/Wiz/shiva/open/doors/lockob"
#endif

string	door_id,	/* A unique (?) id of the door */
        exit_dir;

mixed   other_room;

object	other_door; /* The door at the other side */

int     door_open;

object *door_locks = ({});

/* 
 * Some prototypes 
 */
void set_other_room(string name);
void set_door_id(string id);
void load_other_door();
void do_open_door();
void do_close_door();
void do_pass_door();
void do_knock_door();
void set_open(int i);
int  query_locked();
mixed query_other_room();
void add_lock(mixed lock);

/*
 * Function name: create_door
 * Description:   Constructor for doors.
 */
public void
create_door()
{
}

/*
 * Function name: create_container
 * Description:   Initialize default values.
 */
void
create_container()
{
    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_VOLUME, 80000);
    add_prop(DOOR_I_HEIGHT, 300);
    add_prop(CONT_M_NO_REM, "It is firmly affixed to the door.\n");
    add_prop(CONT_M_NO_INS, "There is no place to hang it.\n");
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_WEIGHT, 2000000);
    add_prop(CONT_I_MAX_VOLUME, 2000000);

    set_open(1);

    create_door();
}

/*
 * Function name: reset_door
 * Description:   Reset the door
 */
void
reset_door() 
{
}

/*
 * Function name: reset_object
 * Description:   Reset the object
 */
nomask void
reset_container()
{
    reset_door();
}

/*
 * Function name: query_door_desc
 * Description:   Give the description of the door as it should appear in
 *                a room.
 * Arguments:     object for_obj - the onlooker
 * Returns:       string description of the door
 */
public varargs string
query_door_desc(object for_obj)
{
    return ((door_open ? "open " : "") + short(for_obj) +
           (strlen(exit_dir) ? " leading " + exit_dir : ""));
}

/*
 * Function name: describe_contents
 * Description:   Used to describe to provide a description of the "contents"
 *                of this door.
 * Arguments:     1. (object) The object for which we're generating the desc
 *                2. (object *) The items we are describing.
 */
public void
describe_contents(object for_obj, object *obarr)
{
    if (!sizeof(obarr))
    {
        return;
    }

    ::describe_contents(for_obj, obarr);
}

/*
 * Function name: closed_door_fail_pass_hook
 * Description:   Redefine this to change the message given when someone
 *                tries to pass through a closed door.
 */
public void
closed_door_fail_pass_hook()
{
    write("The " + short() + " is closed.\n");
}

/*
 * Function name: prevent_pass_door
 * Description:   Redefine this to prevent passage through the door.  You
 *                should provide your own failure messages.
 * Returns:       1 - passage prevented
 *                0 - passage allowed
 */
public int
prevent_pass_door()
{
    return 0;
}

/*
 * Function name: pass_door
 * Description:   Try to pass through the door
 */
public void
pass_door()
{
    if (!other_door)
    {
	load_other_door();
    }

    if (door_open)
    {
        if (prevent_pass_door())
	{
            return;
	}

        do_pass_door();
    }
    else
    {
        closed_door_fail_pass_hook();
    }
}

/*
 * Function name: door_pass_cmd
 * Description:   This gets called when the "pass" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the pass command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_pass_cmd(string arg)
{
    mixed obs;

    if (strlen(arg))
    {
        if (!parse_command(arg, all_inventory(environment()),
            "[through] [the] %i", obs) ||
            !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
	{
            notify_fail(capitalize(query_verb()) + " what?\n");
            return 0;
	}

        if (sizeof(obs) > 1)
	{
            notify_fail("You can only " + query_verb() + " one thing " +
                "at a time.\n");
            return 0;
	}

        if (obs[0] != this_object())
	{
            return 0;
	}
    }

    pass_door();
    return 1;
}

/*
 * Function name: do_pass_door
 * Description:   Move the living through the door
 */
public void
do_pass_door()
{
    this_player()->move_living(query_verb(), query_other_room());
}

/* 
 * Function name: prevent_open_door
 * Description:   Redefine this to prevent opening of the door.  You should
 *                print your own failure messages.
 * Returns:       1 - opening prevented
 *                0 - opening allowed
 */
public int
prevent_open_door()
{
    return 0;
}

/* 
 * Function name: locked_door_fail_open_hook
 * Description:   Redefine this to change the message given when the door
 *                could not be opened because it is locked.
 */
public void
locked_door_fail_open_hook()
{
    write("The " + short() + " is locked.\n");
}

/*
 * Function name: open_door_fail_open_hook
 * Description:   Redefine this to change the message given whe the door
 *                could not be opened because it is already open.
 */    
public void
open_door_fail_open_hook()
{
    write("The " + short() + " is already open.\n");
}

/*
 * Function name: door_open_hook
 * Description:   Redefine this to change the message given when the door
 *                is opened.
 */
public void
door_open_hook()
{
    write("Ok.\n");
    say(QCTNAME(this_player()) + " opens the " + short() + ".\n");
    tell_room(query_other_room(), LANG_THESHORT(other_door) + " opens.\n");
}

/*
 * Function name: open_door
 * Description:   Try to open the door.
 */
public void
open_door()
{
    if (!other_door)
    {
	load_other_door();
    }

    if (!door_open)
    {
	if (query_locked())
	{
            locked_door_fail_open_hook();
            return;
	}

        if (prevent_open_door())
	{
            return;
	}

	do_open_door();
	other_door->do_open_door();
        door_open_hook();
    }
    else
    {
	open_door_fail_open_hook();
    }
}

/*
 * Function name: door_close_cmd
 * Description:   This gets called when the "open" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the open command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_open_cmd(string arg)
{
    mixed *obs;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, all_inventory(environment()),
        "[the] %i", obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
        return 0;
    }

    if ((sizeof(obs) > 1) || (obs[0] != this_object()))
    {
        return 0;
    }

    open_door();
    return 1;
}

/* 
 * Function name: do_open_door
 * Description:   Open the door 
 */
void
do_open_door()
{
    door_open = 1;
}

/*
 * Function name: closed_door_fail_close_hook
 * Description:   Redefine this to change the message given when the door
 *                cannot be closed because it is already closed.
 */
public int
closed_door_fail_close_hook()
{
    write("The " + short() + " is already closed.\n");
    return 1;
}

/*
 * Function name: door_close_hook
 * Description:   Redefine this to change the message given when the door
 *                is closed.
 */
public void
door_close_hook()
{
    write("Ok.\n");
    say(QCTNAME(this_player()) + " closes the " + short() + ".\n");
    tell_room(query_other_room(), LANG_THESHORT(other_door) + " closes.\n");
}

/*
 * Function name: prevent_close_door
 * Description:   Redefine this to prevent opening of the door.  You must
 *                print your own failure message.
 * Returns:       1 - closing prevented
 *                0 - closing allowed
 */
public int
prevent_close_door()
{
    return 0;
}

/*
 * Function name: close_door
 * Description:   Try to close the door.
 */
public void
close_door()
{
    if (!other_door)
    {
	load_other_door();
    }

    if (door_open)
    {
        if (prevent_close_door())
	{
            return;
	}

	do_close_door();
	other_door->do_close_door();
        door_close_hook();
    }
    else
    {
        closed_door_fail_close_hook();
    }
}

/*
 * Function name: door_close_cmd
 * Description:   This gets called when the "close" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the close command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_close_cmd(string arg)
{
    mixed *obs;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, all_inventory(environment()),
        "[the] %i", obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
        return 0;
    }

    if ((sizeof(obs) > 1) || (obs[0] != this_object()))
    {
        return 0;
    }

    close_door();
    return 1;
}

/*
 * Function name: do_close_door
 * Description:   Close the door
 */
void
do_close_door()
{
    door_open = 0;
}

/*
 * Function name: open_door_fail_lock_hook
 * Description:   Redefine this to change the message give when the door
 *                cannot be locked because it is open.
 */
public void
open_door_fail_lock_hook()
{
    write("You must close the " + short() + " first.\n");
}

/*
 * Function name: prevent_lock_door
 * Description:   Redefine this to prevent the door from being locked.  You
 *                must print your own failure message.
 * Returns:       1 - lock prevented
 *                0 - lock allowed
 */
public int
prevent_lock_door()
{
    return 0;
}

/*
 * Function name: lock
 * Description:   Called from the lock, this is a hook for the door to
 *                prevent the lock from being locked.
 * Arguments:	  object lock - The lock that is being locked
 *                object key  - The key being used.
 * Returns:       1 - We allow the lock to be locked
 *                0 - We do not allow the lock to be locked
 */
public int
lock(object lock, object key)
{
    if (!other_door)
    {
	load_other_door();
    }

    if (door_open)
    {
	open_door_fail_lock_hook();
        return 0;
    }

    if (prevent_lock_door())
    {
        return 0;
    }

    return 1;
}

/*
 * Function name: door_lock_cmd
 * Description:   This gets called when the "lock" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the lock command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_lock_cmd(string arg)
{
    string door_str, key_str, lock_str;
    object key, lock;
    mixed *obs;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!sscanf(arg, "%s with %s", door_str, key_str))
    {
        door_str = arg;
    }

    sscanf(door_str, "%s on %s", lock_str, door_str);

    if (!parse_command(door_str, all_inventory(environment()), "[the] %i",
        obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (sizeof(obs) > 1)
    {
        notify_fail("You can only " + query_verb() +
            " one thing at a time.\n");
        return 0;
    }

    if (obs[0] != this_object())
    {
        return 0;
    }

    if (lock_str)
    {
        if (!parse_command(lock_str, door_locks, "[the] %i", obs) ||
            !sizeof(obs = NORMAL_ACCESS(obs, "lock_access", this_object())))
	{
            notify_fail(capitalize(query_verb()) + " what on the " +
                short() + "?\n");
            return 0;
	}

        if (sizeof(obs) > 1)
	{
            notify_fail("You can only " + query_verb() + " one thing " +
                "at a time.\n");
            return 0;
	}

        lock = obs[0];
    }
    else if (sizeof(door_locks) < 1)
    {
        notify_fail("There is no lock on the " + short() + ".\n");
	return 0;
    }
    else if (sizeof(door_locks) > 1)
    {
        notify_fail(capitalize(query_verb()) + " what on the " +
            short() + "?\n");
        return 0;
    }
    else
    {
        lock = door_locks[0];
    }
    
    if (strlen(key_str))
    {
        if (!parse_command(key_str, all_inventory(this_player()), "[the] %i",
            obs) ||
            !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
	{
            notify_fail(capitalize(query_verb()) + " the " + short() +
                " with what?\n");
            return 0;
	}

        if (sizeof(obs) > 1)
	{
            notify_fail("You can only " + query_verb() + " the " + 
                lock->short() + " with one item.\n");
            return 0;
	}

        key = obs[0];
    }

    lock->try_lock(key);
    return 1;
}

/*
 * Function name: open_door_fail_unlock_hook
 * Description:   Redefine this to change the message given when the door
 *                cannot be unlocked because it is open.
 */
public void
open_door_fail_unlock_hook()
{
    write("The " + short() + " is open.  There is no reason to " +
        query_verb() + " it.\n");
}

/* 
 * Function name: prevent_unlock_door
 * Description:   Redefine this to prevent the door from being unlocked.  You
 *                must print your own failure message.
 * Returns:       1 - unlock prevented
 *                0 - unlock allowed
 */
public int
prevent_unlock_door()
{
    return 0;
}

/*
 * Function name: unlock
 * Description:   Called from the lock, this is a hook for the door to
 *                prevent the lock from being unlocked.
 * Arguments:	  object lock - The lock that is being unlocked
 *                object key  - The key being used.
 * Returns:       1 - We allow the lock to be unlocked
 *                0 - We do not allow the lock to be unlocked
 */
public int
unlock(object lock, object key)
{
    if (!other_door)
    {
	load_other_door();
    }

    if (door_open)
    {
	open_door_fail_unlock_hook();
        return 0;
    }

    if (prevent_unlock_door())
    {
        return 0;
    }

    return 1;
}

public int
lock_access(object ob)
{
    /* We want all items */
    return 1;
}

/*
 * Function name: door_unlock_cmd
 * Description:   This gets called when the "unlock" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the unlock command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_unlock_cmd(string arg)
{
    string door_str, key_str, lock_str;
    object key, lock;
    mixed *obs;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!sscanf(arg, "%s with %s", door_str, key_str))
    {
        door_str = arg;
    }

    sscanf(door_str, "%s on %s", lock_str, door_str);

    if (!parse_command(door_str, all_inventory(environment()), "[the] %i",
        obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (sizeof(obs) > 1)
    {
        notify_fail("You can only " + query_verb() +
            " one thing at a time.\n");
        return 0;
    }

    if (obs[0] != this_object())
    {
        return 0;
    }

    if (lock_str)
    {
        /* We need to use "lock_access" in the NORMAL_ACCESS below to
         * block filtering of items not in the actor's inventory/environment.
	 * Perhaps it would be better not to use NORMAL_ACCESS at all.
         */
        if (!parse_command(lock_str, door_locks, "[the] %i", obs) ||
            !sizeof(obs = NORMAL_ACCESS(obs, "lock_access", this_object())))
	{
            notify_fail(capitalize(query_verb()) + " what on the " +
                short() + "?\n");
            return 0;
	}

        if (sizeof(obs) > 1)
	{
            notify_fail("You can only " + query_verb() + " one thing " +
                "at a time.\n");
            return 0;
	}

        lock = obs[0];
    }
    else if (sizeof(door_locks) < 1)
    {
        notify_fail("There is no lock on the " + short() + ".\n");
	return 0;
    }
    else if (sizeof(door_locks) > 1)
    {
        notify_fail(capitalize(query_verb()) + " what on the " +
            short() + "?\n");
        return 0;
    }
    else
    {
        lock = door_locks[0];
    }
    
    if (strlen(key_str))
    {
        if (!parse_command(key_str, all_inventory(this_player()), "[the] %i",
            obs) ||
            !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
	{
            notify_fail(capitalize(query_verb()) + " the " + short() +
                " with what?\n");
            return 0;
	}

        if (sizeof(obs) > 1)
	{
            notify_fail("You can only " + query_verb() + " the " + 
                lock->short() + " with one item.\n");
            return 0;
	}

        key = obs[0];
    }

    lock->try_unlock(key);
    return 1;
}

/*
 * Function name: open_door_fail_pick_hook
 * Description:   Redefine this to change the message given when the door
 *                cannot be picked because it is open.
 */
public void
open_door_fail_pick_hook()
{
    write("The " + short() + " is open.  There is no reason to " +
        query_verb() + " it.\n");
}

/*
 * Function name: prevent_pick_door
 * Description:   Redefine this to prevent the door from being picked.  You
 *                must print your own failure message
 * Returns:       1 - pick prevented
 *                0 - pick allowed
 */
public int
prevent_pick_door()
{
    return 0;
}

/*
 * Function name: pick
 * Description:   This is called from the lock to allow the door to block
 *                an attempt to pick the lock.
 * Returns:       1 - door cannot be picked
 *                0 - door can be picked
 */
public int
pick(object lock)
{
    if (!other_door)
    {
        load_other_door();
    }

    if (door_open)
    {
        open_door_fail_pick_hook();
        return 0;
    }

    if (prevent_pick_door())
    {
        return 0;
    }

    return 1;
}

/*
 * Function name: pick_lock
 * Description:   Pick the lock of the door.
 * Arguments:	  str - arguments given
 */
public void
pick_lock(object lock)
{
    if (!other_door)
    {
	load_other_door();
    }

    lock->try_pick_lock(this_player());
    return;
}

/*
 * Function name: door_pick_cmd
 * Description:   This gets called when the "pick" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the pick command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_pick_cmd(string arg)
{
    string door_str, lock_str;
    object lock;
    mixed *obs;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!sscanf(arg, "%s on %s", lock_str, door_str))
    {
        notify_fail(capitalize(query_verb()) + " which lock on what?\n");
        return 0;
    }

    if (!parse_command(door_str, all_inventory(environment()), "[the] %i",
        obs) || !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " " + door_str + " on what?\n");
        return 0;
    }

    if (sizeof(obs) > 1)
    {
        notify_fail("You can only " + query_verb() + " one thing at a time.\n");
        return 0;
    }

    if (obs[0] != this_object())
    {
        return 0;
    }

    if (!parse_command(lock_str, door_locks, "[the] %i", obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs, "lock_access", this_object())))
    {
        notify_fail(capitalize(query_verb()) + " what on the " +
            short() + "?\n");
        return 0;
    }
    
    if (sizeof(obs) > 1)
    {
        notify_fail("You can only " + query_verb() + " one thing " +
            "at a time.\n");
        return 0;
    }
    
    pick_lock(obs[0]);
    return 1;
}
    
/*
 * Function name: door_knock_hook
 * Description:   Redefine this to change the message given when the door
 *                is knocked on.
 */
public void
door_knock_hook()
{
    if (!door_open)
    {
    	write("You "+ query_verb() + " on the " + short() + ".\n");
    	say(QCTNAME(this_player()) + " " + query_verb() + "s on the " +
    	     short() + ".\n");
    	tell_room(query_other_room(), "You hear someone " + query_verb() +
    	    " on " + LANG_THESHORT(other_door) + ".\n");
    }
    else
    {
    	write("You " + query_verb() + " on the open " + short() + ".\n");
    	say(QCTNAME(this_player()) + " " + query_verb() +
    	    "s on the open " + short() + ".\n");
    	tell_room(query_other_room(), "You hear someone foolishly " + query_verb() +
    	    " on the open " + short() + ".\n");
    }
}

/*
 * Function name: prevent_knock_door
 * Description:   Redefine this to prevent knocking on the door.  You must
 *                print your own failure message.
 * Returns:       1 - knocking prevented
 *                0 - knocking allowed
 */
public int
prevent_knock_door()
{
    return 0;
}

/*
 * Function name: knock_door
 * Description:   Try to knock on the door
 */
public void
knock_door()
{
    if (!other_door)
    {
	load_other_door();
    }

    if (prevent_knock_door())
    {
        return;
    }

    door_knock_hook();
    do_knock_door();
}

/*
 * Function name: door_knock_cmd
 * Description:   This gets called when the "knock" command(s) are
 *                executed.
 * Arguments:     string arg - Arguments to the knock command
 * Returns:       1/0 - success/syntax failure
 */
public int
door_knock_cmd(string arg)
{
    mixed *obs;

    if (!strlen(arg))
    {
        return 0;
    }

    if (!parse_command(arg, all_inventory(environment()),
        "[on] [the] %i", obs) ||
        !sizeof(obs = NORMAL_ACCESS(obs, 0, 0)))
    {
        return 0;
    }

    if ((sizeof(obs) > 1) || (obs[0] != this_object()))
    {
        return 0;
    }

    knock_door();
    return 1;
}

/*
 * Function name: do_knock_door
 * Description:   knock on the door
 */
public void
do_knock_door()
{
}

/*
 * Function name: set_open
 * Description:   Set the open staus of the door
 * Arguments:     int open - 1 (open) or 0 (closed)
 */
public void
set_open(int open)
{
    door_open = open;
}

/*
 * Function name: query_open
 * Description:   Get the open status of the door
 * Returns:       1/0 - open/closed
 */
public int
query_open()
{
    return door_open;
}

/*
 * Function name: set_other_room
 * Description:   Indicate where the other side of the door is.
 * Arguments:     The filename of the other room (suggested) or the room
 *                object itself.
 */
void
set_other_room(mixed room)
{
    other_room = room;
}

/*
 * Function name: query_other_room
 * Description:   Find out which room holds the other side of the door.
 * Returns:       The filename of the other room or the room object itself.
 */
mixed
query_other_room()
{
    return other_room;
}

/*
 * Function name: check_locks
 * Description:   Find out if this side of the door is locked.  Since doors
 *                can have more than one lock, we return 1 if any lock is
 *                locked.
 * Returns:       1/0 - locked/unlocked
 */
public int
check_locks()
{
    int i;

    for (i = 0; i < sizeof(door_locks); i++)
    {
        if (door_locks[i]->query_locked())
	{
            return 1;
	}
    }

    return 0;
}

/*
 * Function name: query_locked
 * Description:   Check to see if the door (either side) is locked.
 * Returns:       1/0 - locked/unlocked
 */
public int
query_locked()
{
    if (!other_door)
    {
        load_other_door();
    }

    return (check_locks() || other_door->check_locks());
}

/*
 * Function name: add_lock
 * Description:   Add a lock to the door.  This can be called multiple times
 *                to add more locks.
 * Arguments:     mixed lock - A single lock object or an array of lock objects
 */
public void
add_lock(mixed lock)
{
    door_locks += (pointerp(lock) ? lock : ({ lock }));
    lock->set_locked_object(this_object());
    lock->move(this_object(), 1);
}

/*
 * Function name: get_default_lock
 * Description:   get a new default lock object
 */
public object
get_default_lock()
{
    setuid();
    seteuid(getuid());
    return clone_object(LOCK_OBJECT);
}
    
/*
 * Function name: add_default_lock
 * Description:   Add a simple, default lock to the door without having to
 *                configure your own.
 * Returns:       The default lock that was added.
 */
public object
add_default_lock()
{
    object lock = get_default_lock();
    add_lock(lock);
    return lock;
}

/*
 * Function name: query_locks
 * Description:   Get all the locks on this door
 * Returns:       An array of lock objects.
 */
public object *
query_locks()
{
    return door_locks + ({});
}

/*
 * Function name: set_door_id
 * Description:   Set the id of the door
 */
void	
set_door_id(string id) 		
{ 
    door_id = id; 
}

/*
 * Function name: query_door_id
 * Description:   Get the door's unique id
 */
public string
query_door_id()
{
    return door_id;
}

/*
 * Function name: set_door_exit_direction
 * Description:   This can be used to indicate that a door leads in a
 *                particular direction ("south", for instance).  Setting
 *                an exit direction will add a short message to the door's
 *                description when viewed in the room.  It will also add
 *                pass commands for the direction.
 * Arguments:     string dir - the direction ("north", "south", "east", etc.)
 */
public void
set_door_exit_direction(string dir)
{
    exit_dir = dir;
}

/*
 * Function name: query_door_exit_direction
 * Description:   Get the exit direction for this door
 */
public string
query_door_exit_direction()
{
    return exit_dir;
}

/*
 * Function name: query_other_door_id
 * Description:   Get the id of the other side of this door.  By default,
 *                this is the same id as this door, but this function can
 *                be redefined to return a different value.
 * Returns:       The id of the other side of this door.
 */      
public mixed
query_other_door_id()
{
    return door_id;
}

/*
 * Function name: query_other_door
 * Description:   Get the other door object pointer. The other
 *		  door will be loaded if neccesary. If that proovs
 *		  impossible, this door will autodestruct.
 */
public object
query_other_door()
{
    return (other_door || load_other_door());
}

/*
 * Function name: pair_locks
 * Description:   Most locks have two sides: one on each side of the door.
 *                When both sides of the door have been loaded, this function
 *                will match each lock on this door with its partner on the
 *                the other side of the door.
 * Arguments:     object odoor - the other side of the door.
 */
public void
pair_locks(object odoor)
{
    int i, j;
    object *olocks = odoor->query_locks();

    for (i = 0; i < sizeof(door_locks); i++)
    {
        for (j = 0; j < sizeof(olocks); j++)
	{
            if (door_locks[i]->query_lock_id() == olocks[j]->query_lock_id())
	    {
                door_locks[i]->set_other_lock(olocks[j]);
                olocks[j]->set_other_lock(door_locks[i]);
                break;
	    }
	}
    }
}

/*
 * Function name: load_other_door
 * Description:   Try to load the door in the other room. If this
 *		  fails, autodestruct.
 */
public object
load_other_door()
{
    object *doors, oroom;
    int i;

    setuid();
    seteuid(getuid());

    /*
     * No other side or already loaded.
     */
    if (other_door || !other_room || 
        (stringp(other_room) && !strlen(other_room)))
    {
	return 0;
    }

    if (stringp(other_room))
    {
    	/*
    	 * Try to load the other side.
    	 */
    	if (!(oroom = find_object(other_room)))
    	{
	    LOAD_ERR(other_room);
	    if (!(oroom = find_object(other_room)))
	    {
		write("Error in loading other side of door: " + other_room +
                    ".\n");
		remove_object();
		return 0;
	    }
	}
    }
    else if (objectp(other_room))
    {
        oroom = other_room;
    }
    else
    {
        // Invalid type for other room
        return 0;
    }

    doors = (object *)oroom->query_prop(ROOM_AO_DOOROB);

    for (i = 0; i < sizeof(doors); i++)
    {
        if (doors[i]->query_door_id() == query_other_door_id())
	{
            other_door = doors[i];
            pair_locks(other_door);
            return other_door;
	}
    }

    write("Other side of door is not in room after it has been loaded: " +
	  (stringp(other_room) ? other_room : file_name(other_room)) + ".\n");
    remove_object();
    return 0;
}

/*
 * Function name: add_door_info
 * Description:   Add information about this door to the room it occupies.
 * Arguments:	  dest - The room that contains the door.
 */
static void
add_door_info(object dest)
{
    object *doors = (object *)dest->query_prop(ROOM_AO_DOOROB);

    if (!doors)
    {
        doors = ({});
    }

    dest->add_prop(ROOM_AO_DOOROB, doors + ({ this_object() }));
}

/*
 * Function name: remove_door_info
 * Description:   Remove information about this door from the room it occupies
 * Arguments:	  dest - The room that contains the door.
 */
static void
remove_door_info(object dest)
{
    object *doors = (object *)dest->query_prop(ROOM_AO_DOOROB);

    if (!sizeof(doors))
    {
        return;
    }

    dest->add_prop(ROOM_AO_DOOROB, doors - ({ this_object() }));
}

/*
 * Function name: enter_env
 * Description:   The door enters a room, activate it.
 * Arguments:	  dest - The destination room,
 * 		  old - Where it came from
 */
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    add_door_info(dest); 
}

/*
 * Function name: leave_env
 * Description:   The door leaves a room, remove it.
 * Arguments:     old - Where it came from,
 * 		  dest - The destination room
 */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    if (!old)
    {
	return;
    }

    remove_door_info(old);
}

/*
 * Function name: add_door_command
 * Description:   Add one or more commands to this door.
 * Arguments:     mixed cmd  - a command string or array of command strings
 *                function f - the command function
 */ 
public void
add_door_command(mixed cmd, function f)
{
    if (pointerp(cmd))
    {
        map(cmd, &add_action(f));
    }
    else
    {
        add_action(f, cmd);
    }
}

/*
 * Function name: add_pass_command
 * Description:   Add one or more commands that allow the user to pass
 *                through the door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */
public void
add_pass_command(mixed cmd)
{
    add_door_command(cmd, door_pass_cmd);
}

/*
 * Function name: add_open_command
 * Description:   Add one or more commands that allow the user to open the
 *                door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */
public void
add_open_command(mixed cmd)
{
    add_door_command(cmd, door_open_cmd);
}

/*
 * Function name: add_close_command
 * Description:   Add one or more commands that allow the user to close the
 *                door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */

public void
add_close_command(mixed cmd)
{
    add_door_command(cmd, door_close_cmd);
}

/*
 * Function name: add_knock_command
 * Description:   Add one or more commands that allow the user to knock on
 *                the door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */
public void
add_knock_command(mixed cmd)
{
    add_door_command(cmd, door_knock_cmd);
}

/*
 * Function name: add_lock_command
 * Description:   Add one or more commands that allow the user to lock the
 *                door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */
public void
add_lock_command(mixed cmd)
{
    add_door_command(cmd, door_lock_cmd);
}

/*
 * Function name: add_unlock_command
 * Description:   Add one or more commands that allow the user to unlock
 *                the door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */
public void
add_unlock_command(mixed cmd)
{
    add_door_command(cmd, door_unlock_cmd);
}

/*
 * Function name: add_pick_command
 * Description:   Add one or more commands that allow the user to pick the
 *                lock(s) on the door.
 * Arguments:     mixed cmd - a command string or array of command strings
 */
public void
add_pick_command(mixed cmd)
{
    add_door_command(cmd, door_pick_cmd);
}

/*
 * Function name: init_door
 * Description:   Add some default commands to the door.
 */    
public void
init_door()
{
    add_pass_command("enter");

    if (exit_dir)
    {
        add_pass_command(({ exit_dir, exit_dir[0..0] }));
    }

    add_open_command("open");
    add_close_command("close");
    add_knock_command(({ "knock", "pound" }));
    add_lock_command("lock");
    add_unlock_command("unlock");
    add_pick_command("pick");
}

/*
 * Function name: init
 * Description:   Initalize the door actions
 */
void
init()
{
    ::init();
    init_door();
}
