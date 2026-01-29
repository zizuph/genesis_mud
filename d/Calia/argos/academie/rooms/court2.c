/*
**   ARGOS - Academie - Courtyard
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**
**   Statue here is part of the Toe Quest of the Metro area. See
**   argos/metro/rooms/toequest.c
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include TOEQUEST
 
/* room definition */
void create_room() {
   set_short("Courtyard of the Academie");
   set_long(
       "A tall statue of a man standing atop a pedestal dominates this "+
       "end of the courtyard, the cloister of a prestigious building "+
       "with windowed walls buttressed by tall thin columns. The grand "+
       "entrance of the structure is to the north, two massive doors "+
       "guarding the foyer. Lush grass carpets the courtyard which "+
       "continues further south, framed by the wings of the building to "+
       "the north, west and east.\n");
 
    add_item(({"building","structure","wing","wings"}),
       "The building is constructed of white marble, its walls flanked "+
       "by tall thin columns, framing the courtyard on three sides. "+
       "Windows line the walls of the building looking out over the "+
       "courtyard. The grand entrance of the building is to the north.\n");
    add_item("columns",
       "The columns are set into the walls of the building, equally "+
       "spaced around the courtyard like guardian sentinels. Each "+
       "is topped with an elaborate capitol.\n");
    add_item(({"capitol","capitols"}),
       "The capitols atop the colums are sculpted in the shape of oak "+
       "leaves which fan out from their base to the top edge of the "+
       "capitol.\n");
    add_item("windows",
       "The windows overlook the couryard from all three sides of "+
       "the building.\n");
   add_item(({"doorway","door","doors","foyer","entrance"}),
       "The grand doorway of the building is on the north side of "+
       "the courtyard, two large doors in the center of that wing.\n");
   add_cmd_item(({"doors","door"}),({"open","unlock"}),
       "The doors are closed and locked for now. They can not be opened.\n");
   add_item(({"yard","grass"}),
       "The yard is carpeted with very short green grass, its lush "+
       "color contrasting beautifully with the white marble of the "+
       "building.\n");
   add_item(({"courtyard","cloister"}),
       "The courtyard is set in the middle of the marble building, "+
       "the columned walls of the building framing it on the "+
       "west, north and east sides. A tall statue atop a pedestal "+
       "stands in the center of the grass carpeted cloister.\n");
   add_item("statue",
       "The statue is of a regal figure wearing an ankle-length robe "+
       "belted with a simple rope, and a long hood which hangs down "+
       "his back. He is holding a scroll in both hands, and a small "+
       "crown sits on his head above a set of eyes which portray "+
       "great intelligence.\n");
   add_item("pedestal",
       "It is a large block of marble on which the statue stands. "+
       "An inscription is written across the face of the pedestal.\n");
   add_item("inscription",
       "It is written in bold letters on the pedestal. Perhaps you can "+
       "read it.\n");
   add_cmd_item("inscription","read",
       "It reads: SOCARTES - FIFTH MONARCH OF ARGOS - 112-172 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the monarch looks a little brighter than the rest "+
       "of the statue.\n");
 
    /* exits */
   add_exit(ROOM_DIR+"court1","south",0);
   toe_quest_set_statue_prop(TOE_QUEST_SOCARTES);
}
