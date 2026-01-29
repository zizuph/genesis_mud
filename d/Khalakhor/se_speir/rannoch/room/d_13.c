/* File         : /d/Khalakhor/se_speir/rannoch/room/d_13.c
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

int climb_wall();

int
climb_wall()
{
   write ("The wall is too high and sheer to climb, and the "
        + "sharpened ends of the poles would not let you "
        + "cross the wall unharmed.\n"); 
   return 1;
}
void
create_khalakhor_room()
{
   create_loch_room();

   add_item(({"wall","wooden wall","pole","poles","layer","layers"}),
              "The wall is made of two layers of wooden poles, "
            + "driven deep into the ground, and reinforced with "
            + "mud and ropes. It looks sturdy enough to keep "
            + "unwanted people out. The top of the poles have "
            + "been sharpened, to prevent anyone from climbing "
            + "over it.\n");

   add_exit(ROAD + "d_12.c","west",0,3,1);
   add_exit(ROOM + "c_12.c","northwest",0,3,1);
   add_exit(ROAD + "c_13.c","north",0,3,1);
   add_exit(ROOM + "c_14.c","northeast",0,2,0);
   add_exit(ROOM + "e_13.c","south",0,2,0);
   add_exit(ROOM + "e_12.c","southwest",0,3,1);

   set_long("The forest grows very near the shore of the lake, "
          + "allowing only a strip of barren, rocky land between it "
          + "and the water. The view here is stunning, allowing a clear "
          + "view of the lake, the mountains on the opposite side, as "
          + "well as a village on the lake's northern end. You see a "
          + "wooden wall out in the water, running alongside the "
          + "shoreline and onto the northern shore.\n");
}
