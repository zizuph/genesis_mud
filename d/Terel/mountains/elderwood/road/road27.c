/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"

public void
create_room()
{
    ::create_room();

    set_short("on a snow covered forest road");
    set_long("You hear the snow crunch beneath you as you " +
             "continue to travel on the snow covered " +
             "road. The vast forest of Elderwood extends on either " +
             "side of you. To the north, you notice a mountainrange just " +
             "above the trees.\n");

    add_item(({"mountains","mountainrange"}),
       "The jagged tips of a vast mountainrange " +
       "can be seen above the trees.\n");

    add_exit(DEFAULT + "road28", "north");
    add_exit(DEFAULT + "road26", "south");
    add_exit(FOREST_DIR + "forest_r7", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_s7", "northeast",0,4,1);
    add_exit(FOREST_DIR + "forest_q7", "southeast",0,4,1);
    add_exit(FOREST_DIR + "forest_r5", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_s5", "northwest",0,4,1);
    add_exit(FOREST_DIR + "forest_q5", "southwest",0,4,1);

    reset_room();
}


