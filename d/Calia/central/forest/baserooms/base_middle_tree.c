// ROOM:  base_mid_tree.c

    /*  Calia Domain

    HISTORY

    [99-06-21] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_MID.DOC].

    PURPOSE

    This file is the inherited base for rooms in the mid-tree level of the
    Great Central Forest. This level is the hub of activity for arboreal
    creatures; the treetops above and bare trunks below offer only limited
    mobility. */

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
#include "let_go.h"
#include FOREST_QUEST

// GLOBAL VARIABLES

string Up_And_Down_Exits;
string This_Location;
string Tree;
int Falling_is_possible;

// FUNCTIONS

// Function:  drop_on_someone(drop_text)

/*

Purpose:  let a player drop an object on someone on the ground directly below.

Arguments:  string containing object and target.

Returns:  0/1.

*/

int
drop_on_someone(string drop_text)

{

    object tp = this_player();
    object ground_room = find_object(GROUND + This_Location);
    object item;
    object enemy;
    object dropping_object;
    int perception = (50 - tp->query_skill(SS_AWARENESS)) * 1000;

    if (!parse_command(drop_text,
        all_inventory(tp) + FILTER_LIVE(all_inventory(ground_room)),
        " %o 'on' %o ", item, enemy)) return 0;

    /*
     *  If the parse_command statement was successful, we should have 
     *  identified one object each that matches the dropped item and the enemy
     *  player. The drop is impossible if it's too dark to see below, and a
     *  heap object or anything lighter than water makes a poor missile.   
     */

    if ((ground_room->query_prop(ROOM_I_LIGHT) < 1 &&
        !tp->query_prop(LIVE_I_SEE_DARK))
        ||
        enemy->query_prop(OBJ_I_VOLUME) < perception)

    {

        write("You can't see your target well enough.\n");
        return 1;

    }

    if (item->num_heap() > 0
        ||
        item->query_prop(OBJ_I_VOLUME) > item->query_prop(OBJ_I_WEIGHT))

    {

        write("That's not a good missile to drop from this distance.\n");
        return 1;

    }

    /*
     *  All basic requirements have been met to drop something on someone, so 
     *  we move the dropping-object to the player which controls the movement
     *  and calculates the results.   
     */

    dropping_object = clone_object(FOREST_DROPPING_OBJECT);
    dropping_object->move(tp);

    dropping_object->start_dropping(tp, item, enemy, ground_room,
        this_object());

    return 1;

}

// Function:  drop_object()

/*

Purpose:  Make a dropped object fall; this function is called after a very
short delay when an object is dropped in the room.

Arguments:  none.

Returns:  nothing.

*/

void
drop_object()

{

    object *loose_objects = query_prop(FOREST_LOOSE_OBJECTS);
    if (!loose_objects) return;
    else loose_objects = FILTER_DEAD(loose_objects);

    while (sizeof(loose_objects))

    {

        /*
         *  The following check is just to account for a nimble player who 
         *  grabs an object after someone drops it but before it leaves the
         *  room.   
         */

        if (environment(loose_objects[0]) == this_object())

        {

            loose_objects[0]->move(GROUND + This_Location);

        }

        loose_objects -= ({loose_objects[0]});

    }

    remove_prop(FOREST_LOOSE_OBJECTS);

}

// Function:  exa_ground()

/*

Purpose:  Let a player see who is on the ground below.

Arguments:  none.

Returns:  string containing information about the ground-level room.

*/

string
exa_ground()

