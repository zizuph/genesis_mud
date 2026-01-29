/* This is a test armour, perhaps appropriate for my gnomes */

inherit "/std/armour";

#include <wa_types.h>       
#include <formulas.h>      
#include <stdproperties.h>  
#include <macros.h>

#define ARMOUR_CLASS 30

void
create_armour()
{
    set_name("chainmail");
    set_pname("chainmails");

    set_adj("light");
    set_adj("forest-green");

    set_short("light forest-green chainmail");
    set_pshort("forest-green chainmails");

    set_long("This chainmail has been made out of thousands of minute" +
      " steel rings, joined together to form a very light and" +
      " flexible armour. It looks like good armour for a warrior," +
      " as well as a scout.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);
    set_am(({ -3,5,-3 }));

    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(ARMOUR_CLASS));

}
