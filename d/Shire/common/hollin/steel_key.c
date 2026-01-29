inherit "/std/key";
inherit "/lib/keep";
#include <stdproperties.h>
#include "defs.h"


create_key()
{

    set_name("key");
    set_pname("keys");
    set_short("large steel key");
    set_pshort("large steel keys");
    set_adj(({"steel","large"}));
    set_key(333222111);
//    set_key("@@set_key_name@@");
    set_long("It's a large steel key.\n");
    add_prop(OBJ_I_WEIGHT, 5*1000);
    set_keep();
}


int set_key_name()
{
    int key_name;

    key_name = 987 + random(500)+ random (99);
    return 1;
}
