inherit "/std/object";
#include "/d/Shire/common/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("kit");
    add_name("_old_kit");
    set_pname("kits");
    set_pshort("old cooking kits");
    set_adj(({"old","cooking"}));
    set_long(
   "This cooking kit is quite rusty and useless. But then, "+
   "it wouldn't take long to get that way down here, so "+
   "it is almost impossible to say how long it has been here. "+
   "You hope the same does not happen to you.\n");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 2);
}
