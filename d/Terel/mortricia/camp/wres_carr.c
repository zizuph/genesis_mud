/* The wrestler's carriage. Mortricia 920927 */
/*

    Modified: 11 Sep 2003, by Bleys
        - Changed the calls to the wrestler in do_lift() so that they
            set an alarm in the wrestler. He was reacting to the lift
            before the lift was reported to the mortal, which makes
            things look backwards to the mortal. I don't think the
            wrestler should be prescient ;-)

*/

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define CAMP_DIR        MORTRICIADIR + "camp/"

object wrestler, weight1, weight2;

void
reset_room()
{
    object belt;

    if (!wrestler) {
        wrestler = clone_object(CAMP_DIR + "wrestler");
        wrestler -> move(TO);
    } else {
        belt = present("belt", wrestler);
        if (!belt) {
            belt = clone_object(CAMP_DIR + "belt");
            belt -> add_prop("blood_stained", 1);
            belt -> move(wrestler);
            wrestler -> command("wear belt");
        }
    }
    if (!weight1) {
        weight1 = clone_object(CAMP_DIR + "weight");
        weight1 -> move(TO);
    }
    if (!weight2) {
        weight2 = clone_object(CAMP_DIR + "weight");
        weight2 -> move(TO);
    }
}

void
create_room()
{
    set_short("The wrestler's carriage");
    set_long(BSN(
        "You have entered the carriage in which the wrestler " +
        "rests in between the shows in the big tent. Well, he also " +
        "does some training here, and that's why there " +
        "are some weights here."
    ));

    add_item("weights", "They are made of solid iron.\n");
    add_cmd_item("weight", "lift", "@@do_lift");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(CAMP_DIR + "camp_07", "south", 0);

    reset_room();
}

do_lift()
{
    int tp_str;
    string str, name, pron;
    object w, iw;

    tp_str = TP -> query_stat(SS_STR);
    name = lower_case(TP -> query_name());
    pron = capitalize(TP -> query_pronoun());
    w = wrestler;
    iw = present("weight");

    if (!iw) {
        str = "You cannot reach the weights.\n";
        return BSN(str);
    }
    say(QCTNAME(TP) + " tries to lift a weight.\n");
    if (tp_str >= 0 && tp_str < 10) {
        str = "The weight doesn't move at all.";
        say(pron + " is too weak. The weight doesn't move at all.\n");
        if ( w )
        {
            w->set_reaction("smile " + name);
        }
    }
    if (tp_str >= 10 && tp_str < 30) {
        str = "The weight moves a little.";
        say(pron + " is too weak. The weight moves only a little.\n");
        if ( w )
        {
            w->set_reaction("smile " + name);
        }
    }
    if (tp_str >= 30 && tp_str < 50) {
        str = "You manage to lift the weight up to your knees.";
        say(pron + " manages to lift the weight up to the knees.\n");
        if ( w )
        {
            w->set_reaction("applaud " + name);
        }
    }
    if (tp_str >= 50 && tp_str < 70) {
        str = "You manage to lift the weight up to your shoulders.";
        say(pron + " manages to lift the weight up to the shoulders.\n");
        if ( w )
        {
            w->set_reaction("stare " + name);
        }
    }
    if (tp_str >= 70 && tp_str < 90) {
        str = "You manage to lift the weight above your head.";
        say(pron + " manages to lift the weight above the head.\n");
        if ( w )
        {
            w->set_reaction("peer " + name);
        }
    }
    if (tp_str >= 90) {
        str = "You handle the weight as if it is pure air.";
        say(pron + " handles the weight as if it was pure air.\n");
        if ( w )
        {
            w->set_reaction("gasp");
        }
    }
    return BSN(str);
}
