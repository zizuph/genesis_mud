/*
 *  /d/Gondor/guilds/rangers/north/vantage_top.c
 *
 *  The vantage point for the Northern Hideout
 *    (a room for spying on the environment nearby)
 *
 *  Coded by Alto, 17 July 2001
 *  Updated--Tigerlily, March 2004, to fix alarms
 *      with this_player() and write calls
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define CHAIR2_NAME                  "second platform"
#define CHAIR_NAME                   "first platform"
#define MOVING_THROUGH_VANTAGE       "_moving_through_vantage"
#define RANGER_WAS_STEALTHY          "_ranger_was_stealthy"
#define RANGER_WAS_MASKED            "_ranger_was_masked"

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../rangers.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"
#include "check_exit.c"

public int         move_ranger(object who);
public int         move_ambush(object actor);
public int         exit_room();
public int         ambush_exit();
public int         grasp_swing(object actor);
public int         scale_wall(object actor);
public void        init();
public void        leave_inv(object ob, object dest);
public string      look_at(string arg);     /* VBFC for chairs */
public int         scan_here(string str);


void
create_gondor()
{
    set_short("A secluded vantage point atop a crumbling tower");
    set_long("You are crouched atop a tall crumbling tower among the "
        + "ruins of ancient Fornost. Every time you shift your weight, "
        + "stone breaks loose beneath your feet and falls into the "
        + "darkness below. Two small platforms have been affixed to "
        + "a large parapet. Perhaps it would be safest to have a seat. "
        + "From here you can easily scan the environment near the "
        + "hideout. When you are ready to leave your watch, you may "
        + "descend into the tower using a small swing mounted just "
        + "below the parapet. It might also be possible to scale the "
        + "outer wall.\n");

    add_prop(ROOM_M_NO_SCRY, 1);

    add_chair(CHAIR2_NAME,
        "[down] [in] / [on] [the] [second] 'platform' / 'small platform'",
        1, "in");

    add_chair(CHAIR_NAME,
        "[down] [in] / [on] [the] [first] 'platform' / 'small platform'",
        1, "in");

    add_cmd_item(({"swing", "the swing", "small swing", "the small swing"}),
        "grasp", &exit_room());
    add_cmd_item(({"wall", "outer wall", "the wall", "the outer wall"}),
        "scale", &ambush_exit());

    add_item(({"tower", "tall tower", "crumbling tower", "the tower"}),
        "The tower you are standing on was built long ago in the days when "
        + "Elendil forged the North Kingdom. It has long since fallen into "
        + "a state of decay, and it seems miraculous that it has not fallen "
        + "in on itself. Perhaps some ancient magic is at work here.\n");
    add_item(({"fornost", "ancient fornost"}), "The ruins of this once "
        + "majestic place spread out below you. Most of the towers toppled "
        + "and fell many years ago. It has been longer still since the "
        + "trumpets of the royal heralds of Arnor rang from these walls. "
        + "Despite the decay and sadness, there remains something of "
        + "beauty and dignity about this place.\n");
    add_item(({"ruins"}), "Crumbled stone lies tumbled about the grass "
        + "as far as the eye can see.\n");
    add_item(({"towers"}), "Few towers remain standing. You wonder why "
        + "this particular tower yet stands.\n");
    add_item(({"stone"}), "The tower is made from stone. Many years of "
        + "weathering without repair have left this stone very fragile. "
        + "It is amazing that the tower can even support its own weight, "
        + "much less yours.\n");
    add_item(({"parapet", "parapets"}), "You are crouched behind a large "
        + "parapet atop the tower. It conceals you from prying eyes "
        + "below.\n");
    add_item(({"swing", "small swing"}), "Someone has mounted a small "
        + "swing over a pulley affixed to the wall below the parapet. As "
        + "you carefully examine the swing, you deduce that there must "
        + "be some kind of counterweight dangling far below. Although the "
        + "swing looks too small to sit in, you may be able to grasp it "
        + "and return to the bottom of the tower. Hopefully you are not "
        + "too heavy, as it is rather a long way down.\n");
    add_item(({"pulley"}), "There is a small swing hanging from it.\n");
    add_item(({"wall", "outer wall", "walls"}), "Over the years, many small "
        + "cracks and fissures have opened in the outer wall of the tower. "
        + "Although these blemishes have weakened the structural integrity "
        + "of the tower, you may be able to use them as hand and footholds "
        + "to scale the outer wall.\n");
    add_item(({"cracks", "fissures", "blemishes"}), "They would make "
        + "excellent handholds and footholds, assuming they do not crumble "
        + "under your weight.\n");
    add_item(({"platform", "small platform", "platforms", "small platforms"}),
        "Which one? There appear to be two of them.\n");
    add_item(({"environment"}), "Although much of the environment below "
        + "cannot be seen without risking your neck by leaning out on "
        + "the crumbling stone, some critical locations might be "
        + "covertly observed if you scan the environment.\n");
    add_item(({"hideout"}), "If it could be seen from the outside, it "
        + "wouldn't really be a very good hideout.\n");

    add_item(({"second platform", "second small platform"}), 
        &look_at(CHAIR2_NAME));
    add_item(({"first platform", "first small platform"}), 
        &look_at(CHAIR_NAME));

    reset_room();
}

