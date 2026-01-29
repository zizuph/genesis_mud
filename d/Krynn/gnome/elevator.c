/* elevator into the gnome area, created by Grrrr
   updates by Aridor, 08/94 */

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "local.h"
inherit "/d/Krynn/std/room";

#define ENTRANCE     (TDIR + "entrance")
#define CAVERN       (TDIR + "cavern1")
#define ELEVATOR     (TDIR + "elevator")

/*prototype*/
int security(object subject);


int location; /* -1 = cavern, 0 = underway, 1 = entrance, 2 = idle*/
int fodder, torchme;
int how_many; /* number of people in the elevator */
string str;

void
create_room()
{
    set_short("An elevator cage");
    set_long("You are standing in a cage suspended above a dark hole. "+
	     "Sounds of steam whistles and construction come from below " +
	     "you. Many cables are attached to the top of the cage. A " +
	     "small sign, well small for being gnomish, is hanging here.\n");
    
    add_item(({"cage", "elevator"}),
	     "It is made of a network of iron bars, most vertical. The " +
	     "floor used to be made the same way, but now an area below " +
	     "your feet looks recently mended, as if something " +
	     "accidentally fell through.\n");
    add_item("sign", "There is something written on it.\n");
    add_cmd_item("sign", "read",
		 "ThisIsTheFamousNever(Almost)FailingCageElevator.\n");
    
    add_prop(OBJ_S_WIZINFO,"Should the elvator get stuck, you can get " +
	     "people out with 'Call here disembark'.\n");

    add_exit("@@whatfloor", "out", 0);
    location = 2;
    how_many = 0;
    torchme = 1;
    INSIDE;
    DARK;
}

int
query_how_many_are_inside()
{
    if (how_many < 0)
      how_many = 0;
    return how_many;
}

void
someone_entered()
{
    how_many++;
}

void
has_been_called(int to_where)
{
    location = to_where;
}

void
reset_room() 
{ 
    torchme = 1; 
}

int
query_busy(int who_calls) 
{ 
    return (location != 2 && location != who_calls); 
}

void
phase1(int step)
{
    object *people;
    int i;
    
    location = 0;
    if (step == -1)
      {
	  location = 1;
	  ENTRANCE->openit();
	  tell_room(TO, "The door swings open, letting in blinding sunlight." +
		    " You step out into the forest clearing. It is much more " +
		    "peaceful up here...\n");
	  people = all_inventory(TO);
	  people->move_living("into the great outdoors", ENTRANCE);
	  how_many = 0;
      }
    else
      {
	  tell_room(TO, "The door slams shut! You hear a scratching " +
		    "sound by your head.\n");
	  set_alarm(itof(random(4) + 3),0.0,"phase2",step);
      }
}

void
phase2(int step)
{
    object torch;
    
    fodder = random(5);
    if (step == 1)
      {
	  if (torchme)
	    {
		torch = clone_object(OBJ + "torch");
		torch->move(TO);
		torchme = 0;
		if (fodder == 0)
		  {
		      str = "A lit torch drops at your feet via a small " +
			"chute in the ceiling.";
		      torch->light_me();
		  }
		else
		  str = "Something drops at your feet.";
		tell_room(TO, str + "\n");
	    }
	  fodder = random(5);
	  if (fodder == 0)
	    str = "You think you hear a cable snap.";
	  else if (fodder == 1)
	    str = "The elevator plummets several feet suddenly! " +
	      "You feel unwell ...";
	  else
	    str = "The elevator sways for a while, then " +
	      "begins to drop jerkily.";
      }
    else
      {
	  if (fodder == 0)
	    str = "The elevator comes to a smooth halt.";
	  else
	    str = "An alarm shrieks below you. The elevator jerks to a halt.";
      }
    tell_room(TO, str + "\n");
    set_alarm(itof(random(4) + 3),0.0,"phase" + (2 + step), step);
}

void
phase3(int step)
{
    fodder = random(5);
    if (step == 1)
      {
	  if (fodder == 0)
	    str = "The descent continues. The temperature drops a bit.";
	  else if (fodder == 1)
	    str = "The elevator stops, then falls a few more meters. " +
	      "A bell starts ringing!";
	  else
	    str = "In uncomfortable jolts, you descend into the earth.";
      }
    else
      {
	  if (fodder == 0)
	    str = "You think you see light above!";
	  else if (fodder == 1)
	    str = "The elevator stops and you hear little feet " +
	      "above your head as some adjustment is made.";
	  else
	    str = "The elevator drops a bit, then resumes its ascent.";
      }
    tell_room(TO, str + "\n");
    set_alarm(itof(random(6)),0.0,"phase" + (3 + step), step);
}

void
phase4(int step)
{
    fodder = random(5);
    if (step == 1)
      {
	  if (fodder > 1)
	    str = "The clanking and grinding sounds much louder down here. " +
	      "You must be close.";
	  else if (fodder == 0)
	    str = "You hear a distant explosion. The elevator rocks " +
	      "back and forth precariously but continues on its way down.";
	  else
	    str = "You hear a voice somewhere below: HasAnyoneTestedThe" +
	      "NewElevatorYet?\nOther voices hush the first.";
      }
    else
      {
	  if (fodder == 0)
	    str = "A gnome shouts: OhNoLookAtThatCableBelowTheEleva" +
	      "torThingie! IsItSupposedToLookLikeThat?";
	  if (fodder == 1)
	    str = "The elevator rises slowly towards the surface.";
	  else
	    str = "The elevator hits the sides a few times, but " +
	      "seems to hold together as it rises through the shaft.";
      }
    tell_room(TO, str + "\n");
    set_alarm(itof(random(4) + 3),0.0,"phase" + (4 + step), step);
}


