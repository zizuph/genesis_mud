/* A room on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/walkers/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";

object rack, cabinet, chest;

create_room()
{
    set_short("Tower Equipment Room");

    set_long("This small, windowless room serves as place for College" +
        " members to store equipment. " + basic_desc + " An archway leads" +
        " north, into the start room.\n");

    add_item("archway", "It's an open archway, with no closing mechanism.\n"); 

    rack = clone_object(TOWER_OBJECTS + "eq_rack.c");
    rack->move(TO);
    cabinet = clone_object(TOWER_OBJECTS + "eq_cabinet.c");
    cabinet->move(TO);
    chest = clone_object(TOWER_OBJECTS + "eq_chest.c");
    chest->move(TO);

    add_exit(TOWER + "tower_start.c", "north", 0, 1);

    make_college_room();
}