#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("helm");
    add_name("helmet");
    set_pname("helms");
    set_adj(({"golden-winged", "dragon"}));
    set_short("golden-winged dragon helm");
    set_pshort("golden-winged dragon helms");
    set_long("A helmet decorated with the golden "+
        "wings of a dragon affixed to it, sweeping back to the "+
        "sides.\n");
    set_keep(1);
    set_default_armour(40, A_HEAD);
    add_prop(OBJ_I_VALUE, 500);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 500);
}
