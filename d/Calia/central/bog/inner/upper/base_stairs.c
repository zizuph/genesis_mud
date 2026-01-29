// ROOM:  base_stairs.c

    /*  Calia Domain

    HISTORY

    [99-06-17] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\UPPER\BASE_STA.DOC].

    PURPOSE

    This is the base for interior rooms at the top of the wall of the
    Sanctimonian fortress.  The fortress is octagonal; there are scaffolds at
    the sides and stairs at the corners on this level.

    SPECIAL NOTE:  This room has only two exits, up and down, which are defined
    inside the create_stairs function.  Do not add other exits in individual
    rooms when using this baseroom.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/d/Calia/central/bog/baseroom";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

#define FILTER_ENEMIES(x) \
    filter(all_inventory(this_object()), &operator(==)(x) @ &->query_attack())

// GLOBAL VARIABLES

object *Stuck_Players = ({});  /*  players who have fallen on the stairs  */
object *Stuck_Items = ({});  /*  objects stuck in the staircase  */
string This_Location;

// FUNCTIONS

// Function:  stair_check()

/*

Purpose:  check to see if a player trips when trying to exit up or down;
manage the disposition of fallen players.

Arguments:  none.

Returns:  1/0.

*/

int
stair_check()

{

    object *inv = ({});
    object *objects_on_stairs = ({});
    object *people_on_stairs = ({});
    object room;
    object weapon;
    object victim = this_player();
    object person;
    string verb;
    string item;
    int ocount;
    int pcount;
    int factor;

    /*
     *  Let's not trip the same player twice in rapid succession.    
     */

    if (member_array(victim, Stuck_Players) != -1)

    {

        Stuck_Players -= ({victim});
        victim->remove_prop(LIVE_S_EXTRA_SHORT);

        write("You pick yourself up off the staircase and carefully" +
            " go on your way.\n");

        tell_room(room,
            QCTNAME(victim) +
            " picks " + victim->query_objective() + "self" +
            " up and goes on " + victim->query_possessive() +
            " way.\n",
            ({victim}));

        return 0;

    }

    /*
     *  Inventory size of 1 indicates nothing/nobody in the room besides 
     *  this_player; in this case, let him pass unmolested.    
     */

    room = this_object();
    inv = all_inventory(room);
    if (sizeof(inv) == 1) return 0;

    objects_on_stairs = FILTER_DEAD(inv);
    people_on_stairs = FILTER_OTHER_LIVE(inv);
    victim = this_player();
    verb = query_verb();
    ocount = sizeof(objects_on_stairs);
    pcount = sizeof(people_on_stairs);
    factor = 1;

    if (random(2))

    {

        weapon = victim->query_weapon(W_LEFT);

    }

    else

    {

        weapon = victim->query_weapon(W_RIGHT);

    }

    if (weapon) factor += 1;

    if (verb == "down") factor += 1;

    factor += sizeof(FILTER_ENEMIES(victim));

    /*
     *  Check for both people and objects on the stairs, only people, and only 
     *  inanimate objects.    
     */

    if (pcount && ocount)

    {

        item = "the " + objects_on_stairs[random(ocount)]->short();
        person = people_on_stairs[random(pcount)];

        if (random(100 * (pcount + ocount + factor)) >
            (victim->query_skill(SS_PARRY) +
            victim->query_skill(SS_ACROBAT) +
            victim->query_stat(SS_INT) +
            victim->query_stat(SS_DEX)))

        {

            if (weapon)

            {

                victim->catch_msg("You trip over " + item +
                    " as you try to go " + verb +
                    ", crash into " + QTNAME(person) +
                    ", knock the two of you" +
                    " flat against the stairs, and leave a" +
                    " big gouge in the timbers" +
                    " with your " + weapon->short() + "!\n");

                person->catch_msg(QCTNAME(victim) +
                    " trips over " + item +
                    " as " + victim->query_pronoun() +
                    " tries to go " + verb +
                    ", crashes into you" +
                    ", knocks the two of you" +
                    " flat against the stairs, and leaves a" +
                    " big gouge in the timbers" +
                    " with " + victim->query_possessive() +
                    " " + weapon->short() + "!\n");

                tell_room(room,
                    QCTNAME(victim) +
                    " trips over " + item +
                    " as " + victim->query_pronoun() +
                    " tries to go " + verb +
                    ", crashes into " + QTNAME(person) +
                    ", knocks the two of them" +
                    " flat against the stairs, and leaves a" +
                    " big gouge in the timbers" +
                    " with " + victim->query_possessive() +
                    " " + weapon->short() + "!\n",
                    ({victim, person}));

                /*
                 *  Since an empty staircase is no hazard at all, I like to 
                 *  grab an item once in a while and jam it into the timbers so
                 *  it will trip the next player.    
                 */

                if (random(200) > victim->query_stat(SS_DEX))

                {

                    tell_room(room,
                        "The " + weapon->short() + " gets" +
                        " jammed into the staircase.\n");

                    weapon->move(room);

                    weapon->add_prop(OBJ_M_NO_GET, "It is" +
                        " stuck firmly between the timbers" +
                        " that form the staircase.\n");

                    Stuck_Items += ({weapon});

                }

            }

            else

            {

                victim->catch_msg("You trip over " + item +
                    " as you try to go " + verb +
                    ", crash into " + QTNAME(person) +
                    ", and knock the two of you" +
                    " flat against the stairs!\n");

                person->catch_msg(QCTNAME(victim) +
                    " trips over " + item +
                    " as " + victim->query_pronoun() +
                    " tries to go " + verb +
                    ", crashes into you" +
                    ", and knocks the two of you" +
                    " flat against the stairs!\n");

                tell_room(room,
                    QCTNAME(victim) +
                    " trips over " + item +
                    " as " + victim->query_pronoun() +
                    " tries to go " + verb +
                    ", crashes into " + QTNAME(person) +
                    ", and knocks the two of them" +
                    " flat against the stairs!\n",
                    ({victim, person}));

            }

            /*
             *  Those who need aid from above the most are the least likely to 
             *  get it in the Sanctimonian fortress!    
             */

            if (random(1000) <
                victim->query_encumbrance_weight() +
                victim->query_panic() +
                victim->query_intoxicated() -
                victim->query_hp())

            {

                write("You tumble down the stairs!\n");

                tell_room(room,
                    QCTNAME(victim) +
                    " tumbles down the stairs!\n",
                    QCTNAME(victim) +
                    " leaves down, " + ({"awkwardly", "ungracefully",
                    "abruptly", "swiftly", "haphazardly"})[random(5)] +
                    ".\n",
                    ({victim}));

                victim->move_living("M",
                    query_exit_rooms()[member_array("down",
                    query_exit_cmds())], 1);

                tell_room(environment(victim),
                    QCTNAME(victim) +
                    " arrives tumbling down the stairs.\n",
                    ({victim}));

                Stuck_Players += ({person});

            }

            else

            {

                Stuck_Players += ({victim, person});

                victim->add_prop(LIVE_S_EXTRA_SHORT,
                    " lying face down on the stairs");

                victim->add_attack_delay(10, 1);

            }

            person->add_prop(LIVE_S_EXTRA_SHORT,
                " sprawled on the stairs");

            person->add_attack_delay(5, 1);

            return 1;

        }

    }

    else if (pcount)

    {

        person = people_on_stairs[random(pcount)];

        if ((random(100) * (pcount + factor)) >
            (victim->query_skill(SS_ACROBAT) +
            victim->query_stat(SS_DEX)))

        {

            if (weapon)

            {

                victim->catch_msg("You clumsily trip over " +
                    QTNAME(person) +
                    " as you try to go " + verb +
                    " and knock the two of you" +
                    " flat against the stairs!\n");

                person->catch_msg(QCTNAME(victim) +
                    " clumsily trips over you" +
                    " as " + victim->query_pronoun() +
                    " tries to go " + verb +
                    " and knocks the two of you" +
                    " flat against the stairs!\n");

                tell_room(room,
                    QCTNAME(victim) +
                    " clumsily trips over " + QTNAME(person) +
                    " as " + victim->query_pronoun() +
                    " tries to go " + verb +
                    " and knocks the two of them" +
                    " flat against the stairs!\n",
                    ({victim, person}));

                Stuck_Players = Stuck_Players - ({victim, person}) +
                    ({victim, person});

                victim->add_prop(LIVE_S_EXTRA_SHORT,
                    " sprawled on the stairs");

                victim->add_attack_delay(10, 1);

                person->add_prop(LIVE_S_EXTRA_SHORT,
                    " lying on the stairs");

                person->add_attack_delay(5, 1);

                return 1;

            }

            else

            {

                if (member_array(person, Stuck_Players) != -1)

                {

                    victim->catch_msg("You deftly hold onto the" +
                        " timbers for balance and" +
                        " leap over " + QTNAME(person) + ".\n");

                    person->catch_msg(QCTNAME(victim) +
                        " deftly holds onto the timbers and leaps" +
                        " over you as " + victim->query_pronoun() +
                        " goes " + verb + " the stairs.\n");

                    tell_room(room,
                        QCTNAME(victim) +
                        " deftly holds onto the timbers for balance" +
                        " and leaps over " + QTNAME(person) + ".\n",
                        ({victim, person}));

                }

                else

                {

                    victim->catch_msg("You stumble and bump into " +
                        QTNAME(person) + " as you go " + verb +
                        " the stairs but manage to grab a" +
                        " timber and keep yourself from falling.\n");

                    person->catch_msg(QCTNAME(victim) +
                        " stumbles and bumps into you as " +
                        victim->query_pronoun() +
                        " goes " + verb + " the stairs but manages" +
                        " to grab a timber and avoid falling.\n");

                    tell_room(room,
                        QCTNAME(victim) +
                        " stumbles and bumps into " + QTNAME(person) +
                        " as " + victim->query_pronoun() +
                        " goes " + verb +
                        " the stairs but manages to grab a" +
                        " timber and avoid falling.\n",
                        ({victim, person}));

                }

                return 0;

            }

        }

    }

    else if (ocount)

    {

        if ((random(100 * (pcount + factor))) >
            (victim->query_skill(SS_AWARENESS) +
            victim->query_stat(SS_DEX)))

        {

            item = "the " + objects_on_stairs[random(ocount)]->short();

            write("You trip over " + item +
                " and fall flat against the stairs!\n");

            Stuck_Players += ({victim});

            victim->add_prop(LIVE_S_EXTRA_SHORT,
                " sprawled on the stairs");

            victim->add_attack_delay(10, 1);

            return 1;

        }

    }

    return 0;

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  register a player (or foreign npc) with the Sanctimonian control
room.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    object room = this_object();

    ::enter_inv(ob, from);

    if (living(ob))

    {

        /*
         *  The following condition will knock down heavily loaded (burden and 
         *  alcohol) players coming from the room below.    
         */

        if (query_verb() == "up" &&
            ob->query_skill(SS_CLIMB) < ob->query_encumbrance_weight() &&
            (random(100) + ob->query_intoxicated()) >
            (ob->query_stat(SS_DEX) + ob->query_skill(SS_ACROBAT)))

        {

            write("You lose your footing and fall down the stairs!\n");

            tell_room(room,
                QCTNAME(ob) +
                " loses " + ob->query_possessive() +
                " footing and falls down the stairs!\n",
                QCTNAME(ob) +
                " leaves down, " + ({"awkwardly", "ungracefully", "abruptly",
                "swiftly", "haphazardly"})[random(5)] +
                ".\n",
                ({ob}));

            ob->move_living("M",
                query_exit_rooms()[member_array("down",
                query_exit_cmds())], 1);

            tell_room(environment(ob),
                QCTNAME(ob) +
                " comes tumbling down the stairs and lands hard!\n",
                ({ob}));

        }

        else if (!ob->sanctimonian()) register_player(ob);

    }

}

