/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

void
create_thief_room()
{
  set_short("In a hallway");
  set_long("@@my_long");
  
  add_exit(THEIWAR + "r3","west");

  DARK;
}

string
my_long()
{
  if (TP->query_race() == "dwarf")
    return "You notice excellent craftmanship here in these halls. " +
      "Only the best dwarven craftsmen were able to produce this  " +
      "fine, even and balanced work. The hallway ends here.\n";
  return "This hallway ends here. You are " +
    "positive that this must be dwarven work, cutting into the hard " +
    "rock like this.\n";
}

reset_thief_room()
{
  object ob;
  if (random(3))
    return;
  ob = clone_object("/std/coins");
  ob->set_coin_type("silver");
  tell_room(TO,"You hear a clear metallic sound as something clinks on the floor.\n");
  ob->move(TO);
}
