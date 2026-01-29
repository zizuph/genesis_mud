#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("jetsam");
    add_name("piece of jetsam");
    add_name("piece of junky jetsam");
    add_pname("pieces of junky jetsam");
    add_pname("pieces of jetsam");
    add_adj("junky");
    set_short("piece of junky jetsam");
    set_pshort("pieces of junky jetsam");
    set_long("This looks like some sort of unidentifiable " +
        "jetsam, possibly junk from some shipwreck that has been " +
        "floating in the water for so long it is now impossible to " +
        "even identify. It does not look valuable.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_I_VALUE, 0);
}