{

    object ground_room = find_object(GROUND + This_Location);
    object low_tree_room = find_object(LOW + This_Location);
    object *ground_live_objects = FILTER_LIVE(all_inventory(ground_room));
    object *low_tree_live_objects = FILTER_LIVE(all_inventory(low_tree_room));
    object *too_small_to_see = ({});
    object tp = this_player();

    /*
     *  Perception sets the threshold for the smallest living object (volume in 
     *  ml) the player can see from this height. A player with awareness of 50
     *  can see everything. Players on the ground can't hide from observers in
     *  the tree.   
     */

    int perception = (50 - tp->query_skill(SS_AWARENESS)) * 1000;
    int m;
    int n;
    string results = "";

    if (ground_room->query_prop(ROOM_I_LIGHT) > 0
        || tp->query_prop(LIVE_I_SEE_DARK))

    {

        m = sizeof(ground_live_objects);

        for (n=0; n<m; n+=1)

        {

            if (ground_live_objects[n]->query_prop(OBJ_I_VOLUME) <= perception)
                too_small_to_see += ({ground_live_objects[n]});

        }

        ground_live_objects -= too_small_to_see;

        too_small_to_see = ({});

    }

    if (low_tree_room->query_prop(ROOM_I_LIGHT) > 0
        || tp->query_prop(LIVE_I_SEE_DARK))

    {

        m = sizeof(low_tree_live_objects);

        for (n=0; n<m; n+=1)

        {

            if (low_tree_live_objects[n]->query_prop(OBJ_I_VOLUME) <=
                perception) too_small_to_see += ({low_tree_live_objects[n]});

        }

        low_tree_live_objects -= too_small_to_see;

    }

    if (sizeof(ground_live_objects))
        results = "On the ground below you see " +
        COMPOSITE_ALL_LIVE(ground_live_objects) + ".";

    else results = "You do not see anybody on the ground below.";

    if (sizeof(low_tree_live_objects))
        results = " You see " + COMPOSITE_ALL_LIVE(low_tree_live_objects) +
        " clinging to the tree trunk.";

    return results + "\n";

}

// Function:  look_down(down)

/*

Purpose:  Let a player see who is on the ground below.

Arguments:  string, must be "down".

Returns:  1/0.

The information is sent with catch_msg statements; the text comes from the
exa_ground function, which returns a string to either this function or to
commands like "exa ground".

*/

int
look_down(string direction)

{

    if (direction == "down")

    {

        this_player()->catch_msg(exa_ground());
        return 1;

    }

    else return 0;

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  cause non-living objects that enter this room to drop to ground level

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    object *loose_objects;

    ::enter_inv(ob, from);

    if (from
        && !living(ob)
        && environment(from) == this_object()
        && query_verb() == "drop")

    {

        loose_objects = query_prop(FOREST_LOOSE_OBJECTS);

        if (loose_objects)
            add_prop(FOREST_LOOSE_OBJECTS, loose_objects + ({ob}));

        else add_prop(FOREST_LOOSE_OBJECTS, ({ob}));

        set_alarm(0.5, 0.0, drop_object);

    }

}

// Function:  leave_inv()

/*

Purpose:  Notify players of the approach of a player who climbs up or down from
this level, or provide messages for non-living items falling to the ground.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

{

    object *players;
    string dest_room_name;

    ::leave_inv(ob, dest);

    if (!dest) return;  /* Covers updates and object clones by wizards. */

    dest_room_name = file_name(dest);

    if (living(ob))

    {

        /*
         *  There are various ways to leave the tree; only climbing down or up 
         *  sends a special message to the destination room.   
         */

        if (query_verb() == "down")

        {

            tell_room(LOW + This_Location,
                QCNAME(ob) + " climbs down the trunk of" +
                " the " + Tree + " tree.\n", ({ob}));

        }

        if (query_verb() == "up")

        {

            tell_room(UPPER + This_Location,
                QCNAME(ob) + " climbs up the trunk of" +
                " the " + Tree + " tree.\n", ({ob}));

        }

    }

    else

    {

        if (dest_room_name != GROUND + This_Location) return;

        /*
         *  This is the routine for non-living objects. I only provide a 
         *  message for items headed to ground level, which indicates that they
         *  have been dropped (objects "dropped on" another player are
         *  controlled by the dropping_object, not this code; their destination
         *  is the fall_room). Players at low-tree level have their faces flush
         *  against the tree trunk; at most only one will notice the fall of a
         *  non-living object.   
         */

        if (ob->num_heap() > 1)

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " fall to the ground.\n");

            tell_room(dest,
                capitalize(LANG_ASHORT(ob)) +
                " fall from the " + Tree + " tree.\n");

        }

        else

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " falls to the ground.\n");

            tell_room(dest,
                capitalize(LANG_ASHORT(ob)) +
                " falls from the " + Tree + " tree.\n");

        }

        players =
            FILTER_LIVE(all_inventory(find_object(LOW + This_Location)));

        if (players && sizeof(players))
            players[random(sizeof(players))]->catch_msg("Something" +
            " whizzes past your head on its way from the forest canopy" +
            " to the ground.\n");

    }

}

