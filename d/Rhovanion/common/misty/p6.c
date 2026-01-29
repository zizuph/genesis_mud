/* highpass */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>


create_room()
{
    add_prop(ROOM_I_INSIDE, 0);
    set_short("at slope");
    set_long("You are climbing the slope of Misty Mountains. You are " + 
             "really tired and wonder how long you will have to climb " +
             "up till you reach the top. Or are you going down??? It " +
             "seems that you are so tired that you forget which way you " +
             "want to go.\n");


              /* The other room,           direction, VBFC, fatigue */
    add_exit("@@which_room_w", "west",    0,    10);
    add_exit("@@which_room_se", "southeast",    0,    10);

}

string
which_room_w()
{
  int i;

  i = 49 + TP->query_skill(SS_LOC_SENSE);
  if(random(100) < i) return MISTY_DIR+"p5";
  return MISTY_DIR+"p7";
} 
string
which_room_se()
{
  int i;

  i = 49 + TP->query_skill(SS_LOC_SENSE);
  if(random(100) < i) return MISTY_DIR+"p7";
  return MISTY_DIR+"p5";
} 
