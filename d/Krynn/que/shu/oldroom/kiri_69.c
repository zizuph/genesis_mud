
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"

# define PERS METNAMEI(this_player())
object monster;

void
create_attack_room()
{
    set_short("On grass path in Que Kiri");
    set_long(BS("This path doesn't seem to see alot of use. Looking"
      + " around you notice a lack of people in this part of the"
      + " village. There is an interesting wooden structure here"
      + " though. Skulls of rather large plains animals hang from"
      + " front walls while a wind chime made of small bones"
      + " rattles in the wind nead the door. The path continues to"
      + " the northeast and southwest.", 70));

    OUTSIDE;

    add_exit(ROOM + "kiri_5a","northeast");
    add_exit(ROOM + "kiri_78","southwest");

}

void
init()
{
::init();
 add_action("open", "open");
}

int
open(string arg)
 {
   if(!arg)
    {
     notify_fail("Open what?\n");
     return 0;
    }
   if(arg == "door" || arg == "the door")
    {
     write(BS("You open the door, causing the rusting hinges to screech"
      + " in protest.", 70));
     say(PERS + " opens the door to the strange looking building.\n");
     add_exit(ROOM + "kiri_7a","enter");
     return 1;
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

