inherit "/std/object";
#include <stdproperties.h>


void
create_object()
{
   set_name("mud");
   add_name(({"pile","heap","brandywine_mud"}));
   add_adj(({"large","slippery"}));
   set_short("large slippery pile of mud");
   set_long("This is mud, a very large hunk of it, made up "+
   "wholly of reddish brown clay.\n");


   add_prop(OBJ_I_WEIGHT, 400);
   add_prop(OBJ_I_VOLUME, 300);
   add_prop(OBJ_I_VALUE, 0);

}

