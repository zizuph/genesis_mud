#pragma strict_types

inherit "/d/Earthsea/std/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_earthsea_wearable_item()
{
    set_name("drum");
    add_name("__es_bonesman_drum__");
    set_short("@@worn_unworn_short");
    set_adj(({"battered", "goatskin", "skin", "wood", "wooden"}));
    set_long("A battered drum made of a wooden circle " +
        "covered by tightly pulled goatskin on each end.\n");
    set_slots(A_ANY_SHOULDER);
    set_layers(5);
    set_looseness(100);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 250);
    add_prop("__es_drum_from_corpse__", 1);
}

public string
worn_unworn_short()
{
    if(query_worn())
    {
        return "battered goatskin drum slung over " +
            (this_player() == wearer ? "your" :
            wearer->query_possessive()) + " shoulder";
    }

    return "battered goatskin drum";
}

public int
play(string str)
{
    string verb = query_verb();
    object tp, bones;

    if(verb != "rimshot" && (!str || !id(str)))
    {
        return notify_fail(capitalize(verb) + " what?\n");
    }

    tp = this_player();

    if(environment() != tp)
    {
        return notify_fail("You don't have the drum!\n");
    }

    if(!(bones = present("__es_bonesman_bones__", tp)))
    {
        return notify_fail("You don't have any bones to beat!\n");
    }

    if(!bones->query_held())
    {
        return notify_fail("You need to hold the pair of bones first.\n");
    }

    if(verb == "rimshot")
    {
        write("You snap a bone against the outer rim of the " +
            "battered goatskin drum creating a deafening crack!\n");
        tell_room(environment(tp), QCTNAME(tp) +
            " snaps a bone against the outer rim of the " +
            "battered goatskin drum creating a deafening crack!\n", ({ tp }));
        return 1;
    }

    write("You whack your bones on the skin of the " +
        "battered goatskin drum producing a thunderous boom!\n");
    tell_room(environment(tp), QCTNAME(tp) +
        " whacks a pair of bones on the skin of the battered goatskin drum " +
        " producing a thunderous boom!\n", ({ tp }));
    return 1;
}

public void
init()
{
    ::init();
    add_action(play, "play");
    add_action(play, "beat");
    add_action(play, "pound");
    add_action(play, "hit");
    add_action(play, "smack");
    add_action(play, "whack");
    add_action(play, "rimshot");
}
