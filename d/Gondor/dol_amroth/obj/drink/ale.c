/* -*- Mode: C -*-
 *   obj/drink/ale.c
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
   set_name("ale");
   set_pname("ales");
   set_adj("foaming");
   set_short("tankard of foaming ale");
   set_pshort("tankards of foaming ale");
   set_long("Ale is a fermented beverage produced from grain and " +
	    "hops. In Gondor ale is used for those occations that " +
	    "is to be special, or for people who wants to show of " +
	    "that they have more money than most other people.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
