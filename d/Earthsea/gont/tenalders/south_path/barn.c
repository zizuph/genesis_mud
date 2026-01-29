/*
 * barn in Gont
 * Coded by Amelia 4/10/98
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <stdproperties.h>

#define CRITTERS ({ \
    "/d/Earthsea/gont/tenalders/npc/cow", \
    "/d/Earthsea/gont/tenalders/npc/goat", \
    "/d/Earthsea/gont/tenalders/npc/pig", \
    "/d/Earthsea/gont/tenalders/npc/chicken" \
})

private object *critters = allocate(3);

public void
create_earthsea_room()
{
    set_short("Inside a barn");
    set_long("The aroma of farm animals and hay assails " +
        "your nostrils inside this barn. The floor is hard-packed " +
        "earth, covered with straw. A few implements hang on the " +
        "walls which are built from bare pine planks. Cracks in " +
        "the walls and high planked ceiling let in a bit of " +
        "light. The large framed doorway opens to the north. " +
        "In the southeast corner stands a ladder which leads up " +
        "to a hay loft.\n");
    add_item((({"straw", "floor"})),
        "The floor is just hard-packed earth, which is covered " +
        "with straw.\n");
    add_item((({"animals", "farm animals"})),
        "This is where some of the farmer's livestock " +
        "live, judging from the smell. You realize you " +
        "had better watch out where you step.\n");
    add_item((({"hay", "hay loft"})),
        "A ladder leads up to a loft, where you see hay " +
        "stacked up to the ceiling.\n");
    add_item((({"ceiling", "walls"})),
        "The walls and ceiling are constructed from bare " +
        "weathered pine planks.\n"); 
    add_item((({"implements", "harnesses", "plow", "scythe"})),
        "Among the implements you see harnesses, an old plow, " +
        "and a scythe.\n"); 
    add_item("cracks", "Cracks between the weathered pine planks " +
        "allow light to enter.\n");
    add_item((({"wooden ladder", "old ladder", "ladder"})),
        "The old ladder is missing a few rungs but looks like " +
        "it might be serviceable for climbing up to the loft.\n");
    add_exit("farm_path_2", "north");
    add_prop(ROOM_I_INSIDE, 1);
    reset_room();
}

public void
reset_room()
{
    int i = 3;

    while(i--)
    {
        if(!objectp(critters[i]))
        {
            critters[i] = clone_object(CRITTERS[random(sizeof(CRITTERS))]);
            critters[i]->move(this_object());
            critters[i]->command("emote walks in.");
        }
    }
}

public int
climb_up(string str)
{
    if(str != "ladder" && str != "wooden ladder")
    {
        return notify_fail("Climb what?\n");
    }

    this_player()->move_living("climbing up the ladder",
        "/d/Earthsea/gont/tenalders/south_path/loft", 1);

    return 1;
}

public void
init()
{
    ::init();
    add_action(climb_up, "climb");
}
