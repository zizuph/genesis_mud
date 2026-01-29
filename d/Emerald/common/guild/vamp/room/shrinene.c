/*	This room was created by Jaypeg : 01/19/97
 *	This room is ShrineNe.c, the northeastern
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("eastern");
    set_dirs_desc(
        "From here you may proceed to the next tablet, "+ 
        "either to the sou'sou'east or west'nor'west, or "+ 
        "follow the clean, narrowing runnel down into the "+ 
        "centre of the bowl." );

    add_exit( "shrinee.c", "sse" );
    add_exit( "shrinen.c", "wnw" );
    add_exit( "shrinec.c", "down" );
}