void
phase5(int step)
{
    object *people;
    int i;
    
    fodder = random(5);
    if (step == 1)
      {
	  location = -1;
	  CAVERN->openit(0);
	  if (fodder == 0)
	    str = "A gnome says: HeyItWorked!\nThe door to the elevator " +
	      "opens and you hop out.";
	  else if (fodder == 1)
	    str = "The elevator lists crazily and stops. You manage to " +
	      "squeeze out the door and drop to the floor. A group " +
	      "of gnomes is nearby, arguing loudly and taking notes, " +
	      "pointing at the elevator.";
	  else
	    str = "As you reach the level of the cave, a gnome runs " +
	      "under the cage and unties a donkey which had been " +
	      "turning a large wheel. Once they are clear, you drop " +
	      "to the floor with a crash. The door swings open and " +
	      "you stagger out ...";
	  set_alarm(4.0,0.0,"disembark");
	  tell_room(TO, str + "\n");
      }
    else
      {
	  location = 0;
	  if (fodder == 0)
	    str = "Springs beneath the elevator cage start you on your " +
	      "upward journey with a jolt.";
	  else if (fodder == 1)
 	    str = "A gnome seems about to stop you, but changes his mind " +
	      "and waves to start the elevator, crossing his fingers.";
	  else
	    str = "While the elevator is propped on timbers, a donkey " +
	      "is led under it to a large wheel. Once it starts " +
	      "walking, you begin to rise. Gnomes with hooks catch " +
	      "the logs before the donkey is crushed.";
	  set_alarm(itof(random(4) + 3),0.0,"phase4",step);
	  tell_room(TO, str + "\n");
      }
}

string
whatfloor()
{
    if (location == 0)
      {
	  write("You can't leave while the elevator is moving!\n");
	  str = ELEVATOR;
      }
    else if (location == 2)
      {
	  write("The elevator is suspended somewhere in the middle.\n" + 
		"It seems you are stuck!\n");
/* maybe a 'call for help' command should be enabled here, if it happens
 * too frequently.
 */
	  str = ELEVATOR;
      }
    else if (location == 1)
      str = ENTRANCE;
    else if (location == -1)
      {
	  if (!security(TP))
	    {
		tell_room(CAVERN, "A gnome says: Hey, wait! I'veSeenThatGnomeOn" +
			  "The'Wanted'PostersInThePostOffice!\n");
		tell_object(TP, "The gnomes seize you and stuff you " +
			    "back in the elevator! Nice try, but until you clear " +
			    "your name by performing a good deed for the community" + 
			    " you're exiled.\n\n");
		tell_room(CAVERN, "A scuffle breaks out among the gnomes, and " +
			  "one is stuffed back into the elevator!\n", TP);
		how_many++;
		seteuid(getuid());
		CAVERN->trig();
		str = ELEVATOR;
	    }
	  else
	    str = CAVERN;
      }
    else
      {
	  write("Hmm, it seems the elevator is pretty messed up. You " +
		"wouldn't be surprised in the least if it was actually " +
		"hanging upside down.\n");
/* call for help here too?? */
	  str = ELEVATOR;
      }
    if (str != ELEVATOR)
      {
	  how_many--;
	  if (how_many < 0)
	    how_many = 0;
      }
    return str;
}

int
security(object subject)
{
    string *list;
    string str1, str2;
    int i;
    
	if (file_size(F_LOG) < 1)
		return 1;
	
    list = explode(read_file(F_LOG), "\n");
    for (i = 0; i < sizeof(list); i++)
      {
	  sscanf(list[i], "%s %s", str1, str2);
	  if (str2 == subject->query_nonmet_name())
	    {
		tell_room(TO, "A shrill alarm goes off!\n");
		return 0;
	    }
      }
    return 1;
}

void
disembark()
{
    object *people;
    int i;
    
    people = all_inventory(TO);
    for (i = 0; i < sizeof(people); i++)
      {
	  if (security(people[i]))
	    {
		people[i]->move_living("into the gnomish caverns", CAVERN);
		how_many--;
		if (how_many < 0)
		  how_many = 0;
	    }
	  else
	    {
		tell_room(TO, "A gnome says: Hey, Wait! I'veSeentThatGnome " +
			  "OnThe'Wanted'PostersInThePostOffice!\n");
		tell_object(people[i], "The gnomes seize you and stuff you " +
			    "back in the elevator! Nice try, but until you clear " +
			    "your name by performing a good deed for the community" + 
			    " you're exiled.\n\n");
		tell_room(CAVERN, "A scuffle breaks out among the gnomes, and " +
			  "one is stuffed back into the elevator!\n", people[i]);
		how_many++;
		seteuid(getuid());
		CAVERN->trig();
	    }
      }
}

