/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's garden
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "garden_tells.h"
#include <filter_funs.h>
#include <composite.h>

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
        "The path continues north and west. " +
        "There is a small hut to the southwest.\n");
    add_item((({"hut", "small hut"})),
        "There is a small hut to the south and west " +
        "of this portion of the garden, covered in " +
        "vines and living thatch.\n");
    add_item("plants",
        "Many types of plants grow here including " +
        "common garden plants and some which " +
        "have planted themselves from the wild.\n");
    add_item("vines",
        "The vines have some little green fruit on " +
        "them, possibly grapes.\n");
    add_item((({"fruit", "green fruit", "red fruit"})),
        "Some small red fruit look ripe, however, " +
        "the green fruit cannot be picked yet.\n");
    add_item((({"herb", "herbs"})),
        "Green and dark purple herbs scent the air.\n");
    add_item((({"path", "ground"})),
        "A narrow grass-covered path winds through " +
        "the garden among the vegetation.\n");
    add_item((({"trees", "small trees"})),
        "Small trees from the neighboring forest " +
        "have taken root here.\n");
    add_item((({"roof", "roof of the hut"})),
        "The roof slopes steeply. " + "@@roof_desc");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_exit("witch_garden_3", "west");
    add_exit("witch_garden_4", "north");
    add_exit("witch_garden_1", "south");
    set_tell_time(80);

    for(i = 0; i < 4; i++)
    {
        add_tell(TELLS[random(sizeof(TELLS))]);
    }
}

public string
roof_desc()
{
    object *on_roof,
        roof = find_object("/d/Earthsea/gont/tenalders/village/witch_roof");
    string liv_desc = "You see no one on the roof";

    if(objectp(roof))
    {
        on_roof = FILTER_LIVE(all_inventory(roof));

        if(sizeof(on_roof))
        {
            liv_desc = "You see ";
            liv_desc += COMPOSITE_LIVE(on_roof);
            liv_desc += " on the roof";
        }
    }

    return liv_desc + ".\n";
}

public void
init()
{
    ::init();
    call_other("/d/Earthsea/gont/tenalders/village/witch_roof",
        "load_me");
}
