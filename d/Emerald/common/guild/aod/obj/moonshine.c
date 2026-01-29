/*
 *  /d/Emerald/common/guild/aod/obj/moonshine.c
 *
 *  This is the mid level drink item from the Mess Hall of the Army of
 *  Darkness.
 *
 *  Sold at: /d/Emerald/common/guild/aod/rooms/mess_hall.c
 *
 *  Created November 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/drink";

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
    set_name("moonshine");
    add_name("bucket");
    add_pname("buckets");
    add_adj( ({ "bucket", "of", "moonshine" }) );

    set_short("bucket of moonshine");
    set_pname("buckets of moonshine");
    set_long("The clear liquid that is sloshing around in this bucket"
      + " could probably take the tarnish off a suit of armour! That"
      + " being the case, it works just fine to quench the thirst of"
      + " an Ogre who has a hankerin' for a nip o' the old hooch.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_soft_amount(100);
    set_alco_amount(45);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
} /* create_drink */
