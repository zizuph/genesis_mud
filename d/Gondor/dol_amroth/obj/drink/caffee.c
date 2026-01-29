/* -*- Mode: C -*-
 *
 *   obj/drink/caffee.c
 *
 *   Soft 100 ml, alco 0 ml, price 3cc.
 *
 *   May be used everywhere.
 *
 *   Olorin, 8-Jul-1997
 *   Modified:
 *   Skippern Feb 2000
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
   set_name("coffee");
   set_pname("coffee");
   add_pname(({"cups", "cups of coffee"}));
   set_adj("fresh");
   set_short("cup of fersh coffee");
   set_pshort("cups of fersh coffee");
   set_long("This cup of coffee smells realy good and fresh. " +
	    "Coffee is normally produced from a type of beans " +
	    "grown in the far Harrad, and the beans are " +
	    "roasted before they are ground and brewed.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(0);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
