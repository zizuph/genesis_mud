#include "def.h"
inherit THIS_DIR+"inside";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("In the forest");
  set_long("You wander through a dense forest of tall, thick"
    +" trees northeast of the Sea of Rhun.  The treetops are covered"
    +" with thick green leaves of a darker shade,  casting heavy"
    +" shadows on the ground below.  The forest floor is carpeted with"
    +" fallen leaves from past seasons, ankle deep in come places.  The"
    +" occassional sound of some small animal scurrying about breaks the"
    +" still air, but, for the most part, the forest is silent."
     +"\n");

  add_exit(RHUN_DIR+"forest/f6","east",0);
  add_exit(RHUN_DIR+"forest/d7", "southwest", 0);
  add_stuff();
}
