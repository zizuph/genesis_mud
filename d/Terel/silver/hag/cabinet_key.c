inherit "/std/key";

#include <stdproperties.h>

create_key()
{
    set_name("key");
    add_name(({"ragata:cabinet_key","_regata_eq"}));
    set_adj("iron");
    set_adj("black");
    set_short("black iron key");
    set_pshort("black iron keys");
    set_long("It's a black iron key.\n");
    add_prop(OBJ_M_NO_BUY,1);
}
