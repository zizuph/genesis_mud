/* -*- Mode: C -*-
 *
 *   obj/drink/water.c
 *
 *   Soft 100 ml, alco 0 ml, price 3cc.
 *
 *   May be used everywhere.
 *
 *   Olorin, 8-Jul-1997
 *   Changes:
 *   Skippern Feb 2000
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink()
{
   set_name("water");
   set_pname("waters");
   add_pname(({"cups", "cups of water"}));
   set_adj("clear");
   set_short("cup of clear water");
   set_pshort("cups of clear water");
   set_long("A cup of water is refreshing on hard days.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(0);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
