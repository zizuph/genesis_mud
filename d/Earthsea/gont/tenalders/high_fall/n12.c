/*
 * coded by Amelia 3/16/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_forest_room";

#include "/d/Earthsea/herbs/herb_sets/forest_herbs.h"

private object bear;

public void
create_forest_room()
{
    set_short("An ancient evergreen forest");
    set_long("Tall evergreen trees march down the steep " +
        "sides of the mountain. Among them you see a very large " +
        "redwood tree to the south. The pines and spruces scent " +
        "the crisp mountain air, and the ground is carpeted with " +
        "pine needles.\n");
    add_item((({"floor", "forest floor"})),
        "The forest floor is fairly steep, and it is " +
        "difficult to walk here.\n");
    add_item((({"tree", "redwood tree"})),
        "A very large redwood tree is just south of you. " +
        "It stands out from the other trees nearby.\n");
    reset_room();
    set_tell_time(120);
    add_exit("n11", "northwest");
    add_exit("n13", "south", "@@go_south");
    set_up_herbs(select_herb_files(FOREST_HERBS), FOREST_LOCATIONS, 3);

    if(!random(4))
    {
        add_herb_file("/d/Earthsea/herbs/herb_files/clover4");
    }
}

public void
reset_room()
{
    ::reset_room();

    if(!objectp(bear))
    {
        bear = clone_object("/d/Earthsea/gont/tenalders/npc/grizzly");
        bear->move(this_object());
        bear->command("emote charges in.");
        bear->command("roar");
    }
}

public int
go_south()
{
    if(present(bear, this_object()))
    {
        write("Rearing up on his hind legs, the bear " +
            "towers over you, blocking the way south.\n");
        bear->command("roar");
        return 1;
    }

    return 0;
}
