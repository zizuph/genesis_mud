/*
 * forest1.c
 *
 * A room in the silver forest.
 */

#include "/d/Terel/include/Terel.h"
inherit SILVER_DIR + "forest_room";

#include "local.h"
object charlie;

public void
reset_room()
{
    if (charlie) return;

    seteuid(getuid());
    charlie = clone_object(SILVER_DIR + "monster/chisel_man");
    charlie->move_living("xx",TO);
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    
    add_exit(SILVER_DIR + "forest6", "north", 0);
    add_exit(SILVER_DIR + "forest2", "east",  0);
    reset_room();
}

