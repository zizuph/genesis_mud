/* room coded by Elizabeth Cook/Mouse, November 1996 */

inherit "std/room";
#include <stdproperties.h>
#include "../../mouse.h"

void create_room()  {
     set_short("Fork in the road");
     set_long("   You have reached a fork in the road leading out of "+
          "Festiwycke. The southwest branch enters a clearing. Billows "+
          "of smoke rise above the treetops in that direction. To the "+
          "southeast, the road disappears around a bend leading deeper "+
          "into the Briarwood Forest. A towering elm tree stands where "+
          "the two roads diverge.\n");
     add_item("fork","The road splits here like a 'Y' in front of an "+
          "ancient elm. One path branches to the southwest, while the "+
          "other leads southeast.\n");
     add_item("road","The dusty dirt road is rutted and worn from the "+
          "weight of countless wagon wheels rolling over it. It is bounded "+
          "on both sides by trees.\n");
     add_item("clearing","You can't see very much of the clearing, other "+
          "than hazy outlines of buildings through the trees.\n");
     add_item("billows","The large cloud of smoke hanging in the air above "+
          "the clearing suggests that something more than the usual domestic "+
          "activities are taking place there.\n");
     add_item("smoke","Something in the clearing is generating a great "+
          "deal of smoke, which hangs in the air above the treetops.\n");
     add_item("treetops","There is a cloud of smoke hanging over the "+ 
          "trees surrounding the clearing to the southwest.\n");
     add_item("trees","The trees are deciduous, mostly maples and elms, "+
          "reaching heights of at least 20 meters. You can see a grayish-"+
          "white haze floating above the trees to the southwest.\n");
     add_item("forest","The southeast branch of the road leads into the "+
          "Briarwood Forest, which blankets an expanse to the west and "+
          "south. The village of Festiwycke lies on the western edge of "+
          "the great forest.\n");
     add_item("elm","An enormous elm that was already ancient for its "+
          "kind when the road was first cut through the forest. It is "+
          "a tall, stately-looking tree, at least five meters taller than "+
          "its neighbors. Its bark is an almost luminous shade of gray "+
          "and its foliage is rough and hairy. The residents of the area "+
          "have a deep reverence for this tree, and consider it the first "+
          "citizen of Festiwycke. No one would ever dream of cutting it "+
          "down.\n");

     add_exit(ROOT+"village/rooms/V2","southwest");
     add_exit(ROOT+"village/rooms/V6","north");
     add_exit(ROOT+"forest/rooms/road1","southeast");
}  


