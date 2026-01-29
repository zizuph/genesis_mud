inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include <ss_types.h>
#define CHECK_AWARE 30
#define DAMAGE 200
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_NO_TIME_DESC,1);
   set_short("Dirt pathway");
   set_long("This dirt pathway you are travelling on winds its way "+
      "among the rolling foothills surrounding you. Tall grasses and stunted "+
      "trees cover the hills, giving the surrounding landscape an eerie look. "+
      "The path continues to the north, deeper into the foothills, and "+
      "south where it eventually reaches the Caravan Route.\n");
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
   add_exit(CPASS(goblin/g7),"north","@@check_aware",2,1);
   add_exit(CPASS(goblin/g5),"south",0,2,1);
}
check_aware()
{
   if(TP->query_skill(SS_AWARENESS) < random(CHECK_AWARE))
      {
      write("You start to walk northwards...\n");
      write("You failed to notice the trap and fall...\n");
      write("...down...\n");
      write("......down until you slam into some stakes!!!\n");
      TP->move_living("the area","/d/Kalad/common/wild/pass/goblin/pit");
      TP->heal_hp(-DAMAGE);
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You continue deeper into the foothills.\n");
   return 0;
}
