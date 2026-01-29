#include "default.h"
#include <tasks.h>
#include <ss_types.h>
#include <macros.h>

inherit CASTLE_ROOM;

int do_climb(string str);

int tied;
int thrown;

void
create_room()
{
   set_short("Metal passage");
   set_long(break_string("This passage is strange, it is metal lined. There "+
         "is stone beneath the metal jacket, but the metal is fairly thick. "+
         "The passage opens into a large room downwards, which you can "+
         "see from here.\n", 76));

   add_exit(CASTLE_DIR + "3k12","east",0);
   add_exit(CASTLE_DIR + "3k14","down","@@do_climb@@", 1);

   add_item(({"passage","metal","jacket"}),"The metal is nice and shiny, "+
      "but cold.\n");
   add_item("room","This passage enters at the top of the room and there "+
      "is at least\na twenty five foot drop to the floor below.\n");
   add_item("stone","The stone can only be felt by the hardness of the "+
      "metal jacket, you\ncannot see it.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_NO_ATTACK, 1);
   add_prop(ROOM_I_LIGHT, 0);
   
   thrown = 0;
}

do_climb()
{
    if(TP->resolve_task(TASK_DIFFICULT, ({TS_STR, SS_CLIMB})) > 0)
    {
        write("You climb gingerly over the edge and climb down.\n");
        tell_room(TO, QCTNAME(TP) + " climbs gingerly over the edge and " +
                  "down to the room below.\n", TP);
        tell_room(CASTLE_DIR + "3k14", QCTNAME(TP) + " climbs down from " +
                  "above.\n", TP);
        TP->move_living("M", CASTLE_DIR + "3k14", 0);
        return 0;
    }
    write("You gingerly climb over the edge, but fall down to the ground "+
          "below.\n");
    tell_room(TO, QCTNAME(TP) + " falls to the ground below.\n", TP);
    tell_room(CASTLE_DIR + "3k14", QCTNAME(TP) + " falls from above.\n");
    TP->move_living("M",CASTLE_DIR + "3k14", 0);
    TP->reduce_hit_point(-20);
    return 1;
}
