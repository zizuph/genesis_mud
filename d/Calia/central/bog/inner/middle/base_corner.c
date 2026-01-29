// ROOM:  base_corner.c

    /*  Calia Domain

    HISTORY

    [99-06-19] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\MIDDLE\BASE_COR.DOC].

    PURPOSE

    This is the base for interior rooms at the middle level of the Sanctimonian
    fortress.  The fortress is octagonal; there are eight rooms at the corners
    and eight at the side at this level.  Two corners have staircases leading
    up and down; the others have landings from the stairs above and exits to
    the sides.  The placement of the staircases depends upon the control_code
    and varies with each rebuilding (reloading) of the fortress.

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

            if (member_array("down", query_exit_cmds()) != -1 &&
                random(1000) <
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

        if (random(100 * (pcount + factor)) >
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
         *  The following condition is true only if the player has fallen from 
         *  the room above while trying to go up the stairs and there are more
         *  stairs in this room leading down.  Under those circumstances, a
         *  player who's overloaded (in more ways than one) may continue
         *  tumbling.    
         */

        if (query_verb() == "up" &&
            file_name(from) == BOG_INNER_UPPER + This_Location &&
            member_array("down", query_exit_cmds()) != -1 &&
            random(200) >
            (ob->query_intoxicated() + ob->query_encumbrance_weight()))

        {

            tell_room(room,
                QCTNAME(ob) +
                " continues falling down the stairs!\n",
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

// Function:  create_corner(location, *adjacent_rooms)

/*

Purpose:  Create the room description and add standard attributes.  Depending
on the value of the control code, this room will be either a staircase leading
up and down or the landing from the staircase above with exits to adjacent
rooms along the inner wall.

Arguments:  string containing the filename of this room, string array
containing filenames of adjacent rooms.

Returns:  nothing.

*/

void
create_corner(string location, string *adjacent_rooms)

{

    /*
     *  The control code is a general-purpose randomly generated number from 0 
     *  to 999.  It is generated whenever the central bog control room is
     *  loaded and the same value is passed to all other bog rooms.  It is used
     *  here to select which rooms have stairs leading down; a similar routine
     *  at the low level coordinates the placement of stairs leading up.  The
     *  formula gives a value of 1, 3, 5, or 7.    
     */

    string *nonzero = ({0});
    int control_code = query_control_code();
    int stair_position = ((control_code % 4) * 2) + 1;
    int n = 0;

    nonzero = adjacent_rooms - nonzero;
    This_Location = location;

    /*
     *  The adjacent_rooms array contains 0 where there are no rooms, so we can 
     *  use the pattern of nonzero values to determine the location of this
     *  room and generate the stairs down if needed.  The eight elements in the
     *  array are ordered along the compass starting at north and rotating
     *  clockwise to northwest, and any two opposite corner rooms will have two
     *  exits that are mirror images of each other.  The formula (x + y) % 8,
     *  where x and y are the positions of the two nonzero elements in
     *  adjacent_rooms, will always yield 1, 3, 5, or 7, with each pair of
     *  opposite rooms having the same value.  Stair_position uses the
     *  control_code to generate one of these values and select the pair that
     *  get stairs leading down.    
     */

    if ((member_array(nonzero[0], adjacent_rooms) +
        member_array(nonzero[1], adjacent_rooms)) % 8 == stair_position)

    {

        set_short("In a spiral staircase");

        set_long("This staircase is made of rough square-cut" +
            " timbers that interlock to form a spiral of steps." +
            " The heavy timbers offer solid footing, but they also" +
            " block your view above and below.\n");

        /*
         *  EXITS 1a    
         */

        add_exit(BOG_INNER_LOW + This_Location, "down",
            "@@stair_check@@", 0);

    }

    else

    {

        set_short("At the bottom of a spiral staircase");

        set_long("This solid platform forms the base of" +
            " a spiral staircase, both made of sturdy" +
            " rough-hewn timbers. Not much light filters in" +
            " through the few slits in the walls, but a" +
            " bit more illumination emanates from" +
            " the adjacent rooms.\n");

        add_item(({"walls", "wall", "slits", "slit"}),
            "The walls have a few slits in them hardly thicker" +
            " than paper; they let in just a bit of light, but" +
            " you can't see through them.\n");

        add_item(({"platform", "solid platform"}),
            "Like the staircase, it's made of heavy timbers neither" +
            " planed nor sanded but squared with an axe just enough" +
            " to make for easy walking.\n");

        /*
         *  EXITS 1b    
         */

        /*
         *  Side exits only exist if there is no down exit.  The baths are on 
         *  the east and west sides of the fortress when (control_code % 4) is
         *  0 or 1, so to isolate them from the barracks (old Sanctimonian
         *  tradition) there are no north or south exits (always elements 0 and
         *  4 in adjacent_rooms) from the staircases.

         *  Similarly, (control_code % 4) is 2 or 3, baths are on the north and
         *  south sides, so there are no east and west exits (always elements 2
         *  and 6 in adjacent_rooms).  We simply set the appropriate elements
         *  of adjacent_rooms to zero to prevent the generation of superfluous
         *  exits.    
         */



        if ((control_code % 4) > 1)

        {

            adjacent_rooms[0] = 0;
            adjacent_rooms[4] = 0;

        }

        else

        {

            adjacent_rooms[2] = 0;
            adjacent_rooms[6] = 0;

        }

        /*
         *  If I did all the math right, this level of the fortress should have 
         *  sixteen rooms, eight corners and eight sides, that connect in the
         *  form of two crescents separated by two isolated side rooms at
         *  either north and south or east and west.  If you want to get from
         *  the barracks to the bath (one of the isolated rooms), you have to
         *  find an up staircase, walk around the upper level, take another
         *  staircase down through middle to low level, walk around the lower
         *  level, and take yet another staircase leading up.  It's not a maze,
         *  really!  It's just the Sanctimonian way of making sure that the
         *  male and female warriors never accidentally walk into the others'
         *  baths.  They retain the principle each time the fortress interior
         *  is burned but not necessarily the exact arangement of rooms.    
         */

        if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
        if (adjacent_rooms[1]) add_exit(adjacent_rooms[1], "northeast", 0, 1);
        if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
        if (adjacent_rooms[3]) add_exit(adjacent_rooms[3], "southeast", 0, 1);
        if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
        if (adjacent_rooms[5]) add_exit(adjacent_rooms[5], "southwest", 0, 1);
        if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);
        if (adjacent_rooms[7]) add_exit(adjacent_rooms[7], "northwest", 0, 1);

    }

    /*
     *  EXITS 2   
     */

    /*
     *  There is always an up exit.    
     */

    add_exit(BOG_INNER_UPPER + This_Location, "up",
        "@@stair_check@@", 4);

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
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 10);  /*  Difficult to hide in confined space. */
    add_prop(ROOM_I_LIGHT, 1);  /*  Dim light. */

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
