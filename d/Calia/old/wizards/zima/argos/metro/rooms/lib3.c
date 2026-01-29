/*
**   ARGOS - Metro - Library - Museum
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**
*/
inherit "/std/room";
inherit "/lib/more.c";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object curator;           /* NPC - curator of the museum                 */
 
void reset_room() {
   object Tr=this_object();
    if (!(curator)) {
       curator=clone_object(NPC_DIR+"curator");
       curator->equip_me();
       curator->move(THIS);
       tell_room(Tr, QTNAME(curator)+" enters from the hall.\n");
    }
}
 
void create_room() {
   set_short("Library of Argos");
   set_long(
      "You are standing in a large room checkered with rows of pedestals "+
      "displaying various objects. Several large paintings adorn the "+
      "walls on all sides. This chamber of the library is obviously a "+
      "museum where visitors may view the various collections "+
      "displayed here. A large entrance leads north back to the "+
      "grand hall of the library.\n");
 
   add_item(({"rows","pedestals","pedestal","row","objects","object"}),
      "There are nine pedestals set in three rows of three each centered "+
      "in the middle of the room, each holding an object of significance "+
      "collected by Alexis on his travels to distant lands. "+
      "A small note is placed on each pedestal with an explanation of "+
      "the object on top. "+
      "You may take a closer look at the objects on each pedestal, the "+
      "first through the ninth.\n");
   add_item(({"paintings","painting"}),
      "Six paintings adorn the walls of the museum, each depicting "+
      "a tale from the travels of Alexis, which have become folklore "+
      "in Argos. "+
      "You may take a closer look at each painting, the first through "+
      "the sixth.\n");
 
   add_item(({"room","chamber","walls","floor"}),
      "The chamber is constructed of gray marble which seems to be coated "+
      "in glass, reflecting light all around and echoing the smallest "+
      "sound.\n");
   add_item("entrance",
      "A wide entrance leads north into the grand hall.\n");
   add_item("ceiling",
      "Set very high above you, the ceiling is made of square slabs of "+
      "glassy gray marble.\n");
   add_item(({"hall","grand hall"}), "It is to the north.\n");
 
   /* descriptions of pedestals and paintings */
#include "lib3.ext"
 
   /* room properties and exits */
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"libhall1","north",0);
   reset_room();
}
