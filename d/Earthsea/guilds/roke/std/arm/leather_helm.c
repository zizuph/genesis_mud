#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name(({"helm", "helmet"}));
    set_pname(({"helms","helmets"}));
    add_adj("leather");
    add_adj("bronze-banded");
    set_short("bronze-banded leather helmet");
    set_pshort("bronze-banded leather helmets");
    set_long("A helmet made of hardened leather "+
        "with earflaps to protect the ears and a bronze guard "+
        "around the crown.\n");
    set_default_armour(20, A_HEAD, ({-1, -1, -1}));
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 295 + random(50));
}
