/* File         : /d/Khalakhor/se_speir/rannoch/room/aa_13.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit FOREST_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_item(({"cliffs","cliff","wall","cliff wall"}),
              "It is a very high cliff, and it is just an "
            + "outcrop of a mountainous region to the east "
            + "and south of here.\n");
   add_item(({"river","stream","water","rapid river"}),
              "You can not see much of the river from here, "
            + "but it is definitely there, you can both see "
            + "and hear it.\n");

   add_cmd_item(({"cliff","cliffs","wall"}),"climb",
            "The cliff wall is too sheer at this point, you doubt "
          + "you would get far up before falling down again.\n");

   add_exit(ROOM + "aa_12.c","west",0,3,1);
   add_exit(ROOM + "z_12.c","northwest",0,3,1);
   add_exit(ROOM + "z_13.c","north",0,3,1);
   add_exit(ROOM + "ab_12.c","southwest",0,3,1);

   set_long(query_long() + "The way east is blocked by high cliffs, "
                         + "and through the trees to the south, you "
                         + "spot a river.\n");
}
