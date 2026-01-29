#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
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
    set_short("A overgrown forest road");
    set_long("This a small forest road leading up to a " +
        "farm. From here you can see a few buildings " +
        "between some trees. The road was probably in " +
        "a much better shape some years ago, but now its " +
        "overgrown and weed has taken over almost " +
        "completely.\n");
    add_item(({"weed","road"}),"The road is almost completely " +
        "overgrown with weed. The wheel tracks are still visible " +
        "but most likely this will change within a while.\n");
    add_item(({"buildings","building"}),"From here the buildings " +
        "look like typical farm buildings. One of them looks like " +
        "a stable, but you cant be sure from this distance.\n");
    add_item("farm","From here you cant see much of the farm. Just " +
        "a few buildings, but you cant make up anything more from " +
        "here.\n");
    add_item(({"trees","pines"}),"The trees, mainly pines, are " +
        "growing close to the forest road. You can see a bit " +
        "between the trunks but nothing else than some farm " +
        "buildings to the north. And of course more trees " +
        "behind the others.\n");
    set_terrain(TERRAIN_OPENSPACE);
    set_terrain(TERRAIN_OUTSIDE);
    add_exit("yard","north");
    add_exit("/d/Terel/dabaay/road/n14","southwest");
    (THIS_DIR + "yard")->teleledningsanka();
}



