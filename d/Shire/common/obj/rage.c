inherit "/std/object";
#include <stdproperties.h>
#include "/sys/macros.h"

#define TP this_player

void
create_object()
{
   set_name("rage");
   set_pname("rages");
   set_adj("wild");
   set_long("This is a very rare flower. It is said to "
	+   "be a great source of power.\n");
   set_short("rage");
   set_pshort("rages");

   add_prop(OBJ_I_VALUE, 10000);
   add_prop(OBJ_I_WEIGHT, 235);
   add_prop(OBJ_I_VOLUME, 1000);
}
