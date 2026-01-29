/* File:          /d/Khalakhor/cobhan/std/plains_base.c
 * Creator:       Teth
 * Date:          February 12, 1998
 * Modifications: Dec 24, 2001 - moved to the Cobhan area
 * Purpose:       This is the base room for the non-special plains
 *                rooms in Cobhan. It is inherited by those rooms.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 * TODO:          Add doable things.
 */

#pragma save_binary
#pragma strict_types

#include "/d/Khalakhor/sys/paths.h"

inherit STDROOM;

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrain.h"
#include "../local.h"

void set_up_plains();
int block_mountain();
int cross_bridge();
int cross_stream();
int enter_forest();
int enter_forest_thru_stream();
int enter_ngate();
int enter_sgate();

public void
reset_plains_room()
{
}

public void
create_plains_room()
{
     add_item("grass", "The grass is healthy.\n");
}

public void
reset_khalakhor_room()
{
    reset_plains_room();
}

public void
create_khalakhor_room()
{ 
    set_short("on the rocky plains");
    set_long("This is the base room.\n");

    add_item(({"sky","crystal-clear blue sky","blue sky",
        "crystal-clear sky"}),"The sky above is crystal-clear blue, " +
      "with nary a cloud in the sky.\n");
    add_item("cloud","There are no clouds in the sky.\n");
    add_item(({"Khalakhor","khalakhor"}),"It is the continent you " +
      "stand on.\n");

    add_prop(OBJ_I_LIGHT, 1);
    set_terrain(TERRAIN_PLAIN);
    add_std_herbs(5,4);
    set_up_terrain();
    
    seteuid(getuid(this_object()));
    create_plains_room();
    reset_khalakhor_room();
}

public int
block_mountain()
{
    write("The sheer face of the mountainside prevents any movement in " +
    "that direction.\n");
    return 1;
}

public int
cross_bridge()
{
    write("You walk over a piece of ancient rubble that acts as an " +
    "arched bridge over the mountain stream.\n");
    return 0;
}

public int
cross_stream()
{
    write("You pass by rubble of an ancient ruin as you wade through " +
    "the stream.\n");
    return 0;
}

public int
enter_forest()
{
    write("You enter the cool air of a forest glade.\n");
    return 0;
}

public int
enter_forest_thru_stream()
{
    write("You pass by rubble of an ancient ruin as you wade through " +
    "the stream before being greeted by the cool air of a forest glade.\n");
    return 0;
}

public int
enter_ngate()
{
    write("You approach a tall barricade.\n");
    return 0;
}

public int
enter_sgate()
{
    write("You approach a tall barricade.\n");
    return 0;
}

public string
my_long()
{
    return "The bloody rocky plains. ";
}

public void
set_up_plains()
{
}


