#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/rohan/isengard/defs.h"

void
create_armour()
{
    set_name(({"helmet","leather helmet","plated helmet"}));
    set_pname("helmets");
    set_short("steel plated leather helmet");
    set_pshort("steel plated leather helmets");
    set_adj("dunlending");
    set_adj("plated");
    set_adj("leather");
    set_long("The helmet is made of leather and covered with steel plates.\n"+
      "It covers head and shoulders when worn.\n");

    set_default_armour(25,A_HEAD,({-2,3,-1}),0);

    add_prop(ISEN_I_ARMOUR, 1);
}
