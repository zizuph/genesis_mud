/* Ashlar, 11 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit OUTER_IN;

object white_giant;

void
reset_neraka_room()
{
  if(!objectp(white_giant))
  {
    white_giant = clone_object(NNPC+"gate_giant");
    white_giant->set_color("white");
    white_giant->move(this_object(), 1);
  }
}

void
create_neraka_room()
{
	set_short("in a short tunnel under the city wall");
	set_long("You are in a short tunnel under the city wall. To the " +
	    "southeast, the tunnel opens up onto a street. A pair of " +
	    "torches illuminate the room, casting a soft yellow light " +
	    "on the bare stone walls.\n");

    add_item_inside();
    add_item(({"torch","torches"}),"The torches are attached to the " +
        "wall.\n");
    add_item("street","The street is to the southeast of here, inside " +
        "the city.\n");

    add_prop(ROOM_I_ALLOW_STEED,1);

    add_exit(NINNER + "r6", "southeast");

    clone_object(NOUTER + "white/in_gate")->move(TO);
    reset_neraka_room();
}

