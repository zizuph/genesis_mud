#include "defs.h"

inherit TRICKSTER_STD_ROOM;

#include "wagon_support.h"

object wagon;

void create_room()
{
 set_short("Tricksters side of the tunnel.");
 set_long("You are on the Tricksters side of the underground tunnel, "+
   "connecting Gont and Tricksters guild. Some torches of the "+
   "walls give you barely enough light to see rope hanging on the "+
   "northern wall. To the west you see tunnel leading into darkness."+
   "Ladder leads up and back to the guildhome.\n");

 add_item(({"torch","torches"}),"Flickering light cast by torches "+
   "is just enough to see your surroundings.\n");
 add_item(({"walls","wall"}),"Walls are prety smooth , long rope is "+
   "hanging from northern wall , while ladder attached to southern "+
   "wall leads back to the guildhome.\n");
 add_item("rope","Strong , sturdy rope , you really should pull it "+
   "if you want to get to the other side.\n");
 add_item("ladder","Wooden ladder , made of cracked wood , it seems "+
   "very unstable and fragile , so you'd better watch your steps.\n");

 add_exit(TRICKSTERS+"hall_end","up");

 wagon=clone_object(WAGON);
 wagon->move(TO);
 (INSIDE_WAGON)->i_am_the_wagon(wagon);

 init_wagon_support();
}

object give_me_wagon() { return wagon; }

