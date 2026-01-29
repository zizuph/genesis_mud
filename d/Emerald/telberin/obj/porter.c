/*
 *  /d/Emerald/telberin/obj/porter.c
 *
 *  This is the low-level alcohol at the Inn in Telberin.
 *
 *  Copyright (c) April 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
inherit "/std/drink";

#include <stdproperties.h>

/*
 * Function name:        create_drink
 * Description  :        set up the drink
 */
public void
create_drink()
{
   set_name("porter");
    add_name( ({ "beer", "alcohol" }) );
   set_adj("stout");
    add_name("mug");

   set_short("mug of stout porter");
   set_pshort("mugs of stout porter");
   set_long("The dark color and fragrant aroma of this beer"
     + " is enough to convert any wine drinker to the art of the"
     + " brew. It has a hint of walnut and smells like warm"
     + " bread.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(270);
   set_alco_amount(8);
   add_prop(OBJ_I_WEIGHT,270);
   add_prop(OBJ_I_VOLUME,270);
} /* create_drink */
