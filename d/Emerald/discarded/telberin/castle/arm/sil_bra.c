
inherit "/std/armour";

#include "/d/Emerald/defs.h"
#include <wa_types.h>

string
create_armour()
{
   set_name("bracers");
   set_short( "silver shining bracers" );
   add_name("armour");
   set_long( "The bracers dazzle you with their shine, obviously "+
      "from the highest quality materials the armourers of "+
      "Telberin could find. They cover the arms with tough plates "+
      "of elven steel, secured to the arms with the softest leather. \n");

   add_adj( "elven" );
   add_adj( "silver" );
   add_adj( "shining" );
   
   set_ac(29);
   set_at(A_ARMS);
   /*    impale  slash   bludgeon   */
   set_am(({ 1, 1, -2 }));
   add_prop(OBJ_I_VALUE, 520);
   add_prop(OBJ_I_WEIGHT, 2150);
   add_prop(OBJ_I_VOLUME, 330);
   
}

