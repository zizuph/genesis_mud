/*
 * Finally, the top of the second tower. Here the player will be rewarded.
 *
 *					Tricky, 28-2-92
 */
inherit "/std/room";

#include "defs.h"
#include "/sys/stdproperties.h"

int solved;

void
create_room()
{
    set_short("On top of southern tower");
    set_long(break_string(
	  "You have made it to the top of the southern tower. "
	+ "To your surprise there is nothing special here, except that "
	+ "large chest that is standing here. "
	+ "From here you have a marvellous view in all directions.\n",70));

    add_item("stairs", break_string(
	  "The broad wooden staircase winds downwards to the second floor, "
	+ "following the wall of the tower.\n", 70));

    /* Climbing the stairs is tiresome... */
    add_exit(STAND_DIR + "tower23", "down", 0, 4);

    add_prop(ROOM_I_INSIDE, 1);

    /* Put the large chest here */
    clone_object(STAND_OBJ + "tower_chest")->move(this_object());

    solved = 0;
}

void
reset_room()
{
    solved = 0;
}

void
init()
{
    object tp;

    ::init();
    add_action("do_look", "look");

    /*
     * Well, the player made it to here, he has almost solved the quest...
     * This way of adding the property is rather crude; now the quest
     * cannot be solved within one reset. Ah well...
     */
    seteuid(getuid());
    if (!solved && living(this_player()))
    {
        this_player()->add_prop("_seen_4th_floor_of_tower_2");
	this_player()->catch_msg("You feel like you are close to solving a quest.\n");
	solved = 1;
    }
}

int
do_look(string str)
{
    switch (str)
    {
    case "south":
	write(break_string(
	    "Peering south you see forests and a hilly land. In that "
	  + "direction must Gondor be. But it probably is far, far "
	  + "away.\n", 70));
	return 1;
    case "east":
	write(break_string(
	    "Peering east you see a hilly landscape. Like a glistening "
	  + "ribbon the Eastroad disappears towards the horizon. "
	  + "Far away you can see a few small villages.\n", 70));
	return 1;
    case "north":
	write(break_string(
	    "Peering north you see the other tower that is just as "
	  + "high as this one. It blocks your view of the northern "
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
