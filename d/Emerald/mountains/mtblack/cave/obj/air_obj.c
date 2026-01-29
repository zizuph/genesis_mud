/* This object keeps track of how much air a player has left to breathe.   */
/* You will find one in the inventory of any mortals who go swimming in    */ 
/* the underwater caves in Emerald. This object replaces the original      */
/* system used in Terel by Dust. This system is more consistent in terms   */
/* of the actual amount of time a swimmer takes to drown.                  */
/* Coded on 06/07/96 by Tulix III.                                         */
/* Check for conventional light sources (lamps, torches) added 12/04/86.   */
/* Note that torches carried in water-proof containers will not be ruined. */


inherit "/std/object";

#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Emerald/tulix/t_defs.h"

/* This line is put in to keep Mercade happy */
#pragma strict_types

/* Some handy definitions */
#define WET_TORCH    "/d/Emerald/mountains/mtblack/cave/obj/wet_torch"
#define WET_LAMP     "/d/Emerald/mountains/mtblack/cave/obj/wet_lamp"

/* Global variable used to track the status of the check_air alarm */
public int alarm_id;

/* Prototype functions */
public void check_air();
public int  remove_check_air_alarm();
public void set_check_air_alarm();
public void check_lights(object swimmer);



/* We may be debugging the code */
#ifndef DEBUG
#define DEBUG 0
#endif


/*
 * Function name:   create_object
 * Description:     define the basic object details
 */
public void
create_object()
{
    set_name("air_obj");
    add_name("monitor");
    set_adj("air");
    set_short("air monitor");
    set_long("This thing monitors the air in your lungs.\n");

    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_INVIS, 100);

    add_prop(OBJ_S_WIZINFO, "The monitor makes sure that if you run out " +
        "of air to breathe while under-water, then you'll get to see your " +
        "old friend with the scythe.\n");

    alarm_id = 0;
}    


/*
 * Function name:   enter_env
 * Description:     called when this object enters a new environment
 * Arguments:       new: destination environment
 *                  old: previous environment
 */
public void
enter_env(object swimmer, object old)
{
    int extra_delay;
    
    ::enter_env(swimmer, old);
    
    /* I assume that how long you can hold your breath is based on CON */
    extra_delay =  swimmer->query_stat(SS_CON) / 12;

    swimmer->add_prop("_live_i_air_remaining", 6);
    swimmer->add_prop("_live_i_breathe_delay", 6 + extra_delay);
    
    return;
}


/*
 * Function name:   check_air
 * Description:     check how much air the player has left, kill if necessary.
 */
public void
check_air()
{
    object swimmer, room;
    int interval, air_remaining, max_hp, drown_pc_hp;
        
    /* This object is always in the inventory of the swimmer. */
    swimmer = ENV(TO);
    
    /* Only living things are likely to drown. */
    if (!living(swimmer))
    {
        TO->remove_object();
    }

    if (DEBUG != 0)
    {
        swimmer->catch_msg("check_air executed....\n");
    }
   
    /* Here we make sure the swimmer is under-water.             */
    /* The swimmer could drown anywhere without this next check! */
    room = ENV(swimmer);
    if (room->query_prop(ROOM_I_TYPE) != ROOM_UNDER_WATER)
    {
        if (DEBUG != 0)
        {
            swimmer->catch_msg("No water to drown in....!\n");
        }
    
        alarm_id = 0;

        return;
    }

    /* See how much air the swimmer has left to breathe. */
    air_remaining = swimmer->query_prop("_live_i_air_remaining");

    /* Check to see if player can breathe water by magical means. */
    if (swimmer->query_prop(MAGIC_I_BREATH_WATER) >= 1 )
    {
        /* We don't want to drown players with this prop set. */
        air_remaining = 12;
        
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("BREATHE_WATER detected.\n");
        }
    }
            
    /* Drown the swimmer if they have no air left to breathe. */
    if (!air_remaining)
    {
        /* Inform swimmer that they have just drowned. */
        swimmer -> catch_msg("You stupid " + swimmer->query_race() + 
                      "! You've just managed to drown yourself!\n");

        setuid();
        seteuid(getuid(TO));
        
        /* set_hp(0) does NOT work when called in players. *grumble*  */
        swimmer->heal_hp(-swimmer->query_hp());  /* This does though. */
        swimmer->do_die(TO);
        
        TO->remove_object();
    }
            
    /* Reduce the amount of air that the swimmer has left to breathe. */
    air_remaining--;
    swimmer->add_prop("_live_i_air_remaining", air_remaining);
    
    drown_pc_hp = 100;
    
    /* Give the swimmer an update on how much air they have left. */
    switch (air_remaining)
    {
        case 12: case 11: case 10: case 9: case 8: case 7:
        case 6: tell_object(swimmer, "You feel very well.\n");
            drown_pc_hp = 100;
            break;

        case 5: tell_object(swimmer, "You feel quite giddy.\n"); 
            drown_pc_hp = 90;
            break;
                
        case 4: tell_object(swimmer, "You feel sick - you need air!\n"); 
            drown_pc_hp = 70;
            break;
                
        case 3: tell_object(swimmer, "You are really out of breath!\n");
            drown_pc_hp = 40;
            break;
                
        case 2: tell_object(swimmer,
            "You are completely out of breath, you'll drown soon!\n");
             drown_pc_hp = 20;
             break;
                
        case 1: tell_object(swimmer,
            "You are near drowning, actually about to die...\n"); 
            drown_pc_hp = 10;
            break;
                
        case 0: tell_object(swimmer,
            "You are drowning and at deaths door....\n");
            drown_pc_hp = 3;
            break;
    }
            
    /* Reduce hp if player is starting to drown */
    max_hp = swimmer->query_max_hp();
    
    if ( (swimmer->query_hp() * 100 / max_hp) > drown_pc_hp )
    {    
        
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("hp reduced to " + drown_pc_hp + "%.\n");
        }
        
        swimmer->set_hp( drown_pc_hp * max_hp / 100 );
    }
    
    interval = swimmer->query_prop("_live_i_breathe_delay");
    
    alarm_id = set_alarm( itof(interval), 0.0, check_air );
    
    if (DEBUG != 0)
    {
        swimmer -> catch_msg("check_air alarm set again (from check_air).\n");
    }
}


