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
    object door;
    int i;
    set_short("A garden");
    set_long("With lush greenery everywhere, this appears to " +
        "be a semi-cultivated, wild garden. Although some " +
        "plants are ranked in rows, others are allowed to " +
        "grow just as they wish. Vines, small trees, herbs " +
        "of all sorts populate the grounds in rich profusion. " +
        "Nature is the gardener here. To the west you see " +
        "a small hut, covered in living thatch anchored in " +
        "the sod roof. The hut is sunk a step down into " +
        "the ground, and there is a wooden door as " +
        "entrance.\n");
    add_item((({"garden", "wild garden"})),
        "The garden is almost wild, although appears " +
        "partly cultivated. The order here is a natural one.\n");
    add_item((({"plants"})),
        "There is a profusion of greenery here, among " +
        "which you can identify common garden plants, " +
        "vegetables and herbs, as well as some plants " +
        "which grow wild in the area.\n");
    add_item("vegetables",
        "Among the vegetables you see small red " +
        "fruits, green flowered stalks, and " +
        "dark green leafy vegetables.\n");
    add_item((({"roof", "roof of the hut"})),
        "The roof slopes steeply. " + "@@roof_desc");
    add_item("hut",
        "The hut is covered in living thatch and vines. " +
        "There is an entrance to the west, which is " +
        "a bit sunken below ground level.\n");
    set_tell_time(100);
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_exit("witch_garden_2", "north");
    add_exit("witch_path", "southwest");
    door = clone_object("/d/Earthsea/gont/tenalders/obj/doors/witch_door_e2");
    door->move(this_object());

    for(i = 0; i++; i < 4)
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
