#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
 
void
create_object()
{
    set_name("cat");
    add_name("schrodingers cat");
    set_pname("small dead cats");
    set_adj("dead");
    set_adj("small");
    set_long("This small brown cat is dead. The horror!\n");
    add_prop(OBJ_I_VALUE, 115);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 40);

}