/*
 * Function name:   remove_check_air_alarm
 * Description:     cancel the check_air alarm, either internal or external 
 * Returns:         0 if alarm not found, 1 if alarm was removed
 */
public void
remove_check_air_alarm()
{
    object swimmer;

    /* This object is always in the inventory of the swimmer. */
    swimmer = ENV(TO);
    
    /* Remove the check_air alarm if is has been set. */
    if (alarm_id)
    {
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("check_air alarm removed.\n");
        }
        
        remove_alarm(alarm_id);
        alarm_id = 0;
        return;
    }
    else        
    {
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("no check_air alarm found.\n");
        }
            
        return;
    }
}


/*
 * Function name:   set_check_air_alarm
 * Description:     set the check_air alarm, called by functions in rooms 
 */
public void
set_check_air_alarm()
{
    object swimmer;
    int interval;

    /* This object is always in the inventory of the swimmer. */
    swimmer = ENV(TO);
    
    /* Extinguish any torches or lamps held by the swimmer. */
    check_lights(swimmer);

    /* Make sure we don't drown players too quickly. */
    interval = swimmer->query_prop("_live_i_breathe_delay");

    if (interval < 6)
    {
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("minimum interval set at 6!\n");
        }
        interval = 6;
    }
    
    if (!alarm_id)
    {
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("check_air alarm set (from room).\n");
        }
        
        alarm_id = set_alarm( itof(interval), 0.0, check_air );
        return;
    }
    else
    {
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("check_air alarm already set!\n");
        }
        return;
    }
}

/*
 * Function name:   check_lights
 * Description:     check players inventory for torches and lamps 
 * Arguments:       object swimmer: the player who is swimming
 */
public void
check_lights(object swimmer)
{
    object *obj_array, item, wet_item, container;
    int i;
        
    /* We may need to clone things in this function */
    setuid();
    seteuid(getuid());
                
    if (DEBUG != 0)
    {
        swimmer -> catch_msg("check_lights executing...\n");
    }
   
    /* Make an array of all the objects carried by the swimmer. */
    obj_array = deep_inventory(swimmer);
    
    /* Swimmer may not be carrying anything (very unlikely). */
    if (!sizeof(obj_array))
    {
        if (DEBUG != 0)
        {
            swimmer -> catch_msg("swimmer has no inventory items!\n");
        }
        return;
    }
    
    /* Check each object in the array, and see if it is a torch or lamp. */
    for (i=0; i<sizeof(obj_array); i++)
    {
        /* Select the item number i from the array. */
        item = obj_array[i];
        
        if (item->query_name() == "lamp")
        {
            if (DEBUG != 0)
            {
                swimmer -> catch_msg("lamp detected...");
            }
            
            /* Make sure that the lamp is not in auto-loading. */ 
            container = ENV(item);
            if (item->query_auto_load())
            {
                if (DEBUG != 0)
                {
                    swimmer -> catch_msg("...but is auto-loading.\n");
                }
                /* Go back and check next item. */
                continue;
            }    
            
            /* Make sure that the lamp is not in a water-proof container. */ 
            container = ENV(item);
            if (container -> query_prop(OBJ_I_RES_WATER) >= 1 )
            {
                if (DEBUG != 0)
                {
                    swimmer -> catch_msg("...in water-proof container.\n");
                }
                /* Go back and check next item. */
                continue;
            }    
            else
            {
                if (DEBUG != 0)
                {
                    swimmer -> catch_msg("...extinguished permanently.\n");
                }
            
                /* Extinguish the lamp permanently. */
                item -> remove_object();
                
                wet_item = clone_object(WET_LAMP);
                if (!wet_item)
                {
                    if (DEBUG != 0)
                    {
                        swimmer -> catch_msg("...buggy wet lamp!\n");
                    }
                    continue;
                }
                wet_item->move(swimmer);
                continue;
            }
        }

        /* Check to see if the object is a torch. */
        if (function_exists("create_torch", item))
        {
            if (DEBUG != 0)
            {
                swimmer -> catch_msg("torch detected...");
            }
            
            /* Make sure that the torch is not in auto-loading. */ 
            container = ENV(item);
            if (item->query_auto_load())
            {
                if (DEBUG != 0)
                {
                    swimmer -> catch_msg("...but is auto-loading.\n");
                }
                /* Go back and check next item. */
                continue;
            }    
            
            /* Make sure that the torch is not in a water-proof container. */ 
            container = ENV(item);
            if (container -> query_prop(OBJ_I_RES_WATER) >= 1 )
            {
                if (DEBUG != 0)
                {
                    swimmer -> catch_msg("...in water-proof container.\n");
                }
                /* Go back and check next item. */
                continue;
            }    
            else
            {
                if (DEBUG != 0)
                {
                    swimmer -> catch_msg("...extinguished permanently.\n");
                }
            
                /* Extinguish the torch permanently. */
                item->remove_object();
                
                wet_item = clone_object(WET_TORCH);
                wet_item->move(swimmer);
                continue;
            }
        }     
    }
    
    if (DEBUG != 0)
    {
        swimmer -> catch_msg("check_lights executed.\n");
    }
    
    return;
}
            
