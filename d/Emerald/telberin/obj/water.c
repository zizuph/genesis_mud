/*
 *  /d/Emerald/telberin/obj/water.c
 *
 *  This is the low-level drink one can order from the Inn in
 *  Telberin.
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
   set_name("water");
   set_adj("spring");

   set_short("glass of spring water");
   set_pshort("glasses of spring water");
   set_long("There is a slight effervecense to this glass of"
     + " spring water. It is a pure draught captured from the"
     + " glacial peaks of the Blackwall Mountains in Emerald.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(90);
   add_prop(OBJ_I_WEIGHT,90);
   add_prop(OBJ_I_VOLUME,90);
} /* create_drink */
