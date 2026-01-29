inherit "/std/object";
#include "/d/Rhovanion/defs.h"
void
create_object()
{
   set_name("corpse");
   set_adj("rotted");
   set_adj("half-eaten");
   set_long("This corpse appears as if it's been here for some time now as numerous maggots have tunneled their way all throughout it.  Once belonging to some poor soul, the corpse now is property of the rats here knawing it to pieces.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT, 30000);
   add_prop(OBJ_I_VOLUME, 29000);
}
