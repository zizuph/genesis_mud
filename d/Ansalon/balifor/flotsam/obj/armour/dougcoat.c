inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
   set_name(({"coat","_flotsam_c_spirit_"}));
   set_short("red velvet coat");
   set_long("A beautiful red velvet waistcoat, with golden "+
      "buttons.\n"); 
   set_adj(({"red","velvet"}));
   set_ac(4);
   set_am(({0,0,0}));
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE, 1500);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_WEIGHT, 500);
}
