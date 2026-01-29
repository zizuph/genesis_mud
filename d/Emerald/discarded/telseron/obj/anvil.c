/* township/obj/anvil.c is cloned by township/forge.c */
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
 
void
create_object()
{
    set_name("anvil");
    set_short("heavy anvil");
    set_adj("heavy");
    set_long("A large iron anvil bolted to the floor in the centre of the room.\n");
 
    add_prop(OBJ_I_WEIGHT,80000);
    add_prop(OBJ_I_VOLUME,30000);
    add_prop(OBJ_M_NO_GET,"You grunt and groan, but just can't manage to lift it.\n");
}
