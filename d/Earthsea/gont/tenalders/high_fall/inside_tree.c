#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include <stdproperties.h>

private object *bees = allocate(5);
private int honeycomb_found, bees_found;

public void
reset_room()
{
    honeycomb_found = 0;
    bees_found = 0;
}

public void
create_earthsea_room()
{
    set_short("Inside a giant redwood tree");
    set_long("You find yourself in a vast dark chamber " +
        "within the hollow giant redwood tree. A sticky residue " +
        "of some kind covers the walls. It is dark " +
        "and stuffy, and when you look up, the darkness seems " +
        "to go on forever.\n");
    add_item((({"chamber", "dark chamber", "tree", "redwood tree",
        "giant redwood tree"})),
        "The tree has been hollowed out to make a vast "+
        "chamber inside.\n");
    add_item((({"walls", "wall"})),
        "A bit above your head on the north wall you see " +
        "a dark mass, from which a loud buzzing noise emits.\n");
    add_item((({"mass", "dark mass", "hive" })),
        "The dark mass appears to be a bee hive.\n");
    add_item("darkness", "Darkness extends a long way up, " +
        "and you can't see the ceiling.\n");
    add_item((({"resin", "redwood resin", "residue"})),
        "The resin makes the floors and walls somewhat " +
        "sticky to the touch.\n");
    reset_room();
    add_prop(ROOM_I_LIGHT, -1);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_S_SEARCH_FUN, "find_honeycomb");
    add_prop(OBJ_I_SEARCH_TIME, 1);
    set_tell_time(85);
    add_tell("The air vibrates with a loud humming noise.\n");
    add_tell("Something buzzes by your ear.\n");
    add_exit("n13", "out");
}

public string
find_honeycomb(object player, string str)
{
    object honeycomb, tp = this_player(), to = this_object();
    int i = 5;

    if(str == "hive" || str == "bee hive" || str == "mass")
    {
        if(present("bee", to))
        {
            return "The bees prevent you from searching the hive.\n";
        }

        if(!bees_found)
        {
            bees_found = 1;

            while(i--)
            {
                if(!objectp(bees[i]))
                {
                    bees[i] = clone_object("/d/Earthsea/gont/tenalders/npc/ta_bee");
                    bees[i]->move(to);
                    bees[i]->command("emote comes buzzing in.");
                }
            }

            return "You found some angry bees!\n";
        }

        if(!honeycomb_found)
        {
            honeycomb = clone_object("/d/Earthsea/gont/tenalders/obj/items/honeycomb");
            honeycomb->move(tp);

            honeycomb_found = 1;

            return "You find a honeycomb!\n";
        }
    }

    return "You find nothing of interest.\n";
}
