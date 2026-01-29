inherit "/std/key";
#include "../local.h"

void
create_key()
{
    ::create_key();

    set_name("house key");
    add_name("key");
    add_name("house_key");
    add_adj("black");
    add_adj("small");
    add_adj("house");
    set_short("small black key");
    set_pshort("small black keys");

    set_long("It's a small black key.\n");

    set_key(BOX_KEY);
}


