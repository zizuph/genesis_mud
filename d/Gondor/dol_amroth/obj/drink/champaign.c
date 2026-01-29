/* -*- Mode: C -*-
 *
 *   obj/drink/champaign.c
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
   set_name("champaign");
   set_pname("champaign");
   set_adj("sparkling");
   set_short("glass of sparkling champaign");
   set_pshort("glasses of sparkling champaign");
   set_long("Champaign is produced from a well guarded " +
	    "recepie. Drinking this fine beverage gives a " +
	    "tingeling sensation in the mouth.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
