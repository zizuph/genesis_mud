#pragma strict_types.h

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/isengard/defs.h"

void
create_armour()
{
    set_name("leather armour");
    add_name("armour");

    set_pname("leathers");
    add_pname("armours");

    set_adj("leather");
    set_adj("studded");

    set_short("studded leather armour");
    set_pshort("studded leather armours");
    set_long("The studded leather armour is made of closely set metal\n"+
      "studs embedded in leather armour.\n");

    set_default_armour(10,A_BODY,0,0);

    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(10)+random(100)-50);
    add_prop(ISEN_I_ARMOUR, 1);
}
