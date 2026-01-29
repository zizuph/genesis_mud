/*
 *  /d/Emerald/telberin/dock/sparkle/ship.c
 *
 *  This is the updated ship for the Sparkle-Emerald line. Far too long
 *  has this code been simplistic and boring. Time to up the quality!
 *
 *  Created August 2007, by Cooper Sherry (Gorboth)
 * Ported to the new ship system by Tapakah, 10/2008
 */
#pragma save_binary
#pragma strict_types

#include <cmdparse.h>
#include <macros.h>

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDSHIP;

/* Prototypes */
public void        create_ship();

/* Definitions */
#define            OUR_DOCK  (TELBERIN_DIR + "dock/sparkle/")
#define            SPARKLE_PIER "/d/Genesis/start/human/town/pier7"
#define            EMERALD_PIER "/d/Emerald/telberin/dock/telberin_dock"

/*
 * Function name:        create_ship
 * Description  :        set up the ship
 */
public void
create_ship()
{
    ::create_ship();
    
    setuid();
    seteuid(getuid());
    
    set_deck(OUR_DOCK + "deck");
    set_cabin(OUR_DOCK + "cabin");
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

    set_ship_line(MASTER_OB(this_object()), 
                  OUR_DOCK + "ncaptain",
                  OUR_DOCK + "ticket", 
                  ({ EMERALD_PIER, 
                     SPARKLE_PIER }) );               
} /* create_ship */
