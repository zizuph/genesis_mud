/* File:          /d/Khalakhor/cobhan/std/sgate_base.c
 * Creator:       Teth
 * Date:          February 12, 1998
 * Modifications: Dec 24, 2001 - moved to the Cobhan area
 * Purpose:       This is the base room for the non-special south
 *                gate rooms in Cobhan. It is inherited by those rooms.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:      set_logged() should be set from 0 to 3.
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

void set_up_sgate();
int enter_plains();
int enter_road();
string *herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD,}));

public void
reset_sgate_room()
{
}

public void
create_sgate_room()
{
}

public void
reset_room()
{
    set_searched(0);
    reset_sgate_room();
}

public void
create_khalakhor_room()
{
    set_short("in the south gate");
    set_long("This is the base room.\n");

    add_item(({"Khalakhor","khalakhor"}),"It is the continent you " +
      "stand on.\n");
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_MIXEDWOOD);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}),({"forest","here","ground","woods",
        "underbrush"}),4);

    seteuid(getuid(this_object()));

    create_sgate_room();
    reset_room();
}

public int
enter_plains()
{
    write("You step onto the plains.\n");
    return 0;
}

public int
enter_road()
{
    write("You leave the gates for the road.\n");
    return 0;
}

public string
my_long()
{
    return "This is the south gate. ";
}

public void
set_up_sgate()
{
}


