#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("flotsam");
    add_name("piece of slimy flotsam");
    add_name("piece");
    add_adj("slimy");
    set_pname("pieces of slimy flotsam");
    add_pname("pieces of flotsam");
    set_short("piece of slimy flotsam");
    set_pshort("pieces of slimy flotsam");
    set_long("This looks like some sort of unidentifiable " +
        "flotsam, possibly junk from some shipwreck. It does not " +
        "look valuable.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 0);
}
