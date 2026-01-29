/* -*- Mode: C -*-
 *   obj/drink/whiskey.c
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
   set_name("whiskey");
   set_pname("whiskey");
   set_adj("amber");
   set_short("tumbler of amber whiskey");
   set_pshort("tumbler of amber whiskey");
   set_long("Whiskey is a liquor made from tipple distilled " +
	    "fermented malts. Many whiskeys are recognized " +
	    "by their special features and tastes, which are " +
	    "a direct result of the environment where the whiskey " +
	    "is produced. This whiskey has a clear amber colour, " +
	    "and the smell seems somewhat salty. The taste is first " +
	    "very smoky, then a hint of seaweed and cherry, before " +
	    "a symphony of exotic spices and banana.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
