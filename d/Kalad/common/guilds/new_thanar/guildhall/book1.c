/**********************************************************************
 * - book.c                                                         - *
 * -                                                                - *
 * - ReCreated by Damaris@Genesis 3/2004                            - *
 **********************************************************************/

#pragma strict_types
inherit "/std/book";
#include <stdproperties.h>
#include "guild.h"

#define  BOOK_DIR  GUILD_DIR + "book/"

void
create_book()
{
   set_name("book");
   set_adj("black");
   add_adj(({ "dark", "dark book of thanar", "leather", "leather book" }));
   set_short("black leather book");
   set_long("\n"+
      "                 The Enlightened Book of Thanar\n"+
      "                 ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"+
      "          This ancient volume, which rests upon the pillar,\n"+
      "          is covered with a skin of hallowed leather. The\n"+
      "          spine is engraved with these words:\n\n"+
      "                 'The Most Holy Clerics of Thanar'\n\n");

   add_item(({ "pillar" }),
      "\nThe black pillar upon which the book rests is crafted from some "+
      "sort of marble like material. It is so black as to be almost invis"+
      "ible.\n\n");

   set_max_pages(6);

   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_M_NO_GET, "\nThe book is firmly secured to the pillar.\n\n");
}

varargs void
read_book_at_page(int which, string verb)
{
   string pagefile;

   switch(which)
   {
      case 1:
         setuid();
         seteuid(getuid());
         pagefile = read_file(BOOK_DIR + "page1");
         break;

      case 2:
         setuid();
         seteuid(getuid());
         pagefile = read_file(BOOK_DIR + "page2");
         break;

      case 3:
         setuid();
         seteuid(getuid());
         pagefile = read_file(BOOK_DIR + "page3");
         break;

      case 4:
         setuid();
         seteuid(getuid());
         pagefile = read_file(BOOK_DIR + "page4");
         break;

      case 5:
         setuid();
         seteuid(getuid());
         pagefile = read_file(BOOK_DIR + "page5");
         break;
         
      case 6:
         setuid();
         seteuid(getuid());
         pagefile = read_file(BOOK_DIR + "page6");
         break;
   }

   if(stringp(pagefile))
      TP->more(pagefile,0);
   return;
}