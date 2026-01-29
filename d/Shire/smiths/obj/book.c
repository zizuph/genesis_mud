/*
    The book placed in /d/Shire/smiths/master_r.c concerning
    the rules and history of the smiths guild
*/

#pragma save_binary;

inherit "/std/object";

#include "smiths.h"
#include "stdproperties.h"
#include "/d/Shire/common/defs.h"
#include "macros.h"

int opened=0;

void
create_object() {
   set_name("book");
   set_adj("brown");
   set_short("brown book");
   set_long("This very large book is bound in brown leather.\nGolden"+
      " letters written on the cover tell you that this book concerns"+ 
      " the rules and history of the smiths guild.\n");
   add_prop(OBJ_I_NO_GET,1);
   add_prop(OBJ_I_WEIGHT,5000);
   add_prop(OBJ_I_VOLUME,3000);
}

init() {
   ::init();
   add_action("read","read");
   add_action("open","open");
   add_action("close","close");
}

int
read(string str) {
   int start=0,lines=0;

   if ((str=="chapter 1") || (str=="1")) {
      start=11;
      lines=16;
   }
   if ((str=="chapter 2") || (str=="2")) {
      start=26;
      lines=10;
   }
   if ((str=="chapter 3") || (str=="3")) {
      start=35;
      lines=26;
   }
   if ((str=="chapter 4") || (str=="4")) {
      start=60;
      lines=20;
   }
   if ((str=="chapter 5") || (str=="5")) {
      start=79;
      lines=6;
   }
   if ((str=="chapter 6") || (str=="6")) {
      start=84;
      lines=9;
   }
   if ((str=="chapter 7") || (str=="7")) {
      start=92;
      lines=9;
   }
   if ((str=="index") || (str=="book")) {
      start=1;
      lines=11;
   }

   if (!start) {
      return 0;
   }

   if (!opened) {
      write("You will have to open the book in order to read it!\n");
      return 1;
   }
   else {
      write("You start reading in the book...\n");
      say(QCTNAME(TP)+" starts reading in the brown book.\n");
      cat(SMITHSDIR_DOC+"smiths_b.doc",start,lines);
   }   
   return 1;
}

int
open(string str) {
   notify_fail("Open what?\n");

   if (str!="book") return 0;
   if (opened==1)
      write("But the book is already opened!\n");
   else {
      write("You open the brown book.\n");
      say(QCTNAME(TP)+" opens the brown book.\n");
      opened=1;
   }
   return 1;
}

int
close(string str) {
   notify_fail("Close what?\n");

   if (str!="book") return 0;
   if (!opened)
      write("But the book is already closed!\n");
   else {
      write("You close the brown book.\n");
      say(QCTNAME(TP)+" closes the brown book.\n");
      opened=0;
   }
   return 1;
}
