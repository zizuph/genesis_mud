/*
 *  /d/Emerald/telberin/obj/wine.c
 *
 *  This is the mid-level alcohol at the Inn in Telberin.
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
   set_name("wine");
   set_adj("southland");

   set_short("glass of Southland Wine");
   set_pshort("glasses of Southland Wine");
   set_long("This glass of wine is tart with a good nose and"
     + " light body. Slightly rose in color, it has hints of"
     + " pear and oak in its finish.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(120);
   set_alco_amount(20);
   add_prop(OBJ_I_WEIGHT,120);
   add_prop(OBJ_I_VOLUME,120);
} /* create_drink */
