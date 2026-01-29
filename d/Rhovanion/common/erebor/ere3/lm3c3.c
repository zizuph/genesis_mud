inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include "door.h"
#define CAVE_DIR ERE_DIR + "ere3/"

object east_door, key, guard;
 
void reset_room();

void
create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("central");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Here is an archway leading east. The gate below the arch is "
        + "beautifully made. This seems to be one of the last constructed "
        + "parts of the cave as well, and almost no signs of age at all.\n");

  east_door = clone_object(CAVE_DIR + "door_lm3c3");
  east_door->move(TO);
 
  /* This is what is needed for the east door */
  key = clone_object(CAVE_DIR + "gold_key");
  key -> set_key(GOLD); /* Setting id number of the key. */
  east_door -> set_key(GOLD); /* Tells the door which key fits. */
  guard = clone_object(CAVE_DIR + "thain");
  guard->move(TO);
 
  add_exit(CAVE_DIR + "lm3c2","west",0,1);
 
  reset_room();
 
}
 
void
sunrise()
{
    if (objectp(guard))
        guard->open_tomb();
}
 
void
reset_room()
{
  if(guard)
    {
    guard->command("say I have to retire one day I suppose.");
      return;
    }
  guard = clone_object(CAVE_DIR + "thain");
  guard->move(TO);
}
