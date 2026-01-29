inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 19

void
create_armour()
{
   set_name(({"armour","_flotsam_c_shell_"}));
   set_pname("armours");
   
   set_adj("sharkskin");
   
   set_short("sharkskin armour");
   set_pshort("sharkskin armours");
   set_long("This leather armour is crafted from the skin of a " +
      "large shark, and is often used by the sea-elves of the " +
      "Bloodsea of Istar. This armour is light yet very strong, " +
      "and allows for free movement in the water. \n");
   
   set_ac(ARMOUR_CLASS);
   set_at(A_BODY);
   
   add_prop(OBJ_I_WEIGHT, 3000);
   add_prop(OBJ_I_VOLUME, 2500);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
