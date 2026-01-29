/*
 * Khalakhor journal
 * Tapakah, 07/2021
 */

#include <stdproperties.h>

inherit "/std/book";

string title = "Khalakhor Journal";

string page_dir = "/d/Khalakhor/open/project/journal/";

void
reset_scroll ()
{
  ::reset_scroll();
  int page_files = sizeof(get_dir(page_dir));
  set_max_pages(page_files);
}

void create_book ()
{
  set_name("journal");
  set_adj("wooden-bound");
  set_short("wooden-bound journal");
  set_long("A thin wooden-bound journal decorated by runes.\n");
  add_item("runes",
           "You figure out the journal has some information "+
           "about the domain.\n");
  add_prop(OBJ_M_NO_GET, "The journal is fastened to the wall.\n");
  setuid();
  seteuid(getuid());
  reset_scroll();
}
 
string
read_book_at_page (int which)
{
  string page_file = page_dir + which + ".txt";
  seteuid(getuid());
  return read_file(page_file);
}
 
void
read_it (string verb)
{
  switch (verb) {
  case "read":
  case "mread": {
    if (book_is_closed)
      write("The " + short() + " is closed.\n");
    else
      write(read_book_at_page(what_page));
    break;
  }
  case "turn":
    turn_me();
    break;
  case "open":
    open_me();
    break;
  case "close":
    close_me();
    break;
  }
}
