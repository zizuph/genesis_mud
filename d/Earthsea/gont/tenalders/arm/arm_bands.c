#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("bands");
    add_name("pair of bronze arm bands");
    add_name("pair of arm bands");
    add_name("pair of bands");
    add_pname("pairs of bronze arm bands");
    add_pname("pairs of arm bands");
    set_pname("pairs of bronze arm bands");
    add_name("pair");
    set_adj(({"bronze", "arm"}));
    set_short("pair of bronze arm bands");
    set_pshort("pairs of bronze arm bands");
    set_long("A set of bronze arm bands, which "+
        "protect the lower arm from the wrist to the elbow.\n");
    set_default_armour(20, A_ARMS, ({-1, 2, -1}));
    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 800);
    add_prop(OBJ_I_VOLUME, 200);
}
