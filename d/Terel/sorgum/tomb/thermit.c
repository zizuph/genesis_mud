inherit "/std/object";
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

create_object()
{
     set_name("thermit");
     set_short("thermit");
     set_long("A powder that burns VERY hot when it is ignited.");

     add_prop(OBJ_I_WEIGHT, 10);
     add_prop(OBJ_I_VOLUME, 2);
     add_prop(OBJ_M_NO_DROP, 0);
     add_prop("is_reactive", 1);
}
     
