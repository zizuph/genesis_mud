/*
 *  Stream Library
 *
 *  Some rooms in the game will want to have a flowing stream of some
 *  kind (fresh water, sewer, etc.) This library gives that functionality
 *  to a room when it inherits it.
 *
 *  Usage Instructions:
 *  Step 1: Add the following inherit to the top of the file
 *
 *     inherit "/d/Sparkle/lib/stream_lib";
 *  
 *  Step 2: Set the flow speed and downstream direction
 *     set_flow_speed(5.0);
 *     set_downstream_dir("south"); // must be the same exit as used in add_exit
 *
 *  Step 3: Mask the enter_inv and call enter_inv_stream
 *
 *      public void
 *      enter_inv(object ob, object from)
 *      {
 *          enter_inv_stream(ob, from);
 *          // ::enter_inv must be called after enter_inv_stream to prevent
 *          // heap merges
 *          ::enter_inv(ob, from);
 *      }
 *  
 *  Step 4: Mask the hooks in order to change the default messages
 *     public void hook_no_downstream_exit(object ob);
 *     public void hook_object_departs_downstream(object ob);
 *     public void hook_object_arrives_upstream(object ob, string source_direction);
 *
 *
 *  Created February 2010, by Matthew Morin (Aeg)
 *                          & Cooper Sherry (Gorboth)
 *  Adapted into a library, April 2010 by Petros
 *  Copied to Earthsea, MAR 2021 by Aeg
 */
#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include <macros.h>

/* Global Variables */
public float    Flow_Speed = 5.0;        /* How fast is the current here?     */
public string   Downstream_Dir = 0;      /* The downstream direction.         */
public int      Enabled = 1;             /* Whether the stream behavior is enabled */

/* Prototypes */
public void         enter_inv_stream(object ob, object from);
public void         move_downstream(object ob);
public void         set_flow_speed(float f)       { Flow_Speed = f;        }
public float        get_flow_speed()              { return Flow_Speed;     }
public void         set_downstream_dir(string s)  { Downstream_Dir = s;    }
public string       get_downstream_dir()          { return Downstream_Dir; }
public void         set_downstream_enabled(int enabled) { Enabled = enabled;     }
public int          get_downstream_enabled()            { return Enabled;        }

/* Defines */
#define OLD_HEAP_S_UNIQUE_ID    "_old_heap_s_unique_id"

/* Hooks to be defined */
public void hook_no_downstream_exit(object ob);
public void hook_object_departs_downstream(object ob);
public void hook_object_arrives_upstream(object ob, string source_direction);


/*
 * Function:    can_move_downstream
 * Description: Maskable function that can help define what can move downstream
 *              from this object or not.
 */
public int
can_move_downstream(object ob)
{
    if (!get_downstream_enabled())
    {
        return 0;
    }
    
    // By default, anything that is living and/or cannot be moved cannot 
    // move downstream. Everything else does.
    if (!objectp(ob)
        || IS_LIVING_OBJECT(ob)
        || ob->query_prop(OBJ_M_NO_GET))
    {
        return 0;
    }
    
    return 1;
}

public void
restore_heap_id(object ob)
{
    mixed old_heap_id;
    if (!objectp(ob)
        || !(old_heap_id = ob->query_prop(OLD_HEAP_S_UNIQUE_ID)))
    {
        return;
    }
    
    ob->add_prop(HEAP_S_UNIQUE_ID, old_heap_id);
    ob->remove_prop(OLD_HEAP_S_UNIQUE_ID);
}

/*
 * Function:    enter_inv_stream
 * Description: This should be called inside the room's enter_inv function.
 *              It will test to see if the object should be moved downstream.
 *              If so, it will call move_downstream
 */
