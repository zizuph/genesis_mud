/*
 *  /d/Gondor/guilds/rangers/hq/vantage5.c
 *
 *  The vantage point for the Ranger Central Headquarters
 *    (a room for spying on the environment nearby)
 *
 *  Coded by Alto, 20 June 2001
 *
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#include "../rangers.h"

#define CHAIR_NAME     "first stool"
#define CHAIR2_NAME    "second stool"
#define MOVING_THROUGH_VANTAGE       "_moving_through_vantage"

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

public int    move_ranger(object tp);
public int    move_ambush(object tp);
public int    exit_room();
public int    ambush_exit();
public int    slide_rope(object tp);
public int    leap_branch(object tp);
public void   init();
public void   leave_inv(object ob, object dest);
public string look_at(string arg);

object actor, *items;
string entrance, trap, road, surroundings;

void
create_gondor()
{
    set_short("a secluded vantage point in the Druedain forest");
    set_long("You are perched near the very top of a tall oak tree. "
        + "A small platform has been lashed to the uppermost branches, "
        + "with two small stools to rest on during the long hours of "
        + "the watch. From here you can easily scan the environment "
        + "near the hideout. A rope running back down the tree is tied "
        + "here. When you are ready to leave your watch, you may slide "
        + "down it. You also notice that some of the branches here might "
        + "bear your weight.\n");

    add_chair(CHAIR_NAME,
     "[down] [in] / [on] [the] [first] 'stool' / 'small stool'", 1, "in");
    add_chair(CHAIR2_NAME,
     "[down] [in] / [on] [the] [second] 'stool' / 'small stool'", 1, "in");

    add_cmd_item(({"rope", "the rope", "down rope", "down the rope"}),
            "slide", &exit_room());
    add_cmd_item(({"branch", "branches", "the branch", "the branches",
            "to branch", "to the branch", "to the branches", "to branches"}),
            "leap", &ambush_exit());

    add_item(({"rope", "the rope"}), "The rope looks very sturdy and "
        + "well-maintained. It disappears into the leaves below you.\n");
    add_item(({"stool", "small stool", "stools", "small stools"}), "Which "
        + "one? There appear to be two of them.\n");
    add_item(({"trees", "druedain", "druedain forest", "tree", "forest"}), 
        "The trees of the Druedain are tall, dense and ancient. The smell of "
        + "leaves is thick in the air.\n");
    add_item(({"leaves", "leaf", "branches"}), "There are so many leaves "
        + "that it is difficult to see through them. Some of the branches "
        + "look as though they might bear your weight if you leaped to "
        + "them.\n");
    add_item(({"sky", "ground"}), "It is difficult to see through the "
        + "dense leaves.\n");
    add_item(({"platform", "small platform"}), "The platform is firmly "
        + "lashed to the tree and is cunningly concealed from below.\n");
    add_item(({"environment"}), "Although much of the environment below "
        + "you is concealed by leaves and branches, several critical "
        + "locations might be covertly observed if you scan it.\n");
    add_item(({"oak tree"}), "This is one of the tallest oak trees you "
        + "have ever seen! You are presently at its apex, rocking gently "
        + "back and forth in the wind.\n");
    add_item(({"second stool", "second small stool"}), &look_at(CHAIR2_NAME));
    add_item(({"first stool", "first small stool"}), &look_at(CHAIR_NAME));

    reset_room();
}

int
finish_moving(object tp)
{
    tp->remove_prop(MOVING_THROUGH_VANTAGE);
    return 1;
}

int
slide_rope(object tp)
{
    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        tp->catch_tell("You are already moving!\n");
        return 1;
    }

    TP->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &tp->catch_tell("You give the rope a good " +
        "tug. It seems to hold.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("You grip the rope tightly " +
        "and wrap your legs around it. With a sigh, you loosen your " +
        "grip.\n\n"));
    set_alarm(5.0, 0.0, &tp->catch_tell("Whee! You slide quickly " +
        "down through the branches!\n\n"));
    set_alarm(10.0, 0.0, &tp->catch_tell("As you near the bottom, " +
        "you begin to tighten your grip again upon the rope. At the " +
        "last moment, you release the rope entirely and spring " +
        "lightly down onto a large branch.\n\n"));
    tell_room(environment(tp), QCTNAME(tp) + " gives the rope a "
        + "good tug and begins to descend it.\n", tp);
    set_alarm(5.0, 0.0, &tell_room(environment(tp), QCTNAME(tp) +
        " slides quickly down through the branches.\n", tp));

    set_alarm(10.0, 0.0, &finish_moving(tp));

    return 1;
}


int
leap_branch(object tp)
{
    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        tp->catch_tell("You are already moving!\n");
        return 1;
    }

    tp->add_prop(MOVING_THROUGH_VANTAGE, 1);

    set_alarm(0.0, 0.0, &tp->catch_tell("After carefully assessing " +
        "the distance, you leap into the open air toward some of " +
        "the sturdier-looking branches.\n\n"));
    set_alarm(2.0, 0.0, &tp->catch_tell("Unfortunately, the branches " +
        "do not bear your weight! You crash heavily through the " +
        "foliage, plunging downward at an increasing rate of speed!\n\n"));
    set_alarm(5.0, 0.0, &tp->catch_tell("Whew! A large cluster of " +
        "branches and leaves breaks your fall.\n\n"));
    set_alarm(7.0, 0.0, &tp->catch_tell("Looking below, you see the " +
        "entrance to the hideout. You carefully drop the remaining " +
        "ten feet to the ground.\n\n"));

    tell_room(environment(tp), QCTNAME(tp) + " suddenly leaps into "
        + "the surrounding branches!\n", tp);
    set_alarm(2.0, 0.0, &tell_room(environment(tp), QCTNAME(tp) +
        " crashes through leaves and branches, falling quickly toward "
        + "the ground.\n", tp));
    set_alarm(5.0, 0.0, &tell_room(environment(tp), "Fortunately, "
        + "a large cluster of branches breaks " + QCTPNAME(tp) +
        " fall!\n", tp));

    set_alarm(7.0, 0.0, &finish_moving(tp));

    return 1;
}


int
exit_room()
{
    object tp = this_player();

    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        tp->catch_tell("You are already moving!\n");
        return 1;
    }

    slide_rope(tp);
    set_alarm(11.0, 0.0, &move_ranger(tp));        
    return 1;
}


int
ambush_exit()
{
    object tp = this_player();

    if (tp->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    leap_branch(tp);
    set_alarm(8.0, 0.0, &move_ambush(tp));        
    return 1;
}

int
move_ranger(object tp)
{
    say(QCTNAME(tp) + " disappears into the branches.\n");
    tp->move_living("M", RANGERS_HQ_DIR + "vantage1", 1, 0);
    tell_room(environment(tp), QCTNAME(tp) + " suddenly "
        + "emerges from the surrounding branches.\n", tp);
    return 1;
}


int
move_ambush(object tp)
{
    tp->move_living("M", "/d/Gondor/anorien/druedain/rangerfield", 1, 0);
    tp->catch_tell("You drop carefully to the ground.\n");
    say(QCTNAME(tp) + " drops carefully to the ground.\n");
    return 1;
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


int
scan_here(string str)
{
    string target;
    object tp = this_player();

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), "[the] %s", target))
    {
        notify_fail("Scan the environment?\n");
        return 0;
    }

    switch (target)
    {
    case "environment":
        write("From here you can probably scan the entrance, the trap "
            + "and the road.\n");
        return 1;

    case "entrance":
        entrance = DRUEDAIN_DIR + "rangerfield";
        entrance->teleledningsanka();
        surroundings = find_object(entrance)->long();
        items = FILTER_CAN_SEE(all_inventory(find_object(entrance)), tp);

        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
                surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items)))+".\n";
            if (sizeof(FILTER_LIVE(items)))
                surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items)))+".\n";
        }

        write("You scan the environment near the entrance of "
            + "the hideout.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(tp), QCTNAME(tp) + " scans the "
            + "environment directly below the platform.\n", tp);

        return 1;

    case "trap":
        trap = DRUEDAIN_DIR + "rangerpath2";
        trap->teleledningsanka();

        surroundings = find_object(trap)->long();
        items = FILTER_CAN_SEE(all_inventory(find_object(trap)), tp);

        
        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
                surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items)))+".\n";
            if (sizeof(FILTER_LIVE(items)))
                surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items)))+".\n";
        }

        write("You scan the environment near the hidden trap "
            + "outside the hideout.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(tp), QCTNAME(tp) + " scans the "
            + "environment to the east of the hideout.\n", tp);

        return 1;

    case "road":
        road = ANO_DIR + "road/wr7";
        road->teleledningsanka();
        surroundings = (find_object(road))->long();
        items = FILTER_CAN_SEE(all_inventory(find_object(road)), tp);

        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
                surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items)))+".\n";
            if (sizeof(FILTER_LIVE(items)))
                surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items)))+".\n";
        }

        write("You scan the environment near the secret path "
            + "from the road beyond the forest.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(tp), QCTNAME(tp) + " scans the "
            + "environment to the northeast of the hideout.\n", tp);

        return 1;

    default:
        NF("What do you want to scan? The environment?\n");
        return 0;
    }
}

/*
 * Function name: look_at
 * Description  : VBFC to describe chair/sofa + occupants
 */
public string
look_at(string arg)
{
    if (arg == CHAIR_NAME)
        return "A plain wooden stool. Two lighter coloured oval patches "
            + "on its surface attest to the many rangers who have sat "
            + "upon it during the long hours of the watch.\n" +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);

    if (arg == CHAIR2_NAME)
        return "This stool has no ovals worn into it. No doubt it has "
            + "only recently been moved up to the platform.\n" +
            sitting_on_chair(CHAIR2_NAME, this_player(), 0);

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
    init_room_chairs();
}
