/*
 * The west guard room in the castle in Telseron
 * By Finwe, November 1996
 */
 
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/telseron/castle/default.h"
 
 
void reset_room();
void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
    set_short("Western guard room");
    set_long("   You stand in the western guard to the King's " +
	"chambers. The guards stand at attention as you enter. " +
	"They have dedicated their lives to protect the king " +
	"and take their oath seriously. Light enter in from " +
	"windows on the western wall. The walls are smooth and " +
	"pure white. They are decorated with floral designs. The " +
	"floors are covered with rich carpets which dampen most " +
	"of the noise. They look comfortable and are luxurious. " +
	"You see some scrapes on the walls from what may be " +
	"recent skirmishes in here. Some elves pass by you as " +
	"they enter the private chambers of the King.\n\n");

    add_item(({"up", "ceiling"}),
        "The ceiling has been richly painted with various scenes. They " +
        "depict the strength of the King's armies.\n");
    add_item(({"wall", "walls"}),
        "The walls are pearly white. They shine brilliantly as they " +
        "are covered with mother of pearl. The surface is so perfectly " +
        "covered you don't detect any seams. The walls have been "+
        "polished and are smooth to the touch.\n");
    add_item(({"floor", "ground", "down", "rug", "rugs",
               "carpet", "carpets"}),
        "The carpets are a rich forest green. Intricate designs of " +
        "leaves decorate the carpet in burgandy, royal blue, gold, " +
        "and dark brown.\n");
    add_item(({"design", "designs", "floral designs"}),
        "The designs are of large flowers twining across the " +
        "wall. They are made of inlaid emerald.\n");
    add_item(({"window", "windows"}),
        "The windows are expansive and fill the corridor with " +
        "light. They are arch shaped.\n");
 
    add_exit( TCASTLE_DIR + "cor14", "north");
    add_exit( TCASTLE_DIR + "k_dr", "east");
}
 
void
reset_room()
{
}
