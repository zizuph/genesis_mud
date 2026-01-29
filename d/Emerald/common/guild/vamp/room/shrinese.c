/*	This room was created by Jaypeg : 01/19/97
 *	This room is ShrineSe.c, the southeastern
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("southeastern");
    set_dirs_desc(
        "From here you may proceed to the next tablet, "+ 
        "either to the nor'nor'east or west'sou'west, or "+ 
        "follow the clean, narrowing runnel down into the "+ 
        "centre of the bowl." );

    add_exit( "shrinee.c", "nne" );
    add_exit( "shrines.c", "wsw" );
    add_exit( "shrinec.c", "down" );
}
