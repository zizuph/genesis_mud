/*	This room was created by Jaypeg : 01/17/97
 *	This room is ShrineN.c, the north
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_short( "Northern point of the shrine of darkness.\n" );
    set_position_desc("northern");
    set_dirs_desc("From here you may proceed to the next tablet, "+ 
        "either to the east'sou'east or west'sou'west, or "+ 
        "follow the clean, narrowing runnel down into the "+ 
        "centre of the bowl.");

    add_exit( "shrinene.c", "ese" );
    add_exit( "shrinenw.c", "wsw" );
    add_exit( "shrinec.c", "down" );
}