// Function:  this_room_desc

/*

Purpose:  return the long description of the room.  People who have done the
forest quest can see all the exits.

Arguments:  none

Returns:  string containing room description.

*/

string
this_room_desc()

{

    string room_desc =
        "You are high in a mighty " + Tree + " tree. Its" +
        " sturdy limbs support your weight easily, and they are so" +
        " large and numerous at this level that they form a" +
        " comfortable floor for you to move around on, although" +
        " there are plenty of spaces for you to fall through" +
        " if you're careless. The limbs reach out in many" +
        " directions toward other trees of similar proportions.\n";

    if (query_noshow_obvious()) room_desc += Up_And_Down_Exits;

    return room_desc;

}

// Function:  start_tree_combat()

/*

Purpose:  put the forest_combat_effect object in the room when fighting begins.
The object is only needed if it isn't here already.

Arguments:  none.

Returns: 0.

*/

int
start_tree_combat()

{

    object to = this_object();
    object combat_effect;

    if (!present("_tree_combat_control", to))

    {

        combat_effect = clone_object(FOREST_TREE_COMBAT);
        combat_effect->move(to);

    }

    return 0;

}

// Function:  climb_check()

/*

Purpose:  Check the player's ability to go higher in the tree.

Arguments:  none.

Returns: 1/0.

I have no interest in stranding a player in the trees, so if he was able to
make it up to this level, I'll let him go back down. But going to the next
level, which for most trees is the highest, requires not only climbing skill
but courage. Burden is a key factor: the better you can climb, the more you can
carry.

*/

int
climb_check()

{

    object tp = this_player();

    int success = tp->query_stat(SS_DIS) + tp->query_panic();

    /*
     *  No, that's not a typo: panic ADDS to your chance of climbing to the 
     *  top. It may also keep you there! The test isn't very hard to pass; it's
     *  basically designed to keep newbies out of the treetops unless they're
     *  trying to evade an attacker.   
     */

    if (success > (random(25) + 10))

    {

        /*
         *  The Central Forest Climbing Rule:  no player can climb a tree if 
         *  his encumbrance is more than his climb skill.   
         */

        if (tp->query_encumberance_weight() > tp->query_skill(SS_CLIMB))

        {

            write ("You are too heavily burdened to climb any higher.\n");
            return 1;

        }

        else return 0;

    }

    else

    {

        write("No, you tremble at the mere thought of ascending" +
            " to that height.\n");

        say(QCTNAME(tp) + " looks up and trembles in fear.\n");

    }

    return 1;

}

// Function:  movement_check()

/*

Purpose:  Check the player's ability to make lateral movements at the mid-tree
level.

Arguments:  none.

Returns: 1/0.

Moving through the forest at mid-tree level takes some training. It's less
tiring than slogging across the forest floor (except when there's a trail), and
you're far less likely to lose your way, but you pay for these benefits by
risking a fatal fall. A player must complete the simple forest quest to be able
to recognize exits at this level; once he's done that, lateral movement is
aided by dex, climb, and acrobat, hampered by panic and burden.

*/

int
movement_check()

