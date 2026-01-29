inherit "/std/room";

#include "defs.h"
#include "wagon_support.h"

void create_room()
{
 set_short("Gont side of the tunnel.");
 set_long("You are on the Gont side of the underground tunnel , "+
   "connecting Gont and Tricksters guild. Some torches of the "+
   "walls give you barely enough light to see rope hanging on the "+
   "northern wall. To the east you see tunnel leading into darkness."+
   "Ladder leads up and back to the surface.\n");

 add_item(({"torch","torches"}),"Flickering light cast by torches "+
   "is just enough to see your surroundings.\n");
 add_item(({"walls","wall"}),"Walls are prety smooth , long rope is "+
   "hanging from northern wall , while ladder attached to southern "+
   "wall leads back to the surface.\n");
 add_item("rope","Strong , sturdy rope , you really should pull it "+
   "if you want to get to the other side.\n");
 add_item("ladder","Wooden ladder , made of cracked wood , it seems "+
   "very unstable and fragile , so you'd better watch your steps.\n");

 add_exit("/d/Earthsea/gont/gont_city/rooms/house","up");

 init_wagon_support();
}

