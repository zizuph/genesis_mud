/* a room coded by Elizabeth Cook/Mouse, January 1997 */

inherit "std/room";
#include <stdproperties.h>
inherit "/d/Gondor/open/HERBS/herbsearch";  
#include "../../mouse.h"   

int searched;

void create_room()  {
     set_short("In front of the Briarwood Inn");
     set_long("   Festiwycke Road seems destined to be swallowed up by the "+
          "wilderness again as it rounds a bend out of sight to the north. "+
          "The woods have already grown thicker, with dense undergrowth "+
          "hugging the road on both sides. The wild growth is only broken "+
          "by the wear of traffic to the west, where several horses and two "+
          "wagons stand before a large white building overlooking the "+ 
          "roadway.\n");
     add_item("road","The road north of Festiwycke has once again become "+
          "a well-worn, dusty path, since the village council has not yet "+
          "thought of a way to charge taxes to birds and trees.\n");
     add_item(({"wilderness","woods"}),"A variety of deciduous trees, "+
          "mainly maples and elms, that mark the western edge of the "+
          "Briarwood Forest.\n");
     add_item("bend","Festiwycke road turns to the east and out of sight "+
          "as you look north.\n");
     add_item("undergrowth", "Tangles of wild plants that have taken "+
          "over the roadsides.\n");
     add_item("horses","Several horses stand before a white building, "+
          "chewing idly and looking rather bored.\n");
     add_item("wagons","The wagons are laden with items tightly covered "+
          "with heavy cloth. They look as if their owners have purchased "+
          "supplies to last a very long time.\n");
     add_item("building","It is a rather large building that looks as if "+
          "it has recently received a new coat of white paint. A sign "+
          "hangs over the wide front door. Delicious smells are wafting "+
          "from its direction.\n");
     add_item("sign","There is a picture of a thorned tree under which "+
          "is some writing you might read.\n");
     add_cmd_item(({"sign","writing"}),"read","Under a picture of a "+
          "thorned tree, it says:  BRIARWOOD INN, FEASTS AND LIBATIONS.\n");
  
     set_up_herbs(({ROOT+"herbs/yarrow",
                    ROOT+"herbs/elecampane",
                    ROOT+"herbs/aconite"}),
                    ({"ditch"}));
     places = ({"ditch"});
     add_exit(ROOT+"village/rooms/V17","north");
     add_exit(ROOT+"village/rooms/V13","south");
     add_exit(ROOT+"village/rooms/bwinn","west");
     clone_object(ROOT+"village/mons/drunkard.c")->move(TO);  
}

void reset_room()
{
  if(!present("drunkard"))
      clone_object(ROOT+"village/mons/drunkard.c")->move(TO);
}
