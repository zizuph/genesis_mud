
/* Mechwarrior, 10 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("Entrance south of gate.");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
  add_exit(THIS_DIR+"r4.c", "north");
  add_exit(THIS_DIR+"r5.c", "northeast");
  add_exit(THIS_DIR+"r15.c","east");
  add_exit(THIS_DIR+"r24.c", "south");
 

}
