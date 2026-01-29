/* A bottle of sacramental wine needed for the vision quest */
/* poisonous if VDQ_POISON prop is set to true              */
/* Drink bug fixed by Maniac 3/5/98 */ 

inherit "/std/drink";
#include <stdproperties.h>
#include "defs.h"
 
create_drink()
{
    set_name(({"wine","bottle of wine","sacramental wine",
               "bottle of sacramental wine","black wine",
               "bottle of black wine", VDQ_WINE}));
    add_adj("black");
    add_adj("sacramental");
    set_short("bottle of black wine");
    set_pshort("bottles of black wine");
    set_long(
       "It is a bottle of sacramental wine, black in color.\n");
    set_soft_amount(200);
    set_alco_amount(5);  /* weak */
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(VDQ_POISONED, 0);
}

int command_drink() {
   mixed res;
   object poison;
   object wine=this_object();
   object TPlay=this_player();
 
   res = ::command_drink(); /* execute standard function */

   if (res != 1)
       return res;

   if (wine->query_prop(VDQ_POISONED)) {
      poison = clone_object(OBJ_DIR+"vispoisn");
      poison->move(TPlay);
      poison->start_poison();
   }
   return 1;
}

