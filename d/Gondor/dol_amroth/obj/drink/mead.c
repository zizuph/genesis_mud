/* -*- Mode: C -*-
 *
 *   obj/drink/mead.c
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
   set_name("mead");
   set_pname("meads");
   set_adj("good");
   set_short("tankard of good mead");
   set_pshort("tankard of good mead");
   set_long("Mead is an alcoholic brew made from honey, and added the " +
      "spices from the herb mead, wich also gives the brew its name. " +
      "This is a traditionally brew for peasants.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
