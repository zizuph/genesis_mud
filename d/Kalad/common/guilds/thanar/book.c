/* 
 * /d/Kalad/common/caravan/thanar/book.c
 * Purpose    : Thanar guild info book.
 * Located    : joinroom.c
 * Created By : Antharanos 
 * Modified By: Rico 20.Mar.97; clean up, general improvements 
 */ 

inherit "/std/book";

#include "/d/Kalad/defs.h"

#define  BOOK_DIR(obj)  "/d/Kalad/open/THANAR_INFO/obj"

void
create_book()
{
   set_name("book");
   set_adj("black");
   add_adj(({ "dark", "dark book of thanar", "leather", "leather book" }));
   set_short("black leather book");
   set_long("\n\t\t\tThe Dark Book of Thanar\n"+
      "\t\t\t~~~~~~~~~~~~~~~~~~~~~~~\n\n"+
      "\tThis ancient volume, which rests upon the pillar, is covered\n"+
      "\twith a skin of night-black leather. The spine is engraved with\n"+
      "\tthe words:\n\n"+
      "\t\t'The Thanars'\n\n");

   add_item(({ "pillar" }),
      "\nThe black pillar upon which the book rests is crafted from some "+
      "sort of marble like material. It is so black as to be almost invis"+
      "ible.\n\n");

   set_max_pages(5);

   add_prop(OBJ_I_VALUE, 500);
   add_prop(OBJ_I_WEIGHT, 500);
   add_prop(OBJ_I_VOLUME, 500);
   add_prop(OBJ_M_NO_GET, "\nThe book is firmly secured to the pillar.\n\n");
}

varargs void
read_book_at_page(int which, string verb)
{
   switch(which)
   {
      case 1:
         this_player()->more(BOOK_DIR(page1), 1,
            (int)this_player()->query_prop(PLAYER_I_MORE_LEN));
         break;

      case 2:
         this_player()->more(BOOK_DIR(page2), 1,
            (int)this_player()->query_prop(PLAYER_I_MORE_LEN));
         break;

      case 3:
         this_player()->more(BOOK_DIR(page3), 1,
            (int)this_player()->query_prop(PLAYER_I_MORE_LEN));
         break;

      case 4:
         this_player()->more(BOOK_DIR(page4), 1,
            (int)this_player()->query_prop(PLAYER_I_MORE_LEN));
         break;

      case 5:
         this_player()->more(BOOK_DIR(page5), 1,
            (int)this_player()->query_prop(PLAYER_I_MORE_LEN));
         break;
   }
}



