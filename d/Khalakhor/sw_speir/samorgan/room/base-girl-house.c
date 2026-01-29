/*
 * A small house in SaMorgan where a single girl lives
 * Tapakah, 04/2021
 */

#pragma no_clone
#pragma strict_types

#include "../defs.h"

inherit SM_HOUSE_BASE;

void
create_samorgan_house (string street, string direction)
{
  ::configure_samorgan_house(street, direction);

  set_long("You are inside a small house in SaMorgan. It contains just one room, "+
           "clean and neat, but also very modest. There is a narrow bed in the "+
           "corner, a sink under one of the windows, and a counter under another. "+
           "A cupboard, a closet, a table and a couple of chairs complete the "+
           "setup.\n");
  add_item("bed", "The bed is simple and narrow, cleanly made.\n");
  add_item("sink", "The sink is clean. There are no dishes in it.\n");
  add_item("cupboard",
           "The cupboard probably contains the dishes and the food. "+
           "It is locked and closed.\n");
  add_item("counter", "The counter has a wooden cutting board on it.\n");
  add_item(({"board", "cutting board"}),
           "The board has scratches from many products that had been cut on it.\n");
  add_item("closet",
           "It is tall and narrow, probably having a few dresses in it and not "+
           "much beyond it.\n");
  add_item("table",
           "A small square table, about a couple of feet a side. The surface "+
           "is wiped clean.\n");
	add_item(({"chair", "chairs"}),
           "The two simple chairs are made out of wood and stand on the opposite "+
           "sides of the table.\n");
  file_choices = SM_GIRLS;
  reset_room();
}
