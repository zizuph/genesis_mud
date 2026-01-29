/*
**   ARGOS - Arena - Courtyard
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/95    Zima       Created
**
**   Statue of Collisimus found here, part of Toe Quest in metro area
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include TOEQUEST
 
/* room definition */
void create_room() {
   set_short("Courtyard of the Konistra of Argos");
   set_long(
       "You are standing in the courtyard of the Konistra of Argos, "+
       "the arena of the city where athletic events are held. The "+
       "Konistra is an enormous circular structure, two levels of tall "+
       "columns ringing its outer walls. A statue of an almost "+
       "nude muscular man stands atop a pedestal in the center of the "+
       "courtyard, a flat grassy area which leads to the entrance "+
       "of the arena to the southwest. A path leads to the northeast "+
       "back to the roads.\n");
 
   add_item(({"courtyard","grass","area"}),
      "The courtyard is a flat grassy area wedged between the main "+
      "roads on the north and east sides, and the round walls of the "+
      "Konistra to the southwest.\n");
   add_item(({"road","roads"}),
      "They border the courtyard on the north and east sides. A "+
      "pathway leads to their intersection to the northeast.\n");
   add_item(({"path","pathway"}),
      "It leads to the intersection of the main roads to the northeast.\n");
   add_item(({"konistra","arena"}),
      "It is an enormous circular building with high marble walls "+
      "buttressed by two levels of tall columns. Shallow arches "+
      "run between each of the close-set columns, adding to the "+
      "architectural wonder of the structure. The entrance is "+
      "to the southwest.\n");
   add_item("walls",
      "The walls of the Konistra are made into a perfect circle, "+
      "rising high into the air, with two levels of columns "+
      "ringing them.\n");
   add_item("columns",
      "The columns are tall and thin, topped with simple capitols, "+
      "set very close together in two levels which ring the "+
      "walls of the Konistra.\n");
   add_item("arches",
      "They run the short distance between the tops of the pairs of "+
      "columns.\n");
   add_item("entrance",
      "The entrance to the Konistra is to the southwest, though "+
      "there is a large iron gate which guards it.\n");
   add_item("gate",
      "The gate blocks the wide entrance of the Konistra to the "+
      "southwest. A sign on the gate reads: All events suspended "+
      "by order of the King.\n");
   add_cmd_item("gate",({"open","unlock"}),
      "The gate is locked and can not be opened.\n");
 
   add_item("statue",
      "It is the statue of a muscular man holding high a wreath of "+
      "olive leaves. The figure is almost nude, wearing only a short "+
      "garment around his waist, but oddly also wears a crown with "+
      "three jewels on his head. He stands atop a large pedestal "+
      "in a triumphant stance.\n");
   add_item("pedestal",
      "The pedestal is a large block of marble inlaid with gold "+
      "designs and lettering. There is an inscription written on "+
      "it which you can read.\n");
   add_item(({"inscription","lettering","letters","letter"}),
      "The inscription on the pedestal is made of large gold letters "+
      "inlaid into the face of the pedestal. Perhaps you can read it.\n");
   add_cmd_item("inscription","read",
       "It reads: COLLISIMUS - SIXTH MONARCH OF ARGOS - 172-189 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the athlete looks a little brighter than the rest "+
       "of the statue.\n");
 
    /* exits */
   add_exit(METRO_DIR+"rooms/aroad7","northeast",0);
   toe_quest_set_statue_prop(TOE_QUEST_COLLISIMUS);
}
