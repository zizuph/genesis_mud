#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("cloak");
    set_adj(({"flowing", "white"}));
    set_short("flowing white cloak");
    set_long("This is a long flowing white cloak. "+
        "When worn it extends from the high neck collar all "+
        "the way down to the ankles. On the back it bears the "+
        "golden insignia of the Lord of Gont.\n");
    set_at(A_ROBE);
    set_ac(15);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 100);
}
