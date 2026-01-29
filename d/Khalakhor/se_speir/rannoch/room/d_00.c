/* File         : /d/Khalakhor/se_speir/rannoch/room/d_00.c
 * Creator      : Darragh@Genesis
 * Date         : 00-10-02      
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

   add_item("bridge",
            "It is a simple bridge made out of timber logs, planks, "
          + "and a lot of rope. But it looks as if someone tried "
          + "to hinder people from crossing by destroying it.\n");

   add_exit(ROAD + "c_00.c","north",0,3,1);
   add_exit(ROOM + "c_01.c","northeast",0,3,1);
   add_exit(ROOM + "d_01.c","east",0,3,1);
   add_exit(ROOM + "e_01.c","southeast",0,3,1);
   add_exit(ROOM + "e_00.c","south",0,3,1);

   set_long("The forest ends here, where a very rapidly "
          + "flowing river cuts through the hills and woods flowing "
          + "southwards. You stand high above the river itself, and "
          + "on the other side the forest and hills continues on. You "
          + "see a bridge across the river, north of you.\n");
}
