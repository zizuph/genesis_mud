#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This is the ground floor of tower. All around " +
    "you are walls made from dark roughly hewn boulders. " +
    "On the southern wall of the room, a flight of stairs " +
    "is leading up to the next floor.");
  add_item(({"floor","ground"}), BSN(
    "The floor seems to be made of the same dark boulders as the " +
    "walls, only they have been hewn into long slabs and then polished."));
  add_item(({"ceiling","roof"}), BSN(
    "The ceiling has been made out of roughly cut wooden planks " +
    "lying on thick wooden beams that run from one wall to the next."));
  add_item(({"flight","stair","stairs","flight of stairs"}), BSN(
    "Along the southern wall of the room, a flight of stairs is leading up " +
    "to the next floor of the tower. The steps of the stairs are made of the same " +
    "large stone slabs as the floor. "));
  add_item(({"wall","walls","stones"}), BSN(
    "The walls of the tower are made from smoothly hewn black boulders. " +
    "They are so black that is seems as if they are swallowing any " +
    "light that might come down here. "));
  set_road(9);
  set_short_desc("inside a mighty tower in Minas Morgul");
  set_side("southeast");

  add_prop(ROOM_I_LIGHT,-1);
  add_prop(ROOM_I_INSIDE,1);
  add_exit(MORGUL_DIR + "city/towers/se_tow2","up","@@tower_stairs|up@@",4);
}

