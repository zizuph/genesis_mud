/*
**   ARGOS - Metro - Protos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "wrong_statue.c"
 
#define NUM 2
object *citizen=allocate(NUM);
 
void make_monster(int i) {
    if (citizen[i]) return;
    citizen[i]=clone_object(NPC_DIR+"citizen");
    citizen[i]->equip_me();
    citizen[i]->move(THIS);
    tell_room(THIS, QCNAME(citizen[i])+" walks up.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++)
      make_monster(i);
}
 
void create_room() {
   set_short("Protos Road");
   set_long(
       "You are standing before the entrance of a large building to "+
       "the east, above which some lettering has been sculpted into "+
       "the marble of the wall. Two blue banners "+
       "hang from poles on either side of the wide entrance, bearing "+
       "the royal arms identifying the building as property of the "+
       "crown. To the west is one "+
       "of the city's temples, where a statue stands on a pedestal "+
       "between the road and the temple wall. Protos road leads "+
       "north and south between the public building and the temple.\n");
 
   add_item("building",
       "It is a large marble building with an angled roof, bordered with "+
       "blue tile along the top and bottom edges. There is a wide "+
       "entrance to the building to the east. It looks newer "+
       "than most of the other grand structures of the city.\n");
   add_item(({"banner","banners"}),
       "The banners hang from a poles which angle from their bases on "+
       "the wall of the building to the east. They are made of blue "+
       "silk and bear the royal arms, a shield emblazoned with a "+
       "winged horse surmounted by a crown with three jewels.\n");
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and the large "+
       "building.\n");
   add_item("lettering",
       "It is sculpted into the face of the building above the "+
       "entrance. Perhaps you can read it.\n");
   add_cmd_item("lettering","read",
       "The lettering reads: BIBLIOTHEKE ARGOS.\n");
 
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. You don't seen an entrance to it "+
       "here but you notice a set of steps further north.\n");
   add_item("steps",
       "They seem to lead up to the temple further north.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   add_item("statue",
       "It is the statue of a elderly priest garbed in light battle "+
       "armour. A sword is sheathed at his belt, and he holds a tall "+
       "staff in one hand like a sceptor, on top of which a falcon is "+
       "perched. His eyes seem full of courage and wisdom.\n");
   add_item("pedestal",
       "It is a larbe cube of white marble, intricately sculpted with "+
       "maple leaves. There is an inscription sculpted into the face "+
       "of the pedestal.\n");
   add_item("inscription",
       "It is sculpted into the face of the pedestal. Perhaps you can "+
       "read it.\n");
   add_cmd_item("inscription","read",
       "It reads: ARMENAEUS - HIEROPHANT OF ARXES.\n");
 
   reset_room();
   /* exits */
   add_exit(ROOM_DIR+"proad12",  "north",0);
   add_exit(ROOM_DIR+"proad14",  "south",0);
   add_exit(ROOM_DIR+"libhall1", "east",0);
}
