inherit "/std/object";
#include <stdproperties.h>
 
void
create_object()
{
   set_name("string");
   add_adj(({"woven","cotton"}));
   set_short("woven cotton string");
   set_long("This woven cotton string is fairly strong and light.\n");
 
   add_prop(OBJ_I_WEIGHT, 175);
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_VALUE,9);
 
}
 
