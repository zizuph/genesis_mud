inherit "/std/armour";

#include <wa_types.h>
#include "/d/Emerald/defs.h"

string
create_armour()
{
   set_name("scale");
   add_name("armour");
   set_short("brigandine scale armour");
   set_long("This brigandine scale armour is of a fairly good quality, and " +
            "is made of a leather shirt with metal plates sown onto it.\n");
   set_adj("brigandine");
   
   set_ac(23);
   add_prop(OBJ_I_VALUE, 395);
   set_at(A_TORSO);
   set_am(({-1,3,-2 }));
}
