inherit "/std/object";

#include <stdproperties.h>

create_object()
{
    set_name("sawdust");
    add_name("_sawd");
    add_name("dust");
    set_short("pile of sawdust");
    set_pshort("piles of sawdust");
    set_long("This is a pile of sawdust.\n");
    add_prop(OBJ_I_VALUE, 80);
    add_prop(OBJ_I_WEIGHT, 60);
}