/* -*- Mode: C -*-
 *
 *   obj/drink/gin.c
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
   set_name("gin");
   set_pname("gin");
   set_adj("smelly");
   set_short("glass of smelly gin");
   set_pshort("glasses of smelly gin");
   set_long("There are nothing positive to say about " +
	    "this liqour, but people drink it anyway. " +
	    "One reason might be that it is roumored that " +
	    "gin gives resistance to swamp diseas. " +
	    "If this roumors are true you dont know, " +
	    "but it sure taste that way.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
