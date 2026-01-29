#include "/d/Krynn/common/defs.h"
#include "local.h"
#include <macros.h>
inherit "/d/Krynn/std/room";

void reset_room();

void
create_room()
{
    set_short("Middle of main cavern");

    set_long(BS("You are in the middle of a vast natural cavern. " +
      	"A number of catapults here are set up with hundreds of ropes " +
      	"attached to them.  Dozens of gnomes clamber over them making " +
       	"often contradictory adjustments.  You wonder why there is such an " +
       	"interest in siege machinery among these harmless-seeming folk...\n" +
	"Someone put up a grey poster here.", 70));

    INSIDE;
    LIGHT;
    add_item(({"cavern", "cave", "caves"}), "Formed through natural " +
	"erosion, this cavern is hundreds of meters long and about " +
	"thirty meters high. It is fairly narrow along its length, " +
	"though it\nis wider higher up.\n");
    add_item(({"catapult", "catapults", "gnomeflinger", "gnomeflingers"}),
      	"Though few are actually fully assembled, the cavern contains " +
	"dozens of these devices. Everywhere you look catapults are " +
	"being tested, adjusted, disassembled, built, or several of " +
	"these all at once. Funny, gnomes don't look very warlike.\n");
    add_item(({"poster", "grey poster"}), "You can read it.\n" +
	     "Next to the poster hangs a bell and a whistle.\n");
    add_cmd_item(({"poster", "grey poster"}), "read",
		 "The poster reads:\nLevel 1: Explosives research facility.\n" +
		 "Level 2: Expansion Guild.\n" +
		 "Level 3: Inventor Guild and Convenience Guild Lab.\n" +
		 "In case of emergency use bell and be patient until help arrives.\n"); 
    add_item("bell","This is an ordinary looking brass bell.\n");
    add_item("whistle","A whistle... Hmmm, nothing special to detect about it though.\n");
    add_item("horn","It huge! And loud! Strange that you overlooked it before!\n");
    add_cmd_item("bell","ring","@@ring_bell@@");
    add_cmd_item("whistle","blow","@@blow_whistle@@");

    add_exit(STAND_DIR + "gnome/cavern5", "south", 0);
    add_exit(STAND_DIR + "gnome/cavern7", "north", 0);
    reset_room();
}

string
ring_bell()
{
    set_alarm(300.0,0.0,"reset_room");
    return ("You ring the bell. A whistle blows in the distance somewhere north " +
	    "and a horn TOOTS right next to your ear.\n");
}

string
blow_whistle()
{
    set_alarm(300.0,0.0,"reset_cavern1");
    return ("You blow the whistle. A bell rings far away south " +
	    "and a horn TOOTS right next to your ear.\n");
}

void
reset_cavern1()
{
    (STAND_DIR + "gnome/cavern1")->reset_room();
}

void
reset_room()
{
    object foreman;
    object flinger;

    if (!present("foreman", TO))
    {
    	foreman = clone_object(MON + "foreman");
    	foreman->move_living("xxx", TO);
    }
    if (!present("gnomeflinger", TO))
    {
    	flinger = clone_object(OBJ + "flinger");
    	flinger->move(TO);
    }
}

string
area() { return "Inthemaincaverns"; }

string
wayout() { return "north south"; }

string
tohelp() { return "north"; }

string
fromhelp() { return "south"; }
