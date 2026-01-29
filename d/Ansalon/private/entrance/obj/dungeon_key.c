inherit "/std/key";
#include "/d/Ansalon/goodlund/kendermore/local.h"

void
create_key()
{
    ::create_key();

    set_name("dungeon key");
    add_name("key");
    add_name("dungeon_key");
    set_adj("large");
    add_adj("skeleton");
    set_short("large skeleton key");
    set_pshort("large skeleton keys");

    set_long("It's a large skeleton key.\n");

    set_key(FOO_BAR);
}


