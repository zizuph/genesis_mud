// OBJECT:  jump rope

    /* Calia Domain

    HISTORY

    [98-12-03] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\JUMPROPE.DOC].

    [99-11-22] Lasso effects added by Uhclem.

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <options.h>

// FUNCTIONS

// Function:  make_jumprope()

/*

Purpose:  create descriptions appropriate to a jump rope.

Arguments:  none

Returns:  nothing

*/

void
make_jumprope()

{

    set_short("jump rope");

    set_long("The rope has a strong but supple leather grip at either end," +
        " and it's just the right length for someone wanting to" +
        " skip rope if he's not feeling very energetic or jump rope" +
        " if he wants a real workout.\n");

}

// Function:  make_lariat()

/*

Purpose:  create descriptions appropriate to a lariat.

Arguments:  none

Returns:  nothing

*/

void
make_lariat()

{

    set_short("lariat");

    set_long("The rope has a strong but supple leather grip at either end," +
        " one of which is tied in a big loop. The lariat isn't" +
        " long enough for you to do any serious roping, but you" +
        " might be able to lasso somebody close by just for fun.\n");

}

// Function:  grip_desc()

/*

Purpose:  return the description of the leather grips, which varies depending
on whether the rope is tied into a lariat or not.

Arguments:  none

Returns:  string of descriptive text

*/

string
grip_desc()

{

    if (short() == "jump rope")

    {

        return "The leather grips make the rope easy to handle. One" +
            " of them is a little bit longer than the other," +
            " making it possible to tie a loop in the rope" +
            " at that end.\n";

    }

    else

    {

        return "One of the leather grips has been tied to make a" +
            " lariat, but it looks like it would be easy to untie" +
            " the loop is you wanted to use the rope" +
            " for something else.\n";

    }

}

// Function:  lasso_someone(target)

/*

Purpose:  lasso a living object.

Arguments:  target to be lassoed.

Returns:  0/1.

*/

int
lasso_someone(string str)

{

    object tp = this_player();
    object thisroom = environment(tp);
    object target;
    string lasso_text;
    int lasso_success = 0;

    if (short() == "jump rope")

    {

        return 0;

    }

    if (!str || !(target = present(str, environment(tp))))

    {

        notify_fail("Lasso whom?\n");
        return 0;

    }

    /*
     *  The target object is in the room.  Living things are lassoed somewhat 
     *  differently from non-living.    
     */

    if (living(target))

    {

        /*
         *  Make it easy to lasso most people but possible for an extremely 
         *  dextrous or well-trained player to frequently evade the rope.    
         */

        if (
            (random(tp->query_skill(SS_WEP_MISSILE) * 5)
            >
            random(target->query_skill(SS_DEFENSE)))
            ||
            (random(tp->query_stat(SS_DEX))
            >
            random(target->query_stat(SS_DEX)))
            )

        {

            tp->catch_msg("You cast your lariat in " + QTNAME(target) +
                "'s direction and manage to" +
                " ensnare " + target->query_objective() +
                " in a smooth, effortless motion.\n");

            target->catch_msg(QCTNAME(tp) +
                " casts " + tp->query_possessive() +
                " lariat in your direction and ensnares you" +
                " in a smooth, effortless motion.\n");

            tell_room(thisroom,
                QCTNAME(tp) + " casts " + tp->query_possessive() +
                " lariat toward " + QTNAME(target) +
                " and ensnares "  + target->query_objective() +
                " in a smooth, effortless motion.\n",
                ({tp, target}));

            lasso_success = 1;

        }

        else

        {

            lasso_text =
                ({
                "by ducking and letting it pass harmlessly overhead",
                "by stepping aside just as the loop is about" +
                " to encircle its target",
                "by slapping it to the ground just as it" +
                " comes within reach",
                "by quickly jogging a short distance out of its range"
                })[random(4)];

            tp->catch_msg("You cast your lariat in " + QTNAME(target) +
                "'s direction, but " + target->query_pronoun() +
                " eludes the rope " + lasso_text +
                ".\n");

            target->catch_msg(QCTNAME(tp) +
                " casts " + tp->query_possessive() +
                " lariat in your direction, but you elude the" +
                " rope " + lasso_text +
                ".\n");

            tell_room(thisroom,
                QCTNAME(tp) + " casts " + tp->query_possessive() +
                " lariat toward " + QTNAME(target) +
                ", but "  + target->query_pronoun() +
                " eludes the rope" + lasso_text +
                ".\n",
                ({tp, target}));

        }

    }

    else

    {

        if (tp->query_skill(SS_WEP_MISSILE) > random(20) ||
            tp->query_stat(SS_DEX) > random(50))

        {

            write("You cast your lariat in the direction" +
                " of the " + target->short() +
                " and lasso it easily!\n");

            say(QCTNAME(tp) + " casts " + tp->query_possessive() +
                " lariat in the the direction" +
                " of the " + target->short() +
                " and lassos it like a real professional roper!\n");

            lasso_success = 1;

        }

        else

        {

            lasso_text =
                ({
                ", but the rope misses by a wide margin",
                ", but the rope just grazes its target and" +
                " falls to the ground",
                ", but the rope misses by a hair's breadth",
                ", but the loop fails to encircle the target and" +
                " falls to the ground"
                })[random(4)];

            write("You cast your lariat in the direction" +
                " of the " + str + lasso_text + ".\n");

            say(QCTNAME(tp) +
                " casts " + tp->query_possessive() + " lariat" +
                " in the direction of the " + str + lasso_text + ".\n");

            lasso_success = 1;

        }

    }

    if (lasso_success)

    {

        tell_room(thisroom,
            "The tension on the lariat opens the loop," +
            " and " + QTNAME(tp) + " pulls the rope back toward " +
            tp->query_objective() + "self as it falls" +
            " to the ground.\n",
            ({tp}));

        write("The tension on the lariat opens the loop," +
            " and you pull the rope back toward yourself as it falls" +
            " to the ground.\n");

        make_jumprope();

    }

    return 1;

}

