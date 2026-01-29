/*
**   ARGOS - Metro - Protos Road
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   1/30/95    Zima       Created
**   5/12/16    Jaacar     Typo fixed
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
       "A statue sitting on a pedestal catches your attention as you "+
       "stroll down Protos road in Argos. The statue sits between the "+
       "road and the temple to the west, a large marble structure with "+
       "walls buttressed with tall pillars. The shops and other buildings "+
       "of the commercial district line the road on the east side. A "+
       "blue flag hangs from a pole on the wall of the one to the "+
       "east.\n");
 
   add_item("statue",
       "It is the statue of a priestly warrior heavily armoured for "+
       "battle. A large battleaxe hangs from his belt and he holds "+
       "a shield on his left arm. A falcon is perched on his shoulder. "+
       "He wears a helmet which covers the top of his face and gives "+
       "him a forboding look.\n");
   add_item("pedestal",
       "It is a large cube of white marble, intricately sculpted with "+
       "maple leaves. There is an inscription sculpted into the face "+
       "of the pedestal.\n");
   add_item("inscription",
       "It is sculpted into the face of the pedestal. Perhaps you can "+
       "read it.\n");
   add_cmd_item("inscription","read",
       "It reads: ARCANEAUS - HERO OF THE BATTLE OF THE DARK WOODS.\n");
   add_item(({"building","shop","establishment"}),
       "It is one of the buildings of the commercial district, a "+
       "simple cube of marble. There is no entrance here, but a blue "+
       "flag hangs from a pole on the wall.\n");
   add_item("flag",
       "It is hanging from a pole which angles from its base on "+
       "the wall of the building to the east. It is made of blue "+
       "silk and bears the royal arms, a shield emblazoned with a "+
       "winged horse surmounted by a crown with three jewels.\n");
   add_item(({"road","roads","street","streets"}),
       "Protos road runs north and south between a temple and a row "+
       "of commercial buildings.\n");
   add_item(({"shops","establishments","buildings"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the east side like white cubes.\n");
   add_item("temple",
       "It is a large structure made of glassy-coated marble, the wall "+
       "buttressed with high pillars. You don't seen an entrance to it "+
       "here but you notice a set of steps further south.\n");
   add_item("steps",
       "They seem to lead up to the temple further south.\n");
   add_item("pillars",
       "They buttress the wall of the temple, topped with capitols "+
       "ringed with sculpted perched falcons.\n");
 
   reset_room();
   /* exits */
   add_exit(ROOM_DIR+"proad8",  "north",0);
   add_exit(ROOM_DIR+"proad10", "south",0);
}
