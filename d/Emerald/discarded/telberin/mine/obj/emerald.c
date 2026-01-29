 
/* mine/obj/emerald.c is cloned by various monsters in mine/ */
 
inherit "/std/object";
 
#include "/d/Emerald/defs.h"
 
create_object()
{
        set_short("emerald");
        set_long("A bright shining lump of raw emerald.\n");
        set_name("emerald");
 
        add_prop(OBJ_I_VOLUME, 26);
        add_prop(OBJ_I_VALUE, 177);
        add_prop(OBJ_I_WEIGHT, 30);
}
 
