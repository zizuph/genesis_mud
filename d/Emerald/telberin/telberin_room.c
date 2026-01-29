/*
 * /d/Emerald/telberin/telberin_room.c
 *
 * base room for telberin
 *
 */

#pragma strict_types

inherit "/d/Emerald/std/room";

#include "telberin_room.h"
#include <stdproperties.h>

static string quarter_name;

public void set_quarter(string quarter);

public void
config_telberin_room(string quarter)
{
    set_quarter(quarter);

    if (strlen(quarter))
    {
        set_short("In the " + quarter + " quarter of Telberin");
    }
    else
    {
        set_short("On Telberin Island");
    }
}

public void
create_telberin_room()
{
}

nomask void
create_emerald_room()
{
    // Telberin is the center of elven life, and the site blessed by Telan-Ri
    // himself.  It is, therefore, one of the brightest parts of Emerald.
    add_prop(ROOM_I_LIGHT, 10);

    create_telberin_room();
}

public void
set_quarter(string quarter)
{
    quarter_name = quarter;
}

public string
query_quarter()
{
    return quarter_name;
}

public void
add_rose_garden(string intro)
{
    add_item("rose garden", (strlen(intro) ? intro + "  " : "") +
        "The rose garden is here.\n");
}

public void add_fruit_garden(string intro)
{
    add_item("fruit garden", intro + "  The fruit garden is here.\n");
}

public void add_wflower_garden(string intro)
{
    add_item("fruit garden", intro + "  The wildflower garden is here.\n");
}

public void 
add_arboreal_garden(string intro)
{
    add_item("arboreal garden", intro + "   The arboreal garden is here.\n");
}

public void
add_moss_garden(string intro)
{
    add_item("moss garden", intro + "  The moss garden is here.\n");
}

public void
add_topiary_garden(string intro)
{
    add_item("topiary garden", intro + "  The topiary garden is here.\n");
}

public void
add_rock_garden(string intro)
{
    add_item("rock garden", intro + "  The rock garden is here.\n");
}

public void
add_magic_garden(string intro)
{
    add_item("magic garden", intro + "  The magic garden is here.\n");
}

public void
add_telberin_outside_items()
{
    // This is where we put descriptions for outside items that should be
    // visible from any outside room in the city--the sky, the lake, etc.
    // When an individual outside room wants these descriptions, it can
    // simply call this function.

    try_item( ({ "sky", "up" }),
        "The sky is a radiant blue, crossed now and again by high"
      + " trailing clouds.\n");
    try_item( ({ "cloud", "clouds", "high clouds", "trailing clouds",
                 "high trailing clouds" }),
        "Clouds drift gently above the city, decorating the vibrant"
      + " blue sky.\n");
}
