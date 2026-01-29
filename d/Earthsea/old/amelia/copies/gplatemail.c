inherit "/std/armour";
#include <macros.h>
#include "/d/Roke/common/defs.h"

create_armour()
{
	set_name("platemail");
   set_short("green steel platemail");
   set_long("It is made from green steel. Accross the "+
            "breastplate is a large symbol of two crossed "+
           "axes over a map of the world.\n");
   set_adj("green");
   add_adj("steel");

   set_default_armour(45);
   add_prop(OBJ_I_VALUE, 900);
}
