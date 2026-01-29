inherit "/std/object";

#include <stdproperties.h>
#include "/d/Emerald/leah/sickelf.h"

void
create_object()
{
   set_name("feather");
   add_name(FEATHER);
   add_adj(({"large", "speckled"}));
   set_short("This feather is rather large for a normal bird, yet "+
	"doesn't appear to be from anything as fantastical as a "+
	"great Roc. You guess that it's from a large natural "+
	"predatory bird.\n");
   add_prop(OBJ_I_VALUE, 5);
   add_prop(OBJ_I_NO_BUY, 1);
   add_prop(OBJ_I_NO_SELL, 1);
}
