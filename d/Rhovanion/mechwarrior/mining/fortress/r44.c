
/* Mechwarrior, 11 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("Cavalry Charge Route");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,0);  
 
  add_exit(THIS_DIR+"r34.c", "north");
  add_exit(THIS_DIR+"r45.c", "east");
  add_exit(THIS_DIR+"r54.c", "south");


  
}
