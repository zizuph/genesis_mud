inherit "/std/key";

#include "defs.h"

void
create_key()
{
    set_name("key");
    set_adj(({"iron", "big"}));
    set_short("big iron key");
    set_pshort("big iron keys");
    set_long("The big iron key feels heavy and looks a bit worn.\n");
    set_key(KEY_TOWER1);
}
