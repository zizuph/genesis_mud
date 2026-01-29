inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>

create_armour()
{
   set_name(({"hat","_flotsam_c_spirit_"}));
   set_short("wide-brimmed hat with a jaunty red plume");
   set_long("A very elegant looking hat with a large red "+
      "plume adorning it.\n"); 
   set_adj(({"wide-brimmed","plumed","red"}));
   set_ac(2);
   set_am(({0,0,0}));
   set_at(A_HEAD);
   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_VOLUME, 100);
   add_prop(OBJ_I_WEIGHT, 200);
}
