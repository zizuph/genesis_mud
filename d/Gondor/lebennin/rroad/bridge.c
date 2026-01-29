/*
 * /d/Gondor/lebennin/rroad/bridge.c
 *
 * Coded by Gwyneth
 */
inherit "/d/Gondor/std/room";

#include <macros.h>
#include <ss_types.h>

public void
create_gondor()
{
    set_short("a muddy bank by the river");
    set_long("The northern arm of the Sirith is fairly deep but not " +
        "very wide. It runs quickly under a narrow bridge and then under " +
        "the city walls through a pipe to the east. The banks of " +
        "the river are very muddy. Large rocks block passage along the " +
        "river away from the city, but a small path leads up a hill away " +
        "from the river to the north.\n");

    add_item(({ "river", "sirith", "Sirith" }), "The northern arm of the " +
        "Sirith is fairly deep, but not very wide. It runs quickly under the " +
        "city walls to the through a pipe to the east.\n");
    add_item(({ "bridge", "narrow bridge" }), "It is just about wide " +
        "enough for an ox-cart to pass over.\n");
    add_item(({ "banks", "mud" }), "The banks of the river are very muddy.\n");
    add_item(({ "rock", "rocks", "large rocks", "large rock" }), "The rocks " +
        "are slippery and rather jagged. It wouldn't be a good idea to " +
        "climb them.\n");
    add_item(({ "path", "small path" }), "It leads away from the river, up " +
        "to the bridge.\n");
    add_item(({ "walls", "city walls", "pipe" }), "The walls are high and " +
        "unclimbable, but perhaps you could enter the city through the " +
        "pipe!\n");
    add_exit("/d/Gondor/lebennin/rroad/rbdg2", "north", 0, 2);
}

public void
do_enter(object who)
{
    who->catch_tell("Luckily, you are carried into the pipe. Not wanting to " +
        "stay in the angry river any longer than you have to, you grab onto " +
        "the first thing that comes along, which happens to be a ladder. " +
        "As you climb the ladder, you find a trapdoor that you slip " +
        "through.\n");
    tell_room("/d/Gondor/common/jewelry/fireplace", QCTNAME(who) +
        " enters the fireplace, dripping with mud.\n");
    set_alarm(0.1, 0.0, &who->move_living("M",
        "/d/Gondor/common/jewelry/fireplace", 1));
}

public int
enter_pipe(string str)
{
    int i, size, seed = atoi(OB_NUM(this_player()));
    object *team, who;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (this_player()->query_skill(SS_SWIM) < 
      (20 + random(10, seed)))
    {
        write("You'd surely drown, as poor a swimmer as you are!\n");
        say(QCTNAME(this_player()) + " looks timidly at the water.\n");
        return 1;
    }

    write("You wade into the river, but its swift current carries you " +
        "down under the water, nearly drowning you.\n");
    tell_room(this_object(), QCTNAME(this_player()) + " enters the water " +
        "and is swept under.\n", ({ this_player() }));
    who = this_player();
    set_alarm(1.0, 0.0, &do_enter(who));

    team = this_player()->query_team();
    for (i = 0, size = sizeof(team); i < size; i++)
    {
        if (present(team[i], this_object()))
        {
            team[i]->catch_tell("Against your better judgement, you follow " +
                this_player()->query_the_name(team[i]) + ". You wade into " +
                "the river, but its swift current carries you down under " +
                "the water, nearly drowning you.\n");
            tell_room(this_object(), QCTNAME(team[i]) + " enters the water " +
                "and is swept under.\n", ({ this_player(), team[i] }));
            set_alarm(1.2, 0.0, &do_enter(team[i]));
        }
    }

    return 1;
}


public void
init()
{
    ::init();

    add_action(enter_pipe, "enter");
    add_action(enter_pipe, "swim");
}
