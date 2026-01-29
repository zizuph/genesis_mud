inherit "std/object";
 
#include "/sys/macros.h"
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"
 
 
void
create_object()
{
 
seteuid(getuid());
 
  set_name("pen");
  set_adj("silver");
  set_long("This is a beautifully made silver pen. It must be very "
      + "valuable to its owner.\n");
 
 
    add_prop(OBJ_I_WEIGHT, 100 + random(10));
    add_prop(OBJ_I_VOLUME, 50 + random(10));
}
