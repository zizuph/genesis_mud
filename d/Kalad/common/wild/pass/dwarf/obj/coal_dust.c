inherit "/std/object.c";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#define KALAD_SHADOW_ING "_kalad_shadow_ing"
/* by korat */
void
create_object()
{
   ::create_object();
   set_name("coal-dust");
    add_name("dust");
   set_adj("handful of");
   set_pshort("handfuls of coal-dust");
   set_long("A handful of coal-dust, sparkling like black diamonds "+
      "in your hand.\n");
    add_prop(KALAD_SHADOW_ING,80);
   add_prop(OBJ_I_VALUE,1);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_I_WEIGHT, 250);
   add_prop(OBJ_M_NO_SELL,1);
}
