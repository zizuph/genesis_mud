/*
 * coded by Amelia 6/1/97
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/d/Earthsea/lib/room_tell";

#include "/d/Earthsea/quest_handler/quest_handler.h"
#include "defs.h"
#include <macros.h>

private int in_nest = 0;

public void
create_earthsea_room()
{
    set_short("Out on a limb");
    set_long("You find yourself out on a limb, balancing " +
        "carefully to keep from falling. There is a small nest " +
        "suspended among the twigs at the end of the limb.\n");
    add_item((({"leaves", "tree", "room", "shady room", "branches",
        "leafy branches"})),
        "Overhead the leafy branches of the oak tree arch like a " +
        "ceiling. It is like a shady room here.\n");
    add_item((({"nest", "bird's nest", "small bird's nest"})),
        "@@exa_nest");
    add_item("limb",
        "You are standing on a limb that extends far out " +
        "from the center of the tree. It is narrow and you find " +
        "yourself balancing carefully to avoid falling. You hope you " +
        "can climb back on it.\n");
    set_tell_time(15);
    add_tell("The limb sways under you in the breeze.\n");
    add_tell("Your foot slips on the limb, you almost fall!\n");
    add_tell("You swing your arms wildly to keep balance. Do you " +
        "think you can fly??\n");
    add_tell("A branch moving in the wind nearly knocks you off.\n");
}

public int
climb(string str)
{
    object tp = this_player();

    if(str == "back" || str == "back on limb" || str == "limb")
    {
        write("You carefully climb back on the limb.\n");
        tell_room(environment(tp), QCTNAME(tp) + " climbs back on the " +
            "limb.\n", ({ tp }));
        tp->move_living("M",
            "/d/Earthsea/gont/tenalders/village/oak_tree", 1);
        tell_room(environment(tp), QCTNAME(tp) + " climbs back " +
            "from the limb.\n", ({ tp }));
        return 1;
    }

    return notify_fail("Climb where?\n");
}

public int
fly_away()
{
    tell_room(this_object(), "The baby bird suddenly flaps " +
        "his wings wildly and flies away.\n");
    in_nest = 0;
    remove_item("bird");
    return 1;
}

public int
put(string str)
{
    object tp = this_player(), bird = present("bird", tp),
        hat = present("_witch_hat_", tp);

    if(objectp(bird))
    {
        if(str == "bird into nest" || str == "bird" ||
            str == "bird in nest")
        {
            write("You gently put the bird into the nest.\n");
            tell_room(environment(tp), QCTNAME(tp) + " gently places the " +
                "baby bird into the nest. Isn't that sweet?\n", ({ tp }));
            set_alarm(10.0, 0.0, &fly_away());
            bird->command("emote chirps happily and flaps his tiny wings.");
            bird->remove_object();
            in_nest = 1;
            add_item("bird",
                "The baby bird looks very happy now, sitting in the nest.\n");
            tp->remove_prop(WORM_GIVEN);

            if((!QH_QUERY_QUEST_COMPLETED(tp, "bird_quest")))
            {
                QH_QUEST_COMPLETED(tp, "bird_quest");
                write("You have done your good deed for the day!\n");
            }

            if(objectp(hat))
            {
                hat->remove_object();
                write("The magical hat disappears in a puff " +
                    "of smoke!\n");
            }

            return 1;
        }
    }

    return notify_fail("Put what where?\n");
}

public void
init()
{
    ::init();
    add_action(put, "put");
    add_action(climb, "climb");
}

public string
exa_nest()
{
    if(in_nest)
    {
        return "There is a small bird's nest in the twigs at the " +
            "end of the limb. It appears to be made from small twigs and " +
            "lined with blue feathers to make it soft for the baby " +
            "birds. There is a baby bird sitting in the nest.\n";
    }

    return "There is a small bird's nest in the twigs at the " +
        "end of the limb. It appears to be made from small twigs and " +
        "lined with blue feathers to make it soft for the baby " +
        "birds. The nest is empty, except for a broken egg shell.\n";
}
