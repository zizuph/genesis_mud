/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's garden
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "garden_tells.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

private object worm;

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
        "The path continues to the east and north. " +
        "There is a small hut directly to the south.\n");
    add_item((({"window", "small window"})),
        "The window is too small to climb through. Hmm... " +
        "You feel someone staring at you...\n");
    add_item((({"hut", "small hut", "roof"})),
        "There is a small hut to the south, where " +
        "you can see a small window looking out " +
        "over the garden. The roof of the hut " +
        "is covered over with living thatch and vines. " +
        "You see a vine-covered trellis to the right " +
        "of the window, which extends to the roof. " +
        "@@roof_desc");
    add_item((({"trellis", "vine-covered trellis"})),
        "The trellis is almost like a ladder, " +
        "covered in vines. You might be able to climb it.\n");
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
    add_item("path",
        "A narrow grass-covered path winds through " +
        "the garden among the vegetation.\n");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_exit("witch_garden_5", "north");
    add_exit("witch_garden_2", "east");
    set_tell_time(80);
    reset_room();

    for(i = 0; i < 4; i++)
    {
        add_tell(TELLS[random(sizeof(TELLS))]);
    }
}

public void
reset_room()
{
    if(!objectp(worm))
    {
        worm = clone_object("/d/Earthsea/gont/tenalders/npc/wooley_worm");
        worm->move(this_object());
        worm->command("emote inches in.");
    }
}

public int
climb(string str)
{
    object tp = this_player();

    if((str != "trellis") && (str != "up") &&
        (str != "up trellis") && (str != "climb up roof"))
    {
        return notify_fail("Climb where?\n");
    }

    tell_room(environment(tp), QCTNAME(tp) +
        " climbs up the trellis to the roof of the hut.\n",
        ({ tp }));
    write("You climb up the trellis to the roof.\n");
    tp->move_living("M",
        "/d/Earthsea/gont/tenalders/village/witch_roof", 1);
    tell_room(environment(tp), QCTNAME(tp) +
        " climbs up the trellis from the garden below.\n",
        ({ tp }));
    return 1;
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
    add_action(climb, "climb");
    call_other("/d/Earthsea/gont/tenalders/village/witch_roof",
        "load_me");
}
