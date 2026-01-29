/*
**   ARGOS - Royal Palace - Courtyard
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include WRONGSTATUE
 
/* room definition */
void create_room() {
   set_short("Courtyard of the Royal Palace");
   set_long(
       "A statue of a great winged horse atop a pedestal demands your "+
       "attention as you enjoy the scenery of the courtyard of the palace. "+
       "A grove of cherry trees populates the courtyard, giving way to the "+
       "monolithic walls of the palace itself to the east and south. You "+
       "dream of what it must be like to live in such grandeur.\n");
 
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
 
   add_item("statue",
      "It is a statue of a winged horse, reared on its rear legs in "+
      "a rampant stance, its great wings spread out in a powerful span. "+
      "The statue must be at least twice the size of a living horse. "+
      "The elegant steed has a strong and noble head, tucked slightly "+
      "toward its neck.\n");
   add_item("pedestal",
      "The pedestal is a large block of marble inlaid with gold "+
      "designs and lettering. There is an inscription written on "+
      "it which you can read.\n");
   add_item(({"inscription","lettering","letters","letter"}),
      "The inscription on the pedestal is made of large gold letters "+
      "inlaid into the face of the pedestal. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
       "It reads: AEROHIPPOLITUS - ROYAL STEED OF THE HOUSE OF ARGOSIUS.\n");
 
   add_item(({"sides","palace","walls"}),
      "The monolithic walls of the Royal Palace of Argos rise above "+
      "the courtyard to the south and west. Divided into enourmous "+
      "square blocks, each lined with blue tile, the walls seem "+
      "an impenetrable fortress for those who reside inside.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"court2","west",0);
}
