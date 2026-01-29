inherit "/std/container";

#include "default.h"

void
create_container()
{
   set_short("bucket");
   set_name("bucket");
   set_long("This bucket is made of wood and metal bands.\n");
   
   add_prop(CONT_I_WEIGHT, 1000);
   add_prop(CONT_I_VOLUME, 1000);
   add_prop(CONT_I_HEIGHT, 20);
   add_prop(CONT_I_MAX_WEIGHT, 10000);
   add_prop(CONT_I_MAX_VOLUME, 10000);
   add_prop(OBJ_I_VALUE, 34);
}