public void
enter_inv_stream(object ob, object from)
{
    if (!can_move_downstream(ob))
    {
        return;
    }
    
    mixed heap_id;
    if (IS_HEAP_OBJECT(ob) && !ob->query_prop(OLD_HEAP_S_UNIQUE_ID))
    {
        heap_id = ob->query_prop(HEAP_S_UNIQUE_ID);
        foreach (string ob_name : ob->query_names())
        {
            if (ob_name[0..2] == "ob_")
            {
                ob->add_prop(HEAP_S_UNIQUE_ID, ob_name);
                ob->add_prop(OLD_HEAP_S_UNIQUE_ID, heap_id);
                break;
            }
        }
    }

    set_alarm(get_flow_speed(), 0.0, &move_downstream(ob));
} /* enter_inv */

public string *
query_clean_exits_for_room(object room)
{
    if (!objectp(room))
    {
        return 0;
    }
    string * avail_exits = room->query_exit();
    if (!sizeof(avail_exits))
    {
        return ({ });
    }    
    for (int index = 0; index < sizeof(avail_exits); index += 3)
    {
        if (wildmatch("*.c", avail_exits[index]))
        {
            // Clean up the .c at the end
            avail_exits[index] = avail_exits[index][..-3];
        }
    }
    return avail_exits;
}

/*
 * Function name:        move_downstream
 * Description  :        move floating items downstream
 * Arguments    :        object ob - the floating item to move
 */
public void
move_downstream(object ob)
{
    if (!objectp(ob))
    {
        return;
    }
    if (IS_HEAP_OBJECT(ob))
    {
        restore_heap_id(ob); // have to undo whatever changes were made before.
        if (environment(ob) != this_object())
        {
            ob->force_heap_merge();
            return;
        }
    }
    
    if (!objectp(ob) || environment(ob) != this_object())
    {
        return;
    }
    
    int exit_index = -1;
    string * avail_exits = query_clean_exits_for_room(this_object());
    if (!strlen(get_downstream_dir())
        || !sizeof(avail_exits)
        || (exit_index = member_array(get_downstream_dir(), avail_exits)) == -1)
    {
        hook_no_downstream_exit(ob);
        return;
    }
    
    string next_room = avail_exits[exit_index - 1];
    ob->move(next_room);
    hook_object_departs_downstream(ob);
    next_room->notify_object_arrives_upstream(ob, this_object());
} /* move_downstream */

/*
 * Function:    notify_object_arrives_upstream
 * Description: This function looks through the existing exits and tries
 *              to find out where the object came from to send the
 *              right message about the source direction.
 */
public void
notify_object_arrives_upstream(object ob, object prev_room)
{
    if (!objectp(ob) || !objectp(prev_room))
    {
        return;
    }
    // Look for the direction that the object came from
    int exit_index = -1;
    string * avail_exits = query_clean_exits_for_room(this_object());
    if (!sizeof(avail_exits)
        || (exit_index = member_array(MASTER_OB(prev_room), avail_exits)) == -1)
    {
        hook_object_arrives_upstream(ob, "");
        return;
    }
    string source_direction = avail_exits[exit_index + 1];    
    hook_object_arrives_upstream(ob, source_direction);
}

// HOOKS TO BE DEFINED
public void
hook_no_downstream_exit(object ob)
{
    if (!objectp(ob))
    {
        return;
    }
    tell_room(this_object(), capitalize(ob->short())
      + " swirls around in the water, moving with"
      + " the current, but doesn't go anywhere.\n");    
}

public void
hook_object_departs_downstream(object ob)
{
    if (!objectp(ob))
    {
        return;
    }
    tell_room(this_object(), capitalize(ob->short()) + " is carried past"
      + " and disappears to the " + get_downstream_dir() + ".\n");    
}

public void
hook_object_arrives_upstream(object ob, string source_direction)
{
    if (!objectp(ob))
    {
        return;
    }
    
    if (!strlen(source_direction))
    {
        tell_room(this_object(), capitalize(ob->short()) + " arrives from"
          + " somewhere, carried by the water.\n");
        return;
    }
    tell_room(this_object(), capitalize(ob->short()) + " arrives from"
      + " the " + source_direction + ", in the current of the "
      + "water.\n"); 
}
