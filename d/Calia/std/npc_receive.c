/* 
 * Inheritable Library Module for NPCs to receive items
 *
 * To use this module, simply follow these steps:
 * 1. Inside of enter_inv, call receive_enter_inv.
 *    Example:
 *      void enter_inv(object ob, object from)
 *      {
 *          ::enter_inv(ob, from);
 *          receive_enter_inv(ob, from);
 *      }
 * 2. Implement should_accept_item to define what npc can accept
 * 3. Define the hook_process_accept_items and hook_process_unaccept_items
 *    to handle what to do with the items that the npc wants and
 *    doesn't want.
 *      
 * Created by Petros, December 2009
*/ 

#pragma strict_types
#pragma save_binary

#include <files.h>
#include <stdproperties.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
static int                  drop_alarm, accept_alarm;
static mapping              items_to_drop = ([ ]);
static mapping              items_to_accept = ([ ]);

// Prototypes
private void        drop_items();
private void        accept_items();
private void        add_accepted_item(object obj, object from, int size = 1);
private void        add_unaccepted_item(object obj, object from, int size = 1);

/*
 * Function:    should_accept_item
 * Description: Returns whether the item should be accepted at this time.
 */
public int
should_accept_item(object obj, object from)
{
    return 0;
}

/* 
 * Function name: receive_enter_inv
 * Description:   Call this function inside enter_inv to add the received
 *                objects to a place to be processed.
 */
public void
receive_enter_inv(object ob, object from)
{
    if (objectp(ob) && objectp(from) && living(from))
    {
        int obj_size = 1; // default to one
        if (IS_HEAP_OBJECT(ob) && (obj_size = ob->num_heap()) && ob->query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        {
            // This object is about to disappear. We need to find the one that is
            // the heaped object that will remain
            object * obs = filter(all_inventory(this_object()),
                &operator(==)(ob->query_prop(HEAP_S_UNIQUE_ID), ) @ &->query_prop(HEAP_S_UNIQUE_ID));
            obs -= ({ ob }); // make sure we're not using ourself
            if (sizeof(obs))
            {
                ob = obs[0];
            }        
        }
        
        send_debug_message("npc_receive", "Receiving " + obj_size
            + " item(s).");
        if (should_accept_item(ob, from))
        {
            add_accepted_item(ob, from, obj_size);
        }
        else
        {
            add_unaccepted_item(ob, from, obj_size);
        }
    }    
}

/*
 * Function:    hook_process_accept_items
 * Description: Redefine this to process all the accepted items
 * Arguments:   mapping items - this is a mapping of the person who gave
 *                              the item to the objects that they gave.
 *                              eg. ([ player : ({ sword }) ])
 */
public void
hook_process_accept_items(mapping items)
{
}

/*
 * Function:    hook_process_unaccept_items
 * Description: Redefine this to process all the unaccepted items
 * Arguments:   mapping items - this is a mapping of the person who gave
 *                              the item to the objects that they gave.
 *                              eg. ([ player : ({ sword }) ])
 */
public void
hook_process_unaccept_items(mapping items)
{
}

private void
drop_items()
{
    mapping items_copy = items_to_drop + ([ ]);
    items_to_drop = ([ ]);
    hook_process_unaccept_items(items_copy);
}

private void
accept_items()
{
    mapping items_copy = items_to_accept + ([ ]);
    items_to_accept = ([ ]);
    hook_process_accept_items(items_copy);
}

private void
add_accepted_item(object obj, object from, int size = 1)
{
    if (!mappingp(items_to_accept[from]))
    {
        items_to_accept[from] = ([ ]);
    }
    items_to_accept[from][obj] = size;
    
    remove_alarm(accept_alarm);
    accept_alarm = set_alarm(0.5, 0.0, &accept_items());
}

private void
add_unaccepted_item(object obj, object from, int size = 1)
{
    if (!mappingp(items_to_drop[from]))
    {
        items_to_drop[from] = ([ ]);
    }
    items_to_drop[from][obj] = size;
    
    remove_alarm(drop_alarm);
    drop_alarm = set_alarm(0.5, 0.0, &drop_items());
}

public void
give_back(object obj, object player, string verb, string preposition, int size = 1)
{
    if (!objectp(obj))
    {
        command("say Hmm... I seem to have lost what I was supposed to give you!");
        return;
    }
    
    if (!IS_HEAP_OBJECT(obj))
    {
        command(verb + " " + OB_NAME(obj) + " " + preposition + " " + OB_NAME(player));
        return;
    }
    
    object to_keep;
    if (obj->num_heap() != size)
    {
        // we have to split up the obj to give back the part that was given to us
        obj->split_heap(size);
        to_keep = obj->make_leftover_heap();
    }
    if (size == 1)
    {
        command(verb + " " + OB_NAME(obj) + " " + preposition + " " + OB_NAME(player));
    }
    else
    {
        command(verb + " " + obj->short() + " " + preposition + " " + OB_NAME(player));
    }
    to_keep->move(this_object());
}

public void
give_back_helper(object obj, object player, int size = 1)
{
    give_back(obj, player, "give", "to", size);
}

