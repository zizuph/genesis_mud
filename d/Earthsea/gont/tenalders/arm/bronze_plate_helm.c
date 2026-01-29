#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("helm");
    add_name("helmet");
    set_adj(({"bronze", "plate", "red-plumed" }));
    set_short("red-plumed bronze helm");
    set_pshort("red-plumed bronze helms");
    set_long("A shiny bronze plate helm. "+
        "Fashioned in the manner of Karego-At, there is an ornament "+
        "of red plumes on the crown that signifies higher ranked "+
        "Karg warriors.\n");
    set_default_armour(30, A_HEAD);
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 500);
}
