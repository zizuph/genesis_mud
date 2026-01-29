/*  
 *  /d/Gondor/anorien/nimrais/trolls/cave2.c
 *
 *  Revision history:
 *   Gorboth: 7-Jul-1996       General code update,
 *                             added check for interactive to west exit.
 *   Tomas:  5-JAN-2018        added new large races, orges and minotaurs
 */
#pragma strict_type

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

// Prototypes
public int     test_size();
public int     blocked();
public int     enter_hole(string str);
public void    reset_room();

static object  gTroll, gTroll2, gTroll3;

public void
create_gondor()
{
    set_short("a tunnel in a hill-troll lair");
    set_long("In this dark tunnel, a foul smell comes with a"
      + " whiff of wind from the northeast. The tunnel continues"
      + " south, but there is another tunnel branching off to the"
      + " east. There is also a little hole in the tunnel wall to"
      + " the west. A small stream of water runs along the floor"
      + " of the tunnel here, breaking off and disappearing into"
      + " the east tunnel.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(NIMRAIS_DIR + "trolls/cave3", "south");
    add_exit(NIMRAIS_DIR + "trolls/cave1", "northeast");
    add_exit(NIMRAIS_DIR + "trolls/foodcave", "east", blocked);
    add_exit(NIMRAIS_DIR + "trolls/treasurecave", "west", test_size);

    add_item(({"ground","floor","cavefloor"}),
        "You find bones and broken bottles littered on the " +
        "floor of the cave. A little stream runs along the " +
        "floor of the cave, turning from the northeast to " +
        "the east here.\n");
    add_item(({"bones"}), "The bones are of varying size, "
      + " some of them clearly coming from small animals such as"
      + " rabbits, while others look more human in nature.\n");
    add_item(({"bottle","bottles"}), "There are empty and"
      + " broken bottles here. A few of them carry a label which"
      + " is marked: Dorwinion, 3012.\n");
    add_item(({"stream","streams"}), "A little stream runs"
      + " along the floor of the tunnel from the northeast,"
      + " turning into the east tunnel here.\n");
    add_item(({"hole","holes"}), "The hole looks dark and"
      + " mysterious, but only a little person would be able to"
      + " enter it.\n");

    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_INSIDE, 1);
    remove_prop(ROOM_I_LIGHT);

    reset_room();
}

public int
blocked()
{
    object  troll = present("troll", TO);
    if (troll && CAN_SEE(troll, TP)  && !TP->query_npc()) 
    {
	write("The " + troll->query_nonmet_name() + " blocks your way!\n");
	say(QCTNAME(this_player()) + " tries to leave, but the " +
            troll->query_nonmet_name() + " stops " +
            this_player()->query_objective()+".\n", this_player());
	return 1;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(enter_hole, "enter");
}

void
reset_room()
{
    ::reset_room();
    gTroll = clone_npc(gTroll, NPC_DIR + "hilltroll");
    gTroll2 = clone_npc(gTroll2, NPC_DIR + "hilltroll");
    gTroll3 = clone_npc(gTroll3, NPC_DIR + "hilltroll");
}

public int
enter_hole(string str)
{
    if (!strlen(str))
    {
	write("Enter what?\n");
	return 1;
    }
    if ((str == "hole") || (str == "little hole"))
    {
	if (!test_size()) 
	{
	    write("You squeeze yourself through the little hole!\n");
	    TP->move_living("through the little hole in the west wall",
			    ANO_DIR + "nimrais/trolls/treasurecave");
	    return 1;
	}
	return 1;
    }
    return 0;
}

int
test_size()
{
    switch (TP->query_race())
    {
    case "human":
    case "elf":
    case "dwarf":
    case "goblin":
    case "troll":
    case "ogre":
    case "minotaur":
        write("You quickly find out that you are too big for the"
            + " little hole!\n");
        say(QCTNAME(this_player()) + " tries to enter the little"
            + " hole, but is too big to do so.\n", this_player());
        return 1;
	break;
    }

    return 0;
}