// Function:  leave_inv(object, dest)

/*

Purpose:  Called by system when room is exited.  Removes "sprawled" effect if
player leaves by teleportation; otherwise, the exit routine will remove it with
a "getting up" message.

Arguments:  object that leaves, object to which it is going

Returns  nothing

*/

void
leave_inv(object ob, object dest)

{

    if (member_array(ob, Stuck_Players) != -1)

    {

        Stuck_Players -= ({ob});
        ob->remove_prop(LIVE_S_EXTRA_SHORT);

    }

    ::leave_inv(ob, dest);

}

// Function:  create_stairs(location)

/*

Purpose:  Create the room description and add standard attributes.

Arguments:  string containing the filename of this room, string indicating
which compass direction this side of the wall faces.

Returns:  nothing.

*/

void
create_stairs(string location)

{

    This_Location = location;

    set_short("In a spiral staircase");

    set_long("This staircase is made of rough square-cut" +
        " timbers that interlock to form a spiral of steps." +
        " The heavy timbers offer solid footing, but they also" +
        " block your view above and below.\n");

    add_item(({"timbers", "timber", "heavy timbers", "heavy timber",
        "square-cut timbers", "square-cut timber"}),
        "The timbers bear obvious marks, most of which clearly" +
        " show that they were hewn with axes. They are rough but" +
        " well squared to provide good traction.\n");

    add_item(({"marks", "obvious marks", "mark", "obvious mark",
        "gouge", "gouges"}),
        "Most of the marks look like the work of an expert" +
        " lumberjack with a sharp axe, but a few look like gouges" +
        " made by other tools or weapons driven into the" +
        " timbers after they were assembled.\n");

    add_item(({"staircase", "spiral staircase", "stairs", "stair"}),
        "The staircase looks solid indeed, soundly built" +
        " of square-cut timbers that would certainly support" +
        " your weight many times over, but it is narrow" +
        " and poorly lit.\n");

    /*
     *  EXITS    
     */

    add_exit(BOG_OUTER_UPPER + This_Location, "up", "@@stair_check@@", 4);
    add_exit(BOG_INNER_MIDDLE + This_Location, "down", "@@stair_check@@", 0);

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 10);  /*  Difficult to hide in confined space. */
    add_prop(ROOM_I_LIGHT, 1);  /*  Shadowy at best. */

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
