#pragma strict_types

inherit "/d/Gondor/morgul/tunnel/hatch_room.c";

#include <macros.h>
#include <ss_types.h>

#include "tunnel_door.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

#define OTHER_ROOM   (MORGUL_DIR + "tunnel/mmtun7")

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun7", "northeast", "@@check_door", 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun9", "up", 0, 4);

    make_the_room(process_string("@@extra_desc"));

    add_item(({"door","metal wall","metal plate","plate"}), VBFC_ME("exa_door"));

    remove_item("ceiling");
    remove_item("roof");
    add_item(({"ceiling","roof"}), VBFC_ME("exa_ceiling"));

    remove_item("wall");
    remove_item("walls");
    add_item(({"wall","walls"}), VBFC_ME("exa_walls"));
    add_item("hatch", VBFC_ME("exa_hatch"));
    add_item("metal plate", VBFC_ME("exa_metal_plate"));
    add_item("black metal plate", VBFC_ME("exa_black_metal_plate"));
    add_item("plate", VBFC_ME("exa_plate"));
    add_item(({"wheel","wooden wheel"}), VBFC_ME("exa_wheel"));
    add_item("lock", VBFC_ME("exa_lock"));

    set_hatch();
}

string extra_desc()
{
  string desc;
  desc = "You seem to have reached the deepest part of this tunnel. " +
    "To the southwest, the tunnel leads steeply upwards, ";

  if((OTHER_ROOM)->query_f_door())
    desc += "while in the other direction the floor levels out. Just under " +
      "the ceiling you can see a thick metal plate protruding. It " +
      "continues into the rock ceiling. This must be a sliding door " +
      "which has been pulled up into the ceiling. ";
  else
    desc += "while in the other direction a metal wall blocks your " +
     "progress. ";

  return desc;
}

int check_door()
{
  if((OTHER_ROOM)->query_f_door())
    return 0;
  else
  {
    write("The metal wall blocks your progress.\n");
    return 1;
  }
  write("\nBUG!\n\n");
  return 1;
}

string exa_door()
{
  if((OTHER_ROOM)->query_f_door())
    return BSN("You can see the lower end of a thick metal plate protruding " +
      "from the ceiling. The upper end of the plate is hidden in the ceiling. " +
      "There are grooves carved into the rock just where the plate meets the " +
      "walls and the floor. The plate probably can be lowered into these " +
      "grooves, thereby blocking the passage northeast. ");
  else
    return BSN("The metal plate blocks the passage to the northeast. It is " +
      "made of thick dark metal. Where it meets the walls, the floor and the " +
      "ceiling, it does not end but disappears into the rock. ");
}

string exa_ceiling()
{
  if((OTHER_ROOM)->query_f_door())
    return BSN("The lower end of a thick metal plate is protruding from the " +
      "ceiling northeast of here. ");
  else
    return "The ceiling is too high for you to reach. \n";
}

void release_wheel()
{
  object partner;

  say(QCTNAME(query_wheel_user()) + " releases " + query_wheel_user()->query_possessive()
      + "grip on the wheel.\n" +
    "The wheel starts turning rapidly. \n");
  write("As you release the wheel, it starts turning rapidly. \n");

  if(partner = HATCH1_ROOM->query_wheel_user())
  {
    partner->catch_msg(BSN("Suddenly, something is pulling on the wheel. " +
      "You need all your strength to prevent the wheel from turning."));
  }
  else
    set_alarm(2.0, 0.0, close_door);
  tell_room(TO,"The wheel stopped turning.\n");
  wheel_user = 0;
}
  
