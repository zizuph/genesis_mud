inherit "/std/object";
#include <stdproperties.h>

void
create_object()
{
   set_short("bottle of honey");
   set_adj("bottle");
   set_name(({"honey","bottle","bottle of honey","_shire_honey_"}));
   set_long("This plain bottle of honey looks mostly full.\n");

   add_prop(OBJ_I_WEIGHT, 129);
   add_prop(OBJ_I_VOLUME, 240);
   add_prop(OBJ_I_VALUE, 23);
}
