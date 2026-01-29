/* Original by Percy and Nick
 * New easier to handle Version of the dragon, by Aridor. */

#include "local.h"
#include "../local.h"

inherit "/d/Krynn/solace/std/outside_base";
inherit STD_DRAGON + "landing";

#include <ss_types.h>
#include <macros.h>


void
create_solace_room()
{
    set_short("On a plain");
    set_long("You are standing in the middle of a small clearing. The " +
	     "clearing is surrounded by mighty vallenwoods. To the south " +
	     "you notice an almost hidden track leading on to a small " +
	     "path. Looking up, you see a wooden bridge-walk, that runs " +
	     "from tree to tree, allowing people to walk high above the " +
	     "ground among the trees. This is the outer parts of " +
	     "Solace, the tree village. However, there is a sign planted " +
	     "in the ground here, perhaps it can tell you what this place " +
        "is used for?\n");
/*
	     "is used for? Next to the sign hangs a horn.\n");
*/
    
    add_exit(CONNECTION2, DIRECTION2);
    
/*
    add_item(({"horn", "bronze horn"}), 
	     "It's a beautifully carved bronze horn with a picture of " +
	     "a dragon on it.\n");
*/
    add_item("sign", "Its a sign, probably readable.\n");
    
/*
    (DRAGON_ROOM)->load_me();
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_prop(OBJ_S_WIZINFO,
	     "Here one can fly with a dragon to Solace. If you blow the horn it " +
	     "will come here (if not occupied elsewhere) and you can mount it. " +
	     "Don't update this room or the dragon unnecessary since it can mess " +
	     "things up.\n");
*/
    OUTSIDE;
}



/* Functions to allow player transport to solace via dragon */
init()
{
    ::init();
    ADA("read");
/*
    ADA("get");
    ADA("blow");
*/
}

/*
int
get(string str)
{
    if ((str == "horn") || (str == "the horn") || (str == "bronze horn"))
      {
	  write("You feel some force keeping the horn where it should be.\n");
	  return 1;
      }
    return 0;
}
*/


/* allows the sign to be read */
int
read(string str)
{
    NF("Read what?\n");
    if (str != "sign" && str != "letters")
      return 0;
    write("You read the sign.\n");
    write("If good dragons ever returned to Krynn, one might take " +
        "you to Vingaard Keep if it ever landed here. As it is, " +
        "you'll have to take the boat to Palanthas from Newports.\n");
/*
    write("A bronze dragon lands here that can take you to Vingaard Keep. " +
	  "If the dragon isn't here, just blow the horn.\n");
*/
    say(QCTNAME(TP) + " reads the sign.\n");
    return 1;
}


/* Handles blowing the horn to summon the dragon */
/*
int
blow(string str)
{
    NF("Blow what?\n");
    if ((str == "horn") || (str == "the horn") || (str == "bronze horn"))
      {
	  write(BS("You blow the horn with all your force. Strangely enough " +
		   "you cannot hear a sound from it.", 70));
	  say(QCTNAME(TP) + " blows the horn, but doesn't produce much sound.\n");
	  seteuid(getuid(TO));
	  if (call_dragon_to_here())
            write("Yet you feel someone heard your call.\n");
	  else
            write(BS("You somehow feel that someone is too busy to attend " +
		     "your call, perhaps you should try again later?", 70));
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
*/







