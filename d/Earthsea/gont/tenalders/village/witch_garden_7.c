/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's garden
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "garden_tells.h"

private object snake;

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
        "Briar bushes block the way to the north. There is " +
        "a path that enters a pine forest to the northwest.\n");
    add_item((({"bushes", "briar bushes"})),
        "The bushes appear covered with thorns and " +
        "have purple berries on them.\n");
    add_item("plants",
        "Many types of plants grow here including " +
        "common garden plants and some which " +
        "have planted themselves from the wild.\n");
    add_item("vines",
        "The vines have some little blue fruit on " +
        "them, possibly grapes.\n");
    add_item((({"fruit", "green fruit", "red fruit"})),
        "Some small red fruit look ripe, however, " +
        "the green fruit cannot be picked yet.\n");
    add_item((({"herb", "herbs"})),
        "Green and dark purple herbs scent the air.\n");
    add_item("path",
        "A narrow path runs between " +
        "a row of thorny bushes to the north, and " +
        "a planted row of smaller bushes to the " +
        "south, which appear to have some ripe and " +
        "some green tomatoes on them.\n");
    set_tell_time(80);
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_herb_file("/d/Earthsea/herbs/herb_files/tomato");
    add_exit("witch_garden_6", "east");
    add_exit("witch_garden_5", "south");
    add_exit("../high_fall/n1", "northwest");
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

    if(!objectp(snake))
    {
        snake = clone_object("/d/Earthsea/gont/tenalders/npc/garden_snake");
        snake->move(this_object());
        snake->command("emote slithers in.");
    }
}
