inherit "/d/Gondor/common/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void    reset_room();

object  captain;

void
create_room()
{
    set_short("Entryhall");
    set_long(BSN(
        "This is the entryhall of the house, the door is leading out to "
      + "the south. Pale stone walls "
      + "are covered by valuable tapestries and on a carpet in the center "
      + "of the room stands a heavy wooden table. Doorways go north and "
      + "west and a flight of stairs is leading to the upper floor of the "
      + "house."));

    add_item(({"walls", "stone walls", "tapestries", }), BSN(
        "The stone walls are covered by valuable tapestries that show "
      + "colourful floral patterns."));
    add_item(({"floor", "carpet"}), BSN(
        "The stone floor is covered by a thick colourful carpet. In the "
      + "middle of the room a massive wooden table is standing on the carpet."));
    add_item("table",BSN(
        "The table is large and massive, the legs decorated by complicated "
      + "carvings."));
    add_item(({"stairs", "flight", "flight of stairs", }), BSN(
        "A dozen stone steps make up a flight of stairs that is leading "
      + "to the upper floor of the building."));
    add_item(({"doorways", "doors"}),
        "They probably lead to the other rooms of the house.\n");

    add_exit(MINAS_DIR+"houses/h3ncrc4","north",0,0);
    add_exit(MINAS_DIR+"houses/h2ncrc4","west",0,0);
    add_exit(MINAS_DIR+"houses/h4ncrc4","up",0,0);

    add_prop(ROOM_I_INSIDE, 1);

    clone_object(MINAS_DIR+"doors/h1_ncrc4_in")->move(TO);

    reset_room();
}

void
reset_room()
{
    if (objectp(captain))
        return;

    captain = clone_object(MINAS_DIR + "npc/quest/captain");
    captain->arm_me();
    captain->move_living("down", TO);
}

