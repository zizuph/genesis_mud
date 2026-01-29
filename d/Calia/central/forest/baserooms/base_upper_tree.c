// ROOM:  base_upper_tree.c

    /*  Calia Domain

    HISTORY

    [99-06-21] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_UPP.DOC].

    PURPOSE

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
#include "let_go.h"

// GLOBAL VARIABLES

string Tree;
string This_Location;

// FUNCTIONS

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

Purpose:  Delete the property associated with a player when he leaves the tree
and notify other players of his approach, or provide messages for non-living
objects dropped from the tree.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

{

    object *players;

    ::leave_inv(ob, dest);

    if (!dest) return;  /* Covers updates and object clones by wizards. */

    if (living(ob))

    {

        remove_prop("tree_" + ob->query_name());
            ob->remove_prop(CALIA_KNOCKDOWN);

        /*
         *  There are various ways to leave the tree; only climbing down sends 
         *  a special message to the destination room.   
         */

        if (query_verb() == "down")

        {

            tell_room(MIDDLE + This_Location,
                QCNAME(ob) + " climbs down the trunk of" +
                " the " + Tree + " tree.\n", ({ob}));

        }

    }

    else

    {

        if (file_name(dest) != GROUND + This_Location) return;

        /*
         *  This is the routine for non-living objects. I only provide a 
         *  message for items headed to ground level, which indicates that they
         *  have been dropped (items which are "put" will stay in the room).
         *  Players in this room and at mid-tree level will see the object
         *  fall. Players at low-tree level have their faces flush against the
         *  tree trunk; only one will notice the fall of a non-living object.
         *    
         */

        if (ob->num_heap() > 1)

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " fall to the ground.\n");

            tell_room(MIDDLE + This_Location,
                capitalize(LANG_THESHORT(ob)) +
                " fall from the treetop and plummet to the ground.\n");

            tell_room(GROUND + This_Location,
                capitalize(LANG_THESHORT(ob)) +
                " fall from the " + Tree + " tree.\n");

        }

        else

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " falls to the ground.\n");

            tell_room(MIDDLE + This_Location,
                capitalize(LANG_THESHORT(ob)) +
                " falls from the treetop and plummet to the ground.\n");

            tell_room(MIDDLE + This_Location,
                capitalize(LANG_THESHORT(ob)) +
                " falls from the " + Tree + " tree.\n");

        }

        players =
            FILTER_LIVE(all_inventory(find_object(LOW + This_Location)));

        if (players)
            players[random(sizeof(players))]->catch_msg("Something" +
            " whizzes past your head on its way from the forest canopy" +
            " to the ground.\n");

    }

}

// Function:  knock_down()

/*

Purpose:  When a player tries to do something that's not on the approved list,
check to see if he falls from the tree. The test is based on the player's wis,
with the idea that any player who tries to roundhouse kick, swarm, or otherwise
make a wild move while clinging to a tree trunk is fairly foolish, but the
wiser ones in this group would at least brace themselves and/or secure a good
handhold before making the attempt. Eventually, all who repeatedly use the
prohibited commands are doomed to fall.

Arguments:  none.

Returns:  0/1.

*/

int
knock_down()

