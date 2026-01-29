
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. The sights and sounds of"
      + " the village overwhelm your senses. Never have you seen"
      + " such a close, interworking group of people. To the northeast"
      + " you spot the beginnings of some tents, which seem to be the"
      + " the main living quarters to these people. To the west you"
      + " spot the entrance of the village.", 70));
    set_change_msg(0,"All the people suddenly turn their heads as " +
		   "a dark shadow can be sensed looming overhead.\n");
    set_change_short(1,"A smoking grass path");
    set_change_long(1,"You are standing on a smoking grass path within " +
		    "the Que Kiri village. The sights and sounds are " +
		    "most disturbing, and you can hear screams and " +
		    "fighting sounds coming from the tents to the " +
		    "northeast. To your west, you can see the remains " +
		    "of the entrance to the village through the smoke.\n");
    set_change_msg(1,"The smoking from the grass slowly fades out.\n");
    set_change_short(2,"A deserted grass path");
    set_change_long(2,"You are standing on burnt grass which once was a " +
		    "path and which is now completely deserted. The remains of " +
		    "something that could have been tents is to your " +
		    "northeast. To the west is a charred black opening in " +
		    "the remains of a kind of wall, which probably used to " +
		    "be the entrance to the village, now barely recognizable.\n");
    set_change_msg(2,"");
    /*  if required add also in a similar way:
       set_change_short(3,...);
       set_change_long(3,...);
       set_change_msg(3,...);
       set_change_short(4,...);
       set_change_long(4,...);
       set_change_msg(4,...);
       */
    
    OUTSIDE;

    add_exit(ROOM + "kiri_c9","northeast");
    add_exit(ROOM + "kiri_d7","west");

    add_item(({"tents","tent","remains"}),"@@tent_desc");
    add_item(({"entrance","wall",}),"@@wall_desc");
    add_item(({"smoke",}),"@@smoke_desc");
}

string
tent_desc()
{
    switch (state_of_room)
      {
	case 0: return "You can reach the tents by going northeast. A lot " +
	  "of laughter and noise is coming from that direction.\n";
	case 1: return "You can reach the tents by going northeast. Strange " +
	  "gurring voices can be heard from there and also human screams.\n";
	case 2: return "These can hardly be called tents anymore. A few metal " +
	  "pieces is all that is left.\n";
	case 3: return "You think you can hear someone there.\n";
	case 4: return "You can see some people rebuilding the tents.\n";
	default: return 0;
      }
}

string
wall_desc()
{
    switch(state_of_room)
      {
	case 0: return "It's the city wall.\n";
	case 1: return "The wall is barely visible through all the smoke.\n";
	case 2:
	case 3: return "Only the foundation of the wall is left, it is all " +
	  "blackened and broken.\n";
	case 4: return "You can see people rebuilding the wall.\n";
	default: return 0;
      }
}

string
smoke_desc()
{
    switch(state_of_room)
      {
	case 1: return "There is smoke all around you! Even the grass " +
	  "under your feet is smoking.\n";
	default: return 0;
      }
}

int
hook_change_room(int which)
{
    if (which == 0)
      {
	  if (monster)
	    return 0;
	  monster = RANDOM_MEET(TABLE);
	  monster->move_living("xx",TO);
	  return 1;
      }
    if (which == 1)
      if (monster)
	return 0;
    return 1;
}

