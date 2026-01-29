/* File         : /d/Khalakhor/se_speir/rannoch/room/o_11.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include "room.h"

inherit SHORE_BASEFILE;

void
create_khalakhor_room()
{
   create_loch_room();

   add_cmd_item(({"cliff","cliffs","wall","rock wall","sheer rock wall"}), 
            "climb",
            "The cliff wall is too sheer at this point, you doubt "
          + "you would get far up before falling down again.\n");

   add_exit(ROOM + "o_10.c","west",0,3,1);
   add_exit(ROOM + "n_10.c","northwest",0,3,1);
   add_exit(ROOM + "n_11.c","north",0,2,0);
   add_exit(ROOM + "p_10.c","southwest",0,3,1);

    set_long("The forest grows very near the shore of the lake, "
           + "allowing only a strip of barren, rocky land between it "
           + "and the water. The view here is stunning, allowing a clear "
           + "view of the lake, the mountains on the opposite side, as "
           + "well as a village on the lake's northern end. The shore "
           + "ends here abruptly against a sheer rock wall, an outcrop "
           + "of the rocky hills that lie south of here.\n");
}
