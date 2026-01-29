/*
 * Base SaMorgan house
 * Tapakah, 05/2021
 */
#pragma no_clone
#pragma strict_types

#include <macros.h>

#include "../defs.h"

inherit SM_ROOM_BASE;

string *file_choices = ({});

public void
configure_samorgan_house (string street, string direction)
{
  set_short("A small house in SaMorgan");
  
  add_exit(street, direction);
  add_fail("auto",
           "The exit to the " + direction + ", and the windows are too "+
           "small to squeeze through.\n");
  add_item(({"window", "windows"}),
           "You can see a few shrubs right under the windows, and the "+
           "village of Sa Morgan beyond.\n");
}

void
reset_room ()
{
  ::reset_room();
  populate_house(file_choices);
}
