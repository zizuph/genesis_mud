
/* Mechwarrior, 11 Sep 1995 */

inherit "/d/Rhovanion/lib/room";
 
#include <stdproperties.h>
#define THIS_DIR "/d/Rhovanion/mechwarrior/mining/fortress/"

void
create_room()
{
  set_short("South Training Area");
  set_long("This is a skeleton room; more detailed descriptions will "+
     "be added later.\n");
 
  add_prop(ROOM_I_INSIDE,0);    
 
  add_exit(THIS_DIR+"t32.c", "north");
  add_exit(THIS_DIR+"t33.c", "northeast");
  add_exit(THIS_DIR+"t43.c", "east");
  add_exit(THIS_DIR+"t41.c", "west");
  add_exit(THIS_DIR+"t31.c", "northwest");

}
