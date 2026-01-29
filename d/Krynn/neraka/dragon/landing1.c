/* Solace coded by Nick */

#include "local.h"

inherit "/d/Krynn/solace/std/outside_base";
inherit STD_DRAGON + "landing";

#include <macros.h>

void
create_solace_room()
{
    set_short("On a platform");
    set_long("You are standing on a platform. It seems someone has built it " +
             "for some reason, but the reason isn't obvious to you. " +
             "However, there is a sign suspended in the air here, and it " +
             "may be able to tell you what the platform is used for. " +
             "Next to the sign floats a horn.\n");

    add_item("platform","The platform is large, as if something " +
             "large landed on it from time to time.\n");
    add_item("sign", "It's a sign, probably readable.\n");
    add_item("horn", "It's a beautifully carved horn with a picture of a " +
	     "dragon on it.\n");

    add_exit("/d/Krynn/tant/room/road16", "southeast", 0, 1);

    (DRAGON_ROOM)->load_me();

    OUTSIDE;  /* An outside room */

    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(OBJ_S_WIZINFO,
	     "Here one can fly with a dragon to Neraka. If you blow the horn it\n" +
	     "will come here (if not occupied elsewhere) and you can mount it.\n" +
	     "Don't update this room or the dragon unneceesary since it can\n" +
	     "mess things up.\n");
}

void
init()
{
    ::init();
    ADA("read");
    ADA("get");
    ADA("blow");
}

int
read(string str)
{
    NF("Read what?\n");
    if ((str == "sign") || (str == "letters"))
      {
	  write("This is the dragon airport built by the Nerakian Office of\n");
	  write("Foreign Relations, ordered by a Dragon Highlord. You might\n");
	  write("find a dragon here to help you get to Neraka.\n");
	  write("If the dragon isn't here, just blow the horn.\n");
	  say(QCTNAME(TP) + " reads the sign.\n");
	  return 1;
      }
    return 0;
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

int
block()
{
    write("The tree village Solace is under attack by dragons and " +
	  "draconians. The wizards of Krynn, has yet again, gone into " +
	  "battle to defend their creation. The battle will go on for " +
	  "several hours, since the wizards are few and the dragons are " +
	  "many. The only thing you can do is to pray to the gods and " +
	  "give them all the support you can.\n");
    return 1;
}







