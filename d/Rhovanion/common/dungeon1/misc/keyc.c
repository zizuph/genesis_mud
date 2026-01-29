inherit "/std/key";
#include <stdproperties.h>

create_key()
{
   set_name("key");
   set_pname("keys");
   set_short("large iron key");
   set_pshort("large iron keys");
   set_adj(({"large","iron"}));
   set_key(200);
   set_long("This is a large, iron key.  It is " +
      "rather featureles and looks well used.\n");
   add_prop(OBJ_I_WEIGHT, 800);
}
