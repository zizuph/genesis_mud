/* ctower/obj/bookc.c is cloned by ctower/blib1.c */
inherit "/std/book";
 
#include "/d/Emerald/defs.h"
#include <stdproperties.h>
#include "../ctower.h" 

void
create_book()
{
  add_prop(OBJ_M_NO_GET, "The book is stuck here!\n");
  set_long("Book of Caverns.\n");
  set_short("cavern book");
  set_name("book");
  add_adj("cavern");
  set_max_pages(1);
  seteuid(getuid());
}
 
varargs void
read_book_at_page(int which, string verb)
{
  string txt = CTOWER_LOG + "cavern.txt";

  if (verb != "mread")
  {
    cat(txt);
  }
  else
  {
    clone_object("/std/board/board_more")->more(txt,1);
  }
}
