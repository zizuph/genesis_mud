#pragma strict_types

inherit "/std/key";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

public void
create_key()
{
    set_name("_karas_key_");
    add_name("key");
    set_adj("crystal");
    set_short("crystal key");
    set_long("A key carved from what appears to be crystal. "+
      "It is fairly large but fits in your hand.\n");
    set_key(CRYSTAL_KEY);
}
