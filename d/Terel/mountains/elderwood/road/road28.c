/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"

object warrior1;
object warrior2;
object warrior3;
object warrior4;

public void
reset_room()
{
    if (!warrior1) {
        warrior1=clone_object(MOUNTAIN_DIR + "stronghld/npc/lancer_leader");
        warrior1->move(this_object());
    }

    if (!warrior2) {
        warrior2=clone_object(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer");
        warrior2->move(this_object());
        warrior1->team_join(warrior2);
    }

    if (!warrior3) {
        warrior3=clone_object(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer");
        warrior3->move(this_object());
        warrior1->team_join(warrior3);
    }

    if (!warrior4) {
        warrior4=clone_object(MOUNTAIN_DIR + "stronghld/npc/dwarven_lancer");
        warrior4->move(this_object());
        warrior1->team_join(warrior4);
    }
 
}



public void
create_room()
{
    ::create_room();

    set_short("on a snow covered forest road");
    set_long("The treeline opens up here into a large " +
       "snowfilled field. At the end of the field " +
       "is a vast mountainrange. From here " +
       "you notice something glistening at the " +
       "mountains edge.\n");

    add_item(({"mountains","mountainrange"}),
       "The jagged tips of a vast mountainrange " +
       "can be seen above the trees.\n");

    add_exit(DEFAULT + "road29", "north");
    add_exit(DEFAULT + "road27", "south");
    add_exit(FOREST_DIR + "forest_s7", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_r7", "southeast",0,4,1);
    add_exit(FOREST_DIR + "forest_s5", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_r5", "southwest",0,4,1);

    reset_room();
}