{

    object tp = this_player();
    object fall_from_tree;
    int success;
    int damage;

    if(!tp->test_bit("Calia", FOREST_QUEST_GROUP, FOREST_QUEST_BIT))

    {

        write("There is no obvious exit " + query_verb + ".\n");
        return 1;

    }

    success = tp->query_stat(SS_DEX) + tp->query_skill(SS_CLIMB) +
        tp->query_skill(SS_ACROBAT) - tp->query_panic() -
        tp->query_encumbrance_weight();

    /*
     *  If you pass the test, you get to move. If you don't, the penalty is 
     *  based upon how you were rated using the above formula, which is
     *  designed so that even a small player can move with confidence once he's
     *  received sufficient training.   
     */

    if (success > random(100)) return 0;

    /*
     *  If there is no room below, you can't fall! The lucky player still has 
     *  to suffer a little bit: he'll get a random selection from one of the
     *  two worst non-falling results.   
     */

    if (!Falling_is_possible && success < 0) success = random(40);

    else

    {

        switch (success)

        {

            case 80..99:

                write("You slip as you start to move but quickly" +
                    " regain your footing.\n");

                say(QCTNAME(tp) + " tries to leave " + query_verb() +
                    " but slips.\n");

                tp->add_panic(5);
                tp->add_fatigue(-3);

                break;

            case 60..79:

                write("As you begin to move your foot slides off the" +
                    " side of the limb supporting your weight! You" +
                    " grab another limb and pull yourself back into" +
                    " a secure position.\n");

                say(QCTNAME(tp) + " tries to leave " + query_verb() +
                    " but loses " + tp->query_possessive() + " footing and" +
                    " has to grab onto a branch for support.\n");

                tp->add_panic(10);
                tp->add_fatigue(-6);

                break;

            case 40..59:

                write("You lose your balance momentarily! As you grope" +
                    " for a secure handhold, you get a good view of" +
                    " the ground below that inspires you to return to" +
                    " a secure position.\n");

                say(QCTNAME(tp) + " tries to leave " + query_verb() +
                    " but loses " + tp->query_possessive() +
                    " balance and barely manages to remain in" +
                    " a standing position.\n");

                tp->add_panic(20);
                tp->add_fatigue(-12);

                break;

            case 20..39:

                write("You lose your footing and nearly fall" +
                    " between the branches! Fortunately, you manage to" +
                    " cling to the tree trunk and drag yourself back" +
                    " to a standing position.\n");

                say(QCTNAME(tp) + " tries to leave " + query_verb() +
                    " but loses " + tp->query_possessive() +
                    " footing and nearly falls between the branches!\n");

                tp->add_panic(40);
                tp->add_fatigue(-24);
                tp->add_prop(LIVE_I_ATTACK_DELAY, 5);

                break;

            case 0..19:

                write("You slip through the branches and find" +
                    " yourself dangling above the forest floor! You" +
                    " cling to one sturdy branch for a few seconds" +
                    " as you regain your composure, then pull yourself" +
                    " back up to safety.\n");

                say(QCTNAME(tp) + " tries to leave " + query_verb() +
                    " but slips and falls between the branches, dangling" +
                    " for a few seconds before pulling " +
                    tp->query_objective() + "self back up to" +
                    " a secure position.\n");

                tp->add_panic(40);
                tp->add_fatigue(-48);
                tp->add_prop(LIVE_I_ATTACK_DELAY, 10);

                break;

            default:

                write("You fall through the branches and plummet to" +
                    " the ground below!\n");

                say(QCTNAME(tp) + " tries to leave " + query_verb() +
                    " but slips and falls to the ground below!\n");

                fall_from_tree = clone_object(FOREST_FALL_FROM_TREE);
                fall_from_tree->move(tp);
                fall_from_tree->start_falling();

                return 1;

        }

    }

}

// Function:  create_tree(location, *rooms, tree_type)

/*

Purpose:  Generate a short description, long description, items, and exits for
a mid-tree level room.

Arguments:  The filename of the room being created, an array of adjacent room
filenames, and a tree type are required. Functions in this room check
directories LOW and UPPER for rooms on those levels in this location, and if
they exist the appropriate exits are added. Smart, huh? The location filename
must be in simplest form: no directory names or ".c" should be attached. The
adjacent room filenames must be in the same format and arranged in the array
starting with the room to the north and proceeding clockwise to northwest; zero
in any array element indicates that no room exists at that location.

*/

varargs void
create_tree(string location, string *rooms, string tree_type)

