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
#include TOEQUEST
 
/* room definition */
void create_room() {
   set_short("Courtyard of the Royal Palace");
   set_long(
       "The sweet smell of the grove of cherry trees which populate "+
       "this courtyard fills the air. A tall statue stands atop a pedestal "+
       "here, rising above the height of the flowering trees which surround "+
       "it. The sides of the royal palace wall this part of the courtyard "+
       "to the south and west, monoliths of marble reflecting the "+
       "sunlight.\n");
 
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
      "It is the statue of a tall bearded man dressed in very "+
      "extavagant jewled robes. He has several rings on his hands "+
      "which clutch a long scepter. He has an elaborate crown with "+
      "three jewels on his head, and a condescinding look about "+
      "his face. The statue stands atop a large pedestal.\n");
   add_item("pedestal",
      "The pedestal is a large block of marble inlaid with gold "+
      "designs and lettering. There is an inscription written on "+
      "it which you can read.\n");
   add_item(({"inscription","lettering","letters","letter"}),
      "The inscription on the pedestal is made of large gold letters "+
      "inlaid into the face of the pedestal. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
       "It reads: PAXEUS - SECOND MONARCH OF ARGOS - 40-64 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the monarch looks a little brighter than the rest "+
       "of the statue.\n");
 
   add_item(({"sides","palace","walls"}),
      "The monolithic walls of the Royal Palace of Argos rise above "+
      "the courtyard to the south and west. Divided into enourmous "+
      "square blocks, each lined with blue tile, the walls seem "+
      "an impenetrable fortress for those who reside inside.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"court2","east",0);
   toe_quest_set_statue_prop(TOE_QUEST_PAXEUS);
}
