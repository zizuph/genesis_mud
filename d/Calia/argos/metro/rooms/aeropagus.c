/*
**   ARGOS - Metro - Aeropagus - "Town Commons"
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/12/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "toequest.c"
#define NUM 2
object speaker;
object *citizen=allocate(NUM);
 
void make_citizen(int i) {
    if (citizen[i]) return;
    citizen[i]=clone_object(NPC_DIR+"citizen");
    citizen[i]->equip_me();
    citizen[i]->move(THIS);
    tell_room(THIS, QCTNAME(citizen[i])+" arrives.\n");
}
 
void make_speaker() {
    if (speaker) return;
    speaker=clone_object(NPC_DIR+"speaker");
    speaker->equip_me();
    speaker->move(THIS);
    tell_room(THIS, QCTNAME(speaker)+" steps up on the dias.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) 
         make_citizen(i);
   make_speaker();
}
 
 
void create_room() {
   set_short("The Aeropagus");
   set_long(
       "You are standing in the Aeropagus, the commons area in the "+
       "center of Argos where people gather to listen to speakers and "+
       "discuss the issues of the city. The ground is covered with "+
       "massive squares of sculpted marble, the area enclosed by a "+
       "row of pillars on all four sides. "+
       "A towering statue stands atop a pedestal "+
       "in the center of the commons, while a round dias serves as a "+
       "stage for speakers. Gaps in the row of pillars allow you to "+
       "enter the streets of the city to the east and south, while "+
       "the Strathmos is to the west.\n");
 
   add_item(({"street","streets"}),
      "They are to the south and east.\n");
   add_item(({"strathmos","Strathmos"}),
      "It is the depot for the city where chariots arrive to transport "+
      "visitors in and out of the city. It is to the west.\n");
   add_item(({"aeropagus","Aeropagus","commons","area"}),
      "It is an open-air forum which serves as a meeting place for "+
      "citizens, appropiately constructed with the rich architecture "+
      "of the city.\n");
   add_item(({"ground","squares"}),
      "Marble squares several paces long on each side cover the "+
      "ground, each sculpted with the arms of Argos on each. You "+
      "think it is almost a shame to walk on such artistic work.\n");
   add_item(({"arms","arms of argos","arms of Argos"}),
      "The arms consists of a shield emblazoned with a rampant winged "+
      "horse, surmounted by a crown with three jewels.\n");
   add_item(({"pillar","pillars","row","row of pillars","rows of pillars"}),
      "A row of pillars frames the Aeropagus on all four sides, "+
      "tall columns of marble with elaborate capitols. They stand like "+
      "marble trees perfectly spaced apart.\n");
   add_item("dias",
      "It is a large round slab of marble on top of which speakers "+
      "stand to be seen by gathering crowds.\n");
   add_item("statue",
      "The statue is of a young military figure, dressed in armour "+
      "and holding a sword above his head, mounted on a winged "+
      "horse, its front legs reared high in a rampant manner.\n");
   add_item("pedestal",
      "The pedestal is a long block of marble supporting the "+
      "statue of the winged horse and its rider. An inscription "+
      "is written on it in bold letters.\n");
   add_item("inscription","It is written on the pedestal. Perhaps "+
      "you can read it.\n");
   add_cmd_item("inscription","read",
      "It reads: ARGOSIUS : FIRST MONARCH OF ARGOS : 37-40 AT.\n");
   add_item(({"toe","toe of statue","toe on statue"}),
       "The toe of the king looks highly polished compared to "+
       "the rest of the statue.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"croad12",   "south",0);
   add_exit(ROOM_DIR+"trroad10",  "east",0);
   add_exit(ROOM_DIR+"depot",     "west",0);
   toe_quest_set_statue_prop(TOE_QUEST_ARGOSIUS);
   reset_room();
   (clone_object("/d/Genesis/obj/donation/column"))->move(this_object());
}
