inherit "/std/container";
#include <stdproperties.h>

create_container()
{

     set_name("bowl");
     add_name("_shire_mixing_bowl_");
     add_adj(({"steel","mixing"}));
     set_short("steel mixing bowl");
     set_pshort("steel mixing bowls");
     set_long("This "+ query_short() + " seems to be used for "+
     "mixing things together, and seems to be able to hold a good many things.\n");

     add_prop(CONT_I_WEIGHT, 1600);
     add_prop(CONT_I_MAX_WEIGHT, 50000);
     add_prop(CONT_I_VOLUME, 3200);
     add_prop(CONT_I_MAX_VOLUME, 20000);
     add_prop(OBJ_I_VALUE, 58);

}
