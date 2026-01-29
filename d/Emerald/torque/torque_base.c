/*
 * torque_base.c
 *
 * Since we plan to have a number of torque-like objects in the game,
 * some of which probably won't function exactly like the version players
 * will possess, we have this base object that implements the important
 * functionality that all torques should have in common.
 */

inherit "/std/object";

#include "torque.h"
#include <macros.h>
#include <composite.h>
#include <living_desc.h>
#include <filter_funs.h>
#include <stdproperties.h>

public void
create_torque()
{
}

nomask public void
create_object()
{
    if (!IS_CLONE)
    {
        return;
    }
    setuid();
    seteuid(getuid());

    TORQUE_MANAGER->register_torque(this_object());

    set_name("torque");
    add_name(TORQUE_ID);

    create_torque();
}

public void
query_torque_active(object user)
{
    return 0;
}

public void
remove_object()
{
    ::remove_object();
    
    TORQUE_MANAGER->unregister_torque(this_object());
}

public void
scry(object scryer, int power)
{
    object env;
    string tmp;
    object *items, *dead, *live;

    env = environment();

    if (env && living(env))
    {
        env = environment(env);
    }

    if (!env)
    {
        scryer->catch_tell("You see only blackness through the torque.\n");
        return;
    }

    scryer->catch_tell("You can see the following:\n");

    if (env->query_prop(OBJ_I_LIGHT) < 1)
    {
        if (!stringp(tmp = env->query_prop(ROOM_S_DARK_LONG)))
        {
            scryer->catch_tell(LD_DARK_LONG);
            return;
        }
         
        scryer->catch_tell(tmp);
        return;
    }

    if (power < 150)
    {  
        scryer->catch_tell(capitalize(env->short()) + ".\n");
        return;
    }

    scryer->catch_tell(env->long());

    if (power > 200)
    {  
        items = FILTER_CAN_SEE(all_inventory(env), this_player());
        if (sizeof(items))
        {
            if (sizeof(dead = FILTER_DEAD(items)))
            {
                tmp = SILENT_COMPOSITE_DEAD(dead);
                if (strlen(tmp))
                {
                    scryer->catch_tell(capitalize(tmp) + ".\n");
                }
            }
            
            if (sizeof(live = FILTER_LIVE(items)))
            {
                tmp = SILENT_COMPOSITE_LIVE(live);
                if (strlen(tmp))
                {
                    scryer->catch_tell(capitalize(tmp) + ".\n");
                }
            }
        }
    }
}
