/* 
 *  /d/Gondor/guilds/rangers/obj/rohan_whiskey.c
 *
 *  Soft 100 ml, alco 45 ml, price 216 cc.
 *  Drink for the Seven Stars Inn
 */
inherit "/std/drink";

#include <stdproperties.h>

public void
create_drink() 
{
   set_name("whiskey");
   set_pname("whiskeys");
   set_adj("dry");
   set_short("glass of dry whiskey");
   set_pshort("glasses of dry whiskey");
   set_long("The dry whiskey is of a golden-brownish colour " +
       "and has a strong smell to it. It was produced somewhere " +
       "in Rohan sometime during the last decade.\n"); 

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(100);
   set_alco_amount(45);
   add_prop(OBJ_I_WEIGHT, 100);
   add_prop(OBJ_I_VOLUME, 100);
}
