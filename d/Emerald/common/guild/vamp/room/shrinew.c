/*	This room was created by Jaypeg : 01/17/97
 *	This room is shrinew.c, the west
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("western");
    set_dirs_desc("From here you may proceed to the next tablet, "+ 
        "either to the nor'nor'east or sou'sou'east, or "+ 
        "follow the narrow runnel down into the "+ 
        "centre dark, ominous centre of the bowl." );

    add_exit( "shrinenw.c", "nne" );
    add_exit( "shrinesw.c", "sse" );
    add_exit( "shrinec.c", "down" );
}
