/*
**   ARGOS - Metro - Library - west end of hallway
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/5/95     Zima       Created
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include "defs.h"
 
void create_room() {
   set_short("Library of Argos");
   set_long(
      "You are standing in the grand hall of the library of Argos, "+
      "an enormous chamber of sparkling gray marble. An ornate copper "+
      "plaque is bolted to the western wall, next to one of two massive "+
      "pillars which mark the exit from the building. Two large "+
      "entrances open up to other chambers of the library to the "+
      "north and south.\n");
 
   add_item(({"ceiling","roof"}),
      "Rising high above you, the ceiling is made of enormous squares "+
      "of gray marble which seem coated in glass.\n");
   add_item(({"hall","chamber","walls","floor"}),
      "The hall is constructed of gray marble which seems to be coated "+
      "in glass, the walls and floor reflecting the light "+
      "from outside. The hall continues further east.\n");
   add_item("entrances","Wide entrances open up into other chambers "+
      "to the north and south.\n");
   add_item("pillars","They stand like sentinels guarding the exit "+
      "from the building to the west.\n");
   add_item("plaque",
      "It is a copper plaque bolted on the western wall, lettered "+
      "with fine writing. Perhaps you can read it.\n");
   add_cmd_item("plaque","read",
      "                                     \n"+
      " +--------------------------------++ \n"+
      " ||                               || \n"+
      " ||         Erected to the        || \n"+
      " ||     Greater Glory of Argos    || \n"+
      " ||              by               || \n"+
      " ||                               || \n"+
      " ||  BIBLIONUS OF HOUSE ARGOSIUS  || \n"+
      " ||  The Eighth Monarch of Argos  || \n"+
      " ||             256 AT            || \n"+
      " ||                               || \n"+
      " ++-------------------------------++ \n");
 
 
   /* room properties */
   add_prop(ROOM_I_INSIDE,1);
 
   add_exit(ROOM_DIR+"lib1","north",0);
   add_exit(ROOM_DIR+"lib3","south",0);
   add_exit(ROOM_DIR+"libhall2","east",0);
   add_exit(ROOM_DIR+"proad13","west",0);
}
