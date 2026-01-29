
inherit "/std/armour";

#include "/d/Emerald/defs.h"
#include <wa_types.h>

void
create_armour()
{
   set_name("greaves");
   set_short("silver shining greaves");
   set_long( "The greaves gleam with a dazzling shine, "+
      "made from the finest workmanship of the smithys of "+
      "Telberin. A tough outer surface protects the wearer, "+
      "while inside, soft supple leather ensures a secure and "+
      "comfortable fit. \n");
   
   add_adj( "paladin" );
   add_adj( "elven" );
   add_adj( "shining" );
   add_adj( "silver" );
   
   set_ac(29);
   set_at(A_LEGS);
   /*    impale  slash   bludgeon   */
   set_am(({ 1, 1, -2 }));
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 2300);
   add_prop(OBJ_I_VOLUME, 410);
   
}
