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
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
void create_room() {
   set_short("Library of Argos");
   set_long(
      "Your footsteps echo off the glassy walls of the chamber as "+
      "you enter giving you a sense of the spaciousness of the large "+
      "room. Tall shelves sit along the walls filled with tomes and "+
      "scrolls, much what you would expect in a library. A "+
      "large entrance leads north to the grand hall of the library.\n");
 
   add_item(({"room","chamber","walls","floor"}),
      "The chamber is constructed of gray marble which seems to be coated "+
      "in glass, reflecting light all around and echoing the smallest "+
      "sound.\n");
   add_item("entrance",
      "A wide entrance leads north into the grand hall.\n");
   add_item("shelves",
      "The line the walls of chamber, reaching into the heights of "+
      "the room. Made of thick oak and intricately carved with leaves, "+
      "they house a collection of scrolls and tomes.\n");
   add_item(({"scrolls","tomes","titles"}),
      "Written in many languages the tomes and scrolls lay on the "+
      "tall shelves. Though most are in an unknown language, you can read "+
      "some of the titles. Try 'list titles' to get a list.\n");
   add_item("ceiling",
      "Set very high above you, the ceiling is made of square slabs of "+
      "glassy gray marble.\n");
   add_item(({"hall","grand hall"}), "It is to the north.\n");
 
 
   /* room properties and exits */
   add_prop(ROOM_I_INSIDE,1);
   add_exit(ROOM_DIR+"libhall2","north",0);
}
 
int list_titles() {
   write("You can read the following titles: (try 'read #'):\n");
   write("1. Alexis     \n");
   write("2. Kretos     \n");
   write("3. Arxes      \n");
   write("4. Thema      \n");
   write("5. Pharos     \n");
   write("6. orichalcum \n");
   return 1;
}
 
int read_it(string N) {
   object Tp=this_player();
   object Tr=this_object();
   string Title,Text;
 
   switch (N) {
      case "1": Title="alexis"; break;
      case "2": Title="kretos"; break;
      case "3": Title="arxes";  break;
      case "4": Title="thema";  break;
      case "5": Title="pharos"; break;
      case "6": Title="orichalcum"; break;
      default: Title="none"; break;
   }
   if (Title=="none")
      write("Read which title? (try 'read 1').\n");
   else {
      tell_room(Tr,QTNAME(Tp)+" reads one of the scrolls from a shelf.\n",Tp);
      Tp->more(read_file(((LIB_DIR+Title+".txt"))));
   }
   return 1;
}
 
void init() {
   ::init();
   add_action("list_titles","list");
   add_action("read_it","read");
}