// Function:  skip_rope(rope)

/*

Purpose:  skip the rope in a leisurely manner.

Arguments:  string indicating this rope

Returns:  0/1

*/

int
skip_rope(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to skip. */

    {

        notify_fail("Skip what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " skips rope in an even, steady" +
            " rhythm, making it look like the easiest thing in" +
            " the world to do.\n");

        write("You skip rope in an even, steady" +
            " rhythm, making it look like the easiest thing in" +
            " the world to do.\n");

        return 1;

    }

    return 0;

}

// Function:  jump_rope(rope)

/*

Purpose:  jump the rope vigorously.

Arguments:  string indicating this rope

Returns:  0/1

*/

int
jump_rope(string str)

{

    object tp = this_player();
    object target;

    if (!stringp(str)) /* Player did not specify what to jump. */

    {

        notify_fail("Jump what?\n");
        return 0;

    }

    if (parse_command(str, all_inventory(tp), "%o", target))

    {

        if (target != this_object()) return 0;

        say(QCTNAME(tp) + " jumps rope vigorously, spinning the" +
            " rope faster and faster until it is only a blur," +
            " yet " + tp->query_possessive() + " feet keep" +
            " up with the blistering pace until " +
            tp->query_pronoun() + " finally halts the rope and" +
            " takes a quick bow.\n");

        write("You jump rope vigorously, spinning the" +
            " rope faster and faster until it is only a blur," +
            " yet your feet keep up with the blistering pace until" +
            " you finally halt the rope and take a quick bow.\n");

        return 1;

    }

    return 0;

}

// Function:  tie_loop

/*

Purpose:  tie a loop in the rope to make a lariat, or untie it to turn the
lariat back into a jumprope.

Arguments:  string containing "loop".

Returns:  0/1

*/

int
tie_loop(string str)

{

    object tp = this_player();
    string this_verb = query_verb();

    if (!wildmatch("*loop*", str))

    {

        notify_fail("Are you trying to " + this_verb + " a loop?\n");
        return 0;

    }

    if (this_verb == "tie")

    {

        if (short() == "jump rope")

        {

            write("You tie a loop in the jump rope to make a lariat.\n");

            say(QCTNAME(tp) + " ties a loop in " + tp->query_possessive() +
                " jump rope to turn it into a lariat.\n");

            make_lariat();

        }

        else

        {

            write("A loop has already been tied in the rope -" +
                " it isn't long enough for two loops.\n");

        }

    }

    else

    {

        if (short() == "lariat")

        {

            write("You untie the loop in the lariat to turn it" +
                " into a jump rope.\n");

            say(QCTNAME(tp) +
                " unties the loop in " + tp->query_possessive() +
                " lariat to turn it into a jump rope.\n");

            make_jumprope();

        }

        else

        {

            write("There's no loop in this rope to untie.\n");

        }

    }

    return 1;

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(skip_rope, "skip");
    add_action(jump_rope, "jump");
    add_action(tie_loop, "tie");
    add_action(tie_loop, "untie");
    add_action(lasso_someone, "lasso");

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_name("rope");
    add_name("toy");
    add_name("jumprope");
    add_name("lariat");
    make_jumprope();

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "The merchant snarls: I don't want that" +
        " rope - why, it's not even long enough to hang" +
        " a gnome with!\n");

    /*
     *  ITEMS    
     */

    add_item(({"grip", "grips", "leather grip", "leather grips", "loop"}),
        "@@grip_desc@@");

    add_item(({"end", "ends", "middle"}),
        "The two ends are separated by just the right amount of middle.\n");

}
