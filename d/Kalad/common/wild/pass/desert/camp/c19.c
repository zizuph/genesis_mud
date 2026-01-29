inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside the central tent");
   set_long("Despite being the largest tent in the entire camp and "+
      "being centrally located, the interior of this large tent is quite bare. "+
      "The sides of this passage are completely bare, while the ground is covered "+
      "by a long red carpet.\n"+
      "East is the exit out of the tent, while west leads further inside.\n");
   add_item(({"large tent","tent"}),"It is what you are currently inside of.\n");
   add_item(({"passage"}),"This passageway has been created by the "+
      "placing of several canvas sheets, which serve as walls.\n");
   add_item(({"canvas sheets","canvas sheet","sheets","sheet","sides","side","walls","wall"}),
      "The tent has been fashioned from the strong hairs of a camel, "+
      "making a sturdy barrier against the harsh winds of the waste.\n");
   add_item(({"ground"}),"Where it isn't covered by the carpet, it is "+
      "nothing more than sand.\n");
   add_item(({"sand"}),"Its grainy and somewhat shiny, just like normal "+
      "sand.\n");
   add_item(({"red carpet","carpet"}),"A camel-hair rug that has been "+
      "dyed with a wonderfully exotic red color.\n");
   add_exit(CPASS(desert/camp/c20),"west",0,-1);
   add_exit(CPASS(desert/camp/c18),"east",0,-1);
}
