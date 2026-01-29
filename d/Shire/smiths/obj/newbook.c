/*
 *       This book is placed in rest_r in Smiths Guild
 *       Allows masters of the Smiths Guild to make new entries
 *       readable by all
 */

inherit "/std/object";

#include "smiths.h"
#include <stdproperties.h>
#include "/d/Shire/common/defs.h"
#include <macros.h>

#define SMITHSDIR_BOOK "/d/Shire/smiths/log/book/"

int opened=0;
string *index = ({});
string header;

object editor;
string text;

void
create_object() {
   set_name("book");
   set_adj("leatherbound");
   set_adj("red");
   set_short("red leatherbound book");
   set_long("This red leatherbound book is written by the Council Masters"+
      " of The Smiths Guild to explain craft of forging to other members"+
      " of the guild.\n");
   add_prop(OBJ_I_NO_GET,1);
   add_prop(OBJ_I_WEIGHT,2000);
   add_prop(OBJ_I_VOLUME,3000);
}

init() {
   ::init();
   add_action("read","read");
   add_action("open","open");
   add_action("close","close");
   add_action("entry","entry");
   add_action("remove","remove");
}

int
read(string str) {
   int i;

   notify_fail("But the book is not opened!\n");

   if ((str=="list") || (str=="scroll")) return 0;

   if (!opened) {
      return 0;
   }

   TO->restore_object(SMITHSDIR_LOG+"book");

   write("You start reading in the "+short()+"...\n");
   say(QCTNAME(TP)+" starts reading in the "+short()+".\n");

   if ((str=="book") || (str=="index")) {
      if (!sizeof(index)) {
         write("There are no pages in the book.\n");
      }
      for (i=0; i<sizeof(index); i++) {
         write("Chapter "+(i+1)+" : "+index[i]+"\n");
      }
      return 1;
   }

   for (i=0; i<sizeof(index); i++) {
      if (index[i]==str) {
         cat(SMITHSDIR_BOOK+index[i]);
         return 1;
      }
   }

   write("It seems there is no such chapter.\n");
   return 1;
}

int
open(string str) {
   notify_fail("Open what?\n");

   if (str!="book") return 0;
   if (opened==1)
      write("But the "+short()+" is already opened!\n");
   else {
      write("You open the "+short()+".\n");
      say(QCTNAME(TP)+" opens the "+short()+".\n");
      opened=1;
   }
   return 1;
}

int
close(string str) {
   notify_fail("Close what?\n");

   if (str!="book") return 0;
   if (!opened)
      write("But the "+short()+" is already closed!\n");
   else {
      write("You close the "+short()+".\n");
      say(QCTNAME(TP)+" closes the "+short()+".\n");
      opened=0;
   }
   return 1;
}

int
entry(string str) {
   notify_fail("");

   if ((str=="list") || (str=="scroll")) return 0;
   
   if (TP->query_skill(SM_MASTER)!=1 ) {
      write("Only masters are allowed to make new entries in the book.\n");
      return 1;
   	 }
   
   if (!opened) {
      write("But the "+short()+" is not opened!\n");
      return 1;
   }

   if (!str) {
      write("What should be the name of the chapter?\n");
      return 0;
   }

   TO->restore_object(SMITHSDIR_LOG+"book");

   index += ({str});

   header=str;

   seteuid(getuid(this_object()));
   
   editor=clone_object("/std/edit");

   editor->edit("done_edit",text);
}

void
done_edit(string text) {
   if (!text) return;
	seteuid(getuid(TO));
   TO->save_object(SMITHSDIR_LOG+"book");

   write("You make a chapter called "+header+".\n");
   say(QCTNAME(TP)+" writes something in the "+short()+".\n");

   write_file(SMITHSDIR_BOOK+header,text);
}

int
remove(string str) {
   notify_fail("The right syntax is <remove chaptername>.\n");

   if ((str=="list") || (str=="scroll")) return 0;

   if ((TP->query_skill(SM_MASTER)!=1)) {
      write("Only masters are allowed to delete entries in the book.\n");
      return 1;
   }

   TO->restore_object(SMITHSDIR_LOG+"book");

   if (!str) {
      write("Remove what chapter?\n");
      return 0;
   }

   index -= ({str});
   rm(SMITHSDIR_BOOK+"str");

   TO->save_object(SMITHSDIR_LOG+"book");

   write("You remove the chapter called "+str+".\n");
   say(QCTNAME(TP)+" removes some pages from the "+short()+".\n");

   return 1;
}

