/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP  this_player()
#define TO  this_object()

public int check_name(object who);

static object acolyte=0;

public void
reset_room()
{
    if (acolyte) return;
   
    acolyte = clone_object(GUILD_DIR + "acolyte");
    acolyte->move_living("M", TO);
    acolyte->set_chat_time(1);
    acolyte->add_chat("If you seek the ways of Antiquity, make yourself known");
}

public void
init()
{
    ::init();
    add_action("do_write", "write");
    if (MEMBER(TP) && TP->query_mystic_office() == OFFICE_NOVICES) {
        add_action("do_erase", "erase");
    }
}

public void
create_room()
{   
   set_short("Antechamber");
   set_long(
      "This small stone hall is dark and filled with shadows. The walls are " +
      "smooth dark stone, lined with silver sconces. In the center of this hall " +
      "is a silver dias, upon which is a book.\n");
   
   add_item("book", "It is a small book of parchment.\n");
   add_cmd_item("book", "read", "@@do_read");
   
   add_item("dias", "It is made of wood overlaid with silver.\n");
   add_item("walls", "They are cold dark stone.\n");
   add_item("sconces", "They are silver and flicker with tiny lights.\n");
   
   add_exit(GUILD_DIR + "chamber", "east", 0);
   reset_room();   
}

public int
do_write(string str)
{
   notify_fail("Write what?\n");
   if (!str) return 0;
   if (str != "my name in book" && str != "my name" && str != "name" &&
       lower_case(str) != lower_case(TP->query_name()))
       return 0;
       
   if (check_name(TP)) {
       write("Although you cannot read the names in the book, you sense " +
             "your name is already there.\n");
       return 1;
   }
       
   write("You write your name in the book.\n");
   say(QCTNAME(TP) + " writes in the book.\n");
   seteuid(getuid(TO));
   write_file(SEEKERS, TP->query_name() + "\n");
   return 1;
}

public string
do_read()
{   
   if (!MEMBER(TP) || TP->query_mystic_office() != OFFICE_NOVICES)
       return "It seems to contain names, but they are obscure.\n";
   
   write("I seek the Order, by name of \n");
   if (file_size(SEEKERS) > 0)
      write(read_file(SEEKERS));
   return "";
}

public int
do_erase(string str)
{
   string *names;
   int i, nerase=0;
   
   if (!MEMBER(TP) || TP->query_mystic_office() != OFFICE_NOVICES) return 0;
   notify_fail("Erase whom?\n");
   if (!str) return 0;
   
   seteuid(getuid());
   if (file_size(SEEKERS) == -1) return 0;
   names = explode(read_file(SEEKERS), "\n");
   rm(SEEKERS);
   for (i=0; i<sizeof(names); i++) {
      if (lower_case(str) != lower_case(names[i]))
          write_file(SEEKERS, names[i] + "\n");
      else
          nerase++;
   }
   
   if (nerase == 0) return 0;
   
   write("You have erased " + capitalize(str) +
         " from the Book of Seekers.\n");
   say(QCTNAME(TP) + " does something with the book.\n");
   return 1;
}

public int
check_name(object who)
{
   string *names;
   
   if (!who) return 0;
   
   seteuid(getuid());
   if (file_size(SEEKERS) == -1) return 0;
   names = explode(read_file(SEEKERS), "\n");
   
   if (member_array(who->query_name(), names) >= 0) return 1;
   
   return 0;   
}

