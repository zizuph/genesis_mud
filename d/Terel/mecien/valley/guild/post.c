/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>

string messages;
int new_mail;

create_room() {
   set_short("Script Chamber");
   set_long(
   "This stone chamber, is shadowy and small, its ceiling is\n"
  +"is supported by wooden arches. A large writing desk stands\n"
  +"at the far end, covered with parchment and quills. Longer,\n"
  +"but smaller desks fill the rest of the chamber, next to each\n"
  +"a candle housed in a wooden box.\n"
   );
  
   add_exit("/d/Terel/mecien/valley/guild/u_hall1", "east", 0);

   add_item(({"candles", "candle", "box", "wooden box"}),
    "These wooden boxes house plain white candles that illuminate\n"
   + "the chamber.\n");
add_item(({"smaller desk", "desks"}), "They are used for writing.\n");
   add_item("arches", "They are dark wood and support the ceiling.\n");
   add_item("desk", "It is used for writing. It is made from a beautiful\n"
   + "dark wood. Upon it are quills and pieces of parchment.\n");
   add_item("quills", "They are used to write.\n");
   add_item("parchment", "A rich type of paper.\n");
   add_item("ceiling", "It is supported by arches.\n");
}

init() {
	::init();
        clone_object("/secure/mail_reader")->move(this_player(), 1);
}

leave_inv(ob, to) {
    object reader;
    ::leave_inv(ob); /* , to); */

    reader = present("mailread", ob);
    if (reader) reader->remove_object();

}
