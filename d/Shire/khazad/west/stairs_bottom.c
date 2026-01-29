
inherit "/d/Shire/khazad/moria_room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("Bottom of stairway");
  set_long("The east end of the entrance hall of Khazad-dum. The "+
  "western wall with Durin's Doors is no longer visible. To the "+
  "east is a stairway as wide as the hall itself. From here the steps "+
  "seem to stretch on forever as they gradually climb deeper into the "+
  "awaiting darkness.\n");

  add_item(({ "hall", "room" }),
     "A cavernous hall in which many races once passed thru in the "+
     "younger days of Khazad-dum.\n");
  add_item(({ "doors", "durin's doors", "doors of durin" }),
     "You see no doors.\n");
  add_item(({ "wall", "western wall" }),
     "It is too far away to see.\n");
  add_item(({ "stairway", "stairs" }),
     "Over a hundred feet across at the base this is the largest "+
     "stairway you have ever seen.\n");
  add_item(({ "steps", "step" }),
     "There is a good five feet between each sprawling step.\n");
  add_item(({ "dust", "dirt" }),
     "It is very fine and has accumulated here for centuries.\n");
  add_exit("/d/Shire/khazad/west/entrance_west","west",0,1);
  add_exit("/d/Shire/khazad/west/stairs","up",0,3);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  switch (random(5))
  {
  case 0:
      tell_room(TO, "The echo of your footsteps breaks the lingering "+
          "silence that has decended on Khazad-dum.\n");
      break;
  case 1:
      tell_room(TO, "As you walk you kick up the fine layer of dust "+
          "that has settled in this empty place.\n");
      break;
  case 2:
      tell_room(TO, "You peer over your shoulder as you think you "+
          "hear the faint fall of soft bare feet.\n");
      break;
  }
}
