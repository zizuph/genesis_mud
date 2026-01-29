/*
 * coded by Amelia 8/2/97
 * climb routine for cliff;)
*/

#pragma no_clone
#pragma strict_types

#include <macros.h>
#include <ss_types.h>

#define CLIMB_LIM 10
#define DEX_LIM 30

private string cliff_up, cliff_down;

public string
set_next_up(string cliff_room)
{
    cliff_up = cliff_room;
}

public string
set_next_down(string cliff_room)
{
    cliff_down = cliff_room;
}

public string
query_up()
{
    return cliff_up;
}

public string
query_down()
{
    return cliff_down;
}

public int
fall_down(object tp)
{
    int hp = tp->query_hp();

    hp = (hp > 0 ? (hp/(random(3)+2)) : 0);

    tell_room(environment(tp),
        QCTNAME(tp) + " suddenly loses " +
        tp->query_possessive() +
        " grasp and tumbles all the way down!\n",
      ({tp}));
    tp->move_living(" falls in with a crash!",
        "/d/Earthsea/gont/gont_city/rooms/city_street/city_road23a",
        1, 0
    );
    write("You fall all the way to the bottom of the " +
        "cliff, crashing on the rocks!\n");
    tp->heal_hp(-hp);
    tp->remove_prop("__es_falling_off_cliff__");

    if(tp->query_hp() <= 0)
    {
        tp->do_die(this_object());
    }

    return 1;
}

public int
climb_cliff(string str)
{
    object tp = this_player();
    int x = random(20);

    if(sizeof(tp->query_weapon(-1)))
    {
        write("You need both hands to climb.\n");
        return 1;
    }

    if(tp->query_steed())
    {
        write("You cannot climb while you are riding a steed.\n");
        return 1;
    }

    if(tp->is_leading_steed())
    {
        write("You cannot climb while you are leading a steed.\n");
        return 1;
    }

    if(tp->query_prop("__es_falling_off_cliff__"))
    {
        write("You cannot climb while you are falling!\n");
        return 1;
    }

    if(tp->query_fatigue() < 30)
    {
        write("You are too tired to climb!\n");
        return 1;
    }

    if(str == "cliff" || str == "up cliff")
    {
        if(query_up() == "on_top")
        {
            write("You are already at the top!\n");
            return 1;
        }

        if((tp->query_skill(SS_CLIMB) > CLIMB_LIM) &&
            (tp->query_stat(SS_DEX) > DEX_LIM))
        {
            if(x > 18)
            {
                write("Using all your climbing skill and " +
                    "dexterity, you try to climb the cliff... " +
                    "But suddenly you slip!\n");

                if(query_down() != "at_bottom")
                {
                    tp->add_prop("__es_falling_off_cliff__", 1);
                    set_alarm(2.0, 0.0, &fall_down(tp));
                }

                return 1;
            }

            write("Using all your climbing skill and " +
                "dexterity, you manage to gain a foothold to climb " +
                "the cliff.\n");
            tp->add_fatigue(-30);
            tell_room(environment(tp), QCTNAME(tp) + " ascends the " +
              "cliff, disappearing into the mist.\n", ({ tp }));
            tp->move_living("M", query_up(), 1);
            tell_room(environment(tp), QCTNAME(tp) + " comes within " +
              "reach scaling the cliff.\n", ({ tp }));
            return 1;
        }

        if(query_down() == "at_bottom") 
        {
            write("You try to climb up, but can't manage to make it off " +
                "the ground.\n");
            return 1;
        }

        write("You try to climb the cliff, but fall " +
            "instead! You are hurt.\n");
        tp->heal_hp((-1 / 10) * tp->query_max_hp());
        tell_room(environment(tp), QCTNAME(tp) + " attempts to " +
            "climb the cliff, but falls back instead!\n", ({ tp }));
        tp->move_living("M", query_down(), 1);
        tell_room(environment(tp), QCTNAME(tp) + " falls down " +
            "the cliff!\n", ({ tp }));
        return 1;
    }

    if(str == "down" || str == "down cliff" || str == "down the cliff")
    {
        if(query_down() == "at_bottom")
        {
            write("You are already at the bottom of the cliff.\n");
            return 1;
        }

        if(x > 18)
        {
            write("Using all your dexterity and climbing skill, " +
                "you try to climb down the cliff... but suddenly you slip!\n");
            set_alarm(2.0, 0.0, &fall_down(tp));
            return 1;
        }

        write("Carefully you climb down some distance, " +
            "clinging with fingers and toes to the rock cliff.\n");
        tell_room(environment(tp), QCTNAME(tp) + " skillfully climbs down " +
            "the sheer rock cliff into the mist below.\n", ({tp}));
        tp->move_living("M", query_down(), 0, 0);
        tell_room(environment(tp), QCTNAME(tp) + " climbs down from " +
            "the mists above.\n", ({ tp }));
        tp->add_fatigue(-30);

        return 1;
    }

    return notify_fail("Climb up what?\n");
}
