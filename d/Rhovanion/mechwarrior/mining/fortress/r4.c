
/* Mechwarrior, 10 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("Main gate");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
  add_exit("/d/Rhovanion/mechwarrior/workroom.c", "north");

  add_exit(THIS_DIR+"r5.c", "east");
  add_exit(THIS_DIR+"r15.c", "southeast");
  add_exit(THIS_DIR+"r14.c", "south");
 

}
