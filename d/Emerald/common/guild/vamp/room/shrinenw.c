/*	This room was created by Jaypeg : 01/1797
 *	This room is shrinenw.c, the northwest
 *	corner of the shrine of darkness.
 */

#include "../guild.h"

inherit VAMP_ROOM_DIR + "shrine_base";

void create_shrine_room()
{
    set_position_desc("northwestern");
    set_dirs_desc("From here you may proceed to the next tablet, "+ 
        "either to the east'nor'east or sou'sou'west, or "+ 
        "follow the narrow runnel down into the "+ 
        "dark, ominous centre of the bowl." );

    add_exit( "shrinen.c", "ene" );
    add_exit( "shrinew.c", "ssw" );
    add_exit( "shrinec.c", "down" );
}
