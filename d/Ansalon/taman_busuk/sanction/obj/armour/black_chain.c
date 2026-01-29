#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/armour";
inherit "/lib/keep";

#define ARMOUR_CLASS 40

object wearer;

void
create_armour()
{
    set_name("chainmail");
    set_adj("black");
    add_adj("blackened");

    set_short("black chainmail");
    set_pshort("black chainmails");
    set_long("This suit of chainmail is made of blackened " +
      "steel. It is very well kept and will offer great protection to its owner.\n");
    
    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 4500);
    add_prop(OBJ_I_VOLUME, 4500);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}
