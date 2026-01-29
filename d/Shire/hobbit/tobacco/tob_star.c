inherit "/d/Shire/common/obj/tob_parent";

#include "/d/Shire/common/defs.h"


void
create_object()
{
   ::create_object();
   set_short("southern star tobacco");
   add_name("pipe-weed");
   set_adj(({"southern","star"}));
   set_long("This pipe-weed is called Southern Star, for it's appearance, "+
      "the tobacco comes from a star-shaped leaf from south farthing.  It's "+
      "shape, wonderful smoking flavour, as well as it's rarity makes "+
      "the smoking of it a rare occasion, usually at a party or some "+
      "other joyous occasion.\n");
   add_prop(OBJ_I_VALUE,60);
}

string
query_flavour()
{
   return "southern star";
}
