/* File         : /d/Khalakhor/se_speir/rannoch/room/ae_09.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit RIVERSIDE_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_item(({"river","rapid river","stream","water"}),
              "This river rushes in from the eastern "
            + "mountains, on its way south towards the sea. "
            + "It is only about fifteen feet wide, but "
            + "you see no possibility of crossing it, "
            + "since it is not only rapid, deep, and "
            + "probably icy cold, but also too far down.\n");

   add_exit(ROOM + "ae_08.c","west",0,3,1);
   add_exit(ROOM + "ad_08.c","northwest",0,3,1);
   add_exit(ROOM + "ad_09.c","north",0,3,1);
   add_exit(ROOM + "ad_10.c","northeast",0,3,1);
   add_exit(ROOM + "ae_10.c","east",0,3,1);
   add_exit(ROOM + "af_08.c","southwest",0,3,1);

    set_long("The forest ends here, where a very rapidly "
           + "flowing river cuts through the hills and woods flowing "
           + "southwards. You stand high above the river itself, and "
           + "on the other side the forest and hills continues on. You "
           + "hear a great noise from the southwest, like that of a "
           + "waterfall.\n");
}
