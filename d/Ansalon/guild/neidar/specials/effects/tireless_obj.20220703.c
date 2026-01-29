/*
 * Tireless Object
 * 
 * When Neidars are in combat, they become tireless, meaning that they
 * never run out of fatigue. This object will clone the shadow and
 * apply it to the Neidar when they have it in their inventory.
 *
 * Created by Petros, April 2009
 */
 
#pragma strict_types

#include <files.h>
#include "../../guild.h"

inherit "/d/Genesis/specials/std/effect_obj_base";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function     : create_effect
 * Description  : The create function called for objects that inherit this
 * Arguments    : none
 * Returns      : nothing
 */
public void
create_effect()
{    
    set_name("_neidar_tireless_obj");
    add_name( ({"neidar_tireless_obj" }) );
    set_short("hidden tireless object");    
    set_long("This is the tireless object for the Neidar Clan. You "
        + "should not see this.\n");

    setuid();
    seteuid(getuid());
}                           

/*
 * Function:    is_neidar_tireless_object
 * Description: Indicates whether this is the Neidar Armour Master
 *              Object. Used in filters during remove_object
 */
public int
is_neidar_tireless_object()
{
    return 1;
}

/*
 * Function     : remove_neidar_tireless_object
 * Description  : Destructor function.
 * Arguments    : none
 * Returns      : nothing
 */
public void
remove_neidar_tireless_object()
{
    remove_object();
}

/*
 * Function name: start
 * Description:   Start up the effect. We override this method so that we
 *                can add the armour master shadow.
 * Returns:       1/0 - effect started/not started
 */
public int
start()
{
    int result;
    object player;
    
    result = ::start();
    // Add the tireless shadow
    if (objectp(player = environment(this_object()))
        && IS_LIVING_OBJECT(player)
        && !player->has_tireless_shadow())
    {
        clone_object(TIRELESS_SH)->shadow_me(player);
    }
    
    return result;
}

public void
remove_object()
{
    object player;
    object * objs;
    
    if (objectp(player = environment(this_object()))
        && IS_LIVING_OBJECT(player))
    {
        // Check to see how tireless objects they have
        objs = filter(all_inventory(player), &->is_neidar_tireless_object());
        if (sizeof(objs) == 1)
        {
            // If we're removing the only one left, we remove the shadow
            player->remove_tireless_shadow();
        }
    }
    
    ::remove_object();
}
