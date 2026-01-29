#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

inherit FOREST_IN;

void
reset_flotsam_room()
{
   return;
}

create_flotsam_room()
{
   set_short("A flooded room within a minotaur maze");
   set_long("@@long_descr");
   
   add_item(({"tiny holes","holes"}),
      "Tiny holes riddle the walls of the maze, their purpose " +
      "now obviously clear... to fill the maze with water " +
      "as the tide rises, quite dangerous for those who " +
      "get lost within it.\n");
   add_item(({"stone walls","walls"}),
      "These are stone walls that are riddled with tiny holes.\n");
   add_item(({"water","sea water"}),
      "Sea water slowly fills the room as the tide rises. You " +
      "would say you are standing in a foot of water, its level " +
      "slowly rising.\n");
   
   add_exit(MAZE + "d1","west",0);
   add_exit(MAZE + "c2","up",0);
   
   set_tell_time(90);
   add_tell("Sea water runs through the tiny holes " +
      "in the walls as the tide rises. You notice the water " +
      "level is slowly getting higher.\n");

   reset_flotsam_room();
}

string
long_descr()
{
   return "You stand in about a foot of sea water on the " +
   "bottom level of the maze. The water shifts through " +
   "tiny holes in the walls as it rises and falls with the " +
   "tide.\n";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
        start_room_tells();
}
