inherit "/std/key";
#include <stdproperties.h>

create_key()
{
    set_name("key");
    set_pname("keys");
    set_short("large steel key");
    set_pshort("large steel keys");
    set_adj(({"steel","large"}));
    set_key(9035768);
    set_long("It's a large steel key.\n");
    add_prop(OBJ_I_WEIGHT, 5*1000);
}
