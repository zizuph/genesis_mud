/*
	LK1 - Asmodean, March 18, 1995 - Property of Cirath Domain
*/
#include "almorel.h"

inherit LAKE_MASTER;

void
create_lakeside()
{
    set_short("Lakeside");
    set_long("You are on a wide street that winds up and down the "+
        "shore of the Lake of Mists. The street is covered in "+
	"packed snow and ice. All around you are single story "+
	"houses with strangely slanted rooves. The street "+
	"continues to the Northeast and South. Through the fog "+
	"to the west, the Tower of Raumkreml can be seen towering "+
	"above the shoreline.\n\n");

    add_exit(ALMOREL+"rd4","south");
    add_exit(ALMOREL+"lk2","northeast");
}
