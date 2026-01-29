/*	This room was created by Jaypeg : 01/19/97
 *	This room is ShrineSw.c, the southwestern
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("southwest");
    set_dirs_desc("From here you may proceed to the next tablet, "+ 
        "either to the nor'nor'west or east'sou'east, or "+ 
        "follow the clean, narrowing runnel down into the "+ 
        "centre of the bowl." );

    add_exit( "shrinew.c", "nnw" );
    add_exit( "shrines.c", "ese" );
    add_exit( "shrinec.c", "down" );
}
