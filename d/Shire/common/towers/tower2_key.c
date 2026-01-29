inherit "/std/key";

#include "defs.h"

void
create_key()
{
    set_name("key");
    set_adj(({"brass", "big"}));
    set_short("big brass key");
    set_pshort("big brass keys");
    set_long("The big brass key is quite heavy.\n");
    set_key(KEY_TOWER2);
}
