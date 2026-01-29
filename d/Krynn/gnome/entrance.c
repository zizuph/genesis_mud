#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "local.h"
inherit "/std/room";

#define BOULDER      (TDIR + "boulder")
#define ELEVATOR     (TDIR + "elevator")

int triggered;

void
create_room()
{
    set_short("A forest clearing with a large rock");
    set_long("@@mylong");
    OUTSIDE;
    LIGHT;
    
    add_item("clearing", "An open space, about 60 feet in diameter, with no "
    	+ "trees at all.\n");
    add_item("trail", "It is well used.\n");
    add_item("message", "Be warned before entering! The gnomes protect "+
	     "their own. Aggression may not be a wise course of action.\n" +
	     "--" + C(WIZARD_IN_CHARGE) + "\n");
    add_cmd_item("message", "read", "Be warned before entering! The " +
		 "gnomes protect their own. Aggression may not be a wise " +
		 "course of action.\n--" + C(WIZARD_IN_CHARGE) + "\n");
    add_item(({"rock", "boulder","large rock"}), 
	     "Closer examination reveals that the boulder has been hewn " +
	     "into this shape.  It is basically spherical.  You could " +
	     "probably climb it fairly easily, though.\n");
    add_item(({"footprint","footprints","print","prints",
		 "track","tracks"}),
	     "There are alot of footprints here, heading north " +
	     "and south. They stop here in the clearing. " +
	     "The prints could only be made by very " +
	     "small feet.\n");

    add_cmd_item(({"rock", "up", "boulder"}), "climb", "@@climb");
    add_cmd_item(({"rock", "boulder", "cage"}), "enter", "@@elevator");

    triggered = 0;
    add_exit(C_WILD, "north", 0);
}

int
climb()
{
    write("You climb to the top of the boulder.\n");
    say(QCTNAME(this_player()) + " climbs to the top of the boulder.\n");
    this_player()->move_living("up the rock", BOULDER);
    return 1;
}

int
query_trig()
{
    return triggered;
}

void
trig()
{
    set_alarm(2.0,0.0,"openit");
}

void
openit()
{
    triggered = 1;
    ELEVATOR->load_me();
    if (ELEVATOR->query_busy(1))
      {
	  triggered = 0;
	  tell_room(TO, "A sign is revealed, hanging above a chasm, with the " +
		    "message:\nTHE ELEVATOR IS BUSY. WE APOLOGIZE FOR ANY " +
		    "INCONVENIENCE CAUSED.\n");
	  set_alarm(0.1,0.0,"closeit");
      }
    else
      {
	  ELEVATOR->has_been_called(1); /* 1 means up here */
	  tell_room(TO, "Part of the boulder swings open, revealing a cage " +
		    "you can enter.\n");
	  set_alarm(22.0,0.0,"closeit");
      }
}

void
closeit()
{
    if (triggered && ELEVATOR->query_how_many_are_inside())
      ELEVATOR->phase1(1);
    else 
      ELEVATOR->has_been_called(2); /* means to go idle */
    triggered = 0;
    tell_room(TO, "The boulder swings shut. You can't even see the seam " +
	      "where the door was.\n");
}

string
mylong()
{
    string str, rock_str;
    if (triggered)
      rock_str = "The area " +
	"is dominated by a large boulder, at least two meters high. " +
  	"A lot of noise is coming from an opening in the boulder, " +
	"a door which trembles as if it hasn't decided if it wants to " +
	"be open or closed...";
    else
      rock_str = "The area " +
	"is dominated by a large boulder, at least two meters high. " +
	"The silence of the forest is disturbed by occasional hissing " +
	"and clanging noises coming from the rock.";
    
    str = "The forest parts here into a small grassy clearing. " +
      "A well-used trail leads north out of the clearing. " +
      "There are some tracks here. A message is scrawled in " +
      "the ground here. ";

    str = str + rock_str + "\n";
    return str;
}

int
elevator()
{
    if (triggered)
    {
   	write("You step into the cage within the boulder. " +
	    "It sways slightly...\n");
    	say(QCTNAME(TP) + " steps into the cage.\n");
    	TP->move_living("into the boulder", ELEVATOR,1);
	ELEVATOR->someone_entered();
    	return 1;
    }
}

