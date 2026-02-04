/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "elderwood/include/road";

#define DEFAULT    MOUNTAIN_DIR + "elderwood/road/" 
#define FOREST_DIR MOUNTAIN_DIR + "elderwood/forest/"


public void
create_room()
{
    ::create_room();

    set_short("on a snow covered forest road.");
    set_long("The road leads to a wooden " +
       "bridge which crosses over a swift running river " +
       "leading to the southwest. The road continues " +
       "to the northeast.\n");

    add_item(({"wooden bridge","bridge"}),
       "The rustic looking barn style bridge looks wide enough " +
       "to allow a good sized cart to pass over it. Beneath the " +
       "bridge is a swift running river.\n");

    add_item(({"swift river","river"}),
       "The swift running river runs northwest and southeast " +
       "through the forest.\n"); 

    add_tell("You hear a rushing sound of the river below " +
       "the bridge.\n");


    add_exit(DEFAULT + "road18", "northeast");
    add_exit(DEFAULT + "road16", "southwest");
    add_exit(FOREST_DIR + "forest_g8", "east",0,4,1);
    add_exit(FOREST_DIR + "forest_g6", "west",0,4,1);
    add_exit(FOREST_DIR + "forest_h6", "northwest",0,4,1);


    reset_room();
}


