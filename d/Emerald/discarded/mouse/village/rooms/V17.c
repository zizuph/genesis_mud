/* a room coded by Elizabeth Cook/Mouse, February 1997 */

inherit "std/room";
inherit "/d/Gondor/open/HERBS/herbsearch.c";
#include <stdproperties.h>
#include "../../mouse.h"

int searched;

void create_room()  {
     set_short("Standing before a bridge");
     set_long("   As Festiwycke Road rounds the bend, a small stone bridge "+
          "becomes visible to the northeast. Lush greenery abounds on both "+ 
          "sides of the road, the trees towering above you swaying slightly "+
          "in the gentle breezes. The sound of running water fills the air, "+
          "from an as of yet invisible source.\n");
     add_item("road","It is a dusty path leading toward Festiwycke to the "+
          "south and approaching the foot of a small stone bridge to the "+
          "northeast.\n");
     add_item(({"trees","woods"}),"A variety of deciduous trees, "+
          "mainly maples and elms, that mark the western edge of the "+
          "Briarwood Forest.\n");
     add_item("greenery","Verdent undergrowth and tall trees flank the "+
          "road.\n");
     add_item("undergrowth","A wild tangle of weeds appears to choke the "+
          "roadsides, making only a slight break just to one side of the "+
          "bridge.\n");
     add_item("break","As you look more closely at the break in the "+
          "undergrowth, you detect a small path leading beneath the bridge.\n");     
     add_item("bend","Festiwycke Road angles from the south to the northeast "+
          "at this location.\n");
     add_item("water", "You cannot see the water, but you suspect the "+
          "source of the sound if flowing beneath the bridge.\n");
     add_item("bridge","It is a small bridge arching gently to the "+
          "northeast. It is constructed of a light gray stone.\n");
  
     set_up_herbs(({ROOT+"herbs/yarrow",ROOT+"herbs/elecampane",
                    ROOT+"herbs/aconite"}),
                    ({"ditch"}));
     places = ({"ditch"});
     add_exit(ROOT+"village/rooms/V18","northeast");
     add_exit(ROOT+"village/rooms/V15","south");
     add_exit(ROOT+"village/rooms/camp","path",0,1,1);

}

