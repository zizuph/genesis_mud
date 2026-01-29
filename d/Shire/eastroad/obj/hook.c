inherit "/std/object";
#include <stdproperties.h>
 
void
create_object()
{
   set_name("hook");
   add_adj(({"shiny","fishing"}));
   set_short("shiny fishing hook");
   set_long("This shiny fishing hook looks quite sharp and "+
   "very suitable for fishing!\n");
 
   add_prop(OBJ_I_WEIGHT, 75);
   add_prop(OBJ_I_VOLUME, 40);
   add_prop(OBJ_I_VALUE,17);
 
}
 
