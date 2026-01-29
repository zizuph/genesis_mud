/* Created by Ckrik November 1997*
 * Tides for Earthsea*
 * A rudimentry tide system for oceanside rooms.*
 */

/* query_tide_string() returns a string describing the*
 * level of the tide.*
 * query_tide_level() returns a number describing the height*
 * of the water. 4 is the max and 0 is the min. So 2 would*
 * medium water height.*
 */

#pragma strict_types
#pragma no_clone
#pragma save_binary
#pragma no_inherit

/* E_TIME is an alias for query_time() which looks up the*
 * Earthsea time. Since the time is in seconds, the TIDE_CYCLE,*
 * which is set at 24 hours.*
 */

#define E_TIME "/d/Earthsea/sys/global/clock"->query_time()
#define TIDE_CYC 86400

/* Tide Description*
 * ----------------*
 * Returns a description of the tide.*
 * ----------------------------------*
 * low tide, far from high tide, half-way to high tide,*
 * close to high tide, high tide, far from low tide,*
 * half-way to low tide, close to low tide, and error.*
 * ----------------------------------------------------*
 * NOTE:*
 * Low tide is set as the 0 remainder of E_TIME / TIDE_CYC,* 
 * + or - 1 hour, or 3600 seconds.*
 * High tide is set as the (TIDE_CYC / 2) remainder of*
 * (E_TIME / 2) / TIDE_CYC, + or - 1 hour. Because the*
 * low tide condition is above the high tide condition,*
 * thus the high tide condition will not override the low*
 * condition.*
 * The other conditions are for interval between low and*
 * high tide.*
 */

public nomask string
query_tide_string()
{
    int time = E_TIME;

    if(time % TIDE_CYC < TIDE_CYC / 8)
    {
        return "low tide";
    }

    if(time % TIDE_CYC < TIDE_CYC / 4)
    {
        return "far from high tide";
    }

    if(time % TIDE_CYC < (3 * TIDE_CYC) / 8)
    {
        return "half-way to high tide";
    }

    if(time % TIDE_CYC < TIDE_CYC / 2)
    {
        return "close to high tide";
    }

    if(time % TIDE_CYC < (5 * TIDE_CYC) / 8)
    {
        return "high tide";
    }

    if(time % TIDE_CYC < (3 * TIDE_CYC) / 4)
    {
        return "far from low tide";
    }

    if(time % TIDE_CYC < (7 * TIDE_CYC) / 8)
    {
        return "half-way to low tide";
    }

    if(time % TIDE_CYC < TIDE_CYC)
    {
        return "close to low tide";
    }

    return "error";
}

/* Tide Water level*
 * ----------------*
 * Returns the water level of the tide.*
 * ------------------------------------*
 * 0 = lowest water level*
 * 1 = low water level*
 * 2 = medium water level*
 * 3 = high water level*
 * 4 = highest water level*
 * -1 = error*
 */

public nomask int
query_tide_level()
{
    int time = E_TIME;

    if(time % TIDE_CYC < TIDE_CYC / 8)
    {
        return 0;
    }

    if(time % TIDE_CYC < TIDE_CYC / 4)
    {
        return 1;
    }

    if(time % TIDE_CYC < (3 * TIDE_CYC) / 8)
    {
        return 2;
    }

    if(time % TIDE_CYC < TIDE_CYC / 2)
    {
        return 3;
    }

    if(time % TIDE_CYC < (5 * TIDE_CYC) / 8)
    {
        return 4;
    }

    if(time % TIDE_CYC < (3 * TIDE_CYC) / 4)
    {
        return 3;
    }

    if(time % TIDE_CYC < (7 * TIDE_CYC) / 8)
    {
        return 2;
    }

    if(time % TIDE_CYC < TIDE_CYC)
    {
        return 1;
    }

    return -1;
}
