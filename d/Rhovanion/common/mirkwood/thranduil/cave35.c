inherit "/d/Rhovanion/lib/caves.c";
#include "/d/Rhovanion/defs.h"
#include "def.h"
#include "/sys/macros.h"
#include "door.h"
#include <filter_funs.h>

 
object key, door;
 
void reset_room();
 
create_cave()
{
 
reset_room();
 
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(1);
  set_long(" You stand in a corridor leading east and west, "
	   + "To the north you see a door.");

  /* This is what is needed for the north door */
  door = clone_object(THIS_DIR + "C1_door");
  door -> move(TO);

  key = clone_object(THIS_DIR + "silver_key");
  key -> set_key(SILVER); /* Setting id number of the key. */
  door -> set_key(SILVER); /* Tells the door which key fits. */

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave36","east",0,1);
  add_exit(THIS_DIR + "cave34","west",0,1,);
}
 
void
reset_room()
{

    int i;
    if(!(sizeof(FILTER_LIVE(all_inventory(TO) ||
     (sizeof(FILTER_LIVE(all_inventory(find_object(THIS_DIR+"C1")))))))))
    {
      door->do_close_door("");
      door->set_locked(1);
      (THIS_DIR + "C1")->remove_prop("_prisoner_free");
      return;
    }
 
}

