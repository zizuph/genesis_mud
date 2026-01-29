/*
 * NIMRAIS_DIR + trolls/outcave.c
 *
 * Coder - Unknown
 *
 * Revision history:
 *
 * Gwyneth, 10/02/02: Neatened and modernized the code. Fixed some bugs.
 *                    Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/std/room";

#include "/d/Gondor/defs.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#define CLIMB_SKILL 40
 
object *gPushers;

int    blocked();
string exa_boulder();
string exa_ground();
string exa_cave();
int    path_blocked();
int    test_boulder_moved();
int    try_push(object player);
int    test_total_str();
int    tell_pushers(string str);
string describe();
void no_reaction();
void remove_pusher(object player);

void
create_gondor()
{
    set_short("Outside the entrance to a dark cave");
    set_long(&describe());
    remove_prop(ROOM_I_INSIDE);
    add_exit(NIMRAIS_DIR + "trolls/entrcave", "south", &blocked());
    add_exit(NIMRAIS_DIR + "trolls/path2","north", &path_blocked());
    add_item(({"stone","boulder","rock"}), &exa_boulder());
    add_item("ground", &exa_ground());
    add_item(({"cave","entrance","opening"}), &exa_cave());
    add_item("valley","The valley is just east of you, widening out in the " +
        "north, and turning southeast, where it ends. A tiny stream runs " +
        "in the bottom of the valley. The ledge that you are on now ends " +
        "here, but continues north.\n");
}
 
int
blocked()
{
    object troll;
    if (!test_boulder_moved())
    {
        if (this_player()->query_race_name()=="troll")
        {
            say(QCTNAME(this_player()) + " rolls the boulder aside and " +
                "enters the cave. Then " + this_player()->query_pronoun() +
                " rolls the boulder back in place.\n");
            return 1;
        }

        write("The entrance to the cave is blocked by a large boulder.\n");
        return 1;
    }

    if (this_player()->query_race_name() == "troll")
        return 0;

    troll = present("troll", TO);
    if(troll && CAN_SEE(troll, TP)  && !TP->query_npc())
    {
        write("The " + troll->query_nonmet_name() + " blocks your way!\n");
        say(QCTNAME(this_player()) + " tries to enter the cave, but the " +
            troll->query_nonmet_name() + " stops " + 
            this_player()->query_objective() + ".\n", this_player());
        return 1;
    }

    return 0;
}
 
int
test_boulder_moved()
{
    FIX_EUID
    (NIMRAIS_DIR + "trolls/entrcave")->teleledningsanka();
    return (NIMRAIS_DIR + "trolls/entrcave")->query_boulder_moved();
}
 
void
set_boulder_moved(int i)
{
    (NIMRAIS_DIR + "trolls/entrcave")->set_boulder_moved(1);
}
 
string
exa_boulder()
{
    if (!test_boulder_moved())
        return "The large boulder is blocking the entrance of the cave. It " +
            "is so large that it would take two to three strong persons to " +
            "roll it aside. It is about 2 meters and a half tall, leaving " +
            "a small opening between the top and the cave ceiling.\n";
    else
        return "The large boulder has been rolled aside from the opening, " +
            "so that it no longer blocks the entrance of the cave. The " +
            "boulder is so large that it probably would take many strong " +
            "men to roll it.\n";
}
 
string
exa_ground()
{
    if (this_player()->query_skill(SS_TRACKING) < 10)
        return "You can't find anything interesting about the barren " +
            "ground.\n";

    if (this_player()->query_skill(SS_TRACKING) < 30)
        return "You see tracks that lead to and from the cave entrance.\n";

    return "You see footprints of hill-trolls leading to and from the " +
        "cave.\n";
}
 
string
exa_cave()
{
    if (test_boulder_moved())
        return "The cave looks dark and awaiting - you can't make out what " +
            "is in there, it's much too dark. The cave mouth measures " +
            "about 3 x 3 meters, and just beside it lies a large boulder, " +
            "slightly smaller than the cave entrance. It is probably used " +
            "to block the cave.\n";

    return "The cave mouth measures about 3 x 3 meters, and a slightly " +
        "smaller boulder is blocking it, leaving but a tiny opening " +
        "between the top of the boulder and the cave roof. You are not " +
        "able to see anything inside the cave because of the boulder.\n";
}
 
string
describe()
{
    string longstr = "You are standing in a barren hillside on the north " +
        "side of the White Mountains. The wide valley you are in continues " +
        "a little further southeast, but the hillside becomes too steep " +
        "here for you to continue that way. Right before you to the south " +
        "is what seems to be entrance to a cave. ";

    if (!test_boulder_moved())
        longstr = longstr + "The cave entrance is blocked by a large " +
            "boulder. ";
    else
        longstr = longstr + "A large boulder seems to have been rolled " +
        "away from the cave mouth. You smell a foul stench coming from " +
        "the cave. ";

    return (longstr + "\n");
}
 
int
push_boulder(string str)
{
    object troll;

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (str=="boulder" || str == "boulder aside")
    {
        if (test_boulder_moved())
        {
            write("But the boulder is already moved away!\n");
            return 1;
        }

        troll = present("troll", this_object());
        if (objectp(troll))
        {
            write("The " + troll->query_nonmet_name() + " stops you " +
                "before you get as far as touching the boulder!\n");
            say(QCTNAME(this_player()) + " tries to push the boulder, but " +
                "the " + troll->query_nonmet_name() + " stops " +
                this_player()->query_objective() + "!\n", this_player());
            return 1;
        }

        if (test_boulder_moved())
        {
            write("You try to push the boulder back in place, but it " +
                "won't budge.\n");
            write("It might help if you got others to push too.\n");
            say(QCTNAME(this_player()) + " tries to push the boulder, but " +
                "it won't budge.\n", this_player());
            return 1;
        }

        try_push(this_player());
        return 1;
    }

    notify_fail(capitalize(query_verb()) + " what?\n");
    return 0;
}
 
int
path_blocked()
{
    if (this_player()->query_race_name() == "troll")
        return 1;

    return 0;
}
 
int
try_push(object player)
{
    if (!objectp(player))
        return 0;

    if (!gPushers)
    {
        gPushers = ({ player });

        if (test_total_str() >= 65)
        {
            write("You summon all your strength, and manage to roll the " +
                "boulder aside!\n");
            say(QCTNAME(player) + " manages to roll the boulder away from " +
                "the cave entrance!\n", player);
            tell_room(NIMRAIS_DIR + "trolls/entrcave", "The large boulder " +
                "suddenly rolls away from the cave exit, pushed by someone " +
                "on the outside!\n");
            set_boulder_moved(1);
            gPushers = ({});
            return 1;
        }

        write("You summon all your strength, but the great boulder won't " +
            "budge.\n");
        say(QCTNAME(player) + " tries to push the boulder away, but isn't " +
            "strong enough.\n", player);
        return 1;
    }

    if (member_array(player, gPushers) != -1)
    {
        write("You keep pushing at the boulder.\n");
        return 1;
    }

    tell_pushers(QCTNAME(player) + " decides to help you push away the " +
        "boulder.\n");
    gPushers += ({ player });
    if (test_total_str() >= 65)
    {
        tell_pushers("You summon all your strength, and the joined " +
            "strength of " + LANG_NUM2WORD(sizeof(gPushers)) + " of you " +
            "forces the great boulder to roll away from the cave opening!\n");
        say("The great boulder is rolled away from the cave opening, as " +
            LANG_NUM2WORD(sizeof(gPushers)) + " persons join forces to " +
            "move it.\n", gPushers);
        tell_room(NIMRAIS_DIR + "trolls/entrcave", "The large boulder " +
            "suddenly rolls away from the cave entrance, pushed by " +
            "someone on the outside!\n");
        set_boulder_moved(1);
        gPushers = ({});
        return 1;
    }

    tell_pushers("You summon all your strength, but not even the joined " +
        "forces of the " + LANG_NUM2WORD(sizeof(gPushers)) + " of you is " +
        "enough to budge the great boulder.\n");
    say(capitalize(LANG_NUM2WORD(sizeof(gPushers))) + " persons try to " +
        "move the boulder together, but it won't budge.\n", gPushers);
    return 1;
}
 
int
test_total_str()
{
    int n, st = 0;
    for (n = sizeof(gPushers) - 1; n >= 0; n--)
        st += gPushers[n]->query_stat(SS_STR);

    return st;
}
 
int
tell_pushers(string str)
{
    int n;
    if (!strlen(str))
        return 0;

    for (n = sizeof(gPushers) - 1; n >= 0; n--)
        gPushers[n]->catch_msg(str);

    return 1;
}
 
int
climb_boulder(string str)
{
    object troll;

    if (!strlen(str))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
      "[up] [over] [across] [through] [the] 'boulder' / 'opening' / 'rock'"))
    {
        notify_fail("Climb what?\n");
        return 0;
    }
    else
    {
        if (test_boulder_moved())
        {
             write("Why climb? The boulder has been moved away from the " +
             "cave mouth!\n");
             return 1;
        }

        troll = present("troll", this_object());
        if (objectp(troll))
        {
            write("The " + troll->query_nonmet_name() + " sees what you " +
                "are trying to do, and drags you down again!\n");
            say(QCTNAME(this_player()) + " starts to climb the large " +
                "boulder, but the " + troll->query_nonmet_name() + " drags " +
                this_player()->query_objective() + " down again!\n",
                this_player());
            return 1;
        }

        if (this_player()->query_skill(SS_CLIMB) < CLIMB_SKILL)
        {
            write("You try to climb the large boulder, but it is too steep " +
                "and smooth. The only result is broken nails and bleeding " +
                "fingers.\n");
            say(QCTNAME(this_player()) + " tries to climb over the large " +
                "boulder, but fails.\n", this_player());
            return 1;
        }

        write("You skillfully climb the large boulder and squeeze yourself " +
            "through the narrow opening between rock-top and cave-roof.\n");
        say(QCTNAME(this_player()) + " manages to climb the large boulder, " +
            "and disappears through the narrow opening between the boulder " +
            "and the cave mouth.\n", this_player());
        tell_room(NIMRAIS_DIR + "trolls/entrcave", QCTNAME(this_player()) +
            " comes climbing in over the large boulder blocking the " +
            "entrance.\n");
        this_player()->move_living("M", NIMRAIS_DIR + "trolls/entrcave", 1);
        return 1;
    }

}
 
void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);

    if (!living(obj))
        return;

    remove_pusher(obj);
}
 
void
remove_pusher(object player)
{
    int n = 0;
    if (!sizeof(gPushers))
        return;

    if (member_array(player, gPushers) != -1)
        gPushers -= ({ player });

    return;
}
 
int
do_knock(string str)
{
    string rock;
    object tp = this_player();

    if(!strlen(str))
    {
        notify_fail("Knock on what?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[on] [the] %w", rock))
    {
        notify_fail("Knock on what?\n");
        return 0;
    }

    if (member_array(rock, ({ "boulder", "stone", "rock" })) == -1)
    {
        notify_fail("Knock on what?\n");
        return 0;
    }

    write("You knock on the " + rock + ".\n");
    say(QCTNAME(tp) + " knocks on the " + rock + ".\n");
    set_alarm(3.0 + rnd(), 0.0, no_reaction);
    return 1;
}
 
void
no_reaction()
{
    tell_room(TO, "Nothing happens.\n");
}
 
void
init()
{
    ::init();
    add_action(push_boulder,"push");
    add_action(push_boulder,"roll");
    add_action(push_boulder,"move");
    add_action(climb_boulder,"climb");
    add_action(do_knock,"knock");
}
