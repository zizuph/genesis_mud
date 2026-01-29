inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"

#define ARMOUR_CLASS 20

void
create_armour()
{
    set_name("gauntlets");
    set_pname("gauntlets");
    add_pname("pairs of gauntlets");
    add_name("armour");
    add_name("pair of gauntlets");
    add_pname("armours");

    set_adj("steel");

    set_short("pair of steel gauntlets");
    set_pshort("pairs of steel gauntlets");
    set_long("This is a pair of well-maintained steel gauntlets. " +
      "They look shiny and in good condition, and would seem likely " +
      "to be good protection for your hands.\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_ARMS);

    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
    add_prop(KALAMAN_NOBUY,1);
}
