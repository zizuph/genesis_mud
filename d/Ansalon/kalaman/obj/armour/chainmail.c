inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/kalaman/local.h"


void
create_armour()
{
    set_name("armour");
    add_name("chainmail");
    set_pname("chainmails");
    add_pname("armours");

    set_adj("shiny");
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("shiny chainmail");
    set_long("This is a suit of chainmail typically " +
      "worn by the guards of Kalaman. That it has " +
      "been kept in good condition is evident by " +
      "how shiny it is.\n");

    set_ac(25);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 10000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(18));
    add_prop(KALAMAN_NOBUY,1);
}
