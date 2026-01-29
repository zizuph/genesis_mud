/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * tunnel9.c
 *
 * A tunnel in LoD.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "tunnel";

/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/steel_guard"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
       
    add_exit(LOD_DIR + "tunnel10g", "south",  0);
    reset_room();
}

int
go_down()
{
    write("This exit is closed for now the legion will probably place its " +
     "dungeon here, in the near future.(countdown started ;-) \n");
    return 1;
}