int
finish_moving(object actor)
{
    actor->remove_prop(MOVING_THROUGH_VANTAGE);
    return 1;
}

int
grasp_swing(object actor)
{

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        actor->catch_tell("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    actor->catch_tell("You grasp the small "
        + "swing and step into the open darkness below.\n\n");
    tell_room(environment(actor), QCTNAME(actor) + " gives the swing a "
        + "good tug and steps off into the yawning darkness below.\n", actor);
    set_alarm(2.0, 0.0, &actor->catch_tell("Whee! You slide quickly down "
        + "through the tower!\n\n"));
    set_alarm(4.0, 0.0, &actor->catch_tell("As you near the bottom, the "
        + "swing slows to a halt. When you release it, the swing quickly "
        + "slides upward, pulled by its counterweight. You easily drop the "
        + "remaining distance to the ground below.\n\n"));
    set_alarm(4.0, 0.0, &finish_moving(actor));

    return 1;
}


int
scale_wall(object actor)
{
    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    actor->add_prop(MOVING_THROUGH_VANTAGE, 1);

    actor->catch_tell("With some reservation, "
        + "you climb over the parapet and lower yourself until your "
        + "feet reach a crack large enough to rest your toes in.\n\n");
    tell_room(environment(actor), QCTNAME(actor) + " climbs over the "
        + "parapet.\n", actor);
    set_alarm(2.0, 0.0, &actor->catch_tell("Mopping sweat from your "
        + "brow, you reach blindly to either side until your fingers " 
        + "find purchase.\n\n"));
    set_alarm(5.0, 0.0, &actor->catch_tell("Stone crumbles beneath your "
        + "hands as you move down the outer face of the tower. You "
        + "cannot turn your head to look, but there is little doubt "
        + "that a fall from here would probably kill you.\n\n"));
    set_alarm(7.0, 0.0, &actor->catch_tell("You reach a place where "
        + "there seem to be no suitable handholds. Trusting that "
        + "you have descended far enough, you let go of the wall "
        + "and drop the remaining distance.\n\n"));

    set_alarm(2.0, 0.0, &tell_room(environment(actor), QCTNAME(actor) +
        " reaches blindly to either side. You find yourself wondering "
        + "if " + PRONOUN(TP) + " will fall. It would then be your job "
        + "to clean up the mess.\n", actor));
    set_alarm(5.0, 0.0, &tell_room(environment(actor), "With some "
        + "reluctance, " + QCTNAME(actor) + " begins to scale the outer "
        + "wall.\n", actor));

    set_alarm(7.0, 0.0, &finish_moving(actor));

    return 1;
}


int
exit_room()
{
    object actor = this_player();

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    grasp_swing(actor);
    set_alarm(5.0, 0.0, &move_ranger(actor));        
    return 1;
}


int
ambush_exit()
{
    object actor = this_player();

    if (actor->query_prop(MOVING_THROUGH_VANTAGE))
    {
        write("You are already moving!\n");
        return 1;
    }

    scale_wall(actor);
    set_alarm(8.0, 0.0, &move_ambush(actor));        
    return 1;
}

