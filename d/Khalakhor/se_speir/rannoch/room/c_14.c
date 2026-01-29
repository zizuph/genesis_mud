/* File         : /d/Khalakhor/se_speir/rannoch/room/c_14.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit SHORE_BASEFILE;

string climb_wall();

string
climb_wall()
{
   if (TP->query_base_skill(SS_CLIMB) <= 30)
   {
      return "You do not even know where to start climbing, "
           + "as you are lacking the training needed. However, "
           + "the wall look awfully high, and you doubt you "
           + "could climb it, ever.\n";

      say(QCTNAME(this_player())+ " stares at the wall for a "
                                + "short while.\n");
   }

   else
   {
      return "You can not even seem to find a reliable foothold "
           + "or grip, climbing up this wall seems hopeless. Even "
           + "if you made it to the top, the sharpened tops of the "
           + "poles could inflict some serious harm.\n";

      say(QCTNAME(this_player())+ " studies the wall closely, as "
                                + "if trying to find a way to climb it.\n");
   }
}

void
create_khalakhor_room()
{
   create_loch_room();

   add_item(({"wall","wooden wall","village wall"}),
              "The wall is about ten feet high, made of thick, "
            + "sturdy wooden poles shoved deep into the ground. "
            + "The tops of the poles have been sharpened, in order "
            + "to discourage any trespassers. It runs north and "
            + "into the woods, and out into the water south of you.\n");
   add_item(({"pole","poles","thick poles","sturdy poles","wooden poles"}),
              "The poles of the wall, look like tree trunks, shoved "
            + "into the ground. They do not look very special, at least "
            + "not from this side. The top of each pole has been sharpened, "
            + "to prevent anyone from climbing over it.\n");

   add_cmd_item(({"wall","the wall","over wall","over the wall",
                  "wooden wall","the wooden wall","over wooden wall",
                  "over the wooden wall","village wall",
                  "the village wall","over village wall",
                  "over the village wall"}),
                  "climb",
                  climb_wall);

   add_exit(ROAD + "c_13.c","west",0,3,1);
   add_exit(ROOM + "b_13.c","northwest",0,3,1);
   add_exit(ROAD + "b_14.c","north",0,2,0);
   add_exit(ROOM + "d_13.c","southwest",0,2,0);

   set_short("On the shore, next to a wooden wall");

   set_long("The forest grows very near the shore of the lake, "
          + "allowing only a strip of barren, rocky land between it "
          + "and the water. A high wooden wall stands to your east, "
          + "running south and out into the lake. The view here is "
          + "stunning, allowing a clear view of the lake and the "
          + "mountains on the opposite side\n");
}
