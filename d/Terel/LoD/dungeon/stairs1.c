/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * stairs1.c
 *
 */

#include "/d/Terel/include/Terel.h"
inherit LOD_DIR + "legion_room";

#include <stdproperties.h>

#define DUNG_DIR  (LOD_DIR + "dungeon/")

object guard = 0;
object prisoner;

public string*
query_moving_object_list()
{
    return ({LOD_DIR + "monster/special_guard"});
}

public void
reset_room()
{
    ::reset_room();
    
    guard = present("special_guard");
    
    if (!guard) return;
    
    seteuid(getuid());
    prisoner = clone_object(LOD_DIR + "monster/pit_prisoner");
    prisoner->move_living("M", TO);
    prisoner->set_guard(guard);
    guard->start_push_seq(prisoner);
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    set_short("stairs down to dungeons");
    set_long("You are standing in a staircase going down to the dungeons " +
             "beneath the Legion of Darkness' quarters. " +
             "This staircase looks much older than the rest of the " +
             "Legion's quarters. They probably discovered this part " +
             "by accident when they enlarged their quarters. The " +
             "staircase is lit up by a torch.\n");

    add_item(({"stair", "stairs"}), "The stairs are made of stone.\n");

    add_item(({"torch"}), "It's a simple looking torch, firmly attached " +
	     "to the wall.\n");

    add_item(({"wall", "walls"}), "The walls are made out of large " +
	     "stones. The stones must have been cut by an expert, since " +
	     "there are almost no gaps between them.\n");

    add_item(({"gap", "gaps"}), "Small amounts of dirty water emerge " +
	     "from the gaps.\n");
       
    add_exit(LOD_DIR + "tunnel11", "up", 0);
    add_exit(DUNG_DIR + "stairs2", "down", 0);
    
    reset_room();
}
