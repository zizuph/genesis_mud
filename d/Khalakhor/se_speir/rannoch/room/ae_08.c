/* File         : /d/Khalakhor/se_speir/rannoch/room/ae_08.c
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


    add_item(({"other side","other side of the river","opposite side",
               "opposite side of the river"}),
               "The opposite side of the river looks just like this one, "
             + "a seemingly endless forest high above the river.\n");

   add_exit(ROOM + "ad_08.c","north",0,3,1);
   add_exit(ROOM + "ad_09.c","northeast",0,3,1);
   add_exit(ROOM + "ae_09.c","east",0,3,1);
   add_exit(ROOM + "af_08.c","south",0,3,1);

    set_long("The forest ends here, where a very rapidly "
           + "flowing river cuts through the hills and woods flowing "
           + "southwards. You stand high above the river itself, and "
           + "on the other side the forest and hills continues on. You "
           + "hear a great noise from the south, like that of a waterfall.\n");
}
