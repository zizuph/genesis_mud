inherit "/std/room";
#include "/d/Calia/abbrev.h"
string messages;
int new_mail;
 
void
create_room()
{
    set_short("Zima's Study");
 
    set_long(break_string(
        "This triangular chamber of black marble is Zima's study.  " +
        "An oak desk and chair sit along the northern wall, where " +
        "Zima sits and reads.  A tall bookcase, carved of olive wood " +
        "by the finest craftsmen of Argos, sits along the southeastern " +
        "wall, filled with books.  A blue banner, embroidered with " +
        "a crest, hangs from a rod of gold on the southwestern wall, " +
        "while a cruci-crescent is placed on the wall above the desk.  " +
        "A mysterious symbol is crafted of white ivory into the floor " +
        "of the chamber.  " +
        "An arched passageway, framed in shining silver, leads to " +
        "the central chamber to the northwest.\n",70));
 
    add_item(({"desk","chair"}), break_string(
        "Made of polished oak, this heavy desk looks as if it has " +
        "been used alot, though well-kept.\n",70));
 
    add_item("bookcase", break_string(
        "Made of olive wood, the bookcase reaches to the ceiling of " +
        "the chamber, its shelves filled with books of many titles.\n",70));
 
    add_item("books", break_string(
        "Sitting on the shelves of the bookcase, some look very ancient " +
        "while others look recently published.  You can make out the " +
        "titles of some of the books, but others are written in " +
        "unknown languages.\n",70));
 
    add_item("titles", break_string(
        "Written across the spine of books in the bookcase, you can make " +
        "out some of the titles, including 'The Chronicles of Argos', " +
        "'The Paedagogus', 'The Travels of Alexis', and " +
        "'The Wheel of Time' by Robert Jordan.  The rest of the titles " +
        "are illegible or are baffling runes.\n",70));
 
    add_item(({"banner","crest"}), break_string(
        "Hanging from a rod of gold on the southwestern wall is a " +
        "banner of royal blue, embroidered with a crest, consisting " +
        "of a sheild emblazoned with a rampant winged horse, surmounted " +
        "by a crown adorned with three jewels.  You recognize this as " +
        "the crest of Argos, of which Zima is the Hierophant, or " +
        "spiritual advisor.\n",70));
 
    add_item("symbol", break_string(
        "Crafted into the black marble floor with white ivory, this " +
        "mysterious symbol is the greek letter NU.\n",70));
 
    add_item("passageway", break_string(
        "An arched entrance, framed with shining silver, which leads " +
        "back into the central chamber.\n",70));
 
    add_item("cruci-crescent", break_string(
        "A fraternal symbol made of gold, it looks like:                    "+
        "                                                                   "+
        "                                  +---------+                      "+
        "                                  |         |  ++                  "+
        "                                  |         |   ++++               "+
        "                                  |         |    ++++++            "+
        "                                  |         |     +++++++          "+
        "                                  |         |      ++++++++        "+
        "                  +---------------+         +---------------+      "+
        "                  |                                         |      "+
        "                  |                                         |      "+
        "                  |                                         |      "+
        "                  +---------------+         +---------------+      "+
        "                    ++            |         |     +++++++++        "+
        "                     ++++         |         |   ++++++++++         "+
        "                      +++++++     |         |++++++++++++          "+
        "                        ++++++++++|         |++++++++++            "+
        "                          ++++++++|         |++++++++              "+
        "                               +++|         |+++                   "+
        "                                  +---------+                      "+
         "\n",66));
 
    add_exit("/d/Calia/zima/workroom","northwest",0);
}
 
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (from == this_object()) return; 
   if (present("mailreader", ob)) return;
   clone_object("/secure/mail_reader")->move(ob);
}
 
leave_inv(ob, to) {
   object reader;
 
   ::leave_inv(ob, to);
   if (to == this_object()) return;
   reader = present("mailreader", ob);
   if (reader) reader->remove_object();
}
 
query_mail(silent) {
   string name;
   string new;
 
   name = lower_case(this_player()->query_name());
   if (!restore_object("/d/Genesis/post_dir/"+name) || messages == "")
      return 0;
   if (silent)
      return 1;
   new = "";
   if (new_mail)
      new = " NEW";
   write("\n"+
      "********************************************************\n"+
      "There is"+new+" mail waiting for you in the nearest PO. \n"+
      "********************************************************\n\n");
   return 1;
}
