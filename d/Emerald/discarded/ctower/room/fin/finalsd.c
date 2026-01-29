#include "../../ctower.h"

inherit FINSTD;
inherit (CTOWER_ROOM + "guardian_room");
 
void
create_fin()
{
    add_item(({"stair", "stairs", "stairway"}),  "This "+
      "stairway appears to be quite sturdy even though"+
      " there doesn't seem to be any visible support.\n" );
   
    add_exit(CTOWER_ROOM_FIN + "fin17", "north", exit_block);
    add_exit(CTOWER_ROOM_ELEM + "airsu", "down");
  
    level = 3;
  
    add_guardian();
}