{

    object tp = this_player();
    object fall_from_tree;
    int risk;
    int knockdown;

    if (member_array(query_verb(), query_prop("tree_" + tp->query_name()))
        != -1)

    {

        /*
         *  I don't care if it is in the approved list, you lose a point when 
         *  you do ANYTHING! But this action won't knock you down by itself; it
         *  just makes you less stable when you try the next prohibited
         *  command.   
         */

        tp->add_prop(CALIA_KNOCKDOWN, (tp->query_prop(CALIA_KNOCKDOWN) - 1));
        return 0;

    }

    /*
     *  Panic, burden, being in a fight, and having your hands full all 
     *  contribute to your demise; higher int means a greater ability to deal
     *  with the dynamic environment of slender and unsteady branches, higher
     *  dis means you maintain your composure in a precarious situation. If the
     *  player has no panic, is not fighting, and is completely unburdened, the
     *  risk value will be 1.

     *  The test is similar to the one at low-tree level, with the exception
     *  that int is measured rather than wis and acrobat skill is added to the
     *  divisor. I figure that if you had any wisdom at all you wouldn't be
     *  taking chances up here, and the movement of the supple branches at this
     *  level create a challenge similar to wirewalking.   
     */

    risk = random(
        (tp->query_panic() +
        tp->query_encumberance_weight() +
        objectp(tp->query_attack()) * 100 +
        objectp(tp->query_weapon(W_LEFT)) * 100 +
        objectp(tp->query_weapon(W_RIGHT)) * 100)
        /
        (tp->query_stat(SS_INT) + tp->query_stat(SS_DIS) +
        tp->query_skill(SS_ACROBAT))) + 1;

    knockdown = tp->query_prop(CALIA_KNOCKDOWN);
    knockdown = knockdown - risk;
    tp->add_prop(CALIA_KNOCKDOWN, knockdown);

    switch (knockdown)

    {

        case -999999..0:  /* Down you go! */

            fall_from_tree = clone_object(FOREST_FALL_FROM_TREE);
            fall_from_tree->move(tp);
            fall_from_tree->start_falling();

            break;

        case 1..10:  /* Just barely hanging in there. */

            write("You lose your grip on the supple branches! Sheer" +
                " luck gives you a handhold as you" +
                " begin to fall, and you just barely manage to" +
                " regain your position.\n");

            say(QCTNAME(tp) + " slips and begins to fall! Sheer luck" +
                " gives " + tp->query_objective() +
                " a handhold at the last second," +
                " and " + tp->query_pronoun() + " just barely regains" +
                " a secure grip on the tree trunk.\n");

            break;

        case 11..30:  /* Not much room for error here. */

            write("You wobble and come close to losing your grip" +
                " as the flexible branches sway under your weight!!\n");

            say(QCTNAME(tp) + " wobbles and comes close to losing" +
                " " + tp->query_possessive() + " grip as the" +
                " flexible branches sway under" + tp->query_possessive() +
                " weight!\n");

            break;

        case 31..70:  /* You're in control, but be careful. */

            write("No, your position isn't secure enough to do" +
                " that! Your movement causes you to monentarily slip," +
                " but you quickly catch yourself and steady your" +
                " position amid the swaying branches.\n");

            say(QCTNAME(tp) + " slips momentarily but quickly regains" +
                " " + tp->query_possessive() + " balance and secures" +
                " a stable position amid the swaying branches.\n");

            break;

        default:  /* No big problem. */

            write("You can't do that while you're trying to" +
                " maintain your position amid the swaying branches!\n");

            /*
             *  Other players don't even notice.    
             */

    }

    return 1;

}

// Function:  tell_mid_tree()

/*

Purpose:  notify players in room below when someone climbs down the tree trunk.

Arguments:  none

Returns:  0.

*/

int
tell_mid_tree()

{

    tell_room(MIDDLE + This_Location,
        QCNAME(this_player()) + " climbs down the trunk of" +
        " the " + Tree + " tree.\n");

    return 0;

}

// Function:  create_tree(location, tree_type)

/*

Purpose:  Add specific attributes to the tree room.

Arguments:  location, a string containing the filename of this room, and tree,
a string representing the tree type. If the tree name requires the article
"an", include it; otherwise, "a" is assumed.

Returns:  0.

*/

void create_tree(string location, string tree_type)

