/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 03/95 
 */

#include "../local.h"
inherit ATTACKROOM;
#include RND_MEET

object monster;

void
create_attack_room()
{
    set_short("Inside a temple");
    set_long("You are inside a temple. Apparently this temple is " +
	     "dedicated to the ancestors of the village folk. " +
	     "There is an altar at the east wall of the room, otherwise, " +
	     "the temple is empty.");
    set_change_msg(0,ATTACK + "@@make_room_outside_room@@");
    set_change_short(1,"The remains of a building");
    set_change_long(1,"You are standing in something that was once a stone " +
		    "building. You cannot see much now anymore, except the " +
		    "blackened stone floor.\n");
    set_change_msg(1,SMOLDER);
    set_change_short(2,"The remains of a building");
    set_change_long(2,"You are standing in something that was once a stone " +
		    "building. You cannot see much now anymore, except the " +
		    "blackened stone floor.\n");
    set_change_msg(2,REBUILD);
    set_change_short(3,"A partly built temple");
    set_change_long(3,"You are standing in a building under construction. " +
		    "This is a stone building and people have already built " +
		    "the walls. The roof is still missing though.");
    set_change_msg(3,FINISH + "@@make_room_inside_room@@");
    
    INSIDE;

    add_exit(ROOM + "arena","southwest");
    add_exit(ROOM + "vill16","northwest");
}

string 
make_room_outside_room()
{
    OUTSIDE;
    return "";
}

string
make_room_inside_room()
{
    INSIDE;
    return "";
}


string
arena_desc()
{
    switch (QUERY_STATE)
      {
	case 0: return ("You cannot see anyone using this arena currently, " +
			"and otherwise you cannot find anything special. " +
			"The arena is about thirty feet in diameter and each " +
			"stone step is one foot high. All inhabitants of the " +
			"village will easily have enough room to watch.\n");
	case 1: return ("You can see dark shapes moving around the burning " +
			"tents around you. Everything is aflame, but luckily " +
			"this spot is surrounded by stone and you feel somewhat " +
			"save. Nonetheless, everything around you, including " +
			"the stone steps which used to be bleachers, are black " +
			"with soot.\n");
	case 2: return ("Everything is deserted and there is a scary silence about. " +
			"The stones around you are covered with black soot, and " +
			"in the middle of the arena, a ... has been erected. " +
			"From it, a corpse is hanging.\n");
	case 3: return ("Someone is cleaning the black soot from the stones and " +
			"slowly the place looks more and more inhabitable again.\n");
	default: return 0;
      }
}

string
smoke_desc()
{
    switch(QUERY_STATE)
      {
	case 0: return ("");
	case 1: return ("There is smoke all around you! Even the grass " +
			"under your feet is smoking.\n");
	case 2: return ("");
	case 3: return ("");
	default: return 0;
      }
}

string
tent_desc()
{
    switch(QUERY_STATE)
      {
	case 0: return ("");
	case 1: return ("");
	case 2: return ("");
	case 3: return ("");
	default: return 0;
      }
}

string
well_desc()
{
    switch(QUERY_STATE)
      {
	case 0: return ("");
	case 1: return ("");
	case 2: return ("");
	case 3: return ("");
	default: return 0;
      }
}

string
soot_desc()
{
    switch(QUERY_STATE)
      {
	case 0: return ("");
	case 1: return ("");
	case 2: return ("");
	case 3: return ("");
	default: return 0;
      }
}

