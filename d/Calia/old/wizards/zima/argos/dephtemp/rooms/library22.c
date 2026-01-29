/*
**  Temple of Dephonia - Library middle room. General info on Order
**
**  History:
**  Coder        Date                       Action
**  ---------- --------  -----------------------------------------------------
**  Zima       1/1/95    Created
**  Zima       7/25/95   replaced multiple add_cmd_items with "read"
**                       action; text of library books moved to *.h
**
*/
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include "library2.h"
 
create_room() {
   set_short("The Library of the Temple of Dephonia");
   set_long(
      "The musty smell of old parchment permeates the air as you " +
      "walk through the quiet shelves of the main part of the temple's "+
      "library. Tall, unornate bookshelves stand in rows, almost " +
      "touching the ceiling, rows of scrolls and tomes lined along " +
      "their shelves. The narrow row between the shelves leads to " +
      "the northwest and southeast through the library.\n");
 
   add_prop(ROOM_I_INSIDE,1);
 
   add_item(({"bookshelf","bookshelves","shelf","shelves"}),
      "Made of dark pine, the shelves are not decorated, except with "+
      "some dust in their corners.\n");
   add_item(({"scrolls","tomes"}),
      "Hundreds of them lay in neat rows on the shelves, though you "+
      "can not read the titles of most due to the language or their "+
      "poor condition. You can make out the following titles: " +
      "Delphia, Demonstrates, Dephonia, the Guardian, "+
      "the Talisman, the Vision, "+
      "History Alpha, History Beta, History Gamma. "+
      "You can read one "+
      "of the scrolls with 'read scroll on <topic>'.\n");
 
   add_exit(ROOM_DIR+"library1","northwest",0);
   add_exit(ROOM_DIR+"library3","southeast",0);
}
 
int read(string Parms) {
   string *Parm;
 
   if (!Parms) {
      write("Read scroll on what?\n");
       return 1;
   }
 
   /* check syntax: Parm0="scroll", Parm1="on",Parm2=<topic> */
   Parm=explode(Parms," ");
   if (((sizeof(Parm))<3)||(!(Parm[0]=="scroll"))||(!(Parm[1]=="on"))) {
      write("Read scroll on what?\n");
      return 1;
   }
 
   Parm[2]=lower_case(Parm[2]);
   if ((sizeof(Parm))>3) Parm[2]=Parm[2]+" "+lower_case(Parm[3]);
   switch (Parm[2]) {
      case "delphia":                   write(Book[0]); break;
      case "demonstrates":              write(Book[1]); break;
      case "dephonia":                  write(Book[2]); break;
      case "guardian":                  write(Book[3]); break;
      case "talisman":                  write(Book[4]); break;
      case "the vision":                write(Book[5]); break;
      case "history alpha":             write(Book[6]); break;
      case "history beta":              write(Book[7]); break;
      case "history gamma":             write(Book[8]); break;
      default:  write("Read scroll on what?\n");
   } /* end switch */
   return 1;
}
 
void init() {
   ::init();
   add_action("read","read");
}
