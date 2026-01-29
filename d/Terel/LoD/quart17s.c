/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * quart17s.c
 *
 * Private quarters in the legion of darkness.
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "quarters";

/*
 * Function name: query_rank
 * Description:   the rank in the army who lives in these quarters.
 * Returns:       a string that is the rank.
 */
public string
query_rank()
{
    return "sergeants";
}

/*
 * Function name: query_object_list
 * Description:   return list of object to clone at each reset.
 */
public string*
query_object_list()
{
    return ({LOD_DIR + "monster/elf_sergeant",
             LOD_DIR + "monster/elf_sergeant"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    add_exit(LOD_DIR + "corr17", "north", 0);
    reset_room();
}
