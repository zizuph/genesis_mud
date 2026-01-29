/*
 *   /d/Gondor/std/drink/ale.c
 *
 *   Soft 100 ml, alco 4 ml, price 12cc.
 *   Can be used everywhere.
 *   Used in the RoN inn (/d/Gondor/common/guild/north/inn.c)
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
   set_adj("golden");
   set_short("glass of golden ale");
   set_pshort("glasses of golden ale");
   set_long(break_string(
      "The golden ale has a golden colour and smells like beer that "
    + "has been mixed with a lot of water.\n",70));

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(4);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
