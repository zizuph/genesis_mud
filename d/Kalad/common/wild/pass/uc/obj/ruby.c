inherit "/std/object.c";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_object()
{
   ::create_object();
   set_name("ruby");
   set_pname("rubies");
   set_adj("lustrous");
   add_adj("scarlet");
   set_short("lustrous scarlet ruby");
   set_pshort("lustrous scarlet rubies");
   set_long("Its many-faceted surface appears to catch even the faintest "+
      "of lights and reflect it back with a radiant sparkle.\n");
   add_prop(OBJ_I_VALUE,500);
   add_prop(OBJ_I_WEIGHT,500);
   add_prop(OBJ_I_VOLUME,500);
}
