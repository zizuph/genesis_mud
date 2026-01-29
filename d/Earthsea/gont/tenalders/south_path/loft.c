/*
 * barn loft in Gont
 * Coded by Amelia 4/10/98
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>
#include <macros.h>

private int plank_exposed = 0, plank_closed = 1;
private object *hens = allocate(5);

public void
create_earthsea_room()
{
    set_short("A hay loft");
    set_long("You find yourself in a loft full of hay. " +
        "It is fragrant here with a clean smell of grasses dried " +
        "in the sun. Round bales of hay are stacked all around, reaching " +
        "up to the pine planked ceiling and lies around thickly " +
        "carpeting the floor of the loft. Sunlight filters in " +
        "from between cracks in the ceiling. It is quiet here " +
        "except for the noise from the animals.\n");
    add_item("floor", "The floor of the loft is covered with " +
        "hay and chicken droppings.\n");
    add_item("loose plank", "@@loose_plank");
    add_item((({"hay", "bales of hay", "bales" })),
        "The hay is stacked in round heaps or bales all " +
        "around you and under your feet.\n");
    add_item((({"ceiling", "walls", "planks", "plank", "wall"})),
        "@@plank_desc");
    add_item("cracks", "Cracks between the wide planks in the " +
        "ceiling allow sunlight to filter in.\n");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "search_hay");
    add_exit("barn", "down");
    add_exit("orchard", "out", "@@plank_closed", 0,
        "@@plank_closed");
    reset_room();
}

public void
reset_room()
{
    object to = this_object();
    int i = 5;

    plank_exposed = 0;
    plank_closed = 1;

    while(i--)
    {
        if(!objectp(hens[i]) || environment(hens[i]) != to)
        {
            hens[i] = clone_object("/d/Earthsea/gont/tenalders/npc/chicken");
            hens[i]->move(to);
            hens[i]->command("emote comes fluttering in.");
        }
    }
}

public int
push_plank(string str)
{
    object tp = this_player();

    if(!plank_exposed || !str || (str != "plank" && str != "loose plank"))
    {
        return notify_fail("Push what?\n");
    }

    if(plank_exposed && !plank_closed)
    {
        return notify_fail("You push on the plank, but it is already " +
            "open.\n");
    }

    plank_closed = 0;
    write("You push and pull on the loose plank " +
        "in the wall, and it comes loose, " +
        "revealing a narrow exit.\n");
    tell_room(this_object(), QCTNAME(tp) + " pushes a plank in the wall, and " +
        "it comes loose, revealing a narrow exit.\n", ({ tp }));

    return 1;
}

public void
init()
{
    ::init();
    add_action(push_plank, "push");
    add_action(push_plank, "pull");
}

public int
plank_opened()
{
    return !plank_closed;
}

public int
plank_closed()
{
    return plank_closed;
}


public string
plank_desc()
{
    if(!plank_exposed)
    {
        return "The ceiling and walls are made of wide weathered " +
            "pine planks, but you can't see much of the walls due " +
            "to the high-stacked hay.\n";
    }

    if(plank_closed)
    {
        return "The hay has shifted around a bit, revealing a " +
            "place in the wall where there appears to be a " +
            "loose plank... It looks as though it might fall " +
            "out if it were pushed a little.\n";
    }

    return "You see that the plank has been pushed open, " +
        "revealing an exit of sorts.\n";
}

public string
search_hay(object player, string str)
{
    if(str && parse_command(str, this_object(),
        "[bales] / [bales] [of] 'hay'"))
    {
        plank_exposed = 1;
        return "After searching around in the hay, some of it " +
            "is moved aside, revealing planks in the wall.\n";
    }

    return "You find nothing of interest there.\n";
}

public string
loose_plank()
{
    if(plank_exposed)
    {
        return "You see an area in the wall where there is a " +
            "loose plank. Looking through the crack you spot an " +
            "orchard behind the barn.\n";
    }

    return "You see no loose plank.\n";
}
