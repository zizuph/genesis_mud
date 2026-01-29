inherit "/std/key";

#include "/d/Gondor/defs.h"

void
create_key()
{
    set_name("key");
    set_adj(({"small", "steel", }));
    set_short("small steel key");
    set_long(BSN("A small steel key. It must fit into a rather small "
      + "keyhole, probably not in a door, but in a chest or a drawer."));
    set_key("baranor_desk_key");
}
