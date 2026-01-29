inherit "/std/key";

#include "/d/Gondor/defs.h"

void
create_key()
{
    set_name("key");
    set_adj(({"large", "iron", "rusty"}));
    set_short("large iron key");
    set_long(BSN("A large iron key. It must have lain on the " +
        "ground for a long time, since it is covered all over by rust."));
    set_key("Emyn-Arnen_Kitchen_Gate");
}
