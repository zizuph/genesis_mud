#include "def.h"
inherit THIS_DIR+"inside";
#include "/d/Rhovanion/defs.h"

reset_room()
{
    ::reset_room();
    if(!present("_rhosgobel_quest_weed"))
       clone_object(RHUN_DIR+"forest/weed")->move(TO,1);
}

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

  add_exit(RHUN_DIR+"forest/j5","east",0);
  add_exit(RHUN_DIR+"forest/h5", "west", 0);
  add_exit(RHUN_DIR+"forest/h4", "northwest", 0);

  reset_room();
  add_stuff();
}
