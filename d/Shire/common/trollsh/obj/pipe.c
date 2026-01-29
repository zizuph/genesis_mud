inherit "/std/object";
#include "/d/Shire/common/defs.h"

#include "/sys/stdproperties.h"

create_object()
{
    set_name("pipe");
   add_name("_old_pipe");
    set_pname(({"", "pipes" }));
    set_pshort("broken old pipes");
   set_adj(({"broken","old"}));
    set_long(
    "This old pipe probably belonged to a hobbit. It is quite "+
   "broken and considering where you found it, you don't think its owner survived.\n");

    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 80);
    add_prop(OBJ_I_VALUE, 2);
}
