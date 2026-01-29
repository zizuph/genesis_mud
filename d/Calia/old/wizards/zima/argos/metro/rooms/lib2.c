/*
**   ARGOS - Metro - Library - History Room
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
 
void create_room() {
   set_short("Library of Argos");
   set_long(
      "Tall shelves line the walls of this spacious chamber, filled "+
      "with scrolls and tomes on various subjects written in several "+
      "languages. You think the tiniest sound would echo off the "+
      "high ceiling of this quiet chamber into a small peal. A "+
      "large entrance leads south to the grand hall of the library.\n");
 
   add_item(({"room","chamber","walls","floor"}),
      "The chamber is constructed of gray marble which seems to be coated "+
      "in glass, reflecting light all around and echoing the smallest "+
      "sound.\n");
   add_item("entrance",
      "A wide entrance leads south into the grand hall.\n");
   add_item("shelves",
      "The line the walls of chamber, reaching into the heights of "+
      "the room. Made of thick oak and intricately carved with leaves, "+
      "they house a collection of historical scrolls and tomes.\n");
   add_item(({"scrolls","tomes","titles"}),
      "Written in many languages, most of which you don't understand, "+
      "the tomes line the shelves of the library. Some of the titles "+
      "you can read, a list of which you can obtain with 'list titles'.\n");
   add_item("ceiling",
      "Set very high above you, the ceiling is made of square slabs of "+
      "glassy gray marble.\n");
   add_item(({"hall","grand hall"}), "It is to the south.\n");
 
 
   /* room properties and exits */
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"libhall2","south",0);
}
 
int list_titles() {
   write("You can read the following titles on the history of Argos: "+
         "(try 'read #'):\n");
   write("1. Prehistory          7. Basileus            \n");
   write("2. Divine Era          8. Socartes            \n");
   write("3. Council Era         9. Collisimus          \n");
   write("4. Argosius           10. Thespia             \n");
   write("5. Paxeus             11. Biblionus           \n");
   write("6. Agrarius           12. Cosmopolitus        \n");
   return 1;
}
 
int read_it(string N) {
   object Tp=this_player();
   object Tr=this_object();
   int    ndx;
 
   ndx=member_array(N,({"1","2","3","4","5","6","7","8","9","10","11","12"}));
   if (ndx>-1) {
      tell_room(Tr,QTNAME(Tp)+" reads one of the scrolls from a shelf.\n",Tp);
      Tp->more(read_file((LIB_DIR+"hist"+N+".txt")));
      }
   else
      write("Read which title? (try 'read 1').\n");
   return 1;
}
 
void init() {
   ::init();
   add_action("list_titles","list");
   add_action("read_it","read");
}
