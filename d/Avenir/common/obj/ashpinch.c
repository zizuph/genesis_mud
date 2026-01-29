// /d/Avenir/common/obj/ashpinch.c
// This is an object currently cloned by /bazaar/intr/apothstore.c
// It may be used as na ingredient for spell-casting, etc.
// Lilith, Feb 1997

inherit "/std/object";

#include "/d/Avenir/common/common.h"
#include "/sys/stdproperties.h"

void
create_object()
{
    set_name("pinch of ash");
    add_name(({"pinch", "_magical_ingredient", "ash"}));
    set_pname(({"pinches of ash"}));
    
    set_short("pinch of ash");
    set_pshort("pinches of ash");
    set_long("This is a pinch of red-brown ash.\n");

    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VALUE, 20);
}