int
move_ranger(object who)
{
    say(QCTNAME(who) + " disappears into the yawning darkness below. "
        + "After a moment, the swing returns to its original position.\n");
    who->move_living("M", RANGERS_NOR_DIR + "vantage1", 1, 0);
    tell_room(RANGERS_NOR_DIR + "vantage1", QCTNAME(who) + " suddenly "
        + "descends from the yawning darkness above.\n", who);
    return 1;
}


int
move_ambush(object actor)
{
    object mcloak = present("_mottled_cloak_", actor);

    say(QCTNAME(actor) + " suddenly drops out of sight.\n");

    if (actor->query_prop(RANGER_WAS_STEALTHY))
    {
        actor->remove_prop(RANGER_WAS_STEALTHY);
        if (!actor->query_autosneak())
            actor->set_autosneak(1);
        write("You prepare to move stealthily again as you were "
            + "when you entered the Arnor hideout.\n");
    }
    if (!actor->query_prop("_rangers_incognito"))
        actor->command("$hood myself");

    if (objectp(mcloak->query_worn()) &&
        actor->query_prop(RANGER_WAS_MASKED))
    {
        actor->command("$mask myself");
        actor->command("$pin cloak");
    }
    actor->move_living("M", FORNOST_DIR + "plaza", 1, 0);
    tell_room(FORNOST_DIR + "plaza", "You hear something "
        + "moving near the column.\n", actor);
    return 1;
}


/*
 * Function name:   init
 * Description :    mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    add_action(&scan_here(), "scan");
    init_room_chairs();  /* add chair verbs */
} /* init */

/*
 * Function name:   leave_inv
 * Description :    mask parent to be sure that departing players
 *             are removed from chair/sofa occupants
 */

public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */


int
scan_here(string str)
{
    string *items, target, entrance, exit, surroundings;
    object actor = TP;

    /* No match */
    if (!strlen(str) || !parse_command(str, ({}), 
        "[the] %w [of] [the] [hideout]", target))
    {
        notify_fail("Scan the environment?\n");
        return 0;
    }

    switch (target)
    {
    case "environment":
        write("From here you can probably scan the entrance and exit "
            + "of the hideout.\n");
        return 1;

    case "entrance":
        entrance = ARNOR_DIR + "fornost/l_building";
        entrance->teleledningsanka();
        if (!objectp(find_object(entrance)))
        {
            surroundings = "Shadows obscure the view " +
                "and prevent you from seeing the surroundings.\n";
            return 1;
        }
        //else
        surroundings = (find_object(entrance))->long();
        items = FILTER_CAN_SEE(all_inventory(find_object(entrance)), actor);

        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
               surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
               surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

        actor->catch_tell("You scan the environment near the entrance of "
            + "the hideout.\nThis is what you see:\n\n" + surroundings
            + "\nYou quickly lean back again so that you do not reveal "
            + "your hiding place.\n");
        tell_room(environment(actor), QCTNAME(actor) + " scans the "
            + "environment to the northwest of the tower.\n", actor);
        return 1;

    case "exit":
        exit = FORNOST_DIR + "outer_wall";
        exit->teleledningsanka();
        surroundings = find_object(exit)->long();

        items = FILTER_CAN_SEE(all_inventory(find_object(exit)), actor);

        if (items) 
        {
            if (sizeof(FILTER_DEAD(items)))
               surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) + ".\n";
            if (sizeof(FILTER_LIVE(items)))
               surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) + ".\n";
        }

        actor->catch_tell("You scan the environment near the exit "
            + "outside the hideout.\nThis is what you see:\n\n"
            + surroundings + "\nYou quickly lean back again so that you "
            + "do not reveal your hiding place.\n");
        tell_room(environment(actor), QCTNAME(actor) + " scans the "
            + "environment to the northeast of the tower.\n", actor);
        return 1;

    default:
        notify_fail("What do you want to scan? The environment?\n");
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
    {
        return "A plain wooden platform. It is bolted to the parapet and "
            + "looks like it might hold your weight better than the "
            + "crumbling stone beneath your feet.\n" +
            sitting_on_chair(CHAIR_NAME, this_player(), 0);
    }

    if (arg == CHAIR2_NAME)
    { 
        return "A plain wooden platform. It is bolted to the parapet and "
            + "looks like it might hold your weight better than the crumbling "
            + "stone beneath your feet.\n" +
            sitting_on_chair(CHAIR2_NAME, this_player(), 0);
    }
}
