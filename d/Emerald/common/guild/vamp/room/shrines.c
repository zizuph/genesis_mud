/*	This room was created by Jaypeg : 01/14/97
 *      This room is ShrineS.c, the southernmost
 *      tip of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("southern");
    set_dirs_desc(
        "From here you may proceed to the next tablet, "+ 
        "either to the west'nor'west or east'nor'east, or "+ 
        "follow the clean, narrowing runnel down "+
        "a gentle slope into the "+ 
        "centre of the bowl.");

    add_item( ({"guardians", "gate", "statues",	"demons"}),
        "Looming behind you are the two gate "+
        "guardians, demons of hideous and "+
        "frightening demeanor, carved from the "+
        "rock of the shrine itself.\n" );


    add_exit("shrinesw", "wnw");
    add_exit("shrinese", "ene");
    add_exit("shrinec", "down");
    add_exit("/d/Emerald/kroad/vamp/bridge3", "south");
}

