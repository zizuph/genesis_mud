/*
* STS Room 2
* Created by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include "../local.h"

inherit SQUARE_BASE;
object fountain;

void
make_fountain()
{
    if(!fountain)
        {
            fountain = clone_object(FOUNTAIN);
            fountain->add_prop(OBJ_I_CONTAIN_WATER, -1);
            fountain->move(TO);
            TO->add_prop(DIRTY, 1);
        }
}

void
reset_solace_room()
{
    make_fountain();
}

void
create_solace_room()
{
    set_add_trees();
    set_add_buildings();
    add_exit(NORTHSTS2, "north");
    add_exit(ROOM4, "south");
    add_exit(ROOM3, "east");
    add_exit(ROOM1, "west");

    add_prop(OBJ_I_CONTAIN_WATER, 1);
    reset_solace_room();
}

void
set_fountain_dirty(int x)
{
    if(x == 0)
    {
        remove_prop(DIRTY);
        fountain->remove_prop(DIRTY);
    }
    else
    {
        add_prop(DIRTY, 1);
        fountain->add_prop(DIRTY, 1);
    }
}