{

    int exit_fatigue = 6;  /* Standard effort for mid-tree lateral movement. */

    This_Location = location;
    Tree = tree_type;

    set_short("High in the " + Tree + " tree");

    set_long("@@this_room_desc@@");

    add_item(({"tree", Tree + " tree", "mighty " + Tree + " tree"}),
        "This magnificent " + Tree + " tree rises up from the forest" +
        " floor like a fantastic column. Below you the trunk is bare," +
        " but here the branches are thick and numerous, and they" +
        " continue above to the sky.\n");

    add_item(({"limbs", "limb", "branches", "branch"}),
        "The " + Tree + " tree's limbs stretch out in every" +
        " direction. Stout and rigid, they easily support the weight of" +
        " you and your belongings and provide ample room for" +
        " moving about. Some of them reach out and touch the limbs" +
        " of other nearby trees, but at the edges they're too slender" +
        " to walk on.\n");

    add_item(({"trees", "nearby trees", "other trees"}),
        "Other trees of similar height and proportions surround this" +
        " one. It occurs to you that you might be able to move" +
        " directly from one to another, if only you could master" +
        " the proper technique.\n");

    add_item(({"space", "spaces"}),
        "While the branches offer sure footing, the spaces between" +
        " them are wide enough for someone your size to" +
        " fall through.\n");

    add_item(({"ground", "floor", "forest floor"}), "@@exa_ground@@");

    if (rooms[0]) add_exit(rooms[0],
        "north", "@@movement_check@@", exit_fatigue);

    if (rooms[1]) add_exit(rooms[1],
        "northeast", "@@movement_check@@", exit_fatigue);

    if (rooms[2]) add_exit(rooms[2],
        "east", "@@movement_check@@", exit_fatigue);

    if (rooms[3]) add_exit(rooms[3],
        "southeast", "@@movement_check@@", exit_fatigue);

    if (rooms[4]) add_exit(rooms[4],
        "south", "@@movement_check@@", exit_fatigue);

    if (rooms[5]) add_exit(rooms[5],
        "southwest", "@@movement_check@@", exit_fatigue);

    if (rooms[6]) add_exit(rooms[6],
        "west", "@@movement_check@@", exit_fatigue);

    if (rooms[7]) add_exit(rooms[7],
        "northwest", "@@movement_check@@", exit_fatigue);

    if (file_size(UPPER + This_Location + ".c") > 0)

    {

        add_exit(UPPER + This_Location, "up", "@@climb_check@@", 9);
        Up_And_Down_Exits = "up";

    }

    if (file_size(LOW + This_Location + ".c") > 0)

    {

        add_exit(LOW + This_Location, "down", 0, 3);
        Falling_is_possible = 1;

        if (Up_And_Down_Exits) Up_And_Down_Exits += " and down";
        else Up_And_Down_Exits = "down";

        /*
         *  The following exits are dummies provided for the benefit of shouts 
         *  (which can be heard from the pits to the treetops) and other
         *  functions that query the room_exits array.   
         */

        add_exit(GROUND + This_Location, "d", 1, 1, 1);
        add_exit(BELOW + This_Location, "u", 1, 1, 1);

    }

    if (Up_And_Down_Exits)

    {

        if (Up_And_Down_Exits == "up and down")
            Up_And_Down_Exits = "There are two obvious exits: up and down.\n";

        else Up_And_Down_Exits = "There is one obvious exit: " +
            Up_And_Down_Exits + ".\n";

    }

    /*
     *  Standard properties for a mid-tree room.   
     */

    add_prop(ROOM_I_HIDE, 50);  /*  A fair place to hide. */
    add_prop(ROOM_I_LIGHT, 2);  /*  In shade but fairly bright. */
    add_prop(ROOM_I_NO_ATTACK, "@@start_tree_combat@@");

}

// Function:  init()

/*

Purpose:  add local commands.

Arguments:  none.

Returns: nothing.

*/

void
init()

{

    object tp = this_player();

    /*
     *  Players who have completed the forest quest get to see all the exits. 
     *    
     */

    if (tp->test_bit("Calia", FOREST_QUEST_GROUP, FOREST_QUEST_BIT))
        set_noshow_obvious(0);

    else set_noshow_obvious(1);

    ::init();

    add_action(look_down, "look");
    add_action(drop_on_someone, "drop");
    add_action(let_go, "let");  /*  TESTING PURPOSES ONLY  */

}
