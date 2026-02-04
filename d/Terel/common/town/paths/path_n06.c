/*  Standard path for the town of Calathin, in the Terel domain

    Original room coded by Vader on 7/21/92

    eventually, there will be 25 path rooms in Calathin, connecting to
    various things such as the ruined manor, houses, farms, and such.

 */

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Terel/common/terel_defs.h"

create_room()
{

   set_short("A small path");
   set_long(break_string("This small path heads into a light forest area.  " +
    "There aren't many trees here, but the few that are are high and " +
    "healthy looking.  The path continues to the west, and " +
    "there is a house to your east.\n", 70));

   add_item(({"tree", "trees"}), "These tall pines really do well in " +
    "this weather.  They are covered\nin snow.\n");

   add_item(({"snow"}), "The snow reflects the sunlight off the top of " +
    "the trees, giving it\na silver color.\n");

   add_item(({"house"}), "It looks like it could use some " +
    "improvements.\n");

   add_item(({"path"}), "It is a lot less beaten than the roads, but " +
    "it still looks worn.\n");

   add_exit(TOWNDIR + "houses/house4", "east", 0);
   add_exit(TOWNDIR + "paths/path_n05", "northwest", 0);


}
 
