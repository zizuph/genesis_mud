inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

object serpent;

/* Prototypes */
void reset_room();

void
create_room()
{
    set_short("On top of northern tower");
    set_long(break_string(
	  "You have made it to the top of the northern tower. "
	+ "From here you have a marvellous view in all directions.\n",70));

    add_item("stairs", break_string(
	  "The broad wooden staircase winds downwards to the second floor, "
	+ "following the wall of the tower.\n", 70));

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower13", "down", 0, 4);

    add_prop(ROOM_I_INSIDE, 1);

    reset_room();
}

void
reset_room()
{
    if (!serpent)
    {
	serpent = clone_object(STAND_MONSTER + "tower_serpent");
	serpent->move(this_object());
    }
}

void
init()
{
    ::init();
    add_action("do_look", "look");
}

int
do_look(string str)
{
    switch (str)
    {
    case "north":
	write(break_string(
	    "Peering north you see mountainous land. Those are the bare "
	  + "planes of the north, in which only a few people dare to "
	  + "travel.\n", 70));
	return 1;
    case "east":
	write(break_string(
	    "Peering east you see a hilly landscape. Like a glistening "
	  + "ribbon the Eastroad disappears towards the horizon. "
	  + "Far away you can see a few small villages.\n", 70));
	return 1;
    case "south":
	write(break_string(
	    "Peering south you see the other tower that is just as "
	  + "high as this one. It blocks your view of the southern "
	  + "horizon.\n", 70));
	return 1;
    case "west":
	write(break_string(
	    "Looking west you notice the sea. Far away a ship sails, but "
	  + "it moves so slow that you cannot make out if it is coming "
	  + "towards, or if it is sailing away from the Grey Havens.\n",70));
	return 1;
    case "up":
	write(break_string(
	    "Looking up, you see the sky. For a moment you think "
	  + "you see a big eagle flying with someone on his back, "
	  + "but when you blink your eyes you cannot find it again.\n", 70));
	return 1;
    case "down":
	write(break_string(
	    "You lean a bit over the edge and see how high "
	  + "this tower actually is. No wonders you are so tired!\n", 70));
	return 1;
    }
    return 0;
}

int
serpent_present()
{
    if (present("serpent"))
	return 1;
    else
	return 0;
}
