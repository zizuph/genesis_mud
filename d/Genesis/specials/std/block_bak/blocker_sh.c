/*
 * /d/Genesis/specials/std/blocker_sh.c
 *
 * This is the shadow for the person performing the block. It
 * mainly keeps track of people who enter the room, and places
 * a block shadow on people as they enter.
 *
 * Created by Petros, November 2008
 */

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>

inherit SHADOW_OBJECT;

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "block_defs.h"

public void
remove_blocker_shadow()
{
    // Removing the shadow removes this person as a blocker
    shadow_who->remove_prop(BLOCK_PROP);
    remove_shadow();
}

public int
has_blocker_shadow()
{
    return 1;
}

public void
init_living()
{
    object entering_living, block_shadow;;
    string living_name;
    
    entering_living = previous_object(-1);
    if (!IS_LIVING_OBJECT(entering_living))
    {
        return;
    }
    
    setuid();
    seteuid(getuid());
    if (BLOCK_ABILITY->query_block_room(shadow_who) == MASTER_OB(environment(shadow_who)))
    {
        if (!entering_living->has_block_shadow())
        {
            living_name = interactive(entering_living) ? 
                capitalize(entering_living->query_real_name()) :
                file_name(entering_living);
            block_shadow = clone_object(BLOCK_SH);
            if (!block_shadow->shadow_me(entering_living))
            {
                send_debug_message("blocker_sh", "Shadowing " + living_name + " with block shadow failed.");
                block_shadow->remove_shadow();
            } else { 
                send_debug_message("blocker_sh", "Entering living is " + living_name + " and will now have a block shadow.");
            }
        }
    }
    else
    {
        // We shouldn't have this shadow
        set_alarm(0.0, 0.0, remove_blocker_shadow);
    }
    
    // Make sure we call init_living to process the rest    
    shadow_who->init_living();
}

/*
 * Function name:   adjust_combat_on_move
 * Description:     Called to let movement affect the ongoing fight. This
 *                  is used to print hunting messages.
 * Arguments:       True if leaving else arriving
 */
public void
adjust_combat_on_move(int leave)
{
    if (leave)
    {
        set_alarm(0.0, 0.0, remove_blocker_shadow);
        send_debug_message("blocker_sh", "Moving out of room, removing "
            + "blocker shadow.");
    }
    shadow_who->adjust_combat_on_move(leave);
}

public void
add_prop(string prop, mixed val)
{
    if (!val)
    {
        shadow_who->add_prop(prop, val);
        return;
    }
    
    switch (prop)
    {
    case OBJ_I_INVIS:    
        shadow_who->catch_tell("As you become invisible, you find "
            + "yourself no longer able to prevent others from exiting "
            + "this room.\n");
        break;
    }
    
    shadow_who->add_prop(prop, val);
}
