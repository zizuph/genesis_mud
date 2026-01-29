inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Within the endless sand dunes");
   set_long("Rising skyward in great sloping mounds all around you are "+
      "the huge glittering ridges of the sand dunes. "+
      "An abundance of loose sand beneath makes your travel extremely difficult, for "+
      "it seems as if you sink lower and lower with each step, and even "+
      "the smallest of sand dunes is a great obstacle to travel. "+
      "To the northwest and northeast lie ways through the dunes, while "+
      "the closest ridges are just to the west, north and east. In "+
      "the south, in contrast to the ridges surrounding you, is a barren "+
      "flatland. "+
      "The continual, burning light of the Kaladian sun strikes the dunes "+
      "all around, the intensity of the reflection is nearly blinding.\n");
   add_item(({"great sloping mounds","great mounds","sloping mounds","mounds","mound","huge glittering ridges","huge ridges","glittering ridges","ridges","sand dunes","sand dune","dunes","dune"}),
      "Formed from the continual action of the harsh desert winds, the great "+
      "collections of sands are ever-shifting in the landscape, threatening "+
      "anything of permanence with ignoble burial.\n");
   add_item(({"loose sand","sand"}),"The tiny, fine granules slip through "+
      "your grasp.\n");
   add_item(({"kaladian sun","sun"}),"The harshly brilliant orb hangs "+
      "in the sky, scorching the land beneath it with its rays of light.\n");
   add_item(({"ways","way"}),"Depressions among the dunes allowing "+
      "travellers passage.\n");
   add_item(({"barren flatland","flatland"}),"A large, apparently "+
      "unending expanse of land, whose monotonously flat landscape is broken "+
      "by small rocks and the occasional cactus.\n");
   add_exit(CPASS(desert/sand/d24),"northwest",0,3);
   add_exit(CPASS(desert/sand/d25),"northeast",0,3);
   add_exit(CPASS(desert/flat/f3),"south","@@block",3);
}
block()
{
   write("You start to head southward, but after several minutes in the "+
      "unending flat landscape you decide to return to the sand dunes, for you "+
      "realize that only death awaits to the south.\n");
   return 1;
}
