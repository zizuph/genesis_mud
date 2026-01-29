// ROOM:  base_corner.c

    /*  Calia Domain

    HISTORY

    [99-06-29] created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\INNER\GROUND\BASE_COR.DOC].

    PURPOSE

    This is the base for interior corner rooms at ground level in the
    Sanctimonian fortress.  The fortress is octagonal; at this level there are
    8 rooms at the corners of the outer wall, eight along the side, a ring of
    twelve inside them, and a central group of 9.  Two corners have staircases
    leading up; the others are simply storage areas.  The placement of the
    staircases depends upon the control_code and varies with each rebuilding
    (reloading) of the fortress.

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

                Stuck_Players += ({victim, person});

                victim->add_prop(LIVE_S_EXTRA_SHORT,
                    " lying face down on the stairs");

                person->add_prop(LIVE_S_EXTRA_SHORT,
                    " sprawled on the stairs");

            }

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

                person->add_prop(LIVE_S_EXTRA_SHORT,
                    " lying on the stairs");

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

    if (living(ob) && !ob->sanctimonian()) register_player(ob);

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
     *  here to select which rooms have stairs leading up.  A similar routine
     *  at the low level coordinates the placement of stairs leading from that
     *  level down to here.  The formula for up_position gives a value of 1, 3,
     *  5, or 7, and matches the values for down_position generated in the room
     *  above.    
     */

    int control_code = query_control_code();

    /*
     *  Uh-oh, what is all this math for?  The first part of the formula is 
     *  copied from the "up_position" definition in the room above.  It's
     *  needed because it's used to compute that room's down position by adding
     *  a second expression to it.  The formula ensures that up_position in
     *  this room matches down_position in the room above so the stairs will
     *  align properly.    
     */

    int up_position = (((control_code % 4) * 2) + 1 +
        ((control_code % 3) + 1) * 2) % 8;

    int room_finder = 0;
    int n;

    This_Location = location;

    /*
     *  EXITS PART 1    
     */

    /*
     *  Each corner room on this level is surrounded by four other rooms in 
     *  four adjacent compass directions.  Starting at north (position 0) and
     *  rotating clockwise, we use room_finder to determine the direction to
     *  the first one.  The resulting value tells us which corner of the
     *  fortress this room occupies and is used to put different contents in
     *  different corners.    
     */

    while (room_finder < 7 &&
        (!adjacent_rooms[room_finder] ||
        !adjacent_rooms[(room_finder + 1) % 8] ||
        !adjacent_rooms[(room_finder + 2) % 8] ||
        !adjacent_rooms[(room_finder + 3) % 8]))

    {

        room_finder += 1;

    }

    /*
     *  As with all my other rooms that use the adjacent_rooms array to 
     *  generate exits, setting the value of any element to zero effectively
     *  makes that room "not adjacent" to this one.  Here I only want one exit
     *  in a cardinal compass direction to the fortress interior.  Taking out
     *  the first and last rooms that we found eliminates the rooms along the
     *  outer walls, and then only allowing exits in cardinal directions makes
     *  sure we only get the one we want.    
     */

    adjacent_rooms[room_finder] = 0;
    adjacent_rooms[(room_finder + 3) % 8] = 0;

    if (adjacent_rooms[0]) add_exit(adjacent_rooms[0], "north", 0, 1);
    if (adjacent_rooms[2]) add_exit(adjacent_rooms[2], "east", 0, 1);
    if (adjacent_rooms[4]) add_exit(adjacent_rooms[4], "south", 0, 1);
    if (adjacent_rooms[6]) add_exit(adjacent_rooms[6], "west", 0, 1);

    /*
     *  The adjacent_rooms array contains 0 where there are no rooms, so we can 
     *  use the pattern of nonzero values to determine the location of this
     *  room and generate the stairs up if needed.  We can use the same formula
     *  as in the low level corner rooms to determine the orientation of this
     *  room, putting up exits where those have down exits.    
     */

    if ((room_finder + ((room_finder + 3) % 8)) % 8 == up_position)

    {

        set_short("On the fortress floor at the bottom of a staircase");

        set_long("The broad planks of the fortress floor meet" +
            " the heavy timbers of a spiral staircase here. All" +
            " the woodwork is rough but neatly joined at" +
            " square angles, simple but sturdy. Stout logs" +
            " driven into the ground form pillars that" +
            " support the rooms above.\n");

        add_item(({"timbers", "timber", "heavy timbers", "heavy timber",
            "square-cut timbers", "square-cut timber"}),
            "The timbers bear obvious marks, most of which clearly" +
            " show that they were hewn with axes. They are rough but" +
            " well squared to provide good traction.\n");

        add_item(({"staircase", "spiral staircase", "stairs", "stair"}),
            "The staircase looks solid indeed, soundly built" +
            " of square-cut timbers that would certainly support" +
            " your weight many times over, but it is narrow" +
            " and poorly lit.\n");

        add_item(({"planks", "broad planks", "floor", "fortress floor",
            "plank", "broad plank", "ground"}),
            "The floor is covered with broad planks that" +
            " hold your weight without bending at all. Although they" +
            " are a bit rough, they are fitted together so that" +
            " there are no gaps.\n");

        add_item(({"logs", "stout logs", "pillars", "rooms", "rooms above",
            "balcony", "log", "stout log", "pillar", "room", "room above"}),
            "Above you is a balcony that rings the fortress" +
            " interior. It is supported by stout logs serving" +
            " as pillars, and above the balcony are some" +
            " rooms that are enclosed.\n");

        add_item(({"fortress", "walls", "wall", "interior",
            "fortress interior", "woodwork"}),
            "The fortress is octagonal in shape with walls that" +
            " are high and straight. The interior is ringed by" +
            " a balcony just over your head and rooms higher up" +
            " of which you can see very little. The ground" +
            " is covered with broad planks upon which have" +
            " been built some wooden structures.\n");

        add_item(({"structures", "wooden structures",
            "structured", "wooden structure", "rows", "row"}),
            "They resemble small plain houses and are laid" +
            " out neatly in three rows. More than that" +
            " you cannot determine from here.\n");

        /*
         *  EXITS PART 2    
         */

        add_exit(BOG_INNER_LOW + This_Location, "up", "@@stair_check@@", 4);

    }

    else

    {

        /*
         *  Using the position of this side within the compass array (minus the 
         *  northeast door) to determine the room contents ensures that we get
         *  seven different rooms, and adding the control code ensures that the
         *  positions of these rooms are scrambled each time the fortress is
         *  rebuilt.    
         */

        n = (room_finder + control_code) % 3;

        switch (n)

        {

            case 0:

            set_short("Lumber stockpile");

            set_long("Logs and timbers in various stages of" +
                " work are piled here, and woodworking tools are" +
                " hung neatly on the wall.\n");

            break;

            case 1:

            set_short("Scrap heap");

            set_long("Scraps of wood and metal are piled in" +
                " a large wooden bin.\n");

            break;

            case 2:

            set_short("Paint and varnish area");

            set_long("Buckets of paint and varnish are lined" +
                " up neatly along one wall along with brushes" +
                " soaking in water. Some freshly painted boards dry" +
                " on a metal stand.\n");

            break;

        }

    }

    /*
     *  "uid" settings required for cloning objects.    
     */

    setuid();
    seteuid(getuid());

    /*
     *  PROPERTIES    
     */

    add_prop(ROOM_I_HIDE, 90);  /*  Lots of places to hide. */
    add_prop(ROOM_I_LIGHT, 2);  /*  Moderate light comes from the interior. */

    /*
     *  SPECIAL FUNCTION    
     */

    /*
     *  Tell the Sanctimonian central control room that this room has been 
     *  loaded.  Function is found in /d/Calia/central/bog/baseroom.c.    
     */

    register_room();

}
