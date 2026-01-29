#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This is the basement of a large building. All around " +
    "you are walls made from dark roughly hewn boulders. A narrow passage " +
    "is leading west. On the northern wall of the room, a flight of stairs " +
    "is leading up to the next floor.");
  add_item(({"tunnel","passage"}), "A dark narrow passage is leading westwards.\n");
    add_tunnel_ceiling();
    add_tunnel_wall();
  add_item(({"flight","stair","stairs","flight of stairs"}), BSN(
    "Along the northern wall of the room, a flight of stairs is leading up into " +
    "the next level of the building. The steps of the stairs are made of the same " +
    "large stone slabs as the floor and the ceiling. "));
  set_road(5);
  set_side("northeast");

  add_prop(ROOM_I_LIGHT,-1);
  add_exit(MORGUL_DIR + "city/tunnels/pass01","west","@@check_exit",3);
  add_exit(MORGUL_DIR + "city/towers/ne_tow3","up","@@check_exit",3);
  clone_object(MORGUL_DIR + "city/doors/bne1trapup")->move(TO);
}

