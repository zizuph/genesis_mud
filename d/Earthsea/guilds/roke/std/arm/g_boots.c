#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("boots");
    add_name("pair");
    add_name("pair of goatskin boots");
    add_pname("pairs");
    set_adj("goatskin");
    set_pname("pairs of goatskin boots");
    set_short("pair of goatskin boots");
    set_long("This is a pair of boots made from goatskin, "+
        "which are both tough and warm, as they are lined with thick "+
        "wool.\n");
    set_at(A_FEET);
    set_ac(15);
    add_prop(OBJ_I_WEIGHT, 1000);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 350);
}
