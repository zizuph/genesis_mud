/* -*- Mode: C -*-
 *
 *   obj/drink/wwine.c
 *
 *   Soft 100 ml, alco 4 ml, price 12cc.
 *   Can be used everywhere.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink.c";

#include <stdproperties.h>

public void
create_drink() 
{
   set_name("wine");
   set_pname("wine");
   set_adj("white");
   set_short("glass of white wine");
   set_pshort("glasses of white wine");
   set_long("Wine is a fermented beverage made from " +
	    "grapes. This wine is not recogniced as a " +
	    "fine wine. It has a strange taste, that " +
	    "leaves an extremely dry feeling in the mouth.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
