/* This comment tells emacs to use c++-mode  -*- C++ -*- */
#pragma strict_types

#include "/d/Terel/include/Terel.h"
#include "/d/Terel/mountains/elderwood/include/local.h"

inherit MOUNTAIN_DIR + "elderwood/include/forest";

object ogre1;
object ogre2;
object ogre3;


public void
reset_room()
{
    if (!ogre1) {
        ogre1=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_ogre");
        ogre1->move(this_object());
    }

    if (!ogre2) {
        ogre2=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_ogre");
        ogre2->move(this_object());
        ogre1->team_join(ogre2);
    }

    if (!ogre3) {
        ogre3=clone_object(MOUNTAIN_DIR + "elderwood/npc/std_ogre");
        ogre3->move(this_object());
        ogre2->team_join(ogre3);
    }
}


public void
create_room()
{
    ::create_room();
    set_short_desc("west");
    set_long_desc(random(10));

    add_exit(FOREST_DIR + "forest_n2", "north",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_m3", "east",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_n3", "northeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_l3", "southeast",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_l2", "south",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_m1", "west",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_l1", "southwest",0,4,"@@exits");
    add_exit(FOREST_DIR + "forest_m1", "northwest",0,4,"@@exits");

    reset_room();
}


