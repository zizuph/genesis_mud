/* created by Aridor 04/19/94 */

#include "../local.h"

inherit ROOM_BASE

#include RND_MEET

object dwarf;

void
create_thief_room()
{
  set_short("In a cavern");
  set_long("@@my_long");
  
  add_exit(THEIWAR + "r38", "west");
  add_exit(THEIWAR + "r34", "east");
  add_exit(THEIWAR + "r24", "down");

  DARK;
}


string
my_long()
{
  return "It's a passageway leading east and west. Next to the north wall, " +
    "there is a hole in the ground. You notice some kind of stairs leading " +
    "down into the hole. The hallway is quite wide here.\n";
}

    
void
reset_thief_room()
{
  if (dwarf)
    return;
  dwarf = RANDOM_MEET(THEIWARTABLE);
  dwarf->move_living("xxx",TO);
}

