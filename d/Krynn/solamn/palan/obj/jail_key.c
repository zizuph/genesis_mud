inherit "/std/key";

#include "../local.h"

create_key() {
    ::create_key();

    set_adj("small");
    add_adj("bronze");
    set_pshort("small bronze keys");
    set_short("small bronze key");
    set_long("It's a small bronze key.\n");

    set_key("the_key_from_the_future");
}
