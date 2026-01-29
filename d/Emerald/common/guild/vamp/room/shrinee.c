/*	This room was created by Jaypeg : 01/19/97
 *	This room is ShrineE.c, the eastern
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("eastern");
    set_dirs_desc(
        "From here you may proceed to the next tablet, "+ 
        "either to the sou'sou'west or nor'nor'west, or "+ 
        "follow the clean, narrowing runnel down into the "+ 
        "centre of the bowl." );

    add_exit( "shrinese.c", "ssw" );
    add_exit( "shrinene.c", "nnw" );
    add_exit( "shrinec.c", "down" );
}
