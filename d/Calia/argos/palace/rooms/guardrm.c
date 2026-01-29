/*
**   ARGOS - Royal Palace - Guard Room
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   8/25/96    Zima       Created
**   5/12/16    Jaacar     Fixed typo
**
*/
/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
/* room definition */
void create_room() {
   set_short("A converted ballroom");
   set_long(
      "The high ceiling with its intricately decorated trim, and the rectangle "+
      "of sculpted pillars along the smooth marble walls of this chamber "+
      "tell of its former use as an elegant ballroom of the palace. It "+
      "has recently been converted into a center of military operation, "+
      "strategically located near the entrance of the royal abode. A row "+
      "of beds line the walls, while crates sit in the center of the floor "+
      "next to a long table and chair. A high archway leads west into the "+
      "grand entrance of the palace.\n");
 
   add_item(({"ceiling","trim"}),
      "It is sculpted with a criss-crossed pattern of rope-shaped strands, "+
      "looking like an elegant net. The gold pattern melds well with the "+
      "white marble of the ceiling it covers.\n");
   add_item(({"pillars","rectangle"}),
      "Sculpted into the walls, the stately pillars rise around the "+
      "perimeter of the chamber, like giant ladies-in-waiting overlooking "+
      "the festivities which once occurred here.\n");
   add_item("beds",
      "Simple wooden beds, but with comfortable mattresses, they serve "+
      "the guards who are stationed here well.\n");
   add_item("crates",
      "They are large wooden crates, probably containing supplies for "+
      "the soldiers who are stationed here. They are all closed and can "+
      "not be opened.\n");
   add_item("table",
      "It is a long wooden table, papers scattered across its top.\n");
   add_item("chair",
      "It is a simple wooden chair behind the table, probably used by a "+
      "supply officer for paperwork.\n");
   add_item("papers",
      "Just various inventories and supply orders. Nothing interesting.\n");
   add_item(({"archway","entrance"}),
      "It is a high rectangular archway marked with two of the stately "+
      "pillars on each side. It leads into the grand entrance.\n");
 
   /* exits */
   add_exit("foyer","west",0);
}
