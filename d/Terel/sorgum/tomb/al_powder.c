inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
     set_name("powder");
     add_name("aluminum");
     set_short("grey powder");
     set_long("A metallic grey powder that seems to be aluminum.\n");
     add_adj(({"grey", "gray"}));

     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);
     add_prop(OBJ_M_NO_DROP, 0);
     add_prop("is_reactive", 1);
}
     
