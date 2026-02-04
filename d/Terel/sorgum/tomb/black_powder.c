inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
     set_name("powder");
     add_name("gunpowder");
     set_short("black powder");
     set_long("A strange black powder that smells of sulphur slightly.\n");

     add_adj("black");
     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);
     add_prop(OBJ_M_NO_DROP, 0);
     add_prop("is_reactive", 1);
     add_prop("is_explosive", 1);
}
     
