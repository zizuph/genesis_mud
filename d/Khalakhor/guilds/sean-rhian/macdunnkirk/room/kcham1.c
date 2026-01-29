// Kirk of Port City - Living quarters of the manachs
//
// History:
// Date        Coder       Action
//----------   ----------- ----------------------------------
// 7/28/97     Zima        Created
// 6/3/98      Zima        Added search for book here
//
/* inherits/includes */
inherit  "/d/Khalakhor/std/room";
#define  NUM 2
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#define  SRCH_AWARENESS 10
#define  BPS "%s 'library' / 'books' / 'shelf' / 'shelves' / 'bookshelf' "+ \
             "/ 'bookshelves' %s"
 
object *monk=allocate(NUM);
int    book_here=1;
 
void make_monk(int i) {
   if (monk[i]) return;
   monk[i]=clone_object(SR_NPC+"kmonk");
   monk[i]->equip_me();
   monk[i]->move(TO);
   monk[i]->set_wander(ROOM+"k", MASTER_OB(TO), 60);
   tell_room(TO,QCTNAME(monk[i])+" enters the chamber.\n");
}
 
void reset_room() {
   int i;
   for (i=0; i<NUM; i++) make_monk(i);
   if (random(2)) book_here=1;
}
 
/* room definition */
void create_khalakhor_room() {
   set_short("Living quarters of the abbey");
   set_long(
      "   This plushly furnished chamber must be the living quarters of the "+
      "abbey manachs. A large rug spreads across the floor in the center "+
      "of the chamber, groups of antique chairs, couches and tables neatly "+
      "arranged on it. Three opaque windows along the west wall and a pair "+
      "of chandeliers above light the room. A large tapestry hangs on the "+
      "eastern wall, flanked by two ornate candelabrum. Tall polished "+
      "bookshelves along the southern wall house a small library. The "+
      "entrance from the corridor is to the east, while a doorway leads "+
      "into another chamber to the north.\n");
   INSIDE;
 
   add_item("rug",
      "It is a large violet rug woven of wool, intricately patterned "+
      "and tasseled around the edges. It covers most of the stone "+
      "floor, and carpets the area beneath the antique furnishings.\n");
   add_item(({"chairs","couches","tables","furniture","furnishings"}),
      "Neatly set in rectangular groups on top of the carpet, "+
      "the cushioned chairs and couches are made of elegantly-carved "+
      "polished cherry. Low tables of matching design center each of "+
      "the groups. They are obviously placed to encourage or facilitate "+
      "relaxed conversations between the manachs.\n");
   add_item(({"candelabras","candelabrum","candelabra","candles"}),
      "There are two ornate candelabrum on either side of the tapestry "+
      "on the eastern wall, similar to those in the corridor. Dozens of "+
      "candles sit along its branches, lighting the chamber.\n");
   add_item(({"chandelier","chain","candles","light"}),
      "Suspended by a thick gold chain from the ceiling, the branches "+
      "of the chandeliers are filled with flickering candles.\n");
   add_item(({"bookshelf","bookshelves"}),
      "A set of elegently carved bookshelves with glass doors sits along "+
      "the southern wall of the chamber. Hundreds of finely-bound books "+
      "are housed in them, neatly placed along the shelves.\n");
   add_item(({"books","library"}),
      "Hundreds of finely-bound books are neatly housed in the elegant "+
      "shelves along the southern wall. Most are untitled, and the "+
      "remaining you are unable to read. They seem placed there more "+
      "for decoration than for heavy reading.\n");
   add_item("tapestry",
      "It is a long tapestry which runs the length of the eastern wall. "+
      "It portrays a scene of manachs, dressed in brown robes belted "+
      "with long white ropes, all kneeling before a regal figure "+
      "dressed in colorful priestly robes who stands before them with "+
      "his hands extended over them as if in blessing. The background "+
      "consists of a small stream shaded by various trees.\n");
   add_item(({"window","windows"}),
      "The windows are made of opaque panes of cream colored glass "+
      "arranged in a lattice of diamond shapes, like those found "+
      "throughout the abbey.\n");
   add_item(({"entrance","corridor"}),
      "The entrance leads into the corridor to the east.\n");
   add_item("doorway",
      "The doorway leads into another chamber to the north.\n");
 
 
   add_exit("kcorr3","east");
   add_exit("kcham2","north");
   reset_room();
   add_prop(OBJ_S_SEARCH_FUN, "srch_fun");
   add_prop(OBJ_I_SEARCH_TIME, 5);
}
 
string srch_fun(object tp, string str)
{
    object book, *inv=all_inventory(TO);
    if (book_here && (tp->query_skill(SS_AWARENESS)>=SRCH_AWARENESS) &&
        stringp(str) && parse_command(str,inv,BPS))
       {
       seteuid(getuid());
       book = clone_object(SR_BOOK+"ossian");
       if (book->move(tp)) book->move(TO);
       book_here=0;
       return ("You find a "+(book->short())+" whose title you can read "+
               "amongst the books.\n");
       }
    return "Your search reveals nothing special.\n";
}
