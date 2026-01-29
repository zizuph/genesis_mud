/*
 * bedroom.c
 *
 * Skippern 20(c)02
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

void
create_inside()
{
    set_short("a bedroom");
    set_long("A lavishly decorated bedroom. In the middle " +
	     "of the room a huge bed with silken bedsheets " +
	     "and head boards in mahogny. An open door leads " +
	     "out to a balchony, and the curtains are light and " +
	     "moving with the wind.\n");

    add_exit(DOL_HILLS + "m-11/upstairs", "south", 0, 1);
    add_exit(DOL_HILLS + "m-11/balcony", "east", 0, 1);
}
