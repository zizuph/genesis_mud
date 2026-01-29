/*
 * A small house in SaMorgan where a single boy lives
 * Tapakah, 04/2021
 */

#pragma no_clone
#pragma strict_types

#include "../defs.h"

inherit SM_HOUSE_BASE;

void
create_samorgan_house (string street, string direction)
{
  configure_samorgan_house(street, direction);
  set_long("You are inside a small house in SaMorgan. It contains just one room, "+
           "and it's already messy as it could be. There is an unmade cot under "+
           "a small window, and a workbench under another. Clothes are piled "+
           "upon a dresser, not inside of it. There are also a table, a chair "+
           "and a small cupboard.\n");
  add_item(({"cot", "bed"}), "It looks like a spot to crash in after a rough "+
           "day.\n");
  add_item("workbench", "A couple of simple tools and pieces of wood are scattered "+
           "on the workbench.");
  add_item(({"tools", "hammer", "cutter", "awl"}),
           "You recognize a hammer, a cutter and an awl among the tools. They "+
           "look old and not very useful anymore.\n");
  add_item(({"wood", "pieces of wood", "pieces", "piece"}),
           "These are just small pieces of wood that someone practiced their "+
           "carpentry skills with.\n");
  add_item(({"clothes", "dresser"}), "Obviously, the owner is not very neat. "+
           "The clothes and the dresser are clean, though.\n");
  add_item("cupboard",
           "The small cupboard probably contains a few dishes and the food. "+
           "It is locked and closed.\n");
  add_item("table",
           "A small square table, about a couple of feet a side. The surface "+
           "still has some crumbs and some cuts from the knife.\n");
	add_item("chair",
           "A simple wooden chair is at the table overlooking the window.\n");
  file_choices = SM_BOYS;
  reset_room();
}
