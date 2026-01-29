
/*
 * BT4.c
 * Bell Tower in the Ruins of Kamesh
 * - Alaron January 1997
 */

#include "default.h"

#define TELLROOMS ({ MONKRUIN_DIR + "mr1", MONKRUIN_DIR + "bt1", \
                      MONKRUIN_DIR + "bt2", MONKRUIN_DIR + "bt3", \
                      MONKRUIN_DIR + "bt4" })

inherit "/std/room";

int do_pull(string str);
int do_jump(string str);

void ring_bell();
int bell;
int ring_count;

void
create_room()
{
  set_short("Top of a Bell Tower");
  set_long("   The small room at the top of the tower feels even smaller "+
	   "as a result of the massive bell taking up the center of "+
	   "the room. The room's west wall is open to crumbling, nearly-"+
	   "fallen wooden flaps which may have at one point been able "+
	   "to open and close to modify acoustics. A huge, thick rope "+
	   "hangs down from inside the bell. This rope is most likely the "+
	   "rope that, when pulled, would cause the bell to sway back and "+
	   "forth and create a tremendously loud ringing. An iron staircase "+
	   "leads down out of the bell tower through a circular hole in "+
	   "the stone floor.\n\n");

  add_prop(ROOM_I_INSIDE, 1);

  add_item( ({"bell", "massive bell", "huge bell"}),
	    "The huge bell dominating the center of the room may "+
	    "have been made of bronze. It is so green and covered "+
	    "with fungus and other signs of decay that the original "+
	    "material that the bell was constructed from is not "+
	    "immediately obvious. A huge rope hangs down from "+
	    "within the bell.\n");

  add_item( ({"rope", "huge rope", "thick rope", "thick huge rope"}),
	    "The thick rope hangs down from inside the massive bell. It "+
	    "looks as though this is the rope that, when pulled on, "+
	    "would ring this bell.\n");

  add_item( ({"wood", "flaps", "wooden flaps", "west wall",
		"crumbling flaps", "west"}),
	    "The west wall is open, with the exception of dozens of "+
	    "bits and pieces of hanging wooden flaps. The wood is "+
	    "ancient and decaying, falling apart and looks to be "+
	    "within minutes of coming apart completely. At one point these "+
	    "flaps may have been able to open and close in varying "+
	    "amounts to control acoustics.\n");

  add_item( ({"hole", "circular hole"}),
	    "There is a circular hole carved in the floor of the "+
	    "tower room. A large, rusting iron staircase winds down "+
	    "through this hole to the levels below.\n");

  add_item( ({"staircase", "stairs", "iron stairs", "iron staircase"}),
	    "The staircase leading down out of the tower is ancient "+
	    "and covered with rust. It is a miracle that the metal "+
	    "has even survived this long. It is a testament to the "+
	    "craftsmanship of the designers of this building how long "+
	    "the core of it has lasted in this environment.\n");

  add_exit(MONKRUIN_DIR + "bt3", "down");
}

init()
{
  ::init();
  add_action(do_pull, "pull");
  add_action(do_jump, "jump");
}

int
do_pull(string str)
{
  if (!str) return 0;

  if ( (str=="rope") || ( str=="on rope"))
    {
      notify_fail("You try to pull on the rope but realize that "+
		  "you can't reach it from here. You'd probably have "+
		  "to jump to reach that far.\n");
      return 0;
    }
  else
    {
    notify_fail("Pull what?\n");
    return 0;
    }
}

int
do_jump(string str)
{
  if (!str) return 0;

  if ( ( str != "rope") && (str != "to rope") &&
       (str != "on rope"))
    {
      notify_fail("Jump where?\n");
      return 0;
    }
  else
    {
      if (sizeof(query_alarms()))
	{
	  notify_fail("The bell is already ringing, why would you want "+
		      "to jump onto the rope?\n");
	  return 0;
	}
      write("You take a few steps back and then dash forward, leaping "+
	    "out to the bell and grabbing hold of the rope. The "+
	    "force of your weight starts the bell swinging but also slides "+
	    "you off of the rope! ... \n\n");
      ring_count = 0;
      bell = set_alarm(10.0, 10.0, ring_bell);
      TP->move_living("sliding down off of the rope", 
		      MONKRUIN_DIR + "bt3", 0, 0);
      
    return 1;
    }
}

void
ring_bell()
{
  int i;

    for (i=0; i<sizeof(TELLROOMS); i++)
    {
        tell_room(TELLROOMS[i], "The entire area shakes with the "+
           "reverberation of a loud bell ringing its deep, "+
           "resonous tone!\n");
     }
  ring_count++;
  if (ring_count > 4)
    remove_alarm(bell);
}

