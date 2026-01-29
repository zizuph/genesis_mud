inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#define ARMOUR_CLASS 20

void
create_armour()
{
    set_name("breastplate");
    set_pname("breastplates");
    add_name("armour");
    add_pname("armours");

    set_adj("hardened");
    add_adj("leather");

    set_short("hardened leather breastplate");
    set_pshort("hardened leather breastplates");
    set_long("This hardened leather breastplate is of fine make, " +
      "and looks like it was crafted for quite a muscular man. " +
      "It has been hardened in some natural juices that makes it " +
      "as tough to penetrate as chainmail.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_TORSO);

    add_prop(OBJ_I_WEIGHT, 15000);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
