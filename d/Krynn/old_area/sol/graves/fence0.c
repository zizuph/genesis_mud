/*This is just a normal room with a fence in it created by Dorak*/

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include "/sys/macros.h"

inherit OUTSIDE_BASE;

void
create_solace_room()
{
    set_short("An Old Fence");
    set_long("This an old weather worn wrought iron fence.  This is the \n"+
	     "south-west corner of the fence.  The fence is easily \n"+
	     "followed to the east.\n");
    
    add_item(({"fence", "wrought iron fence", "old fence"}),
             "This is a tall old wrought iron fence.  It is painted black,\n" +
             "but the paint is peeling and the fence is very rusty.  \n" +
             "There are vines and brambles crowding all along it.\n");
    add_item("brambles",
             "These brambles have very long thorns that look very sharp. \n"+
             "You couldn't possibly climb the fence here.\n");
    add_item(({"vines","vine"}),
             "You're no botanist, but you certainly recognize those vines \n" +
             "growing along the top of the fence.  They are\n"+
             " definately poison ivy.  You start to itch just looking at\n"+
             "it and back away from it.\n");
             
    add_exit(TDIR + "fence1", "east", "@@east_msg");
    add_exit(TDIR + "o_grave0","north",0);
    
    LIGHT;
}

int
east_msg()
{	write("Click!\n");
	return 0;
}
