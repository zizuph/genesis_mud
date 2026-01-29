/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's garden
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "garden_tells.h"

private object gopher;

public void
create_herb_room()
{
    int i;
    set_short("A garden");
    set_long("The path winds through what appears to " +
        "be a semi-cultivated, wild garden. Although some " +
        "plants are ranked in rows, others are allowed to " +
        "grow just as they wish. Vines, small trees, herbs " +
        "of all sorts populate the grounds in rich profusion. " +
        "The path continues north, east, and south.\n");
    add_item("plants",
        "Many types of plants grow here including " +
        "common garden plants and some which " +
        "have planted themselves from the wild.\n");
    add_item((({"here", "ground", "bushes", "trees"})),
        "Many varieties of herbs, small trees, and other " +
        "vegetation cover the ground and path.\n");
    add_item("vines",
        "The vines have some little green fruit on " +
        "them, possibly grapes.\n");
    add_item((({"fruit", "green fruit", "red fruit"})),
        "Some small red fruit look ripe, however, " +
        "the green fruit cannot be picked yet.\n");
    add_item((({"herb", "herbs"})),
        "Green and dark purple herbs scent the air.\n");
    add_item("path",
        "A narrow grass-covered path winds through " +
        "the garden among the vegetation.\n");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_herb_file("/d/Earthsea/herbs/herb_files/tomato");
    set_tell_time(80);
    add_exit("witch_garden_7", "north");
    add_exit("witch_garden_4", "east");
    add_exit("witch_garden_3", "south");
    reset_room();

    for(i = 0; i < 4; i++)
    {
        add_tell(TELLS[random(sizeof(TELLS))]);
    }
}

public void
reset_room()
{
    ::reset_room();

    if(!objectp(gopher))
    {
        gopher = clone_object("/d/Earthsea/gont/tenalders/npc/gopher");
        gopher->move(this_object());
        gopher->command("emote pops up from a hole in the ground.");
    }
}
