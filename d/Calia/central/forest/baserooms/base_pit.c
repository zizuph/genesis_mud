// ROOM:  base_pit.c

/* Calia Domain

HISTORY

[June 21, 1999] created by Uhclem from
[D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_PIT.DOC].

PURPOSE

Thi is a pit in the interior of the Great Central Forest. It's designed to be a
particularly unpleasant place, especially if you're not alone.

*/

// INCLUSIONS AND DEFINITIONS

inherit "/std/room";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// FUNCTIONS

// Function:  climb_out()

/*

Purpose:  determine if you can climb out of the pit.

Arguments:  none.

Returns: 0/1.

*/

int
climb_out()

{

    object tp = this_player();

    /*  In its simplest form, climbing success is based on comparing the sum of
        a player's skill (SS_CLIMB) and a stat (SS_STR) against a random number
        between 0 and 100, not bad odds considering that this sum can exceed
        200 for an advanced player. However, we do add a few modifications to
        increase the range of that random number: the amount that you're
        panicking, the burden you're carrying (as a percent of the max you can
        hold), and an additional 100 for fighting and for each hand that's
        wielding a weapon.

        This test is similar to the one used in GROUND_LEVEL rooms to determine
        if a player can climb a tree. The main difference lies in that trees
        test dexterity as the key stat while the pit tests strength. */

    int success = 100 +
        tp->query_panic() +
        tp->query_encumbrance_weight() +
        objectp(tp->query_attack()) * 100 +
        objectp(tp->query_weapon(W_LEFT)) * 100 +
        objectp(tp->query_weapon(W_RIGHT)) * 100;

    if ((tp->query_stat(SS_STR) + tp->query_skill(SS_CLIMB)) > random(success))

    {

        return 0;  /* You made it! */

    }

    else

    {

        switch (success)

        {

            case 0..200:

                /*
                 *  This is just a slip. The low success threshold means that 
                 *  you're doing it right but are just unlucky. There's only a
                 *  tiny fatigue penalty.   
                 */

                if (tp->query_fatigue() > 1) tp->add_fatigue(-1);

                write("You nearly escape from the pit, but your hands" +
                    " slip and you fall back in.\n");

                break;

            case 201..300:

                /*
                 *  At this level you're doing something wrong, maybe carrying 
                 *  too much or trying to climb wielding a halberd. There's a
                 *  modest fatigue penalty. Since I figure that the effort you
                 *  put into the climb is roughly dependent on how much energy
                 *  you've got left, I calculate the penalty as a percentage of
                 *  your current fatigue.   
                 */

                tp->add_fatigue(tp->query_fatigue() / -20);

                write("You struggle to pull yourself out of the pit," +
                    " but the slippery sides offer little support and" +
                    " you fall back in.\n");

                break;

            case 301..400:

                /*
                 *  At this level you're doing several things wrong and may be 
                 *  trying to escape the pit while some other guy (maybe 2)
                 *  wielding a halberd is whacking your helmet. There's a
                 *  significant fatigue penalty.   
                 */

                tp->add_fatigue(tp->query_fatigue() / -10);

                write("You vainly try to extract yourself from the" +
                    " pit, but your attempt is labored and after a" +
                    " few seconds you fall back in frustration.\n");

                break;

            default:

                /*
                 * At this level you're in big trouble, carrying too much 
                 *  weight, holding weapons in your hands, and fighting with
                 *  someone while you try to climb. There's a serious fatigue
                 *  penalty.   
                 */

                tp->add_fatigue(tp->query_fatigue() / -5);

                write("You desperately try to escape from the pit," +
                    " but the effort is too much for you. You fall" +
                    " back without even getting a glimpse of" +
                    " the ground above.\n");

        }

        say(QCTNAME(tp) + " tries to climb out of the pit but" +
            " slips and falls back in.\n");

    }

    return 1;

}

// Function:  leave_inv()

/*

Purpose:  Delete the property associated with a player when he leaves the pit.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

{

    ::leave_inv(ob, dest);
    if (living(ob)) remove_prop("pit_" + ob->query_name());

}

// Function:  sorry_pal()

/*

Purpose:  Tell the player he can't do whatever he just tried to do in the pit
if it isn't on the pit-approved list.

Arguments:  none.

Returns:  0/1.

*/

int
sorry_pal()

{

    object tp = this_player();

    if (member_array(query_verb(), query_prop("pit_" + tp->query_name())) !=
        -1)

    {

        return 0;

    }

    write("You can't do that in the oppressive confines of the pit!\n");

    return 1;

}

// Function:  init()

/*

Purpose:  add local commands. In actuality, it adds a property containing the
list of verbs a player can use while in the pit. The property is a big array,
so it's added to room, not the player! Basically, the player can use standard
Genesis commands; nothing from guild or other cmdsouls or from objects (other
than Calian forest objects) is allowed. However, commands that mask standard
commands, like specialized "say" or "team" functions are not blocked.

Arguments:  none.

Returns: nothing.

*/

void
init()

{

    object tp = this_player();
    mixed *command_list;
    mixed *details;
    string *soul_list;
    string *verb_list;
    string defined_by;
    string *dont_override = ({});
    int m;
    int n;

    ::init();

    if (tp->query_wiz_level()) return;  /* Don't block wizards. */

    command_list = commands(tp);
    m = sizeof(command_list);

    for (n=0; n<m; n+=1)

    {

        details = command_list[n];
        defined_by = file_name(details[2]);

        if (wildmatch("/d/Genesis*", defined_by)
            || wildmatch("/cmd/live*", defined_by)
            || wildmatch("/std*", defined_by)
            || wildmatch("/d/Calia/central/forest*", defined_by))

        {

            dont_override += ({details[0]});

        }

    }

    soul_list = tp->query_cmdsoul_list();
    m = sizeof(soul_list);

    for (n=0; n<m; n+=1)

    {

        verb_list = m_indices(find_object(soul_list[n])->query_cmdlist());

        if (wildmatch("/d/Genesis*", soul_list[n])
            || wildmatch("/cmd/live*", soul_list[n])
            || wildmatch("/std*", soul_list[n]))

        {

            dont_override += verb_list;

        }

    }

    add_prop("pit_" + tp->query_name(), dont_override);

    add_action(sorry_pal, "", 1);

}

// Function:  create_pit(this_location)

/*

Purpose:  provides the create_room functions for the pit.

Arguments:  string containing the location of this room according to the column
and row scheme used for the entire forest.

Returns:  nothing.

*/

void
create_pit(string this_location)

{

    set_short("In a deep pit");

    set_long("You find yourself wading in smelly water at the bottom of" +
        " a deep pit. The sides are soft and covered with" +
        " wet vegetation.\n");

    add_item(({"side", "sides", "vegetation", "wet vegetation"}),
        "There's really nothing interesting about the sides of the" +
        " pit other than the vegetation, which may give you enough" +
        " traction to get back up to ground level.\n");

    add_item(({"water", "smelly water"}),
        "This is an unfinished pit. You stand ankle-deep in" +
        " nondescript water, your feet resting on a nonexistent" +
        " bottom. Don't you feel silly?\n");

    add_exit(GROUND + this_location, "up", "@@climb_out@@", 20);

    /*
     *  Following exit is a dummy to allow shouts from the pit to be heard in 
     *  the trees.   
     */

    add_exit(LOW + this_location, "u", 1, 1, 1);

    add_prop(ROOM_I_HIDE, 99);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

}
