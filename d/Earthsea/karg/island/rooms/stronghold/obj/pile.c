inherit "/std/object";

#include <stdproperties.h>

#include "defs.h"

int cat_id;

void create_object()
{
 set_name("pile of wood");
 add_name("pile");
 add_name("wood");
 set_adj("big");
 set_long("This is large pile of wood , that barely resembles "+
   "large catapult.\n");

 add_prop(OBJ_I_WEIGHT,500000);
 add_prop(OBJ_I_VOLUME,500000);
}

