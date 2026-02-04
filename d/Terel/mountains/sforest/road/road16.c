/* This comment tells emacs to use c++-mode  -*- C++ -*- */


#include "/d/Terel/include/Terel.h"
inherit MOUNTAIN_DIR + "sforest/include/road";
// inherit MOUNTAIN_DIR + "sforest/include/river";

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/" 


public void
create_room()
{
    ::create_room();
    set_long(query_long() + "The road leads to a wooden " +
       "bridge which crosses over a swift running river " +
       "leading to the northeast. The road continues " +
       "south.\n");

    add_item(({"wooden bridge","bridge"}),
       "The rustic looking barn style bridge looks wide enough " +
       "to allow a good sized cart to pass over it. Beneath the " +
       "bridge is a swift running river.\n");

    add_item(({"swift river","river"}),
       "The swift running river runs northwest and southeast " +
       "through the forest.\n"); 

    add_tell("You hear a rushing sound of the river below " +
       "the bridge.\n");

    add_exit(DEFAULT + "road17", "northeast");
    add_exit(DEFAULT + "road15", "south");

    reset_room();
}


