#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("The dark and narrow street is running north at the foot " +
    "of the eastern city wall. To the west, you can see the dark entrance " +
    "into an old building, but your attention is diverted to a gaping " +
    "archway in the east wall.");
    set_road(4);
    set_side("east");

    add_barracks();
    
    add_item(({"archway", "gaping archway"}),
             "This arched passage way is even bigger than you first had " +
             "thought, reaching over fifteen feet in height. It is almost " +
             "as wide. Some fragmentary remains of an original lining may " +
             "still be seen around the upper parts of the archway, pieces " +
             "of glazed tiles, painted white and silver. The coping of " +
             "the archway is crowned with an ornamental moulding.\n");
    
  add_exit(MORGUL_DIR + "city/barrstr5","north","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/barrstr3","south","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/barrack7","west","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/mm_stables/archway", "east", "@@check_exit",1);
}
