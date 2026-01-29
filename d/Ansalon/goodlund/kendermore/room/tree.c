/* Created by Gwyneth on June 10, 1999. */

#include "/d/Ansalon/goodlund/kendermore/local.h"
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit STREET_DESC;
inherit KENDERMORE_OUT;

object bird;

#define PLAYER_I_FOUND_STRING "_player_i_found_string"

void
reset_kendermore_room()
{
    if (!bird)
        {
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
            bird = clone_object(KNPC + "bird");
            bird->move(TO);
        }    
}

void
create_kendermore_room()
{
    set_short("In the branches of an ancient tree");
    set_long("@@long_descr");

    add_item(({"branches", "branch"}), "They reach out in all directions " + 
        "from here. You imagine that many kender have had fun climbing " + 
        "this tree.\n");
    add_item("bark", "It's smooth and brown, except for one slightly " + 
        "unusual spot.\n");
    add_item(({"leaves", "green leaves"}), "They surround you, waving " + 
        "gently in the breeze.\n");
    add_item("spot", "This spot looks different from the rest of the " + 
        "bark!\n");
    add_item(({"street", "streets"}), "@@street_descr@@\n");
    add_cmd_item(({"spot", "bark"}),"search", "@@search_bark");
    add_cmd_item("down", "climb", "@@climb_down");
    reset_kendermore_room();
    return;
}

public void
init()
{
    ::init();

    add_action("climb_branch", "climb");
}

string
long_descr()
{
    return (tod_descr() + season_descr() + "You are surrounded by " +
        "walls of green leaves and bark. You can just barely see the " + 
        "streets below you, and the sky above. Branches reach out from " + 
        "here.\n"); 
}

public int
climb_branch(string arg)
{
    object rstring;
    NF("Climb where?\n"); /* Failure message */

    if (!strlen(arg))
    {
        return 0;  /* no arg */
    }
    arg = L(arg); /* Be sure it's lowercase. */
    if (!parse_command(arg, ({}), 
        "[up] [out] [on] [onto] 'branch' / 'branches'")) 
    {
        return 0;  /* bad arg */
    }

    if (TP->query_prop(PLAYER_I_FOUND_STRING))
    {
        write("You crawl out onto one of the largest branches where " + 
            "you find a bird's nest.\n");
        say(QCTNAME(TP) + " crawls out onto a large branch.\n" + 
            QCTNAME(TP) + " crawls back from the branch.\n");
        return 1;
    }

    write("You crawl out onto one of the largest branches where you find " + 
        "a bird's nest. A colourful object catches your eye, and you " + 
        "pick it up, slipping it into your pocket.\n");
    rstring = clone_object(KOBJ + "rstring");
    rstring->move(TP);
    TP->add_prop(PLAYER_I_FOUND_STRING, 1);
    say(QCTNAME(TP) + " crawls out onto a large branch.\n" + QCTNAME(TP) +
        " crawls back from the branch.\n");
    return 1;

}

string
climb_down()
{
    if (TP->query_skill(SS_CLIMB) < 30)
    {
        write("You have no clue how you got up here, but going down " + 
            "is going to be painful! You close your eyes and begin to " + 
            "climb down. Your foot slips, sending you tumbling down to " + 
            "the ground.\n");
        say(QCTNAME(TP) + " starts to climb down, but falls to the street " + 
            "below instead.\n");
        tell_room(KROOM + "street45", QCTNAME(TP) + " falls from the tree " + 
            "above.\n");
        TP->move_living("M", KROOM + "street45", 1, 0);
        TP->heal_hp(-50);
        return "";
    }
    if ((TP->query_skill(SS_CLIMB) < 45) && 
        (TP->query_encumberance_weight() > 29))
    {
        write("The ground looks very far away to scamper down with so " + 
            "much weighing you down.\n");
        return "";
    }

    write("You carefully climb down the ancient tree.\n");
    say(QCTNAME(TP) + " climbs carefully down the ancient tree.\n");
    tell_room(KROOM + "street45", QCTNAME(TP) + " climbs carefully " + 
        "down the ancient tree.\n");
    TP->move_living("M", KROOM + "street45", 1, 0);
    return "";
}

string
search_bark()
{
    write("It looks like something's been hidden in the tree, but you " + 
        "just can't figure out how to get at it!\n");
    return "";
}
