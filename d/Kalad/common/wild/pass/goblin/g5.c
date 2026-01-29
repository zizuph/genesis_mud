inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Dirt pathway");
   set_long("This dirt pathway you are travelling on winds its way "+
      "among the rolling foothills surrounding you. Tall grasses and stunted "+
      "trees cover the hills, giving the surrounding landscape an eerie look. "+
      "The path continues southwest to the Caravan Route and north, deeper into "+
      "the foothills.\n");
   add_item(({"dirt pathway","pathway","path"}),"A narrow twisting path that "+
      "winds its way among the surrounding foothills.\n");
   add_item(({"rolling foothills","foothills","foothill","hills","hill"}),
      "The gentle, rolling landscape is dominated by tall, waist-high "+
      "grasses, and is dotted by the occasional odd tree.\n");
   add_item(({"landscape"}),"It gives you an odd feeling...\n");
   add_item(({"tall grasses","grasses","grass"}),"The plant is "+
      "well-suited to the somewhat dry, wind-blown foothills of the "+
      "Hespyre range.\n");
   add_item(({"stunted trees","trees","tree"}),"The only trees in this "+
      "area are small and stunted, showing the clear effects of the "+
      "somewhat dry, and windy environment.\n");
   add_item(({"caravan route","route"}),"It lies farther down the path, "+
      "in the southwest.\n");
   add_exit(CPASS(goblin/g6),"north",0,2,1);
   add_exit(CPASS(goblin/g2),"southwest","@@msg",2,1);
}
msg()
{
   write("You feel a sense of relief as you leave the foothills.\n");
   return 0;
}
