#include "defs.h"
inherit "/std/key";

void
create_key()
{
    set_adj("golden");
    add_adj("jewelled");
    set_long("A beautiful jewelled key that gleams in the light.\n");
    set_key(VAULT_KEY);
}
