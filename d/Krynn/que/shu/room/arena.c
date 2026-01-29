/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 03/95 
 */

#include "../local.h"
inherit OUTBASE_ROOM;
#include RND_MEET

int corpse = 0;

void
create_que_shu_room()
{
    set_place(ARENA);
    set_long_desc("You are standing in the middle of a round spot surrounded " +
		  "by three huge stone steps serving as bleachers. This is the " +
		  "center of Que Shu, the arena. The sights and sounds of the " +
		  "village overwhelm your senses. Never have you seen such a " +
		  "close, interworking group of people. To the northeast you " +
		  "see a large building made from clay, which appears to be " +
		  "some kind of temple. To the south and southwest, you spot " +
		  "the beginnings of some tents, which seem to be the " +
		  "main living quarters to these people. To the west you see " +
		  "some more tents, and southwest there's another tent beyond " +
		  "the well. A fairly large building catches your eye to the " +
		  "northwest, some kind of large hall. The only way out of the " +
		  "arena is back north.\n");

    add_exit(ROOM + "intersect1","north");

    add_item(({"spot","round spot","arena","bleachers","stone steps","steps"}),
	     "@@arena_desc@@");
    set_auto_reset(SHUTABLE,random(3),random(3));
}

string
arena_desc()
{
    return ("You cannot see anyone using this arena currently, " +
	    "and otherwise you cannot find anything special. " +
	    "The arena is about thirty feet in diameter and each " +
	    "stone step is one foot high. All inhabitants of the " +
	    "village will easily have enough room to watch.\n");
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


