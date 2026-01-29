/*
 *  Hin Warrior Library, the part where the guildbooks are kept.
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/open/randomize.h" /* for random colours and books */
#include "defs.h"

void
create_room()
{
   set_short("Library");
   set_long(break_string(
      "You are in the middle of a library in the inner parts of the "
    + "mountain. The walls are lined with shelves containing ancient "
    + "tomes and scrolls. This part of the library contains spellbooks "
    + "and magical tomes. There are numerous types of "
    + "books, in many different colours. One tome catches your attention, "
    + "it is labeled 'index'. The other part of the library lies to "
    + "the east.\n",70));

   add_item(({"shelf","shelves"}), break_string(
      "The shelves form a kind of bookcase. They all have been fastened "
    + "to the walls and bear hundreds of rare books and tomes.\n",70));

   add_item(({"book","books","tome","tomes"}), break_string(
      "Most of the books are very old. They all are dusted on a regular "
    + "basis by the librarian of the Hin Warriors, who takes care of this "
    + "precious library.\n",70));

   add_exit(HINROOM_DIR + "libr1","east");

   add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

void
init()
{
   ::init();
   add_action("do_read","read",0);
}

string
the_index()
{
   int i;
   string index, *books;

   index =
      "You take the thick tome labeled 'index' from a shelf and read:\n\n"
    + "   Behold, ye reader! As thou mayst search very long I Kusak,\n"
    + "   librarian of the Hin Warrior Guild, have written down the\n"
    + "   books that are of most importance to thee:\n\n";
    
   seteuid(getuid());
   books = get_dir(HIN_DIR + "SPELL_BOOKS/*");
   books = books[2..sizeof(books)];  /* Remove "." and ".." */
   while (sizeof(books)%6)
      books += ({ " " });

   for (i=0; i < sizeof(books); i += 6)
   {
      index += sprintf("   %-11s %-11s %-11s %-11s %-11s %-11s\n",
                       capitalize(books[i]), capitalize(books[i+1]),
                       capitalize(books[i+2]), capitalize(books[i+3]),
                       capitalize(books[i+4]), capitalize(books[i+5]));
   }
   index += "\n";

   return index;
}

int
do_read(string str)
{
   string colour,type;

   if (!str || str == "")
      return 0;

   str = lower_case(str);

   if (str == "index")
   {
      write(the_index());
      say(QCTNAME(this_player()) + " takes the thick tome labeled 'index' "
        + "from a shelf and starts to study it.\n");
      return 1;
   }

   if (file_size(HIN_DIR + "SPELL_BOOKS/" + str) > 0)
   {
      colour = random_colour();
      type = random_book();
      write("You take out a " + colour + " " + type + " from a shelf and "
          + "read:\n\n");
      say(QCTNAME(this_player()) + " takes a " + colour + " " + type
        + " titled '" + capitalize(str) + "' from a shelf and starts to "
        + "study it.\n");
      cat(HIN_DIR + "SPELL_BOOKS/" + str);
      write("\n");
      return 1;
   }
   return 0; /* Enable people to read notes as well */
}
