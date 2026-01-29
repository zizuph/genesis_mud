inherit "/std/object.c";
#include "/d/Kalad/defs.h"

void
create_object()
{
   set_name("chair");
   set_adj("ebony");
   add_adj("high-backed");
   set_short("a high-backed ebony chair");
   set_long("This ebony chair, looks comfotable and relaxing, the "+
   "chair is covered in soft black leather pads.\n");
   add_prop(OBJ_I_WEIGHT,20000);
   add_prop(OBJ_I_VOLUME,15000);
   add_prop(OBJ_I_VALUE,300000);
    add_prop(OBJ_M_NO_GET, 1);
}
