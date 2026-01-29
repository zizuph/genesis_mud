/*
 *   /d/Gondor/std/drink/water.c
 *
 *   Soft 100 ml, alco 0 ml, price 3cc.
 *
 *   May be used everywhere.
 *   Used in the RoN inn.
 *
 *   Olorin, 8-Jul-1997
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
   add_pname(({"glasses", "glasses of water"}));
   set_adj("fresh");
   set_short("glass of fresh water");
   set_pshort("glasses of fresh water");
   set_long("A glass of fresh water. It will make you less thirsty.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(0);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
