/*
 *  /d/Emerald/telberin/dock/sparkle/ship.c
 *
 *  This is the updated ship for the Sparkle-Emerald line. Far too long
 *  has this code been simplistic and boring. Time to up the quality!
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/ship";

#include <cmdparse.h>

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* Prototypes */
public void        create_ship();
public void        reset_ship();

/* Definitions */
#define            OUR_DOCK  (TELBERIN_DIR + "dock/sparkle/")
#define            OCEAN_DIR (TELBERIN_DIR + "dock/")


/*
 * Function name:        create_ship
 * Description  :        set up the ship
 */
public void
create_ship()
{
    object  cap;
    
    setuid();
    seteuid(getuid());

    set_deck(OUR_DOCK + "deck");
    cap = clone_object(OUR_DOCK + "captain");
    cap->arm_me();
    set_captain(cap);

    set_places_to_go( ({
        "/d/Emerald/telberin/dock/telberin_dock",
        OCEAN_DIR + "lakeroom1",
        OUR_DOCK + "sea1",
        OUR_DOCK + "sea2",
        OUR_DOCK + "sea3",
        OUR_DOCK + "sea4",
        OUR_DOCK + "sea5",
        OUR_DOCK + "sea6",
        OUR_DOCK + "sea7",
        OUR_DOCK + "sea8",
        "/d/Genesis/start/human/town/pier7",
        OUR_DOCK + "sea8",
        OUR_DOCK + "sea7",
        OUR_DOCK + "sea6",
        OUR_DOCK + "sea5",
        OUR_DOCK + "sea4",
        OUR_DOCK + "sea3",
        OUR_DOCK + "sea2",
        OUR_DOCK + "sea1",
        OCEAN_DIR + "lakeroom1",
        }));

    set_time_between_stops(({ 24,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                              24,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                               2,
                           }));

    set_ticket_id("Telberin to Sparkle Line");

    set_short("strange gleaming vessel");
    set_long("Unlike the standard sailing ships which operate"
      + " throughout the realms of Genesis, this ship boasts no"
      + " visible masts or sails of any kind. Rather, it is comprised"
      + " of a grand hull glowing with an illumination all its own"
      + " which rises majestically out of the water.\n");

    set_name("ship");
    add_name( ({ "vessel", "transport" }) );
    add_adj( ({ "strange", "gleaming", "glowing" }) );

    add_item( ({ "mast", "masts" }),
        "How strange ... the glowing vessel has no masts of any kind!\n");
    add_item( ({ "sail", "sails" }),
        "No sails are visible upon the vessel. One wonders how such a"
      + " ship would move through the water.\n");
    add_item( ({ "hull", "grand hull" }),
        "The hull of the vessel is similar to what one would expect to"
      + " see on a sizeable ship of its kind. The absence of masts and"
      + " sails does, however, cause the hull to take on a bit of an"
      + " unusual quality.\n");
    add_item( ({ "illumination", "light", "glow", "gleam" }),
        "The ship gleams with an illumination that seems to be emenating"
      + " from the very material which comprises the hull.\n");

    enable_reset();   
} /* create_ship */


/* 
 * Function name:        reset_ship
 * Description  :        reload the captain, if he has been
 *                       killed
 */
void
reset_ship()
{
    object cap;
    if (!objectp(query_captain()))
    {
        cap = clone_object(OUR_DOCK + "captain");
	cap->arm_me();
        set_captain(cap);
        cap->move(query_deck()[0]);
        start_ship(location);
    }
} /* reset_ship */

