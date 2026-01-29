#pragma strict_types
#pragma no_clone

inherit "/d/Genesis/ship/deck";

#include <macros.h>
#include <stdproperties.h>

private int started = 0;

public void
create_deck()
{
    set_short("Deck");
    set_long("The coracle's deck is small and " +
        "suited to transporting only a few people at a time. To the " +
        "aft you see a set of long oars affixed to oarlocks. There is " +
        "a pine board there for a rowing bench.\n");
    add_item((({"bench", "rowing bench", "pine board", "board"})),
        "There is a pine board set into the aft part of the boat " +
        "for a rowing bench.\n");
    add_item((({"oars", "oarlocks" })),
        "The oars are fastened to bronze oarlocks in such a way " +
        "as to provide a fulcrum to the rowing action.\n");
    add_cmd_item((({"oars", "boat"})), "row", "You try to grab " +
        "the oars and row, but they are only for the captain.\n");
    add_item((({"planks", "pine planks"})),
        "The pine planks that comprise the deck are aged and stained " +
        "from sea water and the elements.\n");
    add_item("deck", "The planked deck is rather small and " +
        "shallow, but suits the purpose.\n");
    set_deck_sound("@@sounds");
    set_bump_sound("@@arrives");
    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_M_NO_STEAL, 1);
}

public string
sounds()
{
    object captain = present("captain", this_object());

    if(!objectp(captain))
    {
        return "There is no one to row the boat!\n";
    }

    if(!started)
    {
        started = 1;
        return QCTNAME(captain) + " pulls hard on the oars, " +
            "navigating the coracle carefully out of dock.\n";
    }

    return QCTNAME(captain) + " pulls hard at the oars, propelling " +
        "the coracle forward.\n";
}

public string
arrives()
{
    started = 0;
    return "The coracle glides into dock, and " +
        "the captain raises the oars.\n";
}
