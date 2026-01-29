/* Ashlar, 13 Jul 97 */

#include "/d/Ansalon/common/defs.h";
#include "../local.h";

inherit OUTER_IN;

object blue_giant;

void
reset_neraka_room()
{
  if(!objectp(blue_giant))
  {
    blue_giant = clone_object(NNPC+"gate_giant");
    blue_giant->set_color("blue");
    blue_giant->move(this_object(), 1);
  }
}
void
create_neraka_room()
{
	set_short("in a short tunnel under the city wall");
	set_long("You are in a short curved tunnel under the city wall. To the " +
	    "northwest, the tunnel opens up onto a street. A pair of " +
	    "torches illuminate the room, casting a soft yellow light " +
	    "on the bare stone walls.\n");

    add_item_inside();
    add_item(({"torch","torches"}),"The torches are attached to the " +
        "wall.\n");
    add_item("street","The street is to the northwest of here, inside " +
        "the city.\n");

	add_prop(ROOM_I_ALLOW_STEED,1);

    add_exit(NINNER + "r22", "northwest");

    clone_object(NOUTER + "blue/in_gate")->move(TO);
}

