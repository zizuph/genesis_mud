/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 07/95 
 */

#include "../local.h"
inherit ATTACKROOM;
#include RND_MEET

object monster;

void
create_attack_room()
{
    set_short("In a tent");
    set_long("This is the inside of a typical village tent. Some kind " +
	     "of bed is along one side, and there is also a table and " +
	     "a few chests.\n");
    set_change_msg(0,ATTACK + "@@add_prop|_room_i_inside|0@@");
    set_change_short(1,"On a burning patch of land");
    set_change_long(1,"You are in the middle of a fire. Around you, all " +
		    "you can see is smoke and flames. The only way out " +
		    "through the fire seems to be to the northeast.\n");
    set_change_msg(1,SMOLDER);
    set_change_short(2,"On a sooty patch of land");
    set_change_long(2,"You are standing on an open patch of land in " +
		    "what used to be the village of Que Kiri. The land "+
		    "around you appears to have burnt just recently and " +
		    "still everything is blackened by the soot.\n");
    set_change_msg(2,REBUILD);
    set_change_short(3,"On a patch of land");
    set_change_long(3,"You are standing on an open patch of land in " +
		    "the village of Que Kiri. The land "+
		    "around you appears to have burnt some time ago and " +
		    "still things are blackened by the soot.\n");
    set_change_msg(3,FINISH + "@@add_prop|_room_i_inside|1@@");
    
    INSIDE;

    add_exit(ROOM + "vill4","northeast");
    add_item("tent","@@tent_desc@@");
    add_item(({"bed","side","table","chests"}),"@@nothing_special@@");
}

string
nothing_special()
{
    switch(QUERY_STATE)
      {
	case 0: return ("You see nothing special.\n");
	case 1: return ("You find no such thing.\n");
	case 2: return ("You find no such thing.\n");
	case 3: return ("You find no such thing.\n");
	default: return 0;
      }
}

string
tent_desc()
{
    switch(QUERY_STATE)
      {
	case 0: return ("This is the inside of a normal tent.\n");
	case 1: return ("You find no tent.\n");
	case 2: return ("You find no tent.\n");
	case 3: return ("You find no tent.\n");
	default: return 0;
      }
}
