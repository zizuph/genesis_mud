#pragma strict_types

inherit "/std/key";

#include "defs.h"

public void
create_key()
{
    set_name("key");
    add_name("_raskalions_key_");
    add_name("key");
    set_adj("brass");
    set_short("shiny brass key");
    add_adj("shiny");
    set_long("A shiny key made from brass. It looks about the " +
        "size of a door key.\n");
    set_key(BRASS_KEY);
}
