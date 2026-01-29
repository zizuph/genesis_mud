/*
**   ARGOS - Royal Palace - Courtyard
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**   8/25/96    Zima       Added doors/entrance into palace
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("Courtyard of the Royal Palace");
   set_long(
       "You are standing in the courtyard of the Royal Palace of Argos "+
       "before the grand entrance of the monolithic structure. Cherry "+
       "trees populate the courtyard, perfuming the air with the pleasant "+
       "smell of their pink blooms. Two enourmous doors guard the entrance "+
       "of the palace, cast of gold with a relief covering their face. "+
       "The courtyard of cherry trees extends to the west and east, "+
       "while a pathway leads north to the road. You stand in awe of "+
       "the oppulence of the regal structure.\n");
 
   add_item(({"building","structure","palace"}),
      "Made of impenetrable walls of glistening white marble, the "+
      "palace defines royal elegance. The walls of the palace are "+
      "divided into enormous squares, each framed in blue tile. "+
      "A pair of towering gold doors bar the entrance to the "+
      "palace, a relief cast into the precious metal of their "+
      "faces.\n");
   add_item(({"doors","door"}),
      "Made of gold, the doors tower high above you, barring the "+
      "entrance into the palace itself. The faces of the doors "+
      "are cast with a relief. They are standing opened.\n");
   add_cmd_item(({"doors","door"}),"lock","You do not have the key.\n");
   add_cmd_item(({"doors","door"}),"unlock","The doors are not locked.\n");
   add_cmd_item(({"doors","door"}),"open",  "They are already opened.\n");
   add_cmd_item(({"doors","door"}),"close",
      "They are too heavy for you to budge.\n");
   add_item("relief",
      "Cast into the faces of the towering gold doors of the palace, "+
      "the relief portrays hundreds of people of all callings "+
      "gathered in a great crowd, their attention toward a scene "+
      "at the top center of the relief. The scene is of three "+
      "dieties, seemingly suspended above clouds, with their hands "+
      "raised over a figure who sits atop a great winged horse. "+
      "The center diety adorns the rider with a crown of three "+
      "jewels.\n");
   add_item(({"trees","grove"}),
      "The trees grow thickly along the north side of the courtyard, "+
      "blocking the view of the road on the other side. Their black bark "+
      "and dark leaves contrast beautifully with their pink blooms. "+
      "Sweet cherries laden their branches, perfuming the area with "+
      "their sweet aroma.\n");
   add_item("road","You can't see it from here.\n");
   add_item(({"bark","branches"}),
      "The black bark of the brances of the trees are laden with "+
      "red cherries.\n");
   add_item("leaves",
      "They are dark green and make a beautiful backdrop for the "+
      "bright pink flowers.\n");
   add_item("flowers",
      "The flowers of the trees are in full bloom, with silky light "+
      "pink petals.\n");
   add_item(({"cherries","cherry"}),
      "They cover the branches of the trees, weighing down the branches. "+
      "There deep red color decorates the perfumed trees.\n");
   add_cmd_item(({"cherries","cherry"}),"pick",
      "Picking cherries from the royal trees is forbidden.\n");
 
    /* exits */
   add_exit(METRO_DIR+"rooms/aroad11","north",0);
   add_exit("foyer","south",0);
   add_exit("court1","west",0);
   add_exit("court3","east",0);
}
