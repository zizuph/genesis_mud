/* bronze platemail for kargs of Gont */

#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("plate");
    add_name("platemail");
    set_adj(({"shiny", "bronze"}));
    set_short("shiny bronze platemail");
    set_long("A shiny bronze platemail, made of "+
        "molded bronze polished to a high shine. It is made to "+
        "cover the shoulders and shaped to the chest where you "+
        "can see the impressed outline of pectoral muscles. It "+
        "bears the symbol of Karego-At above the heart.\n");
    set_default_armour(40, A_TORSO);
    add_prop(OBJ_I_VALUE, 800);
    add_prop(OBJ_I_WEIGHT, 5500);
    add_prop(OBJ_I_VOLUME, 1200);
}
