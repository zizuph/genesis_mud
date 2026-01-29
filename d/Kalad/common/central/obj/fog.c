inherit "/std/object";
#include <stdproperties.h>
void
create_object()
{
   ::create_object();
   set_name("fog");
   set_adj("black");
   set_long("A thick, black fog that envelopes the area.\n");
    add_prop(OBJ_I_WEIGHT, 250000);
   add_prop(OBJ_I_VOLUME, 50000);
   add_prop(OBJ_M_NO_GET,"Get a fog??\n");
   add_prop(OBJ_I_LIGHT, -10);
}

