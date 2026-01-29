inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"


create_object()
{
     set_name("spoon");
    add_name("_shire_mixing_spoon_");
     add_adj(({"large","wooden"}));
     set_short("large wooden spoon");
     set_pshort("large wooden spoons");
     set_long("A "+short()+ " which looks pretty clean.\n");

     add_prop(OBJ_I_WEIGHT, 100);
     add_prop(OBJ_I_VOLUME, 250);
     add_prop(OBJ_I_VALUE, 15);

}
