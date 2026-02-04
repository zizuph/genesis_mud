/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


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

    reset_room();
}


