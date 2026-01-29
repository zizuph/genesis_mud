
/* Mechwarrior, 10 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("inside fortress");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
  add_exit(THIS_DIR+"r29.c", "east");
  add_exit(THIS_DIR+"j38.c", "south");
  add_exit(THIS_DIR+"r27.c", "west");
 

}
