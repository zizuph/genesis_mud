/* Carridin */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit OUTER_IN;

object green_giant;

void
reset_neraka_room()
{
  if(!objectp(green_giant))
  {
    green_giant = clone_object(NNPC+"gate_giant");
    green_giant->set_color("green");
    green_giant->move(this_object(), 1);
  }
}

void
create_neraka_room()
{
	set_short("in a short tunnel under the city wall");
	set_long("You are in a short tunnel under the city wall. To the " +
	    "northeast, the tunnel opens up onto a street. A pair of " +
	    "torches illuminate the room, casting a soft yellow light " +
	    "on the bare stone walls.\n");

    add_item_inside();
    add_item(({"torch","torches"}),"The torches are attached to the " +
        "wall.\n");
    add_item("street","The street is to the northeast of here, inside " +
        "the city.\n");

	add_prop(ROOM_I_ALLOW_STEED,1);

    add_exit(NINNER + "r14", "northeast");

    clone_object(NOUTER + "green/in_gate")->move(TO);
}

