inherit "/std/object";
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"



create_object()
{
     set_name("cloth");
     add_name("_shire_cloth_");
     add_adj(({"strong","clean"}));
     set_pname("cloths");
     set_short("strong clean cloth");
     set_pshort("strong clean cloths");
     set_long("This cloth looks strong and sturdy.\n");


     add_prop(OBJ_I_WEIGHT, 178);
     add_prop(OBJ_I_VOLUME, 1000);
     add_prop(OBJ_I_VALUE, 11);

}
