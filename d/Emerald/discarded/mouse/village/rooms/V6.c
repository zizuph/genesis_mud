/* room coded by Elizabeth Cook/Mouse, November 1996 */

inherit "std/room";
#include <stdproperties.h>
#include "../../mouse.h"

void create_room()  {
     set_short("Festiwycke Road");
     set_long("   This well-travelled, dusty path is the main road passing "+
          "through the village of Festiwycke. The increased traffic "+
          "indicates that the center of town is not far away. A few "+
          "small huts can be spotted through the trees along the roadside "+
          "to the northwest. A trail leads to a clearing in the east, "+
          "where you notice some activity. A smoky cloud hangs over the "+
          "treetops a bit to the south.\n");
     add_item(({"road","path"}),"The dirt road is rutted and worn from "+
          "the weight of countless wagon wheels rolling over it. The "+
          "ruts are deeper on the trail running toward the east and on "+ 
          "the road to the north.\n");
     add_item("trail","A rutted track leads to the clearing east of "+
          "here.\n");
     add_item("clearing","You notice a gathering of people and wagons in "+
          "clearing to the east. You can also barely see some structures "+
          "that are unidentifiable from this distance.\n");    
     add_item(({"smoke","cloud"}),"Something toward the south is "+ 
          "generating a great deal of smoke, which hangs in the air "+ 
          "above the treetops.\n");
     add_item("treetops","There is a cloud of smoke hanging over the "+ 
          "trees in a southwesterly direction.\n");
     add_item("trees","The trees are deciduous, mostly maples and elms, "+
          "reaching heights of at least 20 meters. You can see a grayish-"+
          "white haze floating above the trees to the southwest.\n");
     add_item("huts","You can see the vague shapes of rough wooden "+
          "dwellings through the trees to the north and west.\n");
  

     add_exit(ROOT+"aaron/ship/rooms/dock2","east");
     add_exit(ROOT+"village/rooms/V7","northwest");
     add_exit(ROOT+"village/rooms/V5","south");
}  


