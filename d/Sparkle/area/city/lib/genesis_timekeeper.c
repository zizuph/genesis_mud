/* 
 * Genesis Timekeeper
 *
 * This module keeps track of time across all Genesis domains. It tries to
 * unify all the various timekeepers in different realms so that there is
 * one place that needs to be called for global queries on time.
 *
 * This only keeps track of hours and minutes during the day.
 * It does not try to keep track of seconds, weeks, months or years.
 *
 * Created by Petros, October 2009
 */

#pragma strict_types

#include <files.h>
#include <stdproperties.h>
#include "/d/Gondor/sys/sunlight.h"

// Domains with Clocks
// Krynn/Ansalon - /d/Krynn/common/clock/clock
// Gondor/Shire - /d/Gondor/common/obj/clock
// Emerald - /d/Emerald/sys/global/clock
// Kalad - /d/Kalad/obj/clock
// Earthsea - /d/Earthsea/sys/global/clock
// Sparkle - /d/Sparkle/lib/libs_clock
// Avenir - /d/Avenir/inherit/avenir_time
// Faerun - /d/Faerun/lib/clock
// Khalakhor - /d/Khalakhor/sys/global/clock
// Raumdor - /d/Raumdor/lib/clock

// Domains without Clock Implementations
// Calia, Cirath, Terel

#define KRYNN_CLOCK     "/d/Krynn/common/clock/clock"
#define GONDOR_CLOCK    "/d/Gondor/common/obj/clock"
#define EMERALD_CLOCK   "/d/Emerald/sys/global/clock"
#define KALAD_CLOCK     "/d/Kalad/obj/clock"
#define EARTHSEA_CLOCK  "/d/Earthsea/sys/global/clock"
#define SPARKLE_CLOCK   "/d/Sparkle/lib/libs_clock"
#define AVENIR_CLOCK    "/d/Avenir/inherit/avenir_time"
#define FAERUN_CLOCK    "/d/Faerun/lib/clock"
#define KHALAKHOR_CLOCK "/d/Khalakhor/sys/global/clock"
#define RAUMDOR_CLOCK   "/d/Raumdor/lib/clock"

// Standard Sunlight Property to override the default values for the domain
#ifndef ROOM_I_SUNLIGHT
#define ROOM_I_SUNLIGHT "_room_i_sunlight"
#endif 

// Default Sunlight Times
// The default values are inclusive, meaning that it will go from 6am to the
// end of 5pm (beginning of 6pm), which is 12 hours.
#define DEFAULT_SUNLIGHT_BEGIN  6
#define DEFAULT_SUNLIGHT_END    17

/*
 * Function:    create
 * Description: Standard create function necessary for every object.
 */
public void
create()
{
    setuid();
    seteuid(getuid());    
}

/*
 * Function:    query_time_for_room
 * Description: This function allows one to query the current time
 *              for a particular room. It only does hour, and minute if 
 *              possible.
 * Returns:     int array of form: ({ hour, minute }), or 0 if
 *              an error condition.
 */
public int *
query_time_for_room(object room)
{
    int hour = 0, minute = 0;
    string domain = lower_case(room->query_domain());
    switch (domain)
    {    
    case "shire":
    case "gondor":
        hour = GONDOR_CLOCK->query_hour();
        minute = GONDOR_CLOCK->query_minute();
        break;
        
    case "emerald":
        hour = EMERALD_CLOCK->query_hour();
        minute = EMERALD_CLOCK->query_minute();
        break;
    
    case "kalad":
        hour = KALAD_CLOCK->query_time();
        // Kalad doesn't track minutes
        break;
    
    case "earthsea":
        hour = EARTHSEA_CLOCK->query_hour();
        minute = EARTHSEA_CLOCK->query_minute();
        break;
    
    case "sparkle":
    case "genesis":
        hour = SPARKLE_CLOCK->s_get_time_hour_of_day();
        minute = (SPARKLE_CLOCK->s_get_time() % 3600) / 60;
        break;
    
    case "avenir":
        hour = AVENIR_CLOCK->get_avenir_hour(); // only has 12 hours
        hour *= 2; // we multiply by two to get the 24 hr number.
        // Avenir has no minutes tracking
        break;
    
    case "faerun":
        hour = FAERUN_CLOCK->query_hour();
        // Faerun has no minutes tracking
        break;
    
    case "khalakhor":
        hour = KHALAKHOR_CLOCK->query_hour();
        minute = KHALAKHOR_CLOCK->query_minute();
        break;
    
    case "raumdor":
        hour = RAUMDOR_CLOCK->query_hour();
        // Raumdor doesn't keep track of minutes.
        break;
        
    // Krynn/Ansalon clock will be used by domains without clocks
    // for the purposes of determining the current time.
    case "krynn":
    case "ansalon":
    // Now the domains without clocks
    case "calia":
    case "terel":
    case "cirath":
    default:
        {
            mixed * time_info = KRYNN_CLOCK->query_time();
            if (sizeof(time_info) == 5)
            {
                hour = time_info[3];
                minute = time_info[4];
            }
        }
        break;
    }
    
    return ({ hour, minute });    
}

