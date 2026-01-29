inherit "/std/door";
#include "/d/Gondor/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#define MIN_STRENGTH 40

create_door()
{
  ::create_door();
  set_door_id("Morgul_B6_Trapdoor");
  set_pass_command(({"u","up"}));
  set_door_name(({"trap door","hole","ceiling","hatch","board","plank","door","trapdoor"}));
  set_door_desc(VBFC_ME("long_desc"));

  set_other_room(MORGUL_DIR + "city/barrack6");

  set_open(0);         /* 1 if open, 0 if closed */
}

open_door(string arg)
{
  int strength;
  strength = TP->query_stat(SS_STR);
  if(!arg || (arg != "trap door" && arg != "hatch" && arg != "door" && 
              arg != "trapdoor" && arg != "board" && arg != "plank"))
    return 0;
  if(strength < MIN_STRENGTH)
  {
    write("The large plank is too heavy.\n");
    say(QCTNAME(TP) + " tries to lift the heavy plank to open the trapdoor, but fails.\n");
    return 1;
  }
  ::open_door(arg);
  return 1;
}

string
long_desc()
{
  if(query_open())
    return BSN("There is a hole in the ceiling. Using the ladder you can climb up " +
      "to the ground floor of the building. ");
  else
    return BSN("Looking at the ceiling, you notice that there seems to be a hole " +
      "covered by a large wooden plank. It looks like a trap door leading up to the " +
      "ground floor of the building. If you are strong enough you might open the " +
      "trap door and climb up using the ladder here. ");
}
