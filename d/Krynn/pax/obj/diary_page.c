/*
   diary_page.c
   ------------

   Coded ........: 95/05/02
   By ...........: Jeremiah

   Latest update : 95/05/02
   By ...........: Jeremiah



*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


void
create_object()
{
   set_name(({"paper", "page", "_diary_page_"}));
   set_short("piece of paper");
   set_long("This is an old piece of paper. The paper is faded and the " +
            "writing on it only vaguely visible. It looks as if it has " +
            "been torn from a book, a diary by the look of it. Maybe you " +
            "can read it ?\n");

   add_adj("old");
   
   add_prop(OBJ_I_VALUE,5);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,20);
}


void
init()
{
   ::init();
   add_action("read_paper", "read");
}


int
read_paper(string what)
{
   if(!what)
   {
      write("Read what ?\n");
      return 1;
   }

   if(what != "paper" && what != "page")
   {
      write("What is it you want to read ?\n");
      return 1;
   }

   write("Studying the page closely, you can make out the following text:\n" +
         "\n" +
         "   ....it had been a hard battle. The sun set in a blood-red\n" +
         "   haze, sinking down into the silent forests of Qualinesti.\n" +
         "   All was quiet in Pax Tharkas..............................\n" +
         "   ..........................................................\n" +
         "   ......we entered the fortress some time after the knights\n" + 
         "   had charged through the gates. Many of the last defending\n" + 
         "   dwarves had escaped the charge, because it had been held\n" +
         "   up by a small group of pikesmen, who had stood their ground\n" +
         "   when the gates were breached, stubbornly refusing to budge.\n" +
         "   ..........................................................\n" +
         "   .......................the bodies of hundred or more gully\n" +
         "   dwarves, lying in even rows, rank upon rank. Most still\n" +
         "   held their pikes clutched tightly in their dead hands.....\n" +
         "   ..........................................................\n" +
         "   (Added at the bottom) I don't think anybody ever told about\n" +
         "   the pitiful sacrifice of these poor gullies. No one cared..\n" +
         "\n");

   return 1;
}

