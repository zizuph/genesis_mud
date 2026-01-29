inherit "std/object";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

void
create_object()
{
   set_name("statue");
   set_short("beautiful statue");
   set_adj(({"beautiful", }));
   add_name(PEL_SQ_STATUE_3);
   add_name(({"artwork", "figurine", }));
   set_long(BSN("This is an exquisite example of artwork. The statue "
     + "depicts the last scene of a fight between a young man "
     + "and an orc. The paint "
     + "highlights the sweat on the youth's brow, and the blood "
     + "where the youth's sword penetrates the simple chain mail of "
     + "the orc gleams in the light. What a glorious battle it must "
     + "have been."));
   add_prop(OBJ_I_WEIGHT,40);
   add_prop(OBJ_I_VOLUME,30);

}
