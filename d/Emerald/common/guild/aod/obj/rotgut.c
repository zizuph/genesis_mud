/*
 *  /d/Emerald/common/guild/aod/obj/piss.c
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
    set_name("keg");
    add_name("rotgut");
    add_pname("kegs");
    add_adj( ({ "keg", "of", "rotgut" }) );

    set_short("keg of rotgut");
    set_pname("kegs of rotgut");
    set_long("This keg is filled with some of the most strong and foul-"
      + "smelling wine you have ever had the misfortune to encounter."
      + " Only a real iron-belly could handle this sort of rotgut."
      + " Naturally, Ogres have bellies that can actually digest"
      + " iron, so this comes as standard fare.\n");

    add_ogre_food_props();

    add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(150);
   set_alco_amount(19);
   add_prop(OBJ_I_WEIGHT, 150);
   add_prop(OBJ_I_VOLUME, 150);
} /* create_drink */
