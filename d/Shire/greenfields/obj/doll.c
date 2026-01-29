inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"


create_object()
{
     set_name("doll");
     add_name("_niece_doll_");
     add_adj(({"small","wooden"}));
     set_short("small wooden doll");
     set_long("A "+short()+ " which resembles a cute little "+
        "hobbit girl.\n");

     add_prop(OBJ_I_WEIGHT, 150);
     add_prop(OBJ_I_VOLUME, 25);
     add_prop(OBJ_I_VALUE, 5);
}
