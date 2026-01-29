inherit "/std/object";
#include <stdproperties.h>
 
void
create_object()
{
   set_name("stick");
   add_adj(({"straight","flimsy"}));
   set_short("straight flimsy stick");
   set_long("This straight stick is rather flimsy and "+
   "flexible.\n");
 
   add_prop(OBJ_I_WEIGHT, 175);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_VALUE,9);
 
}
 
