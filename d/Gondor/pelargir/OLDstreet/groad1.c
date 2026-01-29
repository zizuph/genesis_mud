inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/citdefs.h"

void
create_room()
{
    set_short("North/South Pelargir street");
    set_long(BSN("This is a cobblestone street leading north "+
       "and south through the city of Pelargir. To the east are "+
       "gates leading to the courtyard of the Admiral's tower, which "+
       "presides over the city and its fleet. To the south the road "+
       "heads towards the busier parts of the city, and to the "+
       "north you can see a few side roads and a bridge across the "+
       "Sirith river."));
   COBBLE;
   add_item("gates",BSN("Each bar of these tall iron gates is made of steel "+
      "nearly six inches thick. Though they are locked now, you "+
      "wonder how many people it takes to push them open when "+
      "they are unlocked."));
   add_item("courtyard",BSN("The courtyard below "+
      "the Admiral's tower is large enough to stage a "+
      "small army in. It is difficult to see much of interest "+
      "there now though, as the gates partially block your view."));
    add_item(({"admiral's tower","tower"}),BSN("This is "+
      "by far the most exquisite piece of masonry in "+
      "all of Pelargir. Its marble smooth walls climb to dizzying "+
      "heights above the Pelargir rooftops. The light of moon and "+
      "sun cause the tower to seemingly glow in pristine white. "+
      "Truly breathtaking."));
    add_exit(PELAR_DIR + "street/groad2","north",0);
    add_exit(PELAR_DIR + "street/groad","south",0);
}
