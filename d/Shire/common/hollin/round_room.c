#include "rom.h"

object troll, key, door;

create_rom()
{
  set_short("A big round room");
  set_long(
	   "This is a big round room with steep walls "+
	   "The room is lighted by a crack high up in the southern ceiling. "+
	   "The crack is so high up that you cannot reach it. "+
	   "A narrow passage leads to the west.\n");
  ADD_EXA("hole,holes", "They are totally uninteresting.");
  ADD_EXA("crack,light", "A dim light shines through.");
  WEST("crack");
  
  door = clone_object(HOLLIN_DIR + "trolldoor");
  door -> move(this_object());

  reset();
}

reset_rom()
{
  if(!troll || !present(troll)) 
    {
      troll = clone_object(NPC_DIR + "cave_troll");
      troll -> move_living("M",this_object());
      
      key = clone_object(HOLLIN_DIR + "steel_key");
      key -> move(troll);
    }
  troll->command("close door");
  troll->command("lock door with key");
}
