
#include "../local.h"

inherit "/std/key";

void
create_key()
{
    set_short("large iron key");
    set_long("This is a large iron key, almost a foot long.\n");
    set_key(VAULT_KEY);
}
