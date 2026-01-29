/*
 * A sea cave tunnel in Faerie
 * By Finwe, August 2004
 */

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit SEA_CAVE_BASE;

void
create_sea_cave_room()
{
    set_short("A tunnel in a sea cave");
    set_long(short() + ". It twists and turns through the dark. The tunnel " +
        "is long and dark looking. The uneven ground runs west and " +
        "northeast.\n");

    remove_prop(ROOM_I_LIGHT);
    set_cave_room();
    reset_room();

    add_exit(FOREST_DIR + "seacave03", "west");
    add_exit(FOREST_DIR + "seacave01", "northeast");
}

public void
init()
{
    ::init();

}
