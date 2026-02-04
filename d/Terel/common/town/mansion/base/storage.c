/*  Basement room in the Mansion.  Coded by Vader on 8/21/92    */
inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"

create_room()
{
   set_short("Storage room");
   set_long(break_string(
     "The dust and cobwebs in this room would make dust mites " +
     "sneeze.  Many footprints have been left on the dust that " +
     "has remained on the floor for years.  This room was used for " +
     "storage, but now stores mostly dust.  The walls are made of " +
     "stone blocks, with the filling in between them drying and " +
     "cracked.\n", 70));

   add_item(({"footprints", "prints"}),  "There are so many, " +
     "that you can't tell where any go or come from.\n");


   add_exit(BASE + "hall2", "east", 0);

}

