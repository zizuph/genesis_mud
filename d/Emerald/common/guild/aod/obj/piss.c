/*
 *  /d/Emerald/common/guild/aod/obj/piss.c
 *
 *  This is the low level drink item from the Mess Hall of the Army of
 *  Darkness.
 *
 *  Sold at: /d/Emerald/common/guild/aod/rooms/mess_hall.c
 *
 *  Created November 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/drink";
inherit "/d/Emerald/common/guild/aod/lib/ogre_food";

#include <stdproperties.h>

/* Prototypes */
public void        create_drink();

/*
 * Function name:        create_drink
 * Description  :        set up the drink object
 */
public void
create_drink()
{
    set_name("barrel");
    add_name("piss");
    add_adj( ({ "piss" }) );

    set_short("piss barrel");
    set_long("Ugh ... Ogres are not the finest brewmasters, as evidenced"
      + " by this completely unacceptable excuse for beer. Someone must"
      + " have been proud of it, though, becuase they filled this moldy"
      + " old barrel with it. Oh well, down the hatch!\n");

    add_ogre_food_props();

    add_prop(OBJ_I_VALUE, 0);
    set_alco_amount(8);
    add_prop(OBJ_I_WEIGHT, 540);
    add_prop(OBJ_I_VOLUME, 540);
} /* create_drink */
