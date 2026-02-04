/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";

object bear;
object bearcub1;
object bearcub2;

public void
reset_room()
{
    if (!bear) {
        bear=clone_object(MOUNTAIN_DIR + "elderwood/monster/bear");
        bear->move(this_object());
    }

    if (!bearcub1) {
        bearcub1=clone_object(MOUNTAIN_DIR + "elderwood/monster/bearcub");
        bearcub1->move(this_object());
    }

    if (!bearcub2) {
        bearcub2=clone_object(MOUNTAIN_DIR + "elderwood/monster/bearcub");
        bearcub2->move(this_object());
    }
 
}


public void
create_room()
{
    ::create_room();
    set_short_desc("north");
    set_long_desc(random(10));

    add_exit(FOREST_DIR   + "forest_l11", "northwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_l12", "north",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_k11", "west",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j11", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j12", "south",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_j13", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR   + "forest_k13", "east",0,4,"@@exits");

    reset_room();
}


