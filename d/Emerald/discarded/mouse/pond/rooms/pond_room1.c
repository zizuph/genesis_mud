/* room coded by Elizabeth Cook/Mouse, October 1996 */

inherit "std/room";
#include <stdproperties.h>
#include "../../mouse.h"

   void create_room()  {
     set_short("The edge of the ravine");
     set_long("   From the edge of the ravine, you see the water of the "+
          "stream passing by below you. A willow tree is growing from "+
          "the base of the ravine and its branches reach almost near "+
          "enough to touch. Both sides of the ravine are thickly wooded "+
          "with stands of mixed deciduous trees. A narrow animal path "+
          "is barely visible along the rim, leading south and downhill "+
          "to the bank of the pond.\n");
     add_item("edge","As you peer over the edge, you note the near "+
          "vertical drop to the water of the stream below. Tufts of coarse "+
          "grass hug the edge like a collar. Many rocky outcroppings "+
          "interrupt the greenery that has taken root in the sparse "+
          "topsoil.\n");
     add_item("ravine","This ravine is not large enough to be considered "+
          "a canyon, but deep and wide enough to be approached with great "+
          "caution. Some plant life has made a home in its walls, but for "+
          "the most part, the walls are composed of loose, barren layers "+
          "of slate or some similar type of sedimentary rock.\n");
     add_item("water","The water of the stream is very clear, you can "+
          "see the rocky bottom of the streambed.\n");
     add_item("stream","The stream at the bottom of the ravine seems to "+
          "flowing in a northwest to southeast direction. There doesn't "+
          "appear to be any way to reach it from this location.\n");
     add_item("trees","The trees growing on both sides of the ravine are "+
          "predominantly oak, though you can identify other types, such "+
          "as beech and maple, as well. There is a substantial amount of "+
          "undergrowth.\n");
     add_item("undergrowth","Saplings, brambles, and other low-growing "+
          "plants consume much of the space left unoccupied by the trees.\n");
     add_item("track","You spot a narrow trail broken through the "+
          "underbrush, most likely by deer making their way to the pond. "+
          "You think it is wide enough to be passable.\n");
     add_item("pond","You can barely see the reflective surface of the "+
          "body of water which lies to the south.\n");
     add_item("willow tree","A willow tree is growing from the bottom "+
          "of the ravine, so that the top of the tree is even with your "+
          "line of vision. It is very close to you, but not close "+
          "enough to reach it safely.\n");
     add_exit(ROOT+"pond/rooms/pond_room2","south");
/* a hidden exit to the north thru the trees will be added later-- */
/* this will be a hilly wooded area where the faerie hill will be located. */
    
}
