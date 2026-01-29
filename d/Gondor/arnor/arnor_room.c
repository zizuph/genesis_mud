/* 
 * Standard file for the rooms in the lost realm of Arnor.
 *
 * November 1994 by Arren
 * The rooms were first made in September 1993, but are now modified
 * to inherit this file.
 *
 *      Modification log:
 *      28-Feb-97, Olorin:      General revision,
 *                              changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static string 
query_arnor_time()
{
    object  clock = find_object(CLOCK);
    string  desc = "",
            time = tod();

    switch (time)
    {
    case "night":
        desc += "Darkness rules the sky. ";
        switch (clock->query_moon())
        {
        case "full":
            desc += "A full moon and many stars give some "+
                "light though. ";
            break;
        case "waxing crescent":
        case "waxing gibbous":
        case "waning gibbous":
        case "waning crescent":
            desc += "The moon and the stars give a little "+
                "light though. ";
            break;
        default:
            desc += "The sky is covered with dark clouds, " +
                "and not even the moon shines through. ";
            break;
        }
        break;
    case "early morning":
        desc += "The light of the day has barely made it over "+
            "the eastern horizon. ";
        break;
    case "morning":
        desc += "The light of the day has worked itself some "+
            "bit up the sky. ";
        break;
    case "noon":
        desc += "The light of the day shines down from right "+
            "above your head. ";   
        break;
    case "afternoon":
        desc += "The light of the day is moving towards the west. ";
        break;
    case "evening":
        desc += "The light of the day is setting in the west. ";
        break;
    }
    desc += "It is " + time + " in the lost realm of Arnor.";
    return desc;
}

public void
create_arnor()
{
}

public void
create_gondor()
{
    create_arnor();
}
