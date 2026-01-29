/* created by Aridor 03/09/94 */
/* Aug 27, 2018: Added no-scry protection in guild (Gorboth) */

#include "../local.h"

inherit ROOM_BASE

#include <stdproperties.h>

#define OTHER    CAVERN + "har2"

void
create_thief_room()
{
  set_short("In a cavern.\nA door is leading north.\n" +
	   "There is one obvious exit: south");
  set_long("This is a hallway leading south.\n" +
	   "A door is leading north.\n" +
	   "There is one obvious exit: south.\n");
  
  set_noshow_obvious(1);

    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

  add_exit(GUILDR + "chapel","south");
  add_exit(OTHER,"north","@@thieves_only");

  LIGHT;
}

int
thieves_only()
{
  SAY(" opens the door.");
  tell_room(OTHER,"The door opens.\n");
  write("You open the door, walk through, and close the door again.\n");
  set_alarm(0.0,0.0,"close_again",TP);
  return 0;
}


close_again(object who)
{
  tell_room(TO,"The door closes again.\n");
  TELL_ROOM(OTHER, who, " closes the door.\n", who);
}
