inherit "/std/room";
#include <stdproperties.h>

string messages;
int new_mail;

#define PATH "/d/Terel/mecien/valley/city/"

create_room() {
  set_short("Postal Station");
  set_long(
   "This brilliantly lit chamber smells of ink and freshly dried\n"
  +"parchment. Large lanterns of glass hang from the ceiling, adding\n"
  +"burning oil to the strength of the smells here. It is a nicely\n"
  +"built room, dark oaken walls and supported roof. A larger counter\n"
  +"stands at the west side of the chamber, a large barred window is\n"
  +"set into it. A sign hangs over the window.\n"
   );
   add_item("sign", "It has writing upon it.\n");
  add_cmd_item("sign", "read", "@@sign");
  add_item("window", "It is a barred window. Behind it the mail is kept\n"
   + "and there the postmaster sorts the mail.\n");
   add_item("bars", "They are very strong.\n");
  add_item("walls", "They are made of dark oak.\n");
  add_item("lanterns", "They are glass, fueled by oil. They are very bright.\n");
   add_item("counter", "It is oak and spans the length of the west wall.\n"
  + "A window is set just above it.\n");
  add_item("desks", "They are fine oak, used for writing letters.\n");

add_exit(PATH + "street4", "east", 0);
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
