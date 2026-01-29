/* Logbook for bury bones quest
 *  Cirion 040996
 */
inherit "/d/Avenir/inherit/book";

#include "/d/Avenir/include/book.h"
#include "/d/Avenir/common/port/bury_bones.h"

create_book()
{
  set_name("logbook");
  add_name(({"book","log",LOGBOOK_ID}));
  set_adj(({"battered","leather"}));
  set_short("battered leather book");

  set_long("It is a thick book, its sturdy leather "
    +"cover worn by age. The pages are made from "
    +"heavy parchment, stained by water but otherwise "
    +"readable. On the cover of the book is stenciled in "
    +"gold leaf: SS Concubine\n");
  
  text_file("/d/Avenir/common/bazaar/Obj/books/logbook.book", 1);
  set_book_type(BOOK_BTEXT);
  set_lang_to_read(15);
  set_max_pages(59);
}
