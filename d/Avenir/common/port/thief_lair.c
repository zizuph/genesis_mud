#pragma strict_types
#include "/d/Avenir/common/common.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";

void
create_room()
{

    object gate;

    set_short("A small chamber");
    set_long("This is a small chamber for thieves.");
    set_terrain(TERRAIN_UNDERGROUND);
    reset_room();
}

void
reset_room()
{

}
