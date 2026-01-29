/* a set of functions to inherit in your room to make it work as
   the librarian's office */

mapping *books;
static string lsave,lib;

#include "/d/Roke/common/defs.h"

check_desc()
{
  if(sizeof(m_indexes(books)))
    TO->add_my_desc("You notice a few books waiting for approval.\n",TO);
  else
    TO->remove_my_desc(TO);
}

void set_lsave(string s)
{
  lsave = s;
}

void set_lib(string s)
{
  lib = s;
}

config_librarian()
{
  seteuid(getuid(TO));
  books=([]);

  restore_object(lsave);

  check_desc();
}

add_book(string nbnam,string nbdesc,string fnam,int flag)
{
  if(!books[nbnam])
    books[nbnam]=({nbdesc,fnam,flag});
  else
    write("Too bad. That book already exists.\n");

  tell_room(this_object(),"Someone has just added a book to the library.\n");
  seteuid(getuid(TO));
  save_object(lsave);
  check_desc();
}

init_lib()
{

    add_action("list_books","list");
    add_action("read_book","read");
    add_action("remove_book","toss");
    add_action("abook","add_book");
  }

abook(string s)
{
  notify_fail("That book doesn't exist.\n");
  if(!books[s])
    return 0;
  
  lib->add_book(s,books[s][0],books[s][1],books[s][2]);
  write("You add the book to the library.\n");
  books = m_delete(books,s);
  seteuid(getuid(TO));
  save_object(lsave);
  check_desc();
  return 1;
}
  
read_book(string s)
{
  notify_fail("That book doesn't exist.\n");

  if(!books[s])
    return 0;

  cat(books[s][1]);
  write("\n");
  return 1;
}

remove_book(string s)
{
  notify_fail("That book doesn't exist.\n");
  if(!books[s])
    return 0;

  rm(books[s][1]);

  books = m_delete(books,s);
  seteuid(getuid(TO));
  save_object(lsave);
  write("You toss the book in the trashcan.\n");
  check_desc();
  return 1;
}

list_books(string s)
{
  int i;
  string *apa;

  notify_fail("List what?\n");
  if(s!="books")
    return 0;

  apa = m_indexes(books);
  
  if(!sizeof(apa))
    write("There are no books here.\n");
  else
    write("Books waiting to be accepted:\n");

  for(i=0;i<sizeof(apa);i++)
    write(apa[i]+": "+books[apa[i]][0]+"\n");

  return 1;
}

