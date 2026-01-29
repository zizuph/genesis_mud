#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

#define ELEVATOR   (TDIR + "elevator")

int triggered;

void
reset_room()
{
    object burden, gnome;
    
    if (!P("emong",TO))
      {
	  gnome = clone_object(MON + "gnome");
	  gnome->move_living("xxx", TO);
      }
    if (!P("donkey",TO))
      {
	  burden = clone_object(MON + "donkey");
	  burden->move_living("xxx", TO);
      }
}

void
create_room()
{
    set_short("Near the elevator");
    set_long("You are in a small underground chamber. This is " +
	     "where the elevator to the surface arrives, powered by a " +
	     "large donkey-powered wheel. A circular tunnel heads east " +
	     "through the stone. It is only partly finished, work widening " +
	     "the passage continues. Among the many cables running to the " +
	     "elevator is a lever you can pull to start the elevator.\n");
    
    add_item("lever", "A metal shaft with a knob at the end, at a " +
	     "comfortable height for someone about a meter tall.\n");
    add_item(({"cable", "cables"}), "Part of a disorderly array of " +
	     "lines running to the elevator cage. They are tied to walls, " +
	     "run through pulleys, and generally tangled.\n");
    add_item("elevator", "@@exa_elev");
    
    add_cmd_item("lever", "pull", "@@trig");
    add_cmd_item(({"cage", "elevator"}), "enter", "@@elevator");
    add_cmd_item(({"in", "into elevator", "in elevator"}), "squeeze", "@@elevator");
    
    INSIDE;
    LIGHT;
    
    triggered = 0;
    add_exit(TDIR + "cavern2", "east", 0);
    reset_room();
}

string
exa_elev()
{
    string race, str;
    
    str = "A metal cage about 6 cubic meters in size. That is 4 square-meters times 1.5 meters "
    	+ "in height.\n";
    race = TP->query_race();
    if(race != "gnome" && race != "goblin" && race != "hobbit")
    	str += "You will have to duck while inside.\n";
    str += "It is suspended by metal wires disappearing into a huge dark hole in the ceiling "
    	+ "of the cavern. There's a";
    if(triggered)
    	str += "n open";
    else
    	str += " closed";
    str += " door in the front.\n";
    return str;
}

int
query_trig()
{ 
    return triggered; 
}

int
trig()
{
    write("You pull the lever.\n");
    set_alarm(2.0,0.0,"openit",TP);
    return 1;
}

void
openit(object who)
{
    triggered = 1;
    ELEVATOR->load_me();
    if (!P("donkey",TO))
      who->catch_msg("The elevator is donkey powered, and someone's aggressive " +
		     "tendencies have interfered with this. Please wait till a " +
		     "new donkey is found.\n");
    else if (ELEVATOR->query_busy(-1))
      {
	  triggered = 0;
	  tell_room(TO, "A sign is revealed, hanging above the floor, with " +
		    "the message:\nTHE ELEVATOR IS BUSY. WE APOLOGIZE FOR THE " +
		    "INCONVENIENCE.\n");
	  set_alarm(0.1,0.0,"closeit");
      }
    else
      {
	  ELEVATOR->has_been_called(-1);/* -1 means down here */
	  tell_room(TO, "Ropes pull the elevator door open far enough for " +
		    "you to squeeze in.\n");
	  set_alarm(18.0,0.0,"closeit");
      }
}

void
closeit()
{
    if (triggered && ELEVATOR->query_how_many_are_inside())
      ELEVATOR->phase5(-1);
    else
      ELEVATOR->has_been_called(2); /* means to go idle */
    triggered = 0;
    tell_room(TO, "A gnome slams the door shut and backs quickly out of " +
	      "the way.\n");
}

string
elevator()
{
    if (triggered)
      {
	  write("You clamber into the elevator cage. The sound of " +
		"tortured metal greets you.\n");
	  TP->move_living("into the elevator", ELEVATOR, 1);
	  ELEVATOR->someone_entered();
	  return "";
      }
    return "The cage is not here now.\n";
}

string 
wayout() { return "east"; }

string
tohelp() { return "east"; }

string
fromhelp() { return "done"; }

string 
area() { return "Inthemaincaverns"; }
