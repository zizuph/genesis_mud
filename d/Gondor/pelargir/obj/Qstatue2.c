inherit "/std/object";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

void
create_object()
{
   set_name("statue");
   set_short("plain statue");
   add_adj("plain");
   add_name(PEL_SQ_STATUE_2);
   set_long(BSN("After careful cleaning and maintenance this statue "
     + "has become recognizable. It seems to be a statue of a young "
     + "man killing an orc. Unfortunately the corrosion has removed "
     + "some of the detail that the mason cannot fix. It looks kind "
     + "of drab."));
   add_prop(OBJ_I_VOLUME,30);
   add_prop(OBJ_I_WEIGHT,40);
}

