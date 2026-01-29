/* Neraka coded by Nick */

#include "local.h"

inherit "/d/Krynn/neraka/std/outside_base";
inherit STD_DRAGON + "landing";

#include <macros.h>

void
create_neraka_room()
{
    set_short("In front of a bridge");
    set_long("You are standing in some mountains, you feel the wind in your hair. " +
	     "North you can see a small river and over it spans a bridge. Behind " +
	     "the bridge you can see a small city. This is also a small dragon " +
	     "airport. Every now and then a dragon might land to take you off " +
	     "to Tantallon. An image of a horn is floating in the air.\n");

    add_item(({"city", "town"}),
	     "You can't see much of it, maybe if you go north to the bridge " +
	     "you'll get a better look of it.\n");
    add_item("bridge",
	     "It's an old fashioned stone bridge, it looks quite safe.\n");
    add_item("river",
	     "The river runs from east to west. The only way to cross it is on " +
	     "that bridge.\n");
    add_item("mountains",
	     "They are just very very big, nothing interesting.\n");
    add_item("horn",
	     "It's just hanging there by some magic force. It has the image of " +
	     "dragon on it.\n");
    
    add_exit(CONNECTION2, DIRECTION2);
    
    (DRAGON_ROOM)->load_me();
    
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(OBJ_S_WIZINFO,
	     "Here one can fly with a dragon to Tantallon. If you blow the " +
             "horn it " +
	     "will come here (if not occupied elsewhere) and you can mount it. " +
	     "Don't update this room or the dragon unnecessary since it can mess " +
	     "things up.\n");
}

void
init()
{
    ::init();
    ADA("get");
    ADA("blow");
}

int
get(string str)
{
    if ((str == "horn") || (str == "the horn"))
      {
	  write("You feel some force keeping the horn where it should be.\n");
	  return 1;
      }
    return 0;
}

int
blow(string str)
{
    NF("Blow what?\n");
    if ((str == "horn") || (str == "the horn"))
      {
	  write("You blow the horn with all your force. Strangely enough " +
		"you cannot hear a sound from it.\n");
	  say(QCTNAME(TP) + " blows the horn, but doesn't produce much sound.\n");
	  seteuid(getuid(TO));
	  if (call_dragon_to_here())
            write("Yet you feel someone heard your call.\n");
	  else
            write("You somehow feel that someone is too busy to attend " +
		  "your call, perhaps you should try again later?\n");
	  return 1;
      }
    return 0;
}

