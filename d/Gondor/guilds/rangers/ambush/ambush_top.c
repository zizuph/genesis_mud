/*
 *  /d/Gondor/guilds/rangers/ambush/ambush_top.c
 *
 *  A base room vantage/ambush point for the rangers
 *    (a room for spying on the environment nearby)
 *
 *  Coded by Alto, 05 August 2001
 *
 *  Modification log:
 *    Gwyneth, 4 May 2004 - Turned into a base room for inheriting.
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#include <macros.h>

inherit RANGERS_AMB_DIR + "ambush_funcs.c";

#define CHAIR_NAME     "first platform"
#define CHAIR2_NAME    "second platform"
#define AMBUSH_I_MOVE  "_ambush_i_move"

public int    move_ambush();
public int    return_road();
public int    ambush_road();
public int    return_road_message();
public int    ambush_road_message();
public void   init();
public void   leave_inv(object ob, object dest);
public void   set_top_exit(string exit);
public void   set_ambush_desc(string desc);
public int    scan_here(string str);
public string look_at(string arg);

public string Exit, Desc;

void
create_ambush_top()
{
    // set_long();
    // set_ambush_move(); - used for move_ranger()
    // set_top_exit(); - used for move_ambush()
    // set_ambush_desc(); - intersection or crossroads
}

void
create_gondor()
{
    create_ambush_top();
    set_short("a secluded vantage point near the road");

    add_chair(CHAIR_NAME,
     "[down] [in] / [on] [the] [first] 'platform' / 'small platform'",
     1, "in");
    add_chair(CHAIR2_NAME,
     "[down] [in] / [on] [the] [second] 'platform' / 'small platform'",
     1, "in");

    add_item(({ Desc, "entrance" }), "Such things "
        + "are better scanned than examined, as they are not nearby.\n");
    add_item(({ "road" }), "It cannot be seen from here, but you know "
        + "it is nearby.\n");

    add_item(({ "second platform", "second small platform" }), 
        &look_at(CHAIR2_NAME));
    add_item(({ "first platform", "first small platform" }), 
        &look_at(CHAIR_NAME));

    reset_room();
}

int
finish_amb_move()
{
    TP->remove_prop(AMBUSH_I_MOVE);
    return 1;
}

int
return_road_message()
{
    object actor = TP;

    if (actor->query_prop(AMBUSH_I_MOVE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(AMBUSH_I_MOVE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You leave your hiding place and "
        + "return to the hidden path.\n\n"));

    tell_room(environment(actor), QCTNAME(actor) + " leaves the "
        + "hiding place and returns to the hidden path.\n", actor);

    set_alarm(2.0, 0.0, &finish_amb_move());

    return 1;
}


int
ambush_road_message()
{
    object actor = TP;

    if (actor->query_prop(AMBUSH_I_MOVE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(AMBUSH_I_MOVE, 1);

    set_alarm(0.0, 0.0, &actor->catch_tell("You carefully examine the "
        + Desc + " before moving.\n\n"));
    set_alarm(2.0, 0.0, &actor->catch_tell("With all the stealth you can "
        + "muster, you sneak toward the " + Desc + ".\n\n"));

    set_alarm(2.0, 0.0, &tell_room(environment(actor), QCTNAME(actor)
        + " looks carefully from side to side and moves toward the "
        + Desc + ".\n", actor));

    set_alarm(3.0, 0.0, &finish_amb_move());

    return 1;
}


int
return_road()
{
    if (TP->query_prop(AMBUSH_I_MOVE))
    {
        write("You are busy navigating the path - concentrate on what "
            + "you are doing!\n");
        return 1;
    }

    return_road_message();
    set_alarm(1.0, 0.0, &move_ranger(TP));        
    return 1;
}

int
ambush_road()
{
    if (TP->query_prop(AMBUSH_I_MOVE))
    {
        write("You are busy navigating the path - concentrate on what "
            + "you are doing!\n");
        return 1;
    }

    ambush_road_message();
    set_alarm(3.0, 0.0, &move_ambush());        
    return 1;
}

int
move_ambush()
{
    say(QCTNAME(TP) + " sneaks carefully toward the " + Desc + ".\n");
    tell_room(Exit, "Something stirs near the edge of the road.\n");

    TP->move_living("M", Exit, 1, 0);
    return 1;
}


/*
 * Function name: init
 * Description  : mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    add_action(&scan_here(), "scan");
    add_action(&return_road(), "return");
    add_action(&ambush_road(), "ambush");
    init_room_chairs();
}

/*
 * Function name: leave_inv
 * Description  : mask parent to be sure that departing players
 *                are removed from chair/sofa occupants
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
}

void
set_top_exit(string exit)
{
    Exit = exit;
}

void
set_ambush_desc(string desc)
{
    Desc = desc;
}

int
scan_here(string str)
{
    /* This should be masked. */
    return 1;
}

/*
 * Function name: look_at
 * Description  : VBFC to describe chair/sofa + occupants
 */
public string
look_at(string arg)
{
    if (arg == CHAIR_NAME)
    {
        return "A plain wooden platform. It is lashed down so that it "
            + "will hold your weight without revealing your location. It "
            + "does not look all that comfortable, but what do you expect?\n" +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }

    if (arg == CHAIR2_NAME)
    { 
        return "A plain wooden platform. It is lashed down so that it "
            + "will hold your weight without revealing your location. It "
            + "does not look all that comfortable, but what do you expect?\n" +
            sitting_on_chair(CHAIR2_NAME, this_player(), 0);
    }

}
