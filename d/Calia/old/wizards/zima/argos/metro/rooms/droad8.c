/*
**   ARGOS - Metro - Dueteros road
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
 
void create_room() {
   set_short("Deuteros Road");
   set_long(
       "The familiar sounds of laughter drift from the establishment "+
       "to the west, while the smell of cooking food wafts from the "+
       "building to the east making you feel hungry. You are standing "+
       "on Deuteros road in the heart of the city's commercial district, "+
       "the street lined with the cubic marble buildings which house "+
       "the local enterprises. You notice signs hanging on each of the "+
       "buildings to the east and west.\n");
 
   add_item(({"road","roads","street","streets"}),
       "Deuteros road runs north and south between the shops and other "+
       "businesses.\n");
   add_cmd_item(({"sign","signs"}), "read",
      "The sign on the western building reads: OUZOPHILUS PUB while "+
      "the eastern one reads THEROS INN.\n");
   add_item(({"shops","establishments","buildings","enterprises"}),
       "They are one-level buildings constructed of marble, lining "+
       "the street on the both sides like white cubes.\n");
   add_item(({"sign","signs"}),
       "The sign on the western building reads: OUZOPHILUS PUB while "+
       "the eastern reads: THEROS INN.\n");
 
   /* exits */
   add_exit(ROOM_DIR+"lroad10","north",0);
   add_exit(ROOM_DIR+"droad9", "south",0);
   add_exit(ROOM_DIR+"inn",    "east",0);
   add_exit(ROOM_DIR+"pub",    "west",0);
}
