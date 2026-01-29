#include "defs.h"
#include <stdproperties.h>

inherit "/std/key";

create_key()
{
    set_name("key");
    add_adj("golden");
    set_short("golden key");
    set_long("A golden key.\n");
    set_key(77670388);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 67);
    add_prop(OBJ_I_VALUE, 40);
}
