inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 25

void
create_armour()
{
    set_name("armour");
    set_pname("armours");

    set_adj("chain");

    set_short("chain armour");
    set_pshort("chain armours");
    set_long("This is fairly ordinary chainmail, although " +
      "a fair size larger so as to fit someone about the size " +
      "of an ogre.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
