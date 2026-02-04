/*  Standard path for the town of Calathin, in the Terel domain

    Original room coded by Vader on 7/21/92

    eventually, there will be 25 path rooms in Calathin, connecting to
    various things such as the ruined manor, houses, farms, and such.
    Updated by Shinto 10-25-98
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <macros.h>
#include <stdproperties.h>

public void
create_room()
{
   set_short("A small path");
    set_long("This small path heads into a light forest area.  " +
        "There aren't many trees here, but the few that are are high and " +
        "healthy looking.  The path continues to the west, and " +
        "there is a house to your east.\n");

    add_item(({"tree", "trees"}), "These tall pines really do well in " +
        "this weather.  They are covered\nin snow.\n");

    add_item(({"snow"}), "The snow reflects the sunlight off the top of " +
        "the trees, giving it\na silver color.\n");

    add_item(({"house"}), "It looks like it could use some " +
        "improvements.\n");

    add_item(({"path"}), "It is a lot less beaten than the roads, but " +
        "it still looks worn.\n");

    add_exit(CALATHIN_DIR + "farms/farm1", "southeast", 0);
/*
    add_exit(CALATHIN_DIR +"paths/path_n07","northeast",0);
*/
    add_exit(CALATHIN_DIR + "paths/path_n05", "northwest", 0);


}
