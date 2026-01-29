inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
   set_name(({"shirt","_flotsam_c_spirit_"}));
   set_short("frilly white silk shirt");
   set_long("A lovely white silk shirt with puffy sleeves, "+
      "and lace cuffs.\n"); 
   set_adj(({"frilly","white","silk"}));
   set_ac(2);
   set_am(({0,0,0}));
   set_at(A_BODY);
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_VOLUME, 200);
   add_prop(OBJ_I_WEIGHT, 250);
}