/*
 * Function:    query_time
 * Description: This function allows one to query the current time
 *              for the room that the player is in. It only does hour,
 *              and minute if possible.
 * Returns:     int array of form: ({ hour, minute }), or 0 if
 *              an error condition.
 */
public varargs int *
query_time(object player = this_player())
{
    object room = environment(player);
    if (!IS_ROOM_OBJECT(room))
    {
        return 0;
    }
    
    return query_time_for_room(room);
}

/*
 * Function:    calculate_time_of_day_desc
 * Description: For domains without time of day calculations, we have
 *              a function here that spits back a description based
 *              on the relative hour to the daylight hours.
 * Arguments:   hour - current hour
 *              day_begin - beginning hour (dawn) of daylight
 *              day_end   - ending hour (dusk) of daylight (inclusive)
 */
public string
calculate_time_of_day_desc(int hour, int day_begin, int day_end)
{
    if (hour == day_begin)
    {
        return "dawn";
    }
    else if (hour == day_end)
    {
        return "dusk";
    }
    else if (hour > day_begin && hour < day_end)
    {
        // Day time
        int hours_from_begin = hour - day_begin;
        int hours_from_end   = day_end - hour;
        if (hours_from_begin < hours_from_end)
        {
            // Earlier part of the day
            return "morning";
        }
        else if (hours_from_end < hours_from_begin)
        {
            return "afternoon";
        }
        else
        {
            return "noon";
        }
    }
    else
    {
        // Night time
        if (hour == 0)
        {
            return "midnight";
        }
        else if (hour < day_begin)
        {
            return "night";
        }
        else
        {
            return "evening";
        }
    }
    
    return "unknown";
}

public string
query_time_of_day(string domain)
{
    string tod_desc = "unknown";
    switch (domain)
    {
    case "shire":
    case "gondor":
        tod_desc = GONDOR_CLOCK->query_time_of_day();
        break;
        
    case "emerald":
        tod_desc = EMERALD_CLOCK->query_time_string(0);
        break;
    
    case "kalad":
        {
            int hour = KALAD_CLOCK->query_time();
            tod_desc = calculate_time_of_day_desc(hour, 7, 21);
        }
        // Kalad doesn't track minutes
        break;
    
    case "earthsea":
        {                    
            int hour = EARTHSEA_CLOCK->query_hour();
            tod_desc = calculate_time_of_day_desc(hour, 6, 17);
        }
        break;
    
    case "sparkle":
    case "genesis":
        // Sparkle is always Day
        tod_desc = "noon";
        break;
    
    case "avenir":
        {                    
            int hour = AVENIR_CLOCK->get_avenir_hour(); // only has 12 hours
            hour *= 2; // we multiply by two to get the 24 hr number.
            tod_desc = calculate_time_of_day_desc(hour, 6, 17);
        }    
        // Avenir has no minutes tracking
        break;
    
    case "faerun":
        tod_desc = FAERUN_CLOCK->query_part_of_day();
        break;
    
    case "khalakhor":
        tod_desc = KHALAKHOR_CLOCK->query_time_of_day();
        break;
    
    case "raumdor":
        // Raumdor is always night
        tod_desc = "midnight";
        break;

    // Krynn/Ansalon clock will be used by domains without clocks
    // for the purposes of determining the current time of day
    case "krynn":
    case "ansalon":
    
    // Now the domains without clocks
    case "calia":
    case "terel":
    case "cirath":
    default:
        tod_desc = KRYNN_CLOCK->query_time_of_day();
    }
    
    return tod_desc;    
}

/*
 * Function:    calculate_sunlight_level
 * Description: This calculates what the sunlight level should be based
 *              on the relative position of the daylight hour to the
 *              amount of daylight available. At noon, the level is the
 *              brightest (30). At night, there is no sunlight.
 * Arguments:   day_begin - The beginning hour of daylight
 *              day_end   - The hour that sunlight ends (inclusive)
 * Returns:     Sunlight level between 0-30 (SUNLIGHT_BRIGHT)
 */
public int
calculate_sunlight_level(int day_begin, int day_end, int current_hour)
{
    if (current_hour < day_begin || current_hour > day_end)
    {
        return 0;
    }
        
    int begin_hour = day_begin - 1;
    int end_hour = day_end + 1;
    int noon_value = ftoi(pow((itof(end_hour) - itof(begin_hour)) / 2.0, 2.0));
        
    return (current_hour - begin_hour) * (end_hour - current_hour) * SUNLIGHT_BRIGHT
            / noon_value;
}

/*
 * Function:    domain_hour_has_sunlight
 * Description: Checks to see whether the domain has sunlight during a
 *              particular hour. By looping through the hours, it makes
 *              it easy to figure out how many hours there are until
 *              sunlight, which is pretty useful information for Vampires
 *              to know.
 */
