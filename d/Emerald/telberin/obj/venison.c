/*
 *  /d/Emerald/telberin/obj/venison.c
 *
 *  This is the top level food item from the Inn in
 *  Telberin in Emerald.
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

/*
 * Function name:        create_food
 * Description  :        set up the food object
 */
public void
create_food()
{
    set_name("venison");
    add_name("filet");
    add_name("meat");
    add_name("steak");
    set_pname("filets of venison");
    add_adj( ({ "filet", "of" }) );

    set_short("filet of venison");
    set_long("This is a choice cut of meat indeed! A generous"
      + " portion of prime venison has been cut into a tall"
      + " filet and grilled to perfection. The inner layers"
      + " are red and juicy, and the meat almost melts in your"
      + " mouth. A more flavorful steak than this is hard to find.\n");

    add_prop(OBJ_I_VALUE, 0);
    set_amount(560);
    add_prop(OBJ_I_WEIGHT,550);
    add_prop(OBJ_I_VOLUME,540);
} /* create_food */
