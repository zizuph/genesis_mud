/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel8.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnel";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit("/d/Terel/common/town/mansion/graveyard/crypt", "north",
             "@@go_north");
    add_exit(LOD_DIR + "tunnel7", "south", 0);
}

public int
go_north()
{
    string name = TP->query_race_name();
    
    if (name == "dog" || name == "bat") return 1;
    return 0;
}
