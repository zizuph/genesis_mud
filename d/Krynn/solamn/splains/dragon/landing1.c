/* Original by Percy and Nick
 * New easier to handle Version of the dragon, by Aridor. */

#include "local.h"
#include "../local.h"

inherit OUTSIDE_BASE;
inherit STD_DRAGON + "landing";

#include <ss_types.h>
#include <macros.h>

void
create_splains_room()
{
    set_short("Circle marked with stones");
    set_long("You are standing in a circle marked with small stones. " +
	     "A path leads outside the circle to a crossroads in the " +
	     "west. To the north you can see a mighty fortress rising " +
	     "up towards the sky. Further east you can see the mighty Vingaard " +
	     "River, the water gleaming in the sunlight. You notice " +
	     "that there is a pier at the river a little south of " +
        "here. There is a sign nailed to a post.\n");
/*
	     "here. There is a post on the edge of the circle and " +
	     "hanging from the post is a bronze horn. There is also " +
	     "a sign nailed to the post.\n");
*/
    
    add_exit(CONNECTION1a, DIRECTION1a);
    add_exit(CONNECTION1b, DIRECTION1b);
    
    add_item(({"keep", "castle", "walls", "wall", "stronghold"}), "@@keep");
    add_item(({"post", "wooden post"}), "It is a simple wooden post.\n");
/*
    add_item(({"horn", "bronze horn"}), "It is a horn made of bronze, chained to the post.\n");
*/
    add_item("sign", "Its a sign for people to read.\n");
    
/*
    (LANDING2)->load_me();
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
    if (str != "sign")
      return 0;
    write("You read the sign.\n");
    write(BS("If the good dragons were to return to Krynn, this " +
        "would be a good place for them to land. As it is, you'll " +
        "have to find some other way of leaving these Plains.", 70));
/*
    write(BS("Here you can <blow horn> to summon a dragon that"
	     + " will take you to Solace. You can then <mount dragon> and"
	     + " when you are on it <kick dragon> to tell it to go.", 70));
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
*/




/* add_item descriptions. */
keep()
{
    write(BS("The keep is very ancient and has withstood the test of time"
	     + " just as much as it has withstood numerous battles. The keep is"
	     + " the stronghold for the solamnian knighthood, a powerful army"
	     + " of knights devoted to the cause of the good deity Paladine.", 70));
    return "";
}

