/* 921016: Dust: lead door for porcia quest */

inherit "/std/door";
#include "/d/Terel/common/terel_defs.h"
#include <macros.h>
#define PORDIR TOWNDIR + "mansion/porcia/"

string desc_text;

void set_desc (string str) { desc_text = str; }

void
init() {
  ::init();
  add_action("do_read","read");
}

int
do_read(string str) {
  notify_fail("Read what?\n");
  if (str != "inscription" && str != "lead" && str != "lead door" &&
	str != "inscription on the lead door" &&
	str != "inscription on lead door" &&
	str != "third inscription") return 0;
  say(QCTNAME(this_player()) + " carefully reads the inscription " +
	"on the lead door.\n");
  write("The inscription on the lead door reads:\n" + desc_text + "\n");
  return 1;
}

create_door() {

  ::create_door();
   set_door_id("leaddoor");
   set_pass_command(({"s", "south"}));
   set_door_name(({"lead door", "door"}));
   set_other_room(PORDIR + "lead_room");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   set_door_desc(break_string("This is a very ancient looking, richly " +
	"decorated door, made of lead. " +
	"Surely it's the work of an artist. In the middle " +
	"of the door you can see an inscription; maybe you should " +
	"read it?\n",70));
   set_open(0);
   set_locked(0);

}


void
reset_door()
{
    if (open_status) {
	do_close_door("The lead door closes magically.\n");
	if (other_door)
	    other_door->do_close_door("The lead door closes magically.\n");
    }
}