{

    Tree = tree_type;

    This_Location = location;

    set_short("At the top of " + LANG_ADDART(Tree) + " tree");

    /*
     *  Determine whether the tree has needles or leaves.   
     */

    if (member_array(Tree, ({"fir", "spruce", "pine"})) > -1)

    {

        set_long("You have reached the top of " + LANG_ADDART(Tree) +
            " tree that towers high above the forest floor. The" +
            " supple branches at this level sway in response to" +
            " the occasional breeze and to your weight, and the" +
            " thick needles make them difficult to grasp. Your position" +
            " is at best unstable, but the fresh air is invigorating" +
            " and the sunlight warms you to the core.\n");

        add_item(({"foliage", "needles", "thick needles"}),
            "The needles cover every portion of the tree that is" +
            " exposed to sunlight, and they bend in response to" +
            " your every movement, making your position" +
            " rather unsteady.\n");

    }

    else

    {

        set_long("You have reached the top of " + LANG_ADDART(Tree) +
            " tree that towers high above the forest floor. The" +
            " supple branches at this level sway in response to" +
            " the occasional breeze and to your weight, and the" +
            " lush covering of leaves makes them a bit slippery." +
            " Your position is at best unstable, but the fresh" +
            " air is invigorating and the sunlight warms you to" +
            " the core.\n");

        add_item(({"foliage", "leaves"}),
            "The leaves cover every portion of the tree that is" +
            " exposed to sunlight, which is just about everywhere" +
            " at this level, and while they may be comfortable to sit" +
            " on, they don't make a very secure perch for someone" +
            " of your weight.\n");

    }

    add_item(({"tree", Tree + " tree"}),
        "You've climbed to the very top of this enormous " + Tree +
        " tree, and while you're certain that you're quite a distance" +
        " above the ground, your view in that direction is" +
        " completely blocked by the abundance of branches and foliage.\n");

    add_item(({"branch", "branches", "supple branches", "swaying branches"}),
        "At this level the branches are supple and ropelike, strong" +
        " enough to support your weight but flexible enough to slip" +
        " out from under you if you're not careful.\n");

    add_exit(MIDDLE + This_Location, "down", 0, 20);

    /*
     *  The following exits are dummies to allow shouts to be heard at all 
     *  levels of the forest.   
     */

    add_exit(LOW + This_Location, "d", 1, 1, 1);
    add_exit(GROUND + This_Location, "d", 1, 1, 1);
    add_exit(BELOW + This_Location, "d", 1, 1, 1);

    add_prop(ROOM_I_HIDE, -1);  /*  Impossible to hide. */
    add_prop(ROOM_I_LIGHT, 3);  /*  Plenty of sunlight. */
    add_prop(ROOM_I_NO_ATTACK, "@@start_tree_combat@@");

}

// Function:  init()

/*

Purpose:  add local commands. In actuality, it adds a property containing the
list of verbs a player can use while clinging to the tree. The property is a
big array, so it's added to the room, not the player! Basically, the player can
use standard Genesis commands; nothing from guild or other cmdsouls or from
objects (other than Calian forest objects) is allowed. However, commands that
mask standard commands, like specialized "say" or "team" functions, are not
blocked.

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

    add_action(let_go, "let");  /*  TESTING PURPOSES ONLY  */

    if (tp->query_wiz_level()) return;  /* Don't block wizards. */

    command_list = commands(tp);
    m = sizeof(command_list);

    for (n=0; n<m; n+=1)

    {

        details = command_list[n];
        defined_by = file_name(details[2]);

        if (wildmatch("/d/Genesis*", defined_by)
            || wildmatch("/cmd/live/items*", defined_by)
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

    /*
     *  Player's list of permitted commands is stored in the room and he is 
     *  assigned a knockdown value based on his climb and acrobat skill. Each
     *  time he uses a prohibited command a random amount based on burden and
     *  other factors will be subtracted from the knockdown value. The player
     *  is knocked to the ground when the value reaches 0.   
     */

    add_prop("tree_" + tp->query_name(), dont_override);
    add_action(knock_down, "", 1);

    tp->add_prop(CALIA_KNOCKDOWN,
        (tp->query_skill(SS_CLIMB) + tp->query_skill(SS_ACROBAT)));

}
