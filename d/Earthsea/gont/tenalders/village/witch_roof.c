/*
 * coded by Amelia for Ten Alders 4/13/97
 * the witch's roof
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/gont/tenalders/std/base_herb_room";

#include <macros.h>
#include "defs.h"
#include "/d/Earthsea/herbs/herb_sets/garden_herbs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

private object goat;

public void
create_herb_room()
{
    set_short("A roof");
    set_long("Living thatch, vines, and green plants " +
        "grow thickly on the roof of the hut, which slants " +
        "down almost to the ground. The roof rises to a dome " +
        "in the center, and to one side of it is a narrow " +
        "stone chimney from which smoke issues forth. " +
        "You have a good view of the village from here, " +
        "as you look around.\n");
    add_item("plants",
        "Numerous types of wild green plants have " +
        "taken root here. Some are just weeds, others " +
        "look more interesting.\n");
    add_item((({ "thatch", "living thatch" })),
        "The thatch is rooted in sod and appears " +
        "very thick and green.\n");
    add_item("vines",
        "The vines are climbing plants which entwine " +
        "themselves in the thatch and which bear " +
        "velvety purple flowers.\n");
    add_item((({ "flowers", "purple flowers" })),
        "Morning glory flowers grow on vines here.\n");
    add_item((({ "view", "view of the village", "village", "town" })),
        "As you look all around, you can see " +
        "a garden to the north and east of the " +
        "hut where you stand. To the west and " +
        "south are other huts, and far to the " +
        "northwest a majestic cliff rises above the " +
        "forest. As you look to the east, you " +
        "can see the distant deep blue sea.\n");
    set_up_herbs(select_herb_files(GARDEN_HERBS), GARDEN_LOCATIONS, 3);
    add_herb_file("/d/Earthsea/herbs/herb_files/morning_glory");
    set_tell_time(80);
    add_tell("A plume of herbal smoke rises from the " +
        "chimney.\n");
    add_tell("Very far away to the southeast you spot a boat " +
        "on the open sea.\n");
    reset_room();
}

public void
reset_room()
{
    if(!objectp(goat))
    {
        goat = clone_object("/d/Earthsea/gont/tenalders/npc/quest_goat");
        goat->move(this_object());
        goat->command("emote leaps in.");
    }
}

public void
goat_jumps(object tp)
{
    object to = this_object();

    if(!present(tp, to) || !present(goat, to))
    {
        return;
    }

    goat->remove_object();
    tell_room(to, "The goat leaps off the roof and " +
        "runs away!\n");
    tp->catch_tell("You feel more experienced!\n");
    QH_QUEST_COMPLETED(tp, "goat_quest");
    tp->remove_prop(GOT_I_GOAT_SPELL);
    tp->remove_prop(GOT_GOAT_QUEST);
}

public int
climb(string str)
{
    object tp = this_player();

    if((str != "down") && (str != "down the vine") &&
        (str != "down from the roof") && (str != "down the roof") &&
        (str != "down roof"))
    {
        return notify_fail("Climb where?\n");
    }

    tell_room(this_object(), QCTNAME(tp) +
        " climbs down from the roof.\n", ({ tp }));
    write("You climb down from the roof.\n");
    tp->move_living("M",
        "/d/Earthsea/gont/tenalders/village/witch_garden_3", 1);
    tell_room(environment(tp), QCTNAME(tp) +
        " climbs down from the roof of the hut.\n", ({ tp }));
    return 1;
}

public int
shout(string str)
{
    object tp = this_player(), to = this_object();

    if(!str || str != GOAT_SPELL)
    {
        write("You shout from the rooftop!\n");
        return 1;
    }

    if(!present(goat, to))
    {
        write("Your words fall on the empty air.\n");
        return 1;
    }

    if(QH_QUERY_QUEST_COMPLETED(tp, "goat_quest"))
    {
        write("That spell will only work once!\n");
        return 1;
    }

    if(tp->query_prop(PLAYER_I_ATTACKED_GOAT))
    {
        write("Baaad player! You should not have attacked " +
            "that goat!\n");
        return 1;
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "honeycomb_quest"))
    {
        write("Hmm ... you did not get the words right.\n");
        return 1;
    }

    if(present("goat", to))
    {
        goat->command("emote looks at you strangely from its yellow " +
            "eyes.");
        set_alarm(2.0, 0.0, &goat_jumps(tp));
        return 1;
    }

    return 0;
}

public void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(shout, "shout");
}
