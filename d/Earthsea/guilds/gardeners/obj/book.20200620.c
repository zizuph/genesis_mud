#pragma strict_types
#pragma no_inherit

inherit "/std/book";

#include "../defs.h"
#include <stdproperties.h>

#define BOOK_ADJ "@@my_book_adj@@"

public string
index_page()
{
   object tp = environment(this_object());
   string index_page = "\n     Page     Topic\n" +
      "     ======== ==============================\n\n",
      name = tp->query_real_name(),
      *subjects = m_indices(restore_map(MEMBER_JOURNAL(name)));
   int i, sz = sizeof(subjects);

   set_max_pages(sz + 1);

   for(i = 0; i < sz; i++)
   {
      index_page += sprintf("     %-8d %-30s\n", (i+2),
         implode(explode(subjects[i], "_"), " "));
   }

   index_page += "\n";

   return index_page;
}

varargs void
read_book_at_page(int page, string verb)
{
   string name, *subjects, *lines, text;
   object tp = environment(this_object());
   mapping journal;
   int i, sz;

   if(page == 1)
   {
      tp->more(index_page());
      return;
   }

   name = tp->query_real_name();
   journal = restore_map(MEMBER_JOURNAL(name));
   subjects = m_indices(journal);
   lines = journal[subjects[page-2]];
   text = "";
   sz = sizeof(lines);

   for(i = 0; i < sz; i++)
   {
      text += lines[i] + "\n";
   }

   tp->more(text);
}

public string
my_book_adj()
{
   int i = 0, title;

   for(i=0; i < GARDENER_NUM_TITLES; i++)
   {
      if(GARDENER_TITLES[i] = environment()->query_guild_title_lay())
      {
         return GARDENER_BOOKS[i];
      }
   }

   return GARDENER_BOOKS[0];
}

public void
create_book()
{
   add_name(GARDENER_JOURNAL_ID);
    add_name("journal");
   add_adj(BOOK_ADJ);
   set_short(BOOK_ADJ + " leather book");
   set_long("This is your Gardeners' Journal, a well-fingered leather " +
      "book filled with information on herbs you have come into " +
      "contact with. For more information, type 'help gardener'.\n");
   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_STEAL, 1);
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_M_NO_GIVE, 1);
   setuid();
   seteuid(getuid());
}

public string
query_auto_load()
{
   return GARDENER_JOURNAL_OBJ;
}

public void
init()
{
    ::init();
    add_action(read_scroll, "lturn");
}

public void
read_it(string verb)
{
    switch (verb)
    {
    case "lturn":
        turn_me(); break;
    default:
        ::read_it(verb); break;
    }
}
