/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 03/95 
 */

#include "../local.h"
inherit ATTACKROOM;
#include RND_MEET

object monster;
int corpse = 0;

void
create_attack_room()
{
    set_short(ARENA);
    set_long("You are standing in the middle of a round spot surrounded by " +
	     "three huge stone steps serving as bleachers. This is the " +
	     "center of Que Kiri, the arena. The sights and sounds of the " +
	     "village overwhelm your senses. Never have you seen such a " +
	     "close, interworking group of people. To the northeast you see " +
	     "a large building made from clay, which appears to be some kind " +
	     "of temple. To the south and southwest, you spot the beginnings " +
	     "of some tents, which seem to be the the main living quarters " +
	     "to these people. To the west you see some more tents, and " +
	     "southwest there's another tent beyond the well. A fairly large " +
	     "building catches your eye to the northwest, some kind of large " +
	     "hall. Southeast is another tent that seems more important than " +
	     "others.\n");
    set_change_msg(0,ATTACK + "@@land_highlord@@");
    set_change_short(1,ARENA);
    set_change_long(1,"You are standing in the middle of a round spot " +
		    "surrounded by three huge stone steps serving as " +
		    "bleachers. This is the center of Que Kiri, the arena. " +
		    "The sight and sounds all around you are not very " +
		    "friendly, you can see smoke and fires around. Someone " +
		    "has set up a gibbet here and a lifeless corpse is hanging " +
		    "from it. To the northeast you see a large building which " +
		    "is on fire and seems to be melting. To the south, southeast and " +
		    "southwest, you spot the beginnings of some tents, which " +
		    "look like they have been set on fire, too! The tents to " +
		    "your west and southwest seems to have encountered the " +
		    "same fate. A well can be seen to the southwest, too, in " +
		    "little better shape. A smoldering something can be seen " +
		    "to the northwest which probably was another building.\n");
    set_change_msg(1,SMOLDER);
    set_change_short(2,ARENA);
    set_change_long(2,"You are standing in the middle of a round spot " +
		    "surrounded by three huge stone steps serving as " +
		    "bleachers. This is the center of Que Kiri, the arena. " +
		    "The sight is devastating, everything is burnt and " +
		    "trashed. You cannot hear one single sound, silence lies " +
		    "on the place like death. All around you there is just " +
		    "black soot and ashes. Something that looks like the " +
		    "foundations of a building can be seen in the northwest " +
		    "and another such thing to the northeast. To the southwest " +
		    "the remains of something made from stones is visible.\n");
    set_change_msg(2,REBUILD + "@@take_corpse_down@@");
    set_change_short(3,ARENA);
    set_change_long(3,"You are standing in the middle of a round spot " +
		    "surrounded by three huge stone steps serving as " +
		    "bleachers. This is the center of Que Kiri, the arena. " +
		    "The sights and sounds of the village overwhelm your " +
		    "senses. Never have you seen such a close, interworking " +
		    "group of people. Despite that, something seems wrong " +
		    "still. All the people are rebuilding the village! You " +
		    "still see traces of soot and the remains of fires every" +
                    "where around you. Clay buildings are under construction " +
		    "to your northwest and northeast, and most everywhere " +
		    "else, tents are being set up. A well is visible to the " +
		    "southwest.\n");
    set_change_msg(3,FINISH);
    
    OUTSIDE;

    add_exit(ROOM + "temple","northeast");
    add_exit(ROOM + "vill2","west");
    add_exit(ROOM + "vill1","north");
    add_exit(ROOM + "vill3","east");
    add_exit(ROOM + "shaman","southeast");
    add_exit(ROOM + "well","southwest");
    add_exit(ROOM + "hall","northwest");
    add_exit(ROOM + "vill4","south");

    add_item(({"spot","round spot","arena","bleachers","stone steps","steps"}),
	     "@@arena_desc@@");
    add_item(({"smoke"}),
	     "@@smoke_desc@@");
    add_item(({"gibbet","corpse"}),
	     "@@corpse_desc@@");
}

string 
land_highlord()
{
    /* Let the highlord land and set up the hanging corpse */
    corpse = 1;
    return "";
}

string
take_corpse_down()
{
    /* A villager cuts down the corpse if it's still there */
    if (corpse)
      tell_room(TO,"A villager arrives.\n" +
		"The villager looks strangely at the corpse hanging from the gibbet.\n" +
		"The villager takes out a knife and cuts down the corpse.\n" +
		"The villager breaks the gibbet down into small pieces.\n" +
		"The villager leaves, dragging the corpse away with him.\n");
    corpse = 0;
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
			"in the middle of the arena, a gibbet has been erected. " +
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
	/*case 0: return ("");*/
	case 1: return ("There is smoke all around you! Even the grass " +
			"under your feet is smoking.\n");
	case 2: return ("");
	case 3: return ("");
	default: return 0;
      }
}

string
building_desc()
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
hall_desc()
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
important_tent_desc()
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

/*
string
corpse_desc()
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
*/

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

