/*
 *	/d/Gondor/anorien/nimrais/trollcave/entrcave.c
 *
 *	Coded by Elessar.
 *
 *	Modification log:
 *	27-Jan-1997, Olorin:	General revision,
 *				changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <composite.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define MIN_STRENGTH    130
#define MIN_CLIMB       40
#define NEXT_ROOM       (NIMRAIS_DIR + "trolls/livcave")
#define OUT_ROOM        (NIMRAIS_DIR + "trolls/outcave")

public int     check_light();
public int     check_troll();
public int     stone_blocked();
public string  exa_stone();
public string  describe();
private void   try_push(object player);

static int     Boulder_Moved;
static object *Pushers = ({ });

public void
create_gondor()
{
    set_short("entrance to a dark, smelly cave");
    set_long(describe);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, check_light);
    add_exit(NIMRAIS_DIR + "trolls/livcave", "south", check_troll);
    add_exit(NIMRAIS_DIR + "trolls/outcave", "north", stone_blocked);
    add_item(({"stone","boulder","rock"}), exa_stone);
    add_item(({"ground","floor"}),
	     "The floor of the cave is littered with bones and rubble.\n");
    add_item(({"bones","rubble"}), "The bones on the floor are of many " +
        "different sizes, you guess that whatever lives here, has had a " +
        "great feast here lately, and that the meal has mainly consisted " +
        "of careless fortune-seekers. You don't find anything interesting " +
        "among the bones and rubble though.\n");
    add_item("cave", "The cave is quite large, about five meters high and " +
        "the same in width. The cave continues south.\n");
}

public int
check_light()
{
    string  time = tod();

    if (!Boulder_Moved)
	return 0;
    if ((time == "evening") || (time == "night")) 
	return 0;
    return 1;
}

public int
check_troll()
{
    object  troll;
    if (TP->query_race() == "troll") 
	return 0;
    if (objectp(troll = present("troll", TO)))
    {
	write("The " + troll->query_nonmet_name() + " blocks your way!\n");
	say(QCTNAME(TP) + " tries to walk south, but the " +
	    troll->query_nonmet_name() + " stops " +
	    TP->query_objective()+".\n", TP);
	return 1;
    }
    return 0;
}

public int
stone_blocked()
{
    string  time = tod();

    if (!Boulder_Moved) 
    {
	if (TP->query_race() == "troll") 
	{
	    switch (time)
	    {
	    case "early morning":
	    case "morning":
	    case "noon":
	    case "afternoon":
		say(QCTNAME(TP) + " notices the sunlight to the north, and " +
		    "decides not to leave the cave.\n");
		return 1;
	    default:
		say(QCTNAME(TP) + " pushes the boulder aside, walks out of " +
		    "the cave, and rolls the boulder back in place.\n", TP);
		return 0;
	    }
	}

	write("The exit is blocked by a large boulder.\n");
	return 1;
    }

    return 0;
}

public string
exa_stone()
{
    if (!Boulder_Moved)
	return "The large boulder is blocking the exit from the cave. It " +
            "is so large that it would take two to three strong persons " +
            "to roll it aside. It is about 2 meters and a half tall, " +
            "leaving a small opening between the top and the cave ceiling.\n";

    return "The large boulder has been rolled aside from the opening, so " +
        "that it no longer blocks the exit from the cave. The boulder is " +
        "so large that it probably would take many strong men to roll it.\n";
}

public string
describe()
{
    string time = tod(),
           longstr = "You are standing inside the entrance to a " +
                     "large cave, possibly a cave complex, as it " +
                     "seems to continue south into a bigger cave. ";
            
    if (!Boulder_Moved) 
	longstr += "To the north is the exit, but it is "+
	    "blocked by a large boulder. ";
    else 
	longstr += "To the north is the exit out to the open air. ";

    switch (time)
    {
    case "early morning":
    case "morning":
    case "noon":
    case "afternoon":
	if (!Boulder_Moved) 
	    longstr += "A few rays of sunlight seep into the cave " +
		"through the cracks between the boulder and the wall. ";
	else 
	    longstr += "The bright light of day shines in through the " +
                "cave opening to the north. ";
	break;
    default:
	if (NEXT_ROOM->test_fire())
	    longstr += "It is completely dark now, but a flickering " +
                "light as if from a campfire further " +
		"south in the cave is casting eerie shadows on " +
		"the walls. ";
	else
	    longstr += "It is completely dark now, except for the gleam " +
                "of your light source. ";
	break;
    }
    longstr += "The floor is littered with bones and rubble, and the foul " +
        "stench here is almost unbearable. ";
    return (longstr + "\n");
}

public int
push_boulder(string str)
{
    object  troll;

    if (!strlen(str) || ((str != "boulder") && (str != "boulder aside")))
    {
	NFN(CAP(query_verb()) + " what?");
	return 0;
    }
    if (objectp(troll = present("troll", TO)))
    {
	write("The " + troll->query_nonmet_name() + " stops you before "
	      + "you get as far as touching the boulder!\n");
	say(QCTNAME(TP) + " tries to push the boulder, but the "
	    + troll->query_nonmet_name() + " stops "
	    + TP->query_objective() + "!\n", TP);
	return 1;
    }
    if (Boulder_Moved) 
    {
	write("You try to push the boulder back, but it won't budge.\n");
	say(QCTNAME(TP) + " tries to push the boulder, but it won't budge.\n");
	return 1;
    }
    try_push(TP);
    return 1;
}

private int
test_total_str()
{
    int    n = -1,
           str;

    if (sizeof(Pushers) < 2)
	return 0;

    while (++n < sizeof(Pushers)) 
	str += Pushers[n]->query_stat(SS_STR);
    return str;
}

private void
tell_pushers(string str1, object *who, string str2)
{
    int     n = -1;
    object *others;

    if (!strlen(str1) || !sizeof(who))
	return;

    while (++n < sizeof(who)) 
    {
	others = who - ({ who[n] });
        who[n]->catch_msg(str1 + COMPOSITE_LIVE(others) + str2);
    }
}

private void
try_push(object player)
{
    if (!objectp(player))
	return;

    Pushers = filter(Pushers, objectp @ &present( , TO));
    if (!sizeof(Pushers))
    {
	Pushers = ({ player });
	player->catch_tell("You summon all your strength, but the great " +
            "boulder won't budge.\n");
	say(QCTNAME(player) + " tries to push the boulder away, but is " +
            "unable to do so alone.\n", player);
	return;
    }

    if (member_array(player, Pushers) > -1)
    {
	player->catch_tell("You keep pushing the boulder.\n");
    }
    else
    {
	Pushers->catch_msg(QCTNAME(player) + " decides to try to help you " +
            "roll away the boulder.\n");
	Pushers += ({ player });
	if (test_total_str() >= MIN_STRENGTH) 
	{
	    tell_pushers("You summon all your strength, and the " +
                "joined strength of ", Pushers, "succeeds to roll the " +
                "great boulder away from the cave opening!\n");
	    say("Due to the joint effort of " + COMPOSITE_LIVE(Pushers) +
                "the great boulder is rolled away from the cave opening.\n",
		Pushers);
	    tell_room(OUT_ROOM, "The large boulder suddenly rolls away " +
                "from the cave entrance, pushed by someone on the inside!\n");
	    Boulder_Moved = 1;
	    Pushers = ({ });
	}
	else
	{
	    tell_pushers("You summon all your strength, but not even the " + 
                "joined forces of ", Pushers, " is enough to budge the " +
                "great boulder.\n");
	    say(COMPOSITE_LIVE(Pushers) + " try to move the boulder " +
                "together, but it won't budge.\n", Pushers);
	}
    }
    return;
}

public int
climb_boulder(string str)
{
    object  troll;
    int result;

    if (!str)
    {
        NFN("Climb what?");
        return 0;
    }

    result = parse_command(str, ({}), 
	   "[over] [across] [through] [the] 'boulder' / 'rock' / 'opening'");

    if (result == 0)
    {
        NFN("Climb what?");
        return 0;
    }

    if (Boulder_Moved) 
    {
        write("Why climb? The boulder has been moved away from the " +
            "cave mouth!\n");
    }
    else if (objectp(troll = present("troll", TO)))
    {
        write("The " + troll->query_nonmet_name() + " sees what you are " +
            "trying to do, and drags you down again!\n");
        say(QCTNAME(TP) + " starts to climb the large boulder, but the " +
            troll->query_nonmet_name() + " drags " + TP->query_objective() +
            " down again!\n");
    }
    else if (TP->query_skill(SS_CLIMB) < MIN_CLIMB) 
    {
        write("You try to climb the large boulder, but it is too steep and " +
            "smooth. The only result is broken nails and bleeding fingers.\n");
        say(QCTNAME(TP) + " tries to climb over the large boulder, but " +
            "fails.\n");
    }
    else
    {
        write("You skillfully climb the large boulder and squeeze yourself " +
            "through the narrow opening between rock-top and cave-roof.\n");
        say(QCTNAME(TP) + " manages to climb the large boulder, and " +
            "disappears out through the narrow opening between rock and " +
            "ceiling.\n");
        tell_room(OUT_ROOM,  QCTNAME(TP) + " comes climbing out above the " +
            "large boulder blocking the entrance.\n");
        TP->move_living("M", OUT_ROOM);
    }
    return 1;
}

int
query_boulder_moved()
{
    return Boulder_Moved;
}
     
void
set_boulder_moved(int i)
{
    Boulder_Moved = i;
}

public void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);

    if (!objectp(obj) || !living(obj))
	return;
    if (!sizeof(Pushers))
	return;
    Pushers -= ({ obj });
}

public void
init()
{
    ::init();
    add_action(push_boulder,  "push");
    add_action(push_boulder,  "roll");
    add_action(push_boulder,  "move");
    add_action(climb_boulder, "climb");
}
