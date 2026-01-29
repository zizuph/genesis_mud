#include "/d/Ansalon/balifor/flotsam/ship/local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
inherit "/d/Krynn/std/deck";
int loaded = 0;
int aimed = 0;
int sunk = 0;

void
create_deck()
{

    set_short("upper bow deck before a large ballista");
    set_long("You stand on the upper bow deck on the foremost " +
      "part of the Golden Lion. In the center of the deck stands " +
      "a large ballista pointing out to sea. A wooden stairway " +
      "leads down to the main deck.\n");

    add_item(({"upper bow deck","bow deck","deck"}),
      "You stand upon the upper bow deck at the foremost part " +
      "of the ship. Apart from the large ballista standing " +
      "Before you, there is nothing else of interest here.\n");
    add_item("main deck","Looking down at the main deck, " +
      "you notice sailors scurrying quickly to the captains " +
      "orders.\n");
    add_item(({"large ballista","ballista"}),
      "A large ballista, mounted onto the deck and pointing out " +
      "to sea. You do not doubt that it could punch a mighty " +
      "hole in the side of any ship. " +
      "@@loaded@@" + "\n");

    add_item("sea","@@sea_descr");
    add_item(({"ship","dragonarmy ship"}),"@@boat_descr");

    add_cmd_item(({"ballista","large ballista"}),
      ({"fire","shoot"}),"@@fire_ballista");
    add_cmd_item(({"ballista at ship","ballista at dragonarmy " +
	"ship","large ballista at ship","large ballista at " +
	"dragonarmy ship"}),"aim",
      "@@aim_ballista");
    add_cmd_item(({"ballista","large ballista"}),
      ({"load","reload"}),"@@load_ballista");

    add_exit("d8","down",0);
}

string
loaded()
{
    if(loaded == 0)
    {
	return "It is loaded, so be careful what you " +
	"fire it at. ";
    }
    return "It is not loaded.";
}


string
sea_descr()
{
    if(sunk == 0)
    {
	return "You look out at the expansive sea before you. " +
	"Its beauty is marred by a ship that seems to be following " +
	"the Golden Lion, the ship you are presently on.\n";
    }
    return "You look out at the beautiful and expansive sea " +
    "before you. It is hard not to feel calm and relaxed " +
    "while watching its tranquil waters.\n";
}

string
boat_descr()
{
    if(sunk == 0)
    {
	return "You look out across the water and notice the " +
	"dark shape of a dragonarmy ship! Armed to the teeth, it " +
	"looks like it has chartered a direct course towards the " +
	"Golden Lion, the ship that you are on! Things are looking " +
	"grim for this vessel and its inhabitants it seems...\n";
    }
    return "Look at what ship? The sea is empty except " +
    "for the Golden Lion.\n";
}

string
aim_ballista()
{
    if(sunk == 0)
    {
	write("You turn the ballista slightly so that it is " +
	  "aimed directly at the Dragonarmy warship that is " +
	  "heading towards you.\n");
	say(QCTNAME(TP) + " turns the ballista slightly.\n");
	aimed = 1;
	return "";
    }
    write("Aim the ballista at what?\n");
    return "";
}

void
reset_chasing_ship()
{
    sunk = 0;
}

string
fire_ballista()
{
    if(loaded == 1)
    {
	write("It is not loaded.\n");
	return "";
    }
    if(aimed == 1)
    {
	write("You shout: Ballista away!!!\n");
	write("You fire the ballista bolt at the dragonarmy ship! " +
	  "Your aim is true, and it strikes a mighty hole in its " +
	  "hull.\n");
	write("The dragonarmy ship falters, and begins to sink.\n");
	say(QCTNAME(TP) + " shouts: Ballista away!\n" +
	  QCTNAME(TP) + " fires the ballista. A " +
	  "bolt streaks across the sea, crunching into a dark " +
	  "vessel that was closing in on the Golden Lion.\n" + 
	  "The dark vessel begins to keel over, and sink.\n");
	loaded = 0;
	aimed = 0;
	sunk = 1;
	set_alarm(3000.0, 0.0, &reset_chasing_ship());

	if(TP->test_bit("ansalon", 0, 0))
	{
	    TP->catch_msg("Nice job, but no experience second " +
	      "time.\n");
	    return "";
	}
	TP->add_exp(150, 0);
	TP->set_bit(0, 0);
	A_QUEST_LOG("quest","Ballista tour", TP, 150);
	TP->catch_msg("You feel a little more experienced!\n");
	return "";
    }
    write("You fire the ballista bolt across the sea! You " +
      "notice it splash into the water in the distance.\n");
    say(QCTNAME(TP) + " fires the loaded ballista. A ballista " +
      "bolt soars across the sea, finally splashing into the " +
      "water a fair distance away.\n");
    loaded = 0;
    return "";
}

string
load_ballista()
{
    if(loaded == 1)
    {
	write("You load the ballista with a ballista bolt.\n");
	say(QCTNAME(TP) + " loads the ballista with a ballista " +
	  "bolt.\n");
	loaded = 0;
	return "";
    }
    write("It is already loaded.\n");
    return "";
}

sounds()
{
    if (random(2))
	return "The ship sways with the wind.\n";

    return "The ship rocks violently to the tune of the turbulent waters.\n";
}

