/*
 *  /d/Emerald/blackwall/del_rimmon/obj/beacon.c
 *
 *  This is an object which controls the beacon effect for the
 *  Del Rimmon area.
 *
 *  Copyright (c) March 2001, by Cooper Sherry (Gorboth)
 */

#pragma  strict_types
#pragma  save_binary
#pragma  no_inherit
#pragma  no_clone

inherit "/std/object";
inherit "/d/Emerald/blackwall/delrimmon/legacy/tell_funcs";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_object();
public void        set_beacon(int i);
public void        light_beacon();
public void        extinguish_beacon();

/* global variables */
public int         Beacon = 0;


public int         query_beacon() { return Beacon; }


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("beacon");
} /* create_object */


/*
 * Function name:        set_beacon
 * Description  :        this function is called when the beacon is
 *                       either lit or extinguished. Either way, we want
 *                       to send tells to people in the are to let
 *                       them know what is happening.
 * Arguments    :        int i
 */
public void
set_beacon(int i)
{
    object *ppl = get_players_in_dir("/d/Emerald/blackwall/delrimmon/*");
    int     n;

    if (i)
    {
        if (Beacon)
        {
            return; /* already lit */
        }

        for (n = 0; n < sizeof(ppl); n++)
        {
            if (!environment(ppl[n])->query_prop(ROOM_I_INSIDE))
            {
                ppl[n]->catch_tell("A brilliant illumination suddenly"
                  + " floods the entire region with light.\n");
                Beacon = i;
            }
        }

        Beacon = i; /* just in case */
        return;
    }

    for (n = 0; n < sizeof(ppl); n++)
    {
        if (!Beacon)
        {
            return ; /* already extinguished */
        }

        if (!environment(ppl[n])->query_prop(ROOM_I_INSIDE))
        {
                ppl[n]->catch_tell("The brilliant illumination fades"
                  + " suddenly, returning the region to its normal"
                  + " appearance.\n");
            Beacon = i;
        }
    }

    Beacon = i; /* just in case */
    return;
} /* set_beacon */


/*
 * Function name:        light_beacon
 * Description  :        use this function to light the beacon. It also
 *                       sets in motion an alarm to extinguish the
 *                       light after 5 minutes.
 */
public void
light_beacon()
{
    if (Beacon)
    {
        return;  /* the beacon is already lit */
    }

    set_beacon(1);
    set_alarm(300.0, 0.0, extinguish_beacon);  /* 5 minutes elapse */
    return;
} /* light_beacon */


/*
 * Function name:        extinguish_beacon
 * Description  :        use this function to extinguish the beacon.
 */
public void
extinguish_beacon()
{
    if (!Beacon)
    {
        return; /* the beacon is not lit */
    }

    set_beacon(0);
    return;
} /* extinguish_beacon */
