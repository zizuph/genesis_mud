/*
 *  /d/Emerald/common/guild/aod/obj/calf.c
 *
 *  This is the low level food item from the Mess Hall of the Army of
 *  Darkness.
 *
 *  Sold at: /d/Emerald/common/guild/aod/rooms/mess_hall.c
 *
 *  Created November 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/food";
inherit "/d/Emerald/common/guild/aod/lib/ogre_food";

#include <stdproperties.h>

/* Prototypes */
public void        create_food();

/*
 * Function name:        create_food
 * Description  :        set up the food object
 */
public void
create_food()
{
    set_name("calf");
    add_name("meat");
    set_pname("roasted calves");
    add_adj( ({ "roast", "roasted" }) );

    set_short("roasted calf");
    set_long("This young calf has been skinned and then roasted in its"
      + " entirety on what must have been a very large grill. Tasty"
      + " juices seep out from cracks in the flesh where the heat has"
      + " opened up this tasty little morsel.\n");

    add_ogre_food_props();

    add_prop(OBJ_I_VALUE, 0);
    set_amount(200);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 150);
} /* create_food */
