#pragma strict_types

inherit "/std/key";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

public void
create_key()
{
    set_name("_maras_key_");
    add_name("key");
    set_adj("diamond");
    set_short("diamond key");
    set_long("A very unusual key, which appears to be made "+
      "from solid diamond. It is fairly large, although it fits "+
      "in your hand.\n");
    set_key(DIAMOND_KEY);
}
