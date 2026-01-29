/* created by Aridor 04/19/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
  set_short("In a cavern");
  set_long("@@my_long");
  
  add_exit(THEIWAR + "r24", "west");
  add_exit(THEIWAR + "r4", "down");

  DARK;
}

string
my_long()
{
  if (TP->query_race() == "dwarf")
    return "You sensitive nose notices the aura of metal in this area, " +
      "it comes from all around you, but maybe not directly. " +
      "The cavern you are in extends to the west, and slopes downwards " +
      "here into a circle. The floor is as even as possible, to avoid " +
      "any hazards when mining goods are transported this way.\n";
  return "The cavern you are in extends to the west, and slopes downwards " +
    "here into a circle. The floor is as even as possible, to avoid " +
    "any hazards when mining goods are transported this way.\n";
}
