/*
 * /d/Cirath/altaruk/houses/dead_kank_inn.c
 *
 * A inn in Altaruk.
 *
 * Azazel
 */

#include "../defs.h"
inherit "/d/Cirath/std/room.c";
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{

}

void
create_room()
{
    set_short("the Dead Kank Inn hallway.");
    set_long("This is a halway upstairs from the bar at the" +
        " Dead Kank inn. There are doors leading west, south" +
        " and east. A stairway leads down to the bar.\n");
   
    add_item("door", "Which door?\n");
       
    add_item(({"wall", "walls"}), "The walls are sandstone" +
        " with dents and carvings You can also see the odd" +
        " bloodstain.\n");
       
    add_prop(ROOM_I_INSIDE,1);
    add_exit("dead_kank_inn.c","down",0,1,0);

    reset_room();

}
