inherit "/d/Gondor/morgul/tunnel/hatch_room";
#include <macros.h>
#include <ss_types.h>
#include "tunnel_door.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

void
create_room()
{
    add_exit(MORGUL_DIR + "tunnel/mmtun5", "up", 0, 4);
    add_exit(MORGUL_DIR + "tunnel/mmtun7", "down", 0, 4);

    make_the_room("The tunnel continues to descend steeply towards " +
        "the southwest, leading upwards to the northeast. ");

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

void release_wheel()
{
  object partner;

  say(QCTNAME(query_wheel_user()) + " releases "+query_wheel_user()->query_possessive()+" grip on the wheel.\n" +
    "The wheel starts turning rapidly. \n");
  write("As you release the wheel, it starts turning rapidly. \n");

  if(partner = HATCH2_ROOM->query_wheel_user())
  {
    partner->catch_msg(BSN("Suddenly, something is pulling on the wheel. " +
      "You need all your strength to prevent the wheel from turning."));
  }
  else
    close_door();
  tell_room(TO,"The wheel stopped turning.\n");
  wheel_user = 0;
}
  
