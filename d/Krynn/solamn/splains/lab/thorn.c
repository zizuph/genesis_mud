/* 
 * A tiny horn as an autoloading item which allows a player to
 * call one of the Krynn dragons to him anywhere in Genesis to
 * let him/herself be transported to one of the normal landing
 * places of the dragon.
 * Actually the bronze dragon takes you to Vingaard Keep and the
 * green dragon takes you to Neraka.
 *
 * Aridor, 09/95
 *
 * Description:
 *   Must solve the (Krynn) ring quest to obtain this item.
 *   Between two uses of the item 24 (RL) hours must pass, otherwise
 *      the horn is lost!
 *   The color of the horn changes from gold to silver when you the
 *      magic of the horn is recharging and you cannot currently call
 *      the dragon without losing the horn.
 *
 */
#include "local.h"
#include <macros.h>
#include <ss_types.h>
#define RECOVER_TIME  200 /* 86400 = 24 RL hours */
#define MANA_USED     300
#define GREEN_DRAGON  "/d/Krynn/neraka/dragon/dragon_room"
#define BRONZE_DRAGON "/d/Krynn/solamn/splains/dragon/dragon_room"
#define DRAGON        (({0,GREEN_DRAGON,BRONZE_DRAGON})[which_dragon])

inherit "/std/object";

int which_dragon = 0;
int last_use = 0;

void
create_object()
{
    add_name("horn");
    set_adj("tiny");
    set_short("tiny horn");
    set_long("This is a tiny @@my_color@@ horn. It is about the size " +
	     "of your hand and it looks like a tube which has been " +
	     "bent and turned around once to make a loop. One end of " +
	     "the tube forms a fairly large opening and the other end " +
	     "has a small opening.\n");

    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,30);
    add_prop(OBJ_I_VALUE,2500);
    add_prop(MAGIC_AM_MAGIC,({ 30,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({}));
    
}

string
my_color()
{
    if (last_use + RECOVER_TIME > time())
      return "silver";
    else
      return "golden";
}

void
set_dragon(string which)
{
    if (which == "green")
      which_dragon = 1;
    else if (which == "bronze")
      which_dragon = 2;
    else
      which_dragon = 0;
}

void
init()
{
    ADA("blow");
}

int
blow(string str)
{
    if (!str)
      return 0;
    
    if (!id(str))
      return 0;
    
    write("You blow the tiny horn with all your force. Strangely enough " +
	  "you cannot hear a sound from it.\n");
    say(QCTNAME(TP) + " blows into a tiny horn, but you cannot hear a sound.\n");
    
    if (E(TP)->query_prop(ROOM_I_INSIDE) ||
	E(TP)->query_prop(ROOM_M_NO_MAGIC))
      {
	  write("You somehow feel that no one has heard your call. This " +
		"doesn't seem to be the right place to make such a call.\n");
	  return 1;
      }

    if (((TP->query_alignment() > 0) + which_dragon == 2) ||
	(random(TP->query_stat(SS_INT)) < random(30)))
      {
	  write("You somehow feel that someone heard your call, yet will not come " +
		"to answer it.\n");
	  return 1;
      }

    if ((last_use + RECOVER_TIME > time()) ||
	(!TP->test_bit("Krynn",KRING_GROUP,KRING_BIT)))
      {
	  write("Something went wrong! There is a strange whistling sound " +
		"coming from the horn......\n");
	  say("Suddenly, a strange whistling sound can be heard from the " +
	      "horn, as though something went wrong.\n");
	  set_alarm(3.0,0.0,"lose_horn",TP);
	  return 1;
      }

    if (TP->query_mana() < MANA_USED)
      {
	  write("You somehow feel that no one has heard your call. You " +
		"don't seem to be mentally strong enough to make such a " +
		"call right now.\n");
	  return 1;
      }

    if (DRAGON->call_dragon(file_name(E(TP))))
      {
	  write("Yet you feel someone heard your call.\n");
	  TP->add_mana(-MANA_USED);
	  last_use = time();
      }
    else
      write("You somehow feel that someone is too busy to attend your call, " +
	    "perhaps you should try again later?\n");
    return 1;
}

void
lose_horn(object who)
{
    set_this_player(who);
    write("...and then the horn crumbles to dust.\n");
    remove_object();
}

string
query_auto_load()
{
    return MASTER + ":" + which_dragon + "," + last_use;
}

void
init_arg(string arg)
{
    int tpe;
    int tme;

    if (sscanf(arg, "%d,%d", tpe, tme) == 2)
    {
	which_dragon = tpe;
	last_use = tme;
    }
}
