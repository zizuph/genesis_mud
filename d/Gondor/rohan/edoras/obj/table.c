 
inherit "/std/object";
 
#include "/sys/stdproperties.h"
#include "/d/Gondor/defs.h"
 
void
create_object()
{
   set_name("table");
   set_short("round table");
   set_long(BSN("A round table that looks well polished " +
   "through the years."));
   add_prop(CONT_I_WEIGHT,10000);
   add_prop(CONT_I_VOLUME, 5000);
}
