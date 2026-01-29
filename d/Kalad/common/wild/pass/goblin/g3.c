inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("The Caravan Route");
   set_long("A series of gently rolling foothills surrounds you from "+
      "all sides. Besides the tall grasses that blanket the hillsides, only "+
      "a few trees stand in this region. Further to the west, and towering "+
      "high into the sky are the great Hespyre mountains, while eastward the land "+
      "grows drier and more inhospitable, eventually becoming the great Kalad waste, "+
      "a desert of vast proportions. The Caravan Route continues to the west "+
      "and east.\n");
   add_item(({"gently rolling foothills","rolling foothills","foothills","foothill","hillsides","hillside"}),
      "The rolling landscape is dominated by tall grasses, which blanket "+
      "every available surface of the foothills. Occasional stands of "+
      "small trees dot the landscape as well.\n");
   add_item(({"small trees","trees","tree"}),"Small and scraggly in "+
      "appearance, these trees are buy tiny replicas of the great stands of "+
      "redwoods that lies further to the west, at the base of the mountains.\n");
   add_item(({"tall grasses","grasses","grass"}),"Tall, hardy plants "+
      "that are perfectly suited to this land.\n");
   add_item(({"great hespyre mountains","great mountains","hespyre mountains","mountains","mountain"}),
      "From this distance, the mountains appear as nothing more than a "+
      "dark grey wall in the horizon.\n");
   add_item(({"caravan route","route"}),"A cobblestoned roadway that "+
      "bears the effects of heavy usage and harsh weather in its cracked "+
      "surface.\n");
   add_exit(CPASS(goblin/g2),"west",0,2,1);
   add_exit(CPASS(goblin/g4),"east",0,2,1);
}
