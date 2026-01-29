inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
   set_name(({"breeches","_flotsam_c_spirit_"}));
   add_name("stockings");
   set_short("red velvet breeches and black stockings");
   set_long("A set of red velvet breeches, and some black "+
      "stockings that look expensive.\n"); 
   set_adj(({"red","velvet","black"}));
   set_ac(3);
   set_am(({0,0,0}));
   set_at(A_LEGS);
   add_prop(OBJ_I_VALUE, 1000);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_WEIGHT, 500);
}
