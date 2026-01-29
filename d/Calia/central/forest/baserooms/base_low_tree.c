// ROOM:  base_low_tree.c

    /*  Calia Domain

    HISTORY

    [99-06-21] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\BASEROOM\BASE_LOW.DOC].

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

string Tree_Type;
string This_Location;

// FUNCTIONS

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

// Function:  burden_check()

/*

Purpose:  Make sure the player isn't violating the climbing rule, which might
happen if he is handed something by another player at this level or receives a
pigeon.

Arguments:  none.

Returns:  0/1.

*/

int
burden_check()

{

    object tp = this_player();

    /*
     *  The Central Forest Climbing Rule:  no player can climb a tree if his 
     *  encumbrance is more than his climb skill.   
     */

    if (tp->query_encumberance_weight() > tp->query_skill(SS_CLIMB))

    {

        write ("You are too heavily burdened to climb up.\n");
        return 1;

    }

    return 0;

}

// Function:  enter_inv(object, from_object)

/*

Purpose:  cause non-living objects that enter this room to drop to ground
level, or give players who enter here a warning message about the dangers of
climbing with a heavy load if they are wise enough to receive it.

Arguments:  object entering the room, object from whence it came.

Returns:  nothing.

*/

void
enter_inv(object ob, object from)

{

    object *loose_objects;

    ::enter_inv(ob, from);

    if (living(ob) && file_name(from) == GROUND + This_Location)

    {

        /*
         *  This is the same max_damage formula as contained in the 
         *  fall_from_tree. As the potential risk gets higher, it becomes
         *  obvious to even the most foolish players.   
         */

        int max_damage = (50
            + (ob->query_encumberance_weight() *
            ob->query_encumberance_weight())
            + ob->query_stat(SS_STR)
            - ob->query_stat(SS_CON)
            - ob->query_stat(SS_DEX)
            - (ob->query_skill(SS_ACROBAT) * 2))
            * ob->query_max_hp() / 100;

        /*
         *  The more wis you have, the more accurately you can assess the level 
         *  of danger.   
         */

        int risk_awareness = ((max_damage - ob->query_max_hp()) / 10) -
            (100 - ob->query_stat(SS_WIS));

        if (risk_awareness < 0) risk_awareness = 0;

        switch (risk_awareness)

        {

            case 0:

                return 0;
                break;

            case 1..10:

                ob->catch_msg("You feel that you are putting yourself" +
                    " in some danger by climbing such a tall tree with" +
                    " a heavy load.\n");

                break;

            case 11..100:

                ob->catch_msg("You sense that you are taking a serious" +
                    " risk by climbing such a tall tree with a" +
                    " heavy load.\n");

                break;

            case 101..1000:

                ob->catch_msg("You perceive that you are taking" +
                    " an enormous risk by climbing such a tall" +
                    " tree while carrying a heavy load.\n");

            break;

            default:

                ob->catch_msg("You suddenly become acutely aware that" +
                    " you are placing your life in serious jeopardy" +
                    " by climbing such a tall tree with a heavy load.\n");

        }

    }

    else if (!living(ob))

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
and notify other players of his approach, or provide message for non-living
object falling from this room.

Arguments:  object leaving the room, object destination.

Returns:  nothing.

*/

void
leave_inv(object ob, object dest)

{

    ::leave_inv(ob, dest);

    if (living(ob))

    {

        remove_prop("tree_" + ob->query_name());
            ob->remove_prop(CALIA_KNOCKDOWN);

        /*
         *  There are various ways to leave the tree; only climbing down or up 
         *  sends a special message to the destination room.   
         */

        if (query_verb() == "down")

        {

            tell_room(GROUND + This_Location,
                QCNAME(ob) + " climbs down the trunk of" +
                " the " + Tree_Type + " tree.\n", ({ob}));

        }

        if (query_verb() == "up")

        {

            tell_room(MIDDLE + This_Location,
                QCNAME(ob) + " climbs up the trunk of" +
                " the " + Tree_Type + " tree.\n", ({ob}));

        }

    }

    else

    {

        if (file_name(dest) != GROUND + This_Location) return;

        if (ob->num_heap() > 1)

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " fall to the ground.\n");

            tell_room(GROUND + This_Location,
                capitalize(LANG_THESHORT(ob)) +
                " fall from the " + Tree_Type + " tree.\n");

        }

        else

        {

            tell_room(this_object(),
                capitalize(LANG_THESHORT(ob)) + " falls to the ground.\n");

            tell_room(GROUND + This_Location,
                capitalize(LANG_THESHORT(ob)) +
                " falls from the " + Tree_Type + " tree.\n");

        }

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
     *  contribute to your demise; higher wis means more prudent risk control,
     *  higher dis means you maintain your composure in a precarious situation.
     *  If the player has no panic, is not fighting, and is completely
     *  unburdened, the risk value will be 1.   
     */

    risk = random(
        tp->query_panic() +
        tp->query_encumbrance_weight() +
        objectp(tp->query_attack()) * 100 +
        objectp(tp->query_weapon(W_LEFT)) * 100 +
        objectp(tp->query_weapon(W_RIGHT)) * 100)
        /
        (tp->query_stat(SS_WIS) + tp->query_stat(SS_DIS)) + 1;

    knockdown = tp->query_prop(CALIA_KNOCKDOWN);
    knockdown = knockdown - risk;
    tp->add_prop(CALIA_KNOCKDOWN, knockdown);

    switch (knockdown)

    {

        case -999999..0:

            /*
             * Down you go!   
             */

            fall_from_tree = clone_object(FOREST_FALL_FROM_TREE);
            fall_from_tree->move(tp);
            fall_from_tree->start_falling();

            break;

        case 1..10:  /* Just barely hanging in there. */

            write("You lose your grip on the tree trunk! Sheer" +
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

            write("You wobble and come close to losing your grip on" +
                " the tree trunk!\n");

            say(QCTNAME(tp) + " wobbles and comes close to losing" +
                " " + tp->query_possessive() + " grip on the" +
                " tree trunk!\n");

            break;

        case 31..70:  /* You're in control, but be careful. */

            write("No, your position isn't secure enough to do" +
                " that! Your movement causes you to monentarily slip," +
                " but you quickly catch yourself and steady your" +
                " position on the tree trunk.\n");

            say(QCTNAME(tp) + " slips momentarily but quickly regains" +
                " " + tp->query_possessive() + " balance and secures" +
                " a stable position against the tree trunk.\n");

            break;

        default:  /* No big problem. */

            write("You can't do that while you're clinging to the" +
                " tree with your face almost pressed against the" +
                " trunk! You teeter a bit as your motion slightly" +
                " upsets your balance, but you quickly right" +
                " yourself and assume a reasonably secure" +
                " position against the tree trunk.\n");

            /*
             *  Other players don't even notice.    
             */

    }

    return 1;

}

// Function:  look_down()

/*

Purpose:  let a player see what's on ground level, if he's brave enough.

Arguments:  none.

Returns:  string containing warning message or description of forest floor.

*/

string
look_down()

{

    object tp = this_player();
    object room;
    object *contents;
    int m;
    int n;

    string text = "You examine the forest beneath you.";

    if (tp->query_stat(SS_DIS) < 10)

    {

        return "You don't have quite enough self-discipline to do that.\n";

    }

    if (room = find_object(GROUND + This_Location))

    {

        contents = all_inventory(room);
        contents = filter(contents, visible);

    }

    if (!contents)  /* Nothing in the room below. */

    {

        text = text + " All is tranquil in the shade beneath the trees.\n";
        return text;

    }

    text = text + " In the shade beneath the trees you see ";

    m = sizeof(contents);

    for (n=0; n<m; n+=1)

    {

        if (living(contents[n])) text = text + QCNAME(contents[n]);
        else text = text + LANG_ADDART(contents[n]);

        switch (m - n)

        {

            case 1:  /* Last item. */

            text = text + ".";
            break;

            case 2:  /* Next to last */

            text = text + " and ";
            break;

            default:

            text = text + ", ";

        }

    }

    return text;

}

// Function:  create_tree(location, tree)

/*

Purpose:  Add specific attributes to the tree room.

Arguments:  location, a string containing the filename of this room, and tree,
a string representing the tree type. If the tree name requires the article
"an", include it; otherwise, "a" is assumed.

Returns:  0.

*/

void create_tree(string location, string tree)

{

    string *tree_splitter = explode(tree, " ");

    if (sizeof(tree_splitter) == 1)

    {

        tree = "a " + tree;
        tree_splitter = ({"a", tree_splitter[0]});

    }

    Tree_Type = tree_splitter[1];

    This_Location = location;

    set_short("Up " + tree + " tree");

    set_long("You are clinging to the trunk of " + tree +
        " tree that towers high above the forest floor. The bark is" +
        " rough and bumpy enough that you can hold on securely, but" +
        " there's not much else you can do in this position.\n");

    add_item(({"forest", "floor", "forest floor"}), "@@look_down@@");

    add_item(({"trees"}),
        "You are surrounded by trees, but with your face pressed against" +
        " the trunk of this " + Tree_Type + " you don't have nearly" +
        " as good a view of them as you can get on ground level.\n");

    add_item(({"tree", tree + " tree", "trunk", "bark", "vine", "vines"}),
        "The tree is covered with rough bark, and thick vines" +
        " wrap themselves around the trunk. You're not far above" +
        " the ground now, and it's a long way to the top, but your" +
        " secure grip gives you confidence to continue climbing.\n");

    add_exit(MIDDLE + This_Location, "up", "@@burden_check@@", 20);
    add_exit(GROUND + This_Location, "down", 0, 1);

    /*
     *  The following exits are dummies to allow shouts to be heard at all 
     *  levels of the forest.   
     */

    add_exit(UPPER + This_Location, "u", 1, 1, 1);
    add_exit(BELOW + This_Location, "d", 1, 1, 1);

    add_prop(ROOM_I_HIDE, -1);  /*  Impossible to hide. */
    add_prop(ROOM_I_LIGHT, 1);  /*  Not much light, same as ground level. */

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
