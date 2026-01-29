/* created by Aridor 09/14/93 */

#include "../local.h"

inherit ROOM_BASE

object inqui;

string
query_to_jail()
{
  return "west";
}

void
create_palan_room()
{
    set_short("Inquisitor's office");
    set_long("@@my_long");

    INSIDE;

    add_exit(PALACE + "hall10","west",0,0);
}


my_long()
{
  string str = "This is the inquisitor's office. Hmm, strange, this room "
     + "looks more like a torture room. There are nasty looking instruments "
     + "here, as well as things like whips lying on the desk and boards. "
     + "There are several chairs here as well, providing room for "
     + "whoever wants to watch. Your impression is to better "
     + "behave yourself while you're in the city, you never know "
     + "what will happen once you've been dragged into this room "
     + "unvoluntarily. ";
  if (inqui)
    str += "It seems you have bad "
	+ "luck today, since the inquisitor is actually here.";
  else
     str += "Fortunately, however, there is no one here at the moment.";
  return BS(str,SL);
}

void
reset_palan_room()
{
    seteuid(getuid(TO));
    if (inqui)
      {
	inqui->command("emote leaves for lunch.");
	inqui->remove_object();
      }
    else
      {
	inqui = clone_object(LIV + "inquisitor");
	inqui->move_living("M",TO);
        inqui->command("emote arrives from lunch.");
      }
}
