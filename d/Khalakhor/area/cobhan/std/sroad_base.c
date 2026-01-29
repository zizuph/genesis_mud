/* File:          /d/Khalakhor/cobhan/std/sroad_base.c
 * Creator:       Teth
 * Date:          February 12, 1998
 * Modifications: Dec 24, 2001 - moved to the Cobhan area
 * Purpose:       This is the base room for the non-special south
 *                road rooms in Cobhan. It is inherited by those rooms.
 * Related Files: /d/Khalakhor/cobhan/
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

void set_up_sroad();
int block_sroad();
int enter_camp();
int enter_cave();
int enter_gate();
int enter_mine();
string *herbs = HERBMASTER->query_herbs(({TERRAIN_MIXEDWOOD,}));

public void
reset_sroad_room()
{
}

public void
create_sroad_room()
{
}

public void
reset_room()
{
    set_searched(0);
    reset_sroad_room();
}

public void
create_khalakhor_room()
{
    set_short("on a road");
    set_long("This is the base room.\n");

    add_item(({"sky","crystal-clear blue sky","blue sky",
        "crystal-clear sky"}),"The sky above is crystal-clear blue, " +
      "with nary a cloud in the sky.\n");
    add_item("cloud","There are no clouds in the sky.\n");
    add_item(({"Khalakhor","khalakhor"}),"It is the continent you " +
      "stand on.\n");
    add_prop(OBJ_I_LIGHT, 1);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs)}),({"forest","here","ground","woods",
        "underbrush"}),4);

    seteuid(getuid(this_object()));

    create_sroad_room();
    reset_room();
}

public int
enter_camp()
{
    write("You enter a small war camp.\n");
    return 0;
}

public int
enter_cave()
{
    write("You enter a lit cave.\n");
    return 0;
}

public int
enter_gate()
{
    write("You approach a gate blocking the road.\n");
    return 0;
}

public int
enter_mine()
{
    write("You enter the humid gloom of a mine.\n");
    return 0;
}

public int
block_sroad()
{
    write("The road south is blocked by rockfall.\n");
    return 1;
}

public string
my_long()
{
    return "This is the south road. ";
}

public void
set_up_sroad()
{

}


