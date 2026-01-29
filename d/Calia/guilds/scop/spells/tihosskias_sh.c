/* 
 * Tihosskias Room Shadow
 *
 * Due to a bug in the interaction between the tihosskias object and
 * abilities that prevent players from leaving the room (block), we
 * need to use a shadow so that the negative effects are applied only
 * when someone actually LEAVES the room, rather than when they
 * attempt to do so. Otherwise, this spell becomes a rather nasty
 * death trap.
 *
 * Created by Petros, March 2010
 */
#pragma strict_types

#include "defs.h"
#include <files.h>

inherit "/std/shadow";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function:    has_tihosskias_shadow
 * Description: If the room is shadowed by this object, then we
 *              return 1.
 */
public int
has_tihosskias_shadow()
{
    return 1;
}

/*
 * Function:    remove_tihosskias_shadow
 * Description: Removes the tihosskias shadow from the room when it
 *              is done.
 */
public void
remove_tihosskias_shadow()
{
    remove_shadow();
}

public object
find_tihosskias_object(object destination)
{
    if (!objectp(destination))
    {
        return 0;
    }
    
    object * wall_objects = filter(all_inventory(shadow_who), &->id("_SCOP_shadow_wall"));
    foreach (object wall_object : wall_objects)
    {
        // See if the destination matches the blocked exit
        string exit = wall_object->query_blocked_exit();
        int exit_position = member_array(exit, shadow_who->query_exit());
        if (exit_position <= 0) // not found
        {
            continue;
        }
        string exit_room = shadow_who->query_exit()[exit_position - 1];
        if (strlen(exit_room) > 0
            && wildmatch(MASTER_OB(destination) + "*", exit_room))
        {
            return wall_object;
        }
    }
    
    // Didn't find it
    return 0;
}

/* 
 * Function:    leave_inv
 * Description: Called when objects leave this container or when an
 *              object is about to change its weight/volume/light status.
 * Arguments:   ob: The object that just left this inventory.
 *              to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    send_debug_message("tihosskias_sh", ob->query_real_name() + " is leaving this room.\n");    
    if (IS_LIVING_OBJECT(ob))
    {
        object oldtp = this_player();
        set_this_player(ob);
        object tihosskias_object = find_tihosskias_object(to);
        if (objectp(tihosskias_object))
        {
            tihosskias_object->try_to_exit();
        }
        set_this_player(oldtp);
    }
        
    shadow_who->leave_inv(ob, to);
}
