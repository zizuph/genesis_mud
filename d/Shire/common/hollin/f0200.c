#include "forest.h"

create_forest()
{
    set_short("By the riverbank of Greyflood");
    set_long(
	"You are standing by the bank of a great river. This must "+
	"be the river Greyflood gushing down towards the southern "+
	"parts of Middle Earth. It flows quietly by but probably " +
    "isn't safe to cross it. A better idea would be to follow it " +
    "north by the river bank.\n");

    ADD_EXA("river,flood,greyflood",
	"It is quite wide here, flowing through the large forest.\n");
    ADD_EXA("bank", "The bank is rather bare, except for the " +
    "trees growing on it.\n");

    WEST("f0100");
/*    SOUTH("f02-1");
      SOUTHWEST("f01-1"); */
    NORTHWEST("f0101");
    NORTH("f0201");
}
