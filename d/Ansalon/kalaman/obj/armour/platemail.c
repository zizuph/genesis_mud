inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"

#define ARMOUR_CLASS 34

void
create_armour()
{
    set_name("armour");
    add_name("platemail");
    set_pname("armours");
    add_pname("platemails");

    set_adj("gleaming");
    add_adj("steel");

    set_short("gleaming steel platemail");
    set_long("This suit of platemail is kept in immaculate condition. Made of expensive " +
      "steel, and bearing the design of the Kalaman Guard, this armour must be considered " +
      "an honour to wear, well, for a Kalamanite that is.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 24000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
    add_prop(KALAMAN_NOBUY,1);
}
