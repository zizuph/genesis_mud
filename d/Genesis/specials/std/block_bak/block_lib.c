/*
 * Blocking Lib Functions
 *
 * This File includes utility functions used by the Block
 * ability.
 *
 * Created by Petros, November 2008
 */
 
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <files.h>
#include "block_defs.h"

// SETTERS AND GETTERS
// 
// We keep track of these properties on each blocker. The following
// functions manage these properties.
// 1. Exit - The exit that the blocker is blocking
// 2. Room - The room that the blocker is blocking
// 3. Strength - The value from 0-1500 that the blocker has to
//               prevent people from leaving. an non-existent value
//               defaults to 1500.
// 4. Blockees - List of blockees that have been blocked

public string
query_block_exit(object blocker)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        return "";
    }
    
    if (!IN_ARRAY(BLOCK_EXIT, m_indices(block_properties)))
    {
        return "";
    }
    
    return block_properties[BLOCK_EXIT];
}

public void
set_block_exit(object blocker, string exit)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        block_properties = ([ ]);
    }

    block_properties[BLOCK_EXIT] = exit;
    blocker->add_prop(BLOCK_PROP, block_properties);
}

public string
query_block_room(object blocker)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        return "";
    }
    
    if (!IN_ARRAY(BLOCK_ROOM, m_indices(block_properties)))
    {
        return "";
    }
    
    return block_properties[BLOCK_ROOM];
}

public void
set_block_room(object blocker, string room)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        block_properties = ([ ]);
    }

    block_properties[BLOCK_ROOM] = room;
    blocker->add_prop(BLOCK_PROP, block_properties);
}

public int
query_block_strength(object blocker)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        return 0;
    }
    
    if (!IN_ARRAY(BLOCK_STR, m_indices(block_properties)))
    {
        // If strength is not set, default it to 1500
        return 1500;
    }
    
    return block_properties[BLOCK_STR];
}

public void
set_block_strength(object blocker, int strength)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        block_properties = ([ ]);
    }

    block_properties[BLOCK_STR] = strength;
    blocker->add_prop(BLOCK_PROP, block_properties);
}

public void
reset_block_strength(object blocker)
{
    mixed block_properties;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        block_properties = ([ ]);
    }

    m_delkey(block_properties, BLOCK_STR);
    blocker->add_prop(BLOCK_PROP, block_properties);    
}

public int
query_block_is_blocking(object blocker, object blockee)
{
    mixed block_properties, blockees;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        return 0;
    }
    
    if (!IN_ARRAY(BLOCK_BLOCKEES, m_indices(block_properties)))
    {
        return 0;
    }
    
    blockees = block_properties[BLOCK_BLOCKEES];
    if (!pointerp(blockees))
    {
        // Not a valid list, thus cannot store blockers
        return 0;
    }
    
    return IN_ARRAY(blockee, blockees);
}

public void
set_block_is_blocking(object blocker, object blockee)
{
    mixed block_properties, blockees;
    
    block_properties = blocker->query_prop(BLOCK_PROP);
    if (!mappingp(block_properties))
    {
        block_properties = ([ ]);
    }

    if (!IN_ARRAY(BLOCK_BLOCKEES, m_indices(block_properties))
        || !pointerp(block_properties[BLOCK_BLOCKEES]))
    {
        block_properties[BLOCK_BLOCKEES] = ({ });
    }
    
    blockees = block_properties[BLOCK_BLOCKEES];
    if (!IN_ARRAY(blockee, blockees))
    {
        blockees += ({ blockee });
    }
    blockees -= ({ 0 });
    
    block_properties[BLOCK_BLOCKEES] = blockees;
    blocker->add_prop(BLOCK_PROP, block_properties);    
}

/*
 * Function:    query_other_blockees_for_exit
 * Description: This function checks the exit that the blocker is blocking
 *              to see if there are any blockees currently trying to break
 *              through. It's especially useful for determining whether
 *              we can reset the strength of the blocker. If there are
 *              still blockees, we cannot reset the strength
 * Arguments:   blocker - person blocking the exit
 * Returns:     List of blockees trying to break through
 */
public object *
query_other_blockees_for_exit(object blocker)
{
    string exit;
    object * blockees;
    
    exit = query_block_exit(blocker);
    blockees = FILTER_LIVING_OBJECTS(all_inventory(environment(blocker)));
    blockees = filter(blockees, &operator(==)(1) @ &->query_trying_to_move());
    blockees = filter(blockees, &operator(==)(exit) @ &->query_trying_to_move_direction());
    
    return blockees;
}

/*
 * Function:    notify_blockee_change_direction
 * Description: This notification function gets called by the block
 *              shadow whenever the blockee changes directions to
 *              go to a different exit. When they try to do this,
 *              we reset the blocker strength if there are no more
 *              blockees trying to leave.
 * Arguments:   blocker - the person blocking
 *              blockee - the person being blocked
 * Returns:     nothing
 */
public void
notify_blockee_change_direction(object blocker, object blockee)
{
    if (!sizeof(query_other_blockees_for_exit(blocker)))
    {
        // Reset the strength if no one else is attempting to
        // break through.
        reset_block_strength(blocker);
    }
}

/*
 * Function:    notify_blockee_leaves_room
 * Description: This notification function gets called by the block
 *              shadow whenever the blockee leaves the room successfully
 *              When this happens, we reset the blocker strength if 
 *              there are no more blockees trying to leave.
 * Arguments:   blocker - the person blocking
 *              blockee - the person being blocked
 * Returns:     nothing
 */
public void
notify_blockee_leaves_room(object blocker, object blockee)
{
    if (!sizeof(query_other_blockees_for_exit(blocker)))
    {
        // Reset the strength if no one else is attempting to
        // break through.
        reset_block_strength(blocker);
    }    
}
