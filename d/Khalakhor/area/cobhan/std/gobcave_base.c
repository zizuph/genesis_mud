/* File:          /d/Khalakhor/cobhan/std/gobcave_base.c
 * Creator:       Teth
 * Date:          February 12, 1998
 * Modifications: Dec 24, 2001 - moved to the Cobhan area
 * Purpose:       This is the base room for the non-special goblin
 *                cave rooms in Cobhan. It is inherited by those rooms.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 * TODO:          Add doable things.
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
#include "../local.h"

inherit HERBSEARCH;

void set_up_gobcave();
int enter_road();
string *herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD,}));

public void
reset_gobcave_room()
{
}

public void
create_gobcave_room()
{
}

public void
reset_room()
{
    set_searched(0);
    reset_gobcave_room();
}

public void
create_khalakhor_room()
{
    set_short("in a cave");
    set_long("This is the base room.\n");

    add_item(({"Khalakhor","khalakhor"}),"It is the continent you " +
      "stand on.\n");
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_MIXEDWOOD);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}),({"forest","here","ground","woods",
        "underbrush"}),4);

    seteuid(getuid(this_object()));

    create_gobcave_room();
    reset_room();
}

public int
enter_road()
{
    write("You walk out on to the road.\n");
    return 0;
}

public string
my_long()
{
    return "This is the goblin cave. ";
}

public void
set_up_gobcave()
{
}


