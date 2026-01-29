/* 
 * /d/Ansalon/guild/society/room/roof.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * Roof of the Kender guild, and training area for combat tactics 
 * Gwyneth 1999
 */
inherit "/lib/skill_raise";

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include <ss_types.h>

#define ROCK (KGOBJ + "rock")
inherit KENDERMORE_OUT;

string climb_down();
string west_rope();
string walk_rope();
string long_descr();

/*
 * Function name : set_up_skills
 * Description : Initialize the trainer and set the skills we train
 */
void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_CTACT_SPECIAL, "use combat tactics", "combat tactics",
        70, 100);
}

void
create_kendermore_room()
{
    set_short("The roof of a large building");
    set_long(&long_descr());
    add_item("pebbles", "They're small round pebbles.\n");
    add_item("target", "This is where you can practice your sling.\n");
    add_item(({"edge", "side"}), "Ropes are tied to the east and " + 
        "west edges.\n");
    add_item("rope", "There are two ropes tied to the edge of the " + 
        "building, one on the west, and one on the east.\n");
    add_item(({"east edge", "east rope", "eastern edge", "eastern rope"}),
        "The rope has been tied to the eastern edge of the building. It " + 
        "hangs over the edge, allowing a person to climb down.\n");
    add_item(({"west edge", "west rope", "western edge", "western rope"}),
        "One side of a rope has been tied to the edge of the building, " + 
        "while the other side has been tied to another building, " + 
        "allowing a person to slide down it. A brave person might walk " + 
        "across it.\n");
    add_item(({"building", "far building", "far away building"}), "It's " + 
        "a building on the far end of town, but you're too far away to " + 
        "see for sure what it is.\n");
    add_cmd_item(({"down", "down rope", "down east rope", "down east edge"}), 
        "climb", &climb_down());
    add_cmd_item(({"down rope", "down west rope", "across rope",
        "across west rope"}), "slide", &west_rope());
    add_cmd_item(({"down rope", "down west rope", "across rope",
        "across west rope"}), "walk", &walk_rope());
    set_up_skills();
}

int
gather(string str)
{
    if (!strlen(str))
    {
        notify_fail("Gather rocks?\n");
        return 0;
    }
    else if (lower_case(str) == "rocks")
    {
    clone_object(ROCK)->move(this_player());
    clone_object(ROCK)->move(this_player());
    clone_object(ROCK)->move(this_player());
    write("You gather a few rocks.\n");
    return 1;
    }
    else
    {
        notify_fail("Gather rocks?\n");
        return 0;
    }
}

public void
init()
{
    ::init();
    init_skill_raise();
    add_action(gather, "gather");
}

int
sk_improve(string sk)
{
    int steps;
    string skill, *tmp;

    if (!sk || sscanf(sk, "%d", steps))
        return sk_list(steps);

    tmp = explode(sk, " ");
    if (sscanf(tmp[sizeof(tmp) -1], "%d", steps) == 1 && sizeof(tmp) > 1)
        skill = implode(tmp[0 .. sizeof(tmp) - 2], " ");
    else
    {
        skill = sk;
        steps = 1;
    }

    if (!TP->query_guild_name_occ(GUILD_NAME))
    {
        write("Only members are allowed to train here!\n");
    }
    return ::sk_improve(sk);
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "You're standing on the roof " + 
        "of a large building. The ground is covered with pebbles, and a " + 
        "target has been set up here. A rope has been securely tied " + 
        "on the eastern edge of the roof, and hangs over the side. " + 
        "Another rope is connected to the western edge, and the far " + 
        "end is tied to another building far away. It " + 
        "slopes down, allowing someone to slide down it. " + 
        "The brave adventurer might try to walk across.\n");
}

string
climb_down()
{
    write("You climb down the rope and slip through the window.\n");
    say(QCTNAME(TP) + " climbs down the rope.\n");
    TP->move_living("M", KGROOM + "board_room", 1, 0);
    tell_room(KGROOM + "board_room", QCTNAME(TP) + " climbs in from the " + 
        "window.\n", TP);
    return "";
}

string
walk_rope()
{
    if (((TP->query_stat(SS_OCCUP)) > 50) && 
      (TP->query_skill(SS_ACROBAT) > 19))
    {
        write("You bravely walk out across the rope. With the long " +
            "experience of a kender, you manage to reach the end. " +
            "You jump onto the roof, then spin off the edge, landing " +
            "with the grace of an acrobat on the ground in front of an " +
            "inn.\n");
        say(QCTNAME(TP) + " bravely walks out across the rope. You " +
            "look on in admiration as " + HE(TP) + " reaches the " +
            "end, jumps onto the roof, spins off the edge and lands " +
            "on the ground with all the grace of a kender acrobat.\n");
        TP->move_living("M", KROOM + "street03", 1, 0);
        tell_room(KROOM + "street03", QCTNAME(TP) + " gracefully " +
            "lands in front of you from somewhere above.\n", TP);
        return "";                                                             
    }
    else
    {
        write("You bravely walk out across the rope, but your " +
            "skill doesn't match your daring. You fall, but manage  " +
            "to land yourself in a water fountain, which you " +
            "quickly climb out of.\n");
        say(QCTNAME(TP) + " bravely walks out across the rope, but " +
            "loses his balance. " + C(HE(TP)) + " lands in a water " +
            "fountain, which " + HE(TP) + " quickly climbs out of.\n");
        TP->move_living("M", KROOM + "street27", 1, 0);
        tell_room(KROOM + "street27", QCTNAME(TP) + " falls from above, " +
            "landing in the water fountain, which " + HE(TP) + " quickly " +
            "climbs out of.\n", TP);
        return "";
    }

    NF("Walk across what?\n");
}

string
west_rope()
{
    write("You grab onto the rope, and slide down to the end. " + 
        "You drop down to the ground, rubbing your hands and " + 
        "reminding yourself to take the more exciting way next " + 
        "time.\n");
    say(QCTNAME(TP) + " grabs onto the rope, and slides down to the " + 
        "end. " + C(HE(TP)) + " drops down to the ground.\n");
    TP->move_living("M", KROOM + "street03", 1, 0);
    tell_room(KROOM + "street03", QCTNAME(TP) + " drops down " + 
        "from above.\n", TP);
    return "";
    NF("Slide down what?\n");
}

void
remove_ex_members(object who)
{
    if (present(who, this_object()))
    {
        who->catch_tell("A very large looking kender enters the room and " +
            "escorts you out of the guild.\n");
        say("A very large looking kender enters the room and escorts " +
            QTNAME(who) + " out of the guild.\n", who);
        tell_room(KGROOM + "joinroom", QCTNAME(who) + " is escorted out " +
            "of the guild by a very large looking kender.\n");
        who->move_living("M", KROOM + "joinroom", 0, 0);
        return;
    }
    return;
}

