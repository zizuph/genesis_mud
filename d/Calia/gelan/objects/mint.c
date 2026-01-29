 /*****************************************************************************
*  /d/Calia/gelan/objects/mint.c
*
*  Description: Mint Chocolate Puffs
*
*  Created Aug 2021, Greneth
*
 *****************************************************************************/

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include <stdproperties.h>
#include "object.h"

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/food";

 /*****************************************************************************
*  Function name: create_food
*  Description  : Constructor for the food, modify this to change.
 *****************************************************************************/
void
create_food() {
   set_name("mint");
   add_name("puff");
   set_adj("chocolate");
   set_short("mint chocolate puff");
   set_pshort("mint chocolate puffs");
   set_long("A tiny puff pastry stuffed with a minty cream and topped "
   + "with a small dollop of chocolate.\n"); 
   add_prop(OBJ_I_VALUE, 144);
   set_amount(50);
}