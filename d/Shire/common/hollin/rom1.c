/*

  12 Aug 2006 Palmer -
    Removed tele() until I figure out if its been replaced
*/


#include "lakeroom.h"


int   alarm_id;

void
create_lakeroom() {
   set_short("West of a dark lake");
   set_long(
      "You are overlooking a quiet and dark lake to the east. "+
      "On the other side of the gloomy water, the insurmountable "+
      "Misty Mountains rise. The steep cliffs look smooth and barren. "+
      "The path winds towards the northern end of the lake. It looks "+
      "like it leads all the way round. A small waterfall trickles "+
      "down the cliffs here and gathers into a brook that runs towards "+
      "the western lowlands. To the south the path leads to a dam. ");
   add_item(({"waterfall","brook"}),
      "It seems like you can follow the brook to the west.\n");
   add_item("lowlands",
      "Far to the west, is the lowlands, from which you once came.\n");
   add_item("dam",
      "The dam is to the south.\n");
   add_item(({"path","paths"}),
      "There are is a path leading north, and a path east towards some stairs.\n");
   
   
   add_exit(STAND_DIR+"rom2","north",0);
   add_exit(STAND_DIR+"steps","west",0);
   add_exit(STAND_DIR+"dam","south",0);
   //alarm_id =set_alarm(itof(random(200)),0.0,"tele");
}

void
tele()
{
   remove_alarm(alarm_id);
   call_other("/d/Shire/moria/mines/orc_lair", "teleledningsanka");
}
