/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 03/95 
 */

#include "../local.h"
inherit ATTACKROOM;
#include RND_MEET

#define WELL "At the well of Que Kiri"

object monster;
int corpse = 0;

void
create_attack_room()
{
    set_short(WELL);
    set_long("Dominating this place is a large round well, made from bricks " +
	     "and topped with a wooden roof. The well doesn't look too deep, " +
	     "and you can see water at the bottom. To your northeast you see " +
	     "some kind of arena. Around you are a few of the typical tents " +
	     "of the village.\n");
    set_change_msg(0,ATTACK);
    set_change_short(1,WELL);
    set_change_long(1,"");
    set_change_msg(1,SMOLDER);
    set_change_short(2,WELL);
    set_change_long(2,"");
    set_change_msg(2,REBUILD);
    set_change_short(3,WELL);
    set_change_long(3,"");
    set_change_msg(3,FINISH);
    
    OUTSIDE;

    add_exit(ROOM + "arena","northeast");

    add_item(({"spot","round spot","arena","bleachers","stone steps","steps"}),
	     "@@arena_desc@@");
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

string
corpse_desc()
{
    if (corpse)
      return ("This is the lifeless body of a hobgoblin. It has been " +
	      "mutilated very badly and the agony from the torture is still " +
	      "visible in what is left of the face. You notice a piece of " +
	      "paper attached to the corpse.\n");
    return ("You find no corpse.\n");
}

string
paper_desc()
{
    if (corpse)
      return ("On the piece of paper attached to the corpse you can read, " +
	      "written in red blood:\n" +
	      "THIS IS WHAT HAPPENS TO THOSE WHO BETRAY ME.\n" +
	      "                              VERMINAARD\n\n");
    return ("You find no paper.\n");
}

