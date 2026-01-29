inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
   set_name("packet");
   add_name(({"mustard","mustard seeds","_shire_mustard_"}));
   add_name(({"seeds", "mustard","mustard seeds","_shire_mustard_"}));
   set_short("packet of mustard seeds");
   set_long("This is a brown paper packet of mustard seeds.\n");

   add_prop(OBJ_I_WEIGHT, 30);
   add_prop(OBJ_I_VOLUME, 42);
   add_prop(OBJ_I_VALUE, 0);
}
   
