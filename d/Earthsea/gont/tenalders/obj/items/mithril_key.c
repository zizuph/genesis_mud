#pragma strict_types

inherit "/std/key";

#include "defs.h"

public void
create_key()
{
    set_name("_aras_key_");
    add_name("key");
    set_adj("mithril");
    set_short("mithril key");
    set_long("An unusual key made from mithril. It is fairly "+
      "large, although it fits in your hand.\n");
    set_key(MITHRIL_KEY);
}
