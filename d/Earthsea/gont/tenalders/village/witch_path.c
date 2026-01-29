/*
 * coded by Amelia for Ten Alders 4/13/97
 * path to the witch's door
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include <filter_funs.h>
#include <composite.h>

public void
create_herb_room()
{
    set_short("A grass-covered path");
    set_long("The grass-covered path leads " +
        "to the northeast around a hut, which " +
        "is directly north of you. The roof of the hut " +
        "is covered in living thatch and vines. You see " +
        "no entrance or windows on this side.\n");
    add_item("hut",
        "The hut is fairly small and sunk a bit " +
        "below ground level. It has a sloping roof " +
        "and a smoking chimney. You wonder if the " +
        "resident is home.\n");
    add_item((({"roof", "roof of the hut"})),
        "The roof slopes steeply. " + "@@roof_desc");
    add_item((({"thatch", "living thatch", "vines"})),
        "It is interesting that the whole roof " +
        "appears like a garden.\n");
    add_exit("witch_garden_1", "northeast");
    add_exit("village_path_1", "west");
    set_tell_time(80);
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
