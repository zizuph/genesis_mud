inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 10

void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntlets");
    add_name("armour");
    add_pname("armours");
    add_name("pair of gauntlets");
    add_pname("pairs of gauntlets");

    set_adj("leather");

    set_short("pair of leather gauntlets");
    set_pshort("pairs of leather gauntlets");
    set_long("This is a pair of finely made leather gauntlets. " +
      "By the looks of them they have been well looked after.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
