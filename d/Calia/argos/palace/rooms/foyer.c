/*
**   ARGOS - Royal Palace - Entrance Foyer
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/96    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("Grand Entrance of the Royal Palace");
   set_long(
       "You are overcome by the grandeur of this great hall, its "+
       "vaulted ceiling trimmed in gold and supported by a matrix of "+
       "tall pillars with majestic capitols, rising from a floor which "+
       "gleams like crystal. A large sculpture sits atop "+
       "a pedestal in the center of the hall, a regal monument to the one "+
       "who rules here. Two massive golden doors guard the exit from the "+
       "palace to the north, while a gate frames the southern end of the "+
       "hall. There are entrances to two chambers to the east and west.\n");
 
   add_item(({"hall","foyer"}),
       "You are standing the the grand entrance of the palace, the chamber "+
       "used to welcome official guests to the royal family. Its vaulted "+
       "ceiling, pillars and central sculpture attest to the importance "+
       "of masterful artwork in the dynasty of this place.\n");
   add_item("ceiling",
      "The ceiling is vaulted into sections, each of which is in the "+
      "form of a dome, detailed with gold scrollwork. It is supported "+
      "by a matrix of pillars which rise from the floor.\n");
   add_item(({"pillars","matrix"}),
      "Tall round pillars made of gleaming marble, cut with trenches "+
      "which run their length. They are topped with magnificent capitols "+
      "where they meet the lower points of the vaults of the ceiling.\n");
   add_item("capitols",
      "Sculpted at the top of each pillar, the capitols are made in the "+
      "form of a ring of winged horses, rising out in a circle from "+
      "around the top of the pillar, their wings outstretched.\n");
   add_item("floor",
      "The floor is made of white marble which seems to be coated in "+
      "crystal, divided into large rectangles with the pillars set "+
      "at the intersections of their corners.\n");
   add_item(({"sculpture","statue","statues"}),
      "The sculpture is of an enormous throne, behind which stand the "+
      "three deities who are worshipped in this city, each with a "+
      "hand outstretched to a regal figure who sits on the throne. "+
      "The sculpture of the enthroned monarch is cast of gold, in "+
      "contrast to the marble of the rest, wearing long robes, holding "+
      "a scepter, and crowned with a diadem bearing three jewels at "+
      "its peak. He holds a hand out toward the entrance of the palace "+
      "in a welcoming manner.\n");
   add_cmd_item(({"sculpture","statue","toe"}),
      "rub","You rub the statue. What a strange thing to do. You suddenly "+
      "remember something about the toes on statues from an old fable.\n");
   add_item(({"toe","toes"}),
      "You can not see the toes of the figures on these statues, as they "+
      "are hidden under their long robes.\n");
   add_item("pedestal",
      "It is a large block of marble, situated in the center of the "+
      "foyer, on which the sculpture is placed. It is trimmed in gold "+
      "and bears an inscription on its face.\n");
   add_item("inscription",
      "It is sculpted into the face of the pedestal. You can read it.\n");
   add_cmd_item("inscription","read",
      "COSMOPOLITUS - Ninth Monarch of Argos - Chosen of the Tritheon - "+
      "Defender of the Holy Remnant - Ruler of the Sacred Valley\n");
   add_item(({"doors","door"}),
      "They are two massive doors of gold, tall enough for a god to walk "+
      "through, which guard the entrance of the palace to the north. They "+
      "are standing open.\n");
   add_cmd_item(({"doors","door"}),"lock","You do not have the key.\n");
   add_cmd_item(({"doors","door"}),"unlock","The doors are not locked.\n");
   add_cmd_item(({"doors","door"}),"open",  "They are already opened.\n");
   add_cmd_item(({"doors","door"}),"close",
      "They are too heavy for you to budge.\n");
   add_item("gate",
      "It is a large gate which completely covers the southern end of "+
      "the hall, preventing anyone from venturing further into the "+
      "palace.\n");
   add_cmd_item("gate",({"open","close","lock","unlock"}),
      "The gate is not made for that, there is no passage through the "+
      "gate.\n");
   add_item(({"entrances","chambers"}),
      "There are entrances to two chambers off the sides of the great "+
      "hall, one to the west and another to the east.\n");
 
    /* exits */
   add_exit("guardrm","east",0);
   add_exit("hq","west",0);
   add_exit("court2","north",0);
}
