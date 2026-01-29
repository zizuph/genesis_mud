
/* Mechwarrior, 11 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("North Training Area");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
  add_exit(THIS_DIR+"r22.c", "north");
  add_exit(THIS_DIR+"t33.c", "east");
  add_exit(THIS_DIR+"t43.c", "southeast"); 
  add_exit(THIS_DIR+"t42.c", "south");
  add_exit(THIS_DIR+"t41.c", "southwest");
  add_exit(THIS_DIR+"t31.c", "west");

}
