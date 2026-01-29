inherit "/std/object";
#include "/d/Shire/common/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("glass");
    add_name("_old_glass");
    set_pname("glass");
    set_pshort("broken slivers of glass");
    set_adj(({"broken","sliver","of"}));
    set_long(
    "This broken sliver of glass looks rather sharp and strong. "+
    "Watch out, you might cut yourself.\n");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 2);
}
