#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/dunland/wild/dunlendings.h"

void
reset_room()
{

    if (!present("galuk"))
        room_add_object(DUN_WILD_NPC + "galuk");
}


public void
create_gondor()
{

    set_short("Inside a small wooden house.");
    set_long("The house is very small, at the "
      + "northeast corner stands a bed. A " 
      + "drawer can be seen next to it. At the "
      + "western wall stands a desk and a chair. "
      + "The walls are simple and made of wood, you "
      + "get the impression that someone might live "
      + "here more permanently.\n");

    add_prop(ROOM_I_INSIDE,1);
    add_item(({"wall","walls"}), BSN(
	"The walls are made of wood like the rest of the "
	+ "house. They are completely bare."));
    add_item("bed", "When you examine the bed closer, "
      + "you notice that it looks recently used. Next "
      + "to it stands a drawer");
    add_item(({"desk", "chair"}), BSN(
	"At the middle of the western wall stands a wooden  " 
	+ "desk and a small chair. On the table you can see "
	+ "some empty sheets of yellowed paper along with a " 
	+ "feather and some ink."));
    add_item(({"floor", "boards", "wooden boards"}), BSN(
	"The floor is made of wooden boards. It "
	+ "crunches a bit when you walk on it."));
    add_item("ceiling", "The ceiling is made of wood. It looks "
      + "as if the one who built it is certain that it does not "
      + "rain in Rohan.\n");
    add_item("drawer", "Next to the bed stands a drawer. It is made of "
      + "wood. It is empty now, but probably it is used to storage "
      + "clothes and weapons while sleeping.\n");
    add_item(({"ink", "feather"}), BSN(
	"On the desk you can see both ink and a feather, "
	+ "undoubtedly used to write things."));
    add_item(({"paper", "papers", "yellowed paper",
	"yellowed papers", "sheets", "sheet"}), BSN(
	"On the paper are some sheets of yellowed paper "
	+ "lying next to some ink and a feather."));

    set_no_exit_msg(({"southwest","south","southeast"}),
      "You decide to walk up to the southern walls, but they look " +
      "quite simple and ordinary. You decide to walk back to the " +
      "centre of the room.\n");
    set_no_exit_msg(({"northwest","north","northeast"}),
      "You decide to walk up to the northern walls, but they look " +
      "quite simple and ordinary. You decide to walk back to the " +
      "centre of the room.\n");
    set_no_exit_msg("west", "You decide to walk up to the western " +
      "wall but it looks quite simple and ordinary. You decide to " +
      "walk back to the centre of the room.\n");
    set_no_exit_msg("east", "You decide to walk up to the eastern " +
      "wall but it looks quite simple and ordinary. You decide to " +
      "walk back to the centre of the room.\n");



    add_exit(DUN_WILD_ROOMS + "field08", "out");

    reset_room();

}
