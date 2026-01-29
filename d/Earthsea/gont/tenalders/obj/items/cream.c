#pragma strict_types

inherit "/std/drink";

#include <stdproperties.h>
#include <macros.h>

public void
create_drink()
{
    set_name("cream");
    add_name("_cream_");
    set_adj(({"white", "thick"}));
    add_name("dish");
    add_name("dish of cream");
    set_short("dish of cream");
    set_long("A dish of thick white cream.\n");
    set_adj(({"thick", "frothy", "white", "goat"}));
    set_soft_amount(35);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
