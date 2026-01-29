#include "../../ctower.h"

inherit FINSTD;
 
void
create_fin()
{
  set_long(query_long() + 
      "The north wall is dominated by a huge mirror.\n" );
  add_exit(CTOWER_ROOM_FIN + "fin2", "south");
  add_item(({"mirror", "huge mirror"}), "@@mirror_desc@@");
  add_item("runes", "You can't decipher them.\n");
}

string mirror_desc()
{
  object mirror;
  string str = "An enormous mirror set into the north wall.  It's " +
      "golden frame is marked with hundreds of runes.\n";

  if (!(mirror = find_object(CTOWER_ROOM_FIN + "in_mirror")) ||
      !sizeof(filter(all_inventory(mirror), interactive)))
  {
    str += "Somehow, the surface of the mirror looks strange..." +
        "as if you could walk straight into it.\n";
  }

  return str;
}

int enter(string str)
{
  object mirror;

  if (!strlen(str))
  {
    return 0;
  }

  if (query_verb() == "enter")
  {
    if (str != "mirror" && str !=  "the mirror" &&
         str != "huge mirror" && str != "the huge mirror")
    {
      return 0;
    }
  }
  else if (str != "through mirror" && str != "through the mirror" &&
      str != "through huge mirror" && str != "through the huge mirror")
  {
    return 0;
  }
    
  write("You step into the mirror and find yourself in another place!\n");

  this_player()->move_living("through the mirror", CTOWER_ROOM_FIN +
      "central2", 1);
  return 1;
}

void init()
{
  ::init();

  add_action(enter, "enter");
  add_action(enter, "walk");
}
 
