
/* Mechwarrior, 11 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("Cavalry Battle Station");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,1);  
 
  add_exit(THIS_DIR+"r54.c", "north");
  add_exit(THIS_DIR+"h65.c", "east");
  add_exit(THIS_DIR+"r63.c", "west");



  
}
