/* 
 *  /d/Gondor/std/drink/ith_wine.c:  
 *
 *  Soft 150 ml, alco 19 ml, price 48 cc.
 *  Drink for the Seven Stars Inn (common/guild/gondor/rangerinn.c)
 */
#pragma save_binary
#pragma strict_types

inherit "/std/drink.c";

#include <stdproperties.h>

public void
create_drink() 
{
   set_name("wine");
   add_name("glass");
   set_pname("wines");
   add_pname(({"glasses"}));
   set_adj(({"glass","of","white"}));
   set_short("glass of white wine");
   set_pshort("glasses of white wine");
   set_long("The sparkling white wine comes from the ripened grapes that were harvested\n"
         +  "in the land of Ithilien some years ago.\n");

   add_prop(OBJ_I_VALUE, 0);
   set_soft_amount(150);
   set_alco_amount(19);
   add_prop(OBJ_I_WEIGHT, 150);
   add_prop(OBJ_I_VOLUME, 150);
}
