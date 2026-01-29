/* Book for Telberin Gathering Hall Library  */
inherit "/std/book";

#include "default.h"
#include <stdproperties.h>

void
create_book()
{
    add_prop(OBJ_M_NO_GET, "The book's brass binding is bolted down.\n"
    +"Evidently, books are taken quite seriously in Telberin.\n");
    set_long("A Royal History.\n");
    set_short("history book");
    set_name("book");
    add_adj("history");
    set_max_pages(1);
    seteuid(getuid());
}

varargs void
read_book_at_page(int which, string verb)
{
    if (verb != "mread")
  cat(THIS_DIR + "history.txt");
    else
  clone_object("/std/board/board_more")->more(THIS_DIR + "history.txt", 1);
}

