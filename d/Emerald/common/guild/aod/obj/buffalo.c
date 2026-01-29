/*
 *  /d/Emerald/common/guild/aod/obj/buffalo.c
 *
 *  This is the top level food item from the Mess Hall of the Army of
 *  Darkness.
 *
 *  Sold at: /d/Emerald/common/guild/aod/rooms/mess_hall.c
 *
 *  Created October 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/food";
inherit "/d/Emerald/common/guild/aod/lib/ogre_food";

#include <stdproperties.h>

/* Prototypes */
public void        create_food();
public string      describe();

/*
 * Function name:        create_food
 * Description  :        set up the food object
 */
public void
create_food()
{
    set_name("buffalo");
    add_name("surprise");
    add_name("meat");
    set_pname("filets of venison");
    add_adj( ({ "surprised" }) );

    set_short("buffalo surprise");
    set_long(describe);

    add_ogre_food_props();

    add_item( ({ "buffalo surprise" }), long);

    add_prop(OBJ_I_VALUE, 0);
    set_amount(570);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 450);
} /* create_food */


/*
 * Function name:        describe
 * Description  :        create a long description for the object
 * Returns      :        string - the text for the description
 */
public string
describe()
{
    if (environment(this_object()) != this_player())
    {
        return "This is a sleeping buffalo that looks to have been"
          + " knocked unconscious.\n";
    }

    return "In your arms is a sleeping buffalo. It looks as if it has"
      + " been knocked unconscious. Wait ... its stirring. Oho! The"
      + " buffalo's eyes snap open and it snorts in surprise as it"
      + " finds itself in your clutches. You quickly knock it back out"
      + " to keep it still until you feel like eating it.\n";
} /* describe */