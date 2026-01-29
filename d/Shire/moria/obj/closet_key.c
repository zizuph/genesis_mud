inherit "/std/key";
#include "defs.h"

create_key()
{
    set_name("key");
    add_adj("dwarven");
    set_pname("keys");
    set_short("dwarven key");
    set_pshort("dwarven keys");
    set_key(77660334);
    set_long("This seems to be a dwarven key, probably to " +
	     "the owner's recidence.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME,  30);
}
