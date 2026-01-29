#include "defs.h"

CreateMines()
{
    set_short("Mining tunnel");
    set_long(
        "You are standing in a steep mining shaft. It looks like " +
        "the dwarves made it in search for the precious moria-silver. " +
        "The shaft continues up into a shining room, and down into the " +
        "darkness. ");
    add_exit("/d/Shire/moria/mines/goldroom","up");
    add_exit("/d/Shire/moria/mines/mining/mining.19","down");
    add_item(({"wall","walls"}),
        "The walls are roughly cut out of the mountain.");
    add_item(({"shaft"}),
	"The shaft is easy to climb, both up and down.\n");
}
