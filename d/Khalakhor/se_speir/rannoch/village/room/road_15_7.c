/* File         : /d/Khalakhor/se_speir/rannoch/village/room/road_15_7.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-19      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Changed structure to coord system (Darragh 2003-07-25) 
 */

#pragma strict_types

#include "room.h"

inherit VILLAGE_BASEFILE;

public void
create_road()
{
    add_item(({"well"}),
               "It stands in the middle of the square, a large well "
             + "covered by a lid.\n");
    add_item(({"lid","cover"}),
               "The lid is a wooden board with a hole in its center. "
             + "A rope hangs down the hole, probably with a bucket on "
             + "its end.\n");
    add_item(({"bucket","rope"}),
               "The rope is secured at the base of the well and hangs "
             + "in the well through the lid, probaly with a bucket "
             + "attached at its end.\n");

    add_exit(ROOM + "road_14_7.c","west",0,1,0);
    add_exit(ROOM + "shop.c","northwest",0,1,0);
    add_exit(ROOM + "road_15_6.c","north",0,1,0);
    add_exit(ROOM + "post.c","northeast",0,1,0);
    add_exit(ROOM + "road_16_7.c","east",0,1,0);
    add_exit(ROOM + "bank.c","southeast",0,1,0);
    add_exit(ROOM + "road_15_8.c","south",0,1,0);

    set_short("Square");
    set_long("Main road W and E.\n"
           + "Shop, post, bank, extra descs.\n"
           + "Well.\n"
           + "Crowd?.\n");
}

