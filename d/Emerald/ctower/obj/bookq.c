/* ctower/obj/bookq.c is cloned by ctower/glib1.c */
inherit "/std/book";
 
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include "../ctower.h"
 
void
create_book()
{
  add_prop(OBJ_M_NO_GET, "The book is stuck here!\n");
  set_long("Book of Quests.\n");
  add_adj("quest");
  set_name("book");
  set_short("quest book");
  set_max_pages(1);
  seteuid(getuid());
}
 
varargs void
read_book_at_page(int which, string verb)
{
  string txt = CTOWER_LOG + "quest.txt";

  if (verb != "mread")
  {
    cat(txt);
  }
  else
  {
    clone_object("/std/board/board_more")->more(txt, 1);
  }
}
