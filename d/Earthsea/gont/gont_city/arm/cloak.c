#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    set_name("cloak");
    set_adj(({"crimson", "pelawi-fur trimmed" }));
    set_short("crimson cloak trimmed with pelawi fur");
    set_pshort("crimson cloaks trimmed with pelawi fur");
    set_pname("cloaks");
    set_long("This is a long crimson cloak, which is "+
        "trimmed in pelawi fur. It is made from a material both "+
        "thick and soft and appears very warm-looking.\n");
    set_at(A_ROBE);
    set_ac(15);
    add_prop(OBJ_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME, 400);
    add_prop(OBJ_I_VALUE, 350);
}
