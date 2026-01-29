inherit "/std/key";
#include "/d/Krynn/icewall/local.h"

create_key() 
{
    ::create_key();
set_name("key");
set_short("small iron key");
set_adj("small");
add_adj("iron");
set_pshort("small iron keys");
set_long("It's a small key made out of iron with the number 4 engraved on it.\n");

    set_key(BASEKEY);
}
