/*
 * Item Recovery Handler
 *
 * This listener is called by the item registry whenever a new item
 * is cloned. This particular handler will determine whether the item
 * should "glow" or not.
 *
 * Created by Petros, November 2009
 */

#pragma strict_types

#include <macros.h>
#include <files.h>

// Defines
#define OBJ_I_IGNORE_RECOVERY "_obj_i_ignore_recovery"

// Global Variables
public int          start_time = 0;
public int          max_time = 0;

public void
create()
{
    setuid();
    seteuid(getuid());
    
    // Register with the callback.
    LISTENER_ADD(MASTER);
}

/* 
 * Function:    refresh_stored_times
 * Description: In order to prevent having to call the SECURITY object
 *              for every object creation, we store the results of
 *              the start_time and max_time every Armageddon. There
 *              are times when this needs to be refreshed.
 */
public void
refresh_stored_times()
{
    start_time = SECURITY->query_start_time();
    max_time = SECURITY->query_uptime_limit();
}

/*
 * Function:    get_percentage_till_armageddon
 * Description: This function returns the percentage of time that is left
 *              during this Armageddon cycle.
 */
public int
get_percentage_till_armageddon()
{
    if (start_time == 0 || max_time == 0)
    {
        refresh_stored_times();
    }    
        
    int expired_time = time() - start_time;
    if (expired_time > max_time)
    {
        // If the expired_time is greater than max_time, then something
        // is wrong with the start_time or max_time. This can occur, for
        // instance, if the start times haven't yet been set in the master
        // because it's the beginning of Armageddon.
        refresh_stored_times();
        expired_time = time() - start_time;
    }
    return min(100, max(0, expired_time * 100 / max_time));    
}

/*
 * Function:    is_valid_recovery_object
 * Description: Only certain types of objects should be treated with
 *              recovery handling. Right now (March 2010), this is limited
 *              to armours and weapons.
 */
public int
is_valid_recovery_object(object obj)
{
    if (IS_ARMOUR_OBJECT(obj)
        || IS_WEAPON_OBJECT(obj))
    {
        if (obj->query_prop(OBJ_I_IGNORE_RECOVERY))
        {
            // Certain objects can define that they will ignore the
            // recovery process changes.
            return 0;
        }
        return 1;
    }
    
    return 0;
}

/* 
 * Function:    notify_new_object
 * Description: This is called by the registry whenever there is a new
 *              object. We do all the processing here.
 */
public varargs void
notify_new_object(object obj)
{
    if (!is_valid_recovery_object(obj))
    {
        return;
    }
    
    obj->set_may_recover();

    //if (random(100) <= get_percentage_till_armageddon())
    //{
    //    obj->set_may_recover();
    //}
    //else
    //{
    //    obj->set_may_not_recover();
    //}
}
