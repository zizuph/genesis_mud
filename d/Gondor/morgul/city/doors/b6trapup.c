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
  set_pass_command(({"d","down"}));
  set_door_name(({"trap door","hatch","board","plank","door","trapdoor"}));
  set_door_desc(VBFC_ME("long_desc"));
  set_closed_desc("");
  set_open_desc("There is an open trap door leading down.\n");

  set_other_room(MORGUL_DIR + "city/tunnels/cellarb6");

  set_open(0);         /* 1 if open, 0 if closed */
  enable_reset();
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
  set_closed_desc("There is a closed trap door leading down.\n");
  ENV(TO)->change_my_desc(query_closed_desc(),TO);
  ::open_door(arg);
  return 1;
}

string
long_desc()
{
  if(query_open())
    return BSN(
      "A simple wooden board on iron hinges that is leaning " +
      "against a wall next to a hole in the floor. Looking into the hole you " +
      "can see a rickety ladder leading down. ");
  else
    return BSN(
      "A simple wooden board on iron hinges that probably covers " +
      "a hole in the floor. The board looks rather heavy. ");

}

void
reset_door()
{
  set_closed_desc("");
}
