inherit "std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

void
create_object()
{
   set_name("statue");
   set_short("corroded statue");
   add_name("figurine");
   add_name(PEL_SQ_STATUE_1);
   set_adj(({"corroded", "chipped", }));
   set_long(BSN("This appears to once have been a statue or figurine "
     + "of some kind. Now it is chipped and corroded with muck so bad "
     + "as to be unrecognizable."));
   add_prop(OBJ_I_WEIGHT,40);
   add_prop(OBJ_I_VOLUME,30);
}