public int
domain_hour_has_sunlight(string domain, int hour)
{
    switch (domain)
    {
    case "gondor":
    case "shire":
        {        
            string time_of_day = GONDOR_CLOCK->query_time_of_day(
                GONDOR_CLOCK->query_month(),
                GONDOR_CLOCK->query_day(),
                hour,
                GONDOR_CLOCK->query_year() - 3017);
            if (time_of_day == "night")
            {
                return 0;
            }
        }
        break;
        
    case "kalad":
        // Kalad specifies that daytime is between 7am and 10pm
        if (hour < 7 || hour > 21)
        {
            return 0;
        }
        break;
    
    case "faerun":
        // Faerun specifies that daytime is between 8am and 10pm
        if (hour < 8 || hour > 21)
        {
            return 0;
        }
        break;
    
    case "raumdor":
        // Raumdor never has any sunlight
        return 0;
        break;
        
    case "sparkle":
    case "genesis":
        // Sparkle always has normal sunlight
        return 1;
        break;
        
    // Krynn and Ansalon go from 6am to 6pm for sunlight.
    case "krynn":
    case "ansalon":
    // All these domains don't specify what is daytime, so we simply
    // use the standard 6am-6pm daylight hours.
    case "emerald":
    case "earthsea":
    case "avenir":
    case "khalakhor":
    case "calia":
    case "terel":
    case "cirath":
    default:
        if (hour < DEFAULT_SUNLIGHT_BEGIN || hour > DEFAULT_SUNLIGHT_END)
        {
            return 0;
        }
        break;
    }
    
    return 1;
}

/*
 * Function:    query_sunlight_for_room
 * Description: Checks to see whether this room should have sunlight or
 *              not. It will use domain specific code for daytime where
 *              applicable and use the default hours otherwise.
 *              NOTE: *never* set the room_i_sunlight property to point
 *                    to this function via VBFC. It will result in a stack
 *                    overflow from the infinite recursion.
 * Returns:     Range of sunlight from 1-30 (based on /d/Gondor/sys/sunlight.h)
 */
public int
query_sunlight_for_room(object room)
{
    if (room->query_prop(ROOM_I_INSIDE))
    {
        // An inside room never has sunlight.
        return 0;
    }
    
    // A room can override what the default for the domain is. We
    // honor this here. Functions can be used as the ROOM_I_SUNLIGHT
    // value.
    mixed sunlight_prop = room->query_prop_setting(ROOM_I_SUNLIGHT);
    if (functionp(sunlight_prop))
    {
        function sunlight_function = sunlight_prop;
        return sunlight_function(room);
    }
    else if (sunlight_prop && intp(sunlight_prop))
    {
        return sunlight_prop;
    }
    
    int sunlight = 0;
    int * time_info = query_time_for_room(room);
    
    // In case of no specifics for this room, we query the sunlight 
    // level based on the domain.
    string domain = lower_case(room->query_domain());
    switch (domain)
    {    
    case "shire":
    case "gondor":
        // Gondor uses its own sunlight calculations in each room
        sunlight = room->check_sunlight();
        break;
        
    case "krynn":
    case "ansalon":
        // Krynn uses its own sunlight calculations in its clock
        sunlight = KRYNN_CLOCK->query_sunlight_level();
        break;        
    
    case "kalad":
        // Kalad specifies that daytime is between 7am and 10pm
        sunlight = calculate_sunlight_level(7, 21, time_info[0]);
        break;
    
    case "faerun":
        // Faerun specifies that daytime is between 8am and 10pm
        sunlight = calculate_sunlight_level(8, 21, time_info[0]);
        break;
    
    case "raumdor":
        // Raumdor never has any sunlight
        sunlight = 0;
        break;
        
    case "sparkle":
    case "genesis":
        // Sparkle always has normal sunlight
        sunlight = SUNLIGHT_NORMAL;
        break;
        
    // All these domains don't specify what is daytime, so we simply
    // use the standard 6am-6pm daylight hours.
    case "emerald":
    case "earthsea":
    case "avenir":
    case "khalakhor":
    case "calia":
    case "terel":
    case "cirath":
    default:
        sunlight = calculate_sunlight_level(DEFAULT_SUNLIGHT_BEGIN, 
                                            DEFAULT_SUNLIGHT_END, 
                                            time_info[0]); 
        break;
    }
    
    return sunlight;
}

/*
 * Function:    query_sunlight
 * Description: Checks to see whether this room should have sunlight or
 *              not. It will use domain specific code for daytime where
 *              applicable and use the default hours otherwise.
 *              NOTE: *never* set the room_i_sunlight property to point
 *                    to this function via VBFC. It will result in a stack
 *                    overflow from the infinite recursion.
 * Returns:     Range of sunlight from 1-30 (based on /d/Gondor/sys/sunlight.h)
 */
public varargs int
query_sunlight(object player = this_player())
{
    object room = environment(player);
    if (!objectp(room)
        || !IS_ROOM_OBJECT(room))
    {
        // If it's not a room, we default to having no sunlight.
        return 0;
    }
    
    return query_sunlight_for_room(room);
}
