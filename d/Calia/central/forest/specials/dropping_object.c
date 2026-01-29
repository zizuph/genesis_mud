// OBJECT:  dropping_object.c

    /* Calia Domain

    HISTORY

    [98-04-24] Created by Uhclem from
    [C:\CALIA\CENTRAL\FOREST\SPECIALS\DROPPING.DOC].

    PURPOSE

    This object controls the trajectory of an object dropped by a player at
    mid-tree level on a player at ground level. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

// GLOBAL VARIABLES

object Player;  /* Who dropped it. */
object Item;    /* What he dropped. */
object Enemy;   /* Who he aimed for. */
object Ground_Room;  /* Where the Enemy was standing it dropped. */
object Tree_Room;    /* Where the Player was standing when it dropped. */

// FUNCTIONS

// Function:  hit_someone()

/*

Purpose:  assess the damage done by drop_on_someone.

Arguments:  none, all information is passed through global variables.

Returns:  nothing.

*/

void
hit_someone()

    {

    object *teammates;
    object armour_worn;
    string damage_text;
    string body_part;
    string tree_type = Ground_Room->query_prop(FOREST_TREE_TYPES)[0];

    int *damage_loc_array = ({A_HEAD, A_HEAD, A_TORSO, A_R_ARM, A_L_ARM,
        A_LEGS});  /* A_HEAD appears twice intentionally. */

    int damage_loc;
    int damage_max;
    int damage_min;
    int damage_type;
    int damage;

    Item->move(Ground_Room);

    /*  This function is called with a 2-second delay after an item is dropped,
        so we have to check to see if either player has moved before we even
        begin to assess the results. */

    /*  If Player drops the object and then immediately leaves his position, he
        must not have been concentrating very well. His aim will be terrible.
        */

    if (environment(Player) != Tree_Room)

        {

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree.\n");

        log_file("forest_events",
            Enemy->query_name() + " was missed by a mile.\n");

        return;

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: You passed concentration test.\n");

    /*  If the enemy has walked away, he is not vulnerable. */

    if (environment(Enemy) != Ground_Room)

        {

        Player->catch_msg(QCTNAME(Enemy) + " left the area" +
            " before your missile reached the ground.\n");

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree.\n");

        log_file("forest_events",
            Enemy->query_name() + " left before it reached the ground.\n");

        return;

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Enemy has remained stationary.\n");

    /*  At this point Player in Tree_Room has released Item which is falling
        toward Enemy who is standing in Ground_Room. Skills and stats will
        determine the outcome. */

    if ((Player->query_stat(SS_INT) + Player->query_skill(SS_LOC_SENSE)) <
        random(200))  /* Check ability to locate target and judge distance. */

        {

        Player->catch_msg("Your missile falls to the ground far" +
            " from its target.\n");

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree.\n");

        log_file("forest_events",
            Enemy->query_name() + " was missed by a mile.\n");

        return;

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: You passed targeting test.\n");

    if ((Player->query_stat(SS_DIS) + Player->query_skill(SS_WEP_MISSILE)) <
        random(200))  /* Check for steady hand and sure aim. */

        {

        Player->catch_msg("Your missile falls in the general vicinity" +
            " of its target but not close enough to be dangerous.\n");

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type +
            " tree not far from " + QTNAME(Enemy) + ".\n");

        log_file("forest_events",
            Enemy->query_name() + " was missed, but not by much.\n");

        return;

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: You passed steadiness test.\n");

    /*  Player has succeeded in accurately dispatching the missile toward its
        target. Now it's up to Enemy to evade it. */

    if ((Enemy->query_stat(SS_WIS) + Enemy->query_skill(SS_FR_TRAP)) >
        random(200))  /* Check ability to recognize the danger. */

        {

        Player->catch_msg("Your missile falls exactly where you" +
            " intended, but the target notices it and easily steps" +
            " out of harm's way.\n");

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and heads directly for " +
            QTNAME(Enemy) + "! " + capitalize(Enemy->query_pronoun()) +
            " sees it coming and easily avoids being hit by" +
            " the missile, which strikes the ground harmlessly.\n", ({Enemy}));

        Enemy->catch_msg(capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and heads directly for" +
            " you, but you see it coming and easily step out of its" +
            " way. It strikes the ground harmlessly.\n");

        log_file("forest_events",
            Enemy->query_name() + " evaded the missile easily.\n");

        return;

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Enemy failed find-trap test.\n");

    if ((Enemy->query_stat(SS_DEX) + Enemy->query_skill(SS_DEFENSE)) >
        random(200))  /* Check ability to duck or jump out of the way. */

        {

        Player->catch_msg("Your missile falls exactly where you" +
            " intended, but the target jumps out of the way at the" +
            " last moment and barely escapes being hit.\n");

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and heads directly for " +
            QTNAME(Enemy) + "! " + capitalize(Enemy->query_pronoun()) +
            " jumps out of the way at the last moment and just" +
            " barely escapes being hit.\n", ({Enemy}));

        Enemy->catch_msg(capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and heads directly for" +
            " you, but you jump out of the way at the last moment" +
            " and just barely escape being hit.\n");

        log_file("forest_events",
            Enemy->query_name() + " just barely evaded the missile.\n");

        return;

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Enemy failed evasion test.\n");

    /*  Enemy has failed to evade the missile. If he's on a team, we'll give
        one teammate a shot at saving him. It pays to be brave, alert, quick,
        and protective. */

    teammates = Enemy->query_team_others();

    if (sizeof(teammates))

        {

        teammates[0] = teammates[random(sizeof(teammates))];

        if ((teammates[0]->query_stat(SS_DIS) +
            teammates[0]->query_skill(SS_AWARENESS) +
            teammates[0]->query_stat(SS_DEX) +
            teammates[0]->query_skill(SS_DEFENSE)) > random(400)
            &&
            environment(teammates[0]) == Ground_Room)

            {

            Player->catch_msg("Your missile falls directly" +
                " toward " + QTNAME(Enemy) +
                ", but " + QNAME(teammates[0]) +
                " sees it and pushes " + Enemy->query_objective() +
                " out of harm's way.\n");

            tell_room(Tree_Room,
                capitalize(LANG_ASHORT(Item)) +
                " falls directly toward " + QTNAME(Enemy) +
                "! " + QCTNAME(teammates[0]) +
                " sees it coming and pushes " + Enemy->query_objective() +
                " out of the way of the missile, which strikes" +
                " the ground harmlessly.\n", ({Player}));

            tell_room(Ground_Room,
                capitalize(LANG_ASHORT(Item)) +
                " falls from the " + tree_type + " tree and heads" +
                " directly for " + QTNAME(Enemy) +
                "! " + QCTNAME(teammates[0]) +
                " sees it coming and pushes " + Enemy->query_objective() +
                " out of the way of the missile, which strikes" +
                " the ground harmlessly.\n", ({Enemy, teammates[0]}));

            teammates[0]->catch_msg(capitalize(LANG_ASHORT(Item)) +
                " falls from the " + tree_type + " tree and heads" +
                " directly for" +
                " " + QTNAME(Enemy) + "! You see it coming" +
                " and push " + Enemy->query_objective() +
                " out of the way of the missile, which strikes" +
                " the ground harmlessly.\n");

            Enemy->catch_msg(QCTNAME(teammates[0]) + " comes running" +
                " at you. " + capitalize(teammates[0]->query_pronoun()) +
                " attempts to tackle you and succeeds. You fall to" +
                " the ground in a very unflattering way.\n");

            log_file("forest_events",
                Enemy->query_name() + " was saved by " +
                teammates[0]->query_name() + ".\n");

            return;

            }

        }

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Enemy failed rescue-by-teammate test.\n");

    /*  The missile strikes its target! Now to calculate damage. Weapons are
        examined carefully to determine damage; other objects are treated
        simply as weight. Broken weapons can be dropped, but they will only do
        1/4 the damage of unbroken weapons. To account for all the vagaries of
        calculating damage done by a falling weapon, such as whether it falls
        handle-first and blade-first or does it land on its side or sharp edge
        down, I have simplified the calculations and provided a large random
        variance. In general, the bigger and denser the object is, the more
        damage it can do. The drop routine won't even let you use an Item as a
        missile if it isn't heavier than water.

        In general, heavy objects can do great damage because of the speed at
        which they hit when dropped from a great height. On the other hand, the
        objects are not being wielded by anyone, so a slight abberration from a
        dead-center hit can greatly reduce the impact. Armour better than class
        1 offers much more protection against falling objects than it does
        against normally wielded weapons. */

    damage_max =
        (Item->query_prop(OBJ_I_WEIGHT) + Item->query_prop(OBJ_I_WEIGHT)
        - Item->query_prop(OBJ_I_VOLUME)) / 10;

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Missile base max damage: " +
        val2str(damage_max) + ".\n");

    damage_min = Item->query_prop(OBJ_I_WEIGHT) / 1000;
    if (damage_min < 1) damage_min = 1;

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Missile base min damage: " +
        val2str(damage_min) + ".\n");

    if (Item->weapon_type())

        {

        if (Player->query_wiz_level())
            Player->catch_msg("WIZ: Missile is a weapon;" +
            " revising damage values.\n");

        damage_type = Item->query_dt();

        if (Player->query_wiz_level())
            Player->catch_msg("WIZ: Missile damage type: " +
            val2str(damage_type) + ".\n");

        damage_max += Item->query_pen() * 10;
        damage_min *= damage_min;
        if (Item->weapon_type() == "axe") damage_min *= 2;

        }

    else damage_type = W_BLUDGEON;

    if (Item->query_prop(OBJ_I_BROKEN)) damage_max /= 4;

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Missile revised max damage: " +
        val2str(damage_max) + ".\n");

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Missile revised min damage: " +
        val2str(damage_min) + ".\n");

    /*  Decide on a hit location and check the armour protecting it. */

    damage_loc = damage_loc_array[random(sizeof(damage_loc_array))];
    armour_worn = Enemy->query_armour(damage_loc);

    if (armour_worn)

        {

        damage_max /= armour_worn->query_ac(damage_loc);
        damage_min -= armour_worn->query_ac(damage_loc);
        if (damage_min < 1) damage_min = 1;

        }

    damage = random(damage_max - damage_min) + damage_min;

    if (Player->query_wiz_level())
        Player->catch_msg("WIZ: Missile damage: " + val2str(damage) + ".\n");

    switch (damage)

        {

        case 1:
        damage_text = "just barely touches";
        break;

        case 2:
        damage_text = "gently bumps against";
        break;

        case 3..4:
        damage_text = "lightly brushes against";
        break;

        case 5..8:
        damage_text = "tickles";
        break;

        case 9..16:
        damage_text = "lightly grazes";
        break;

        case 17..32:
        damage_text = "grazes";
        break;

        case 33..64:
        damage_text = "bangs against";
        break;

        case 65..128:
        damage_text = "scrapes";
        break;

        case 129..256:
        damage_text = "hits";
        break;

        case 257..512:
        damage_text = "strikes";
        break;

        case 513..1024:
        damage_text = "slams into";
        break;

        default:
        damage_text = "smashes against";

        }

    switch (damage_loc)

        {

        case A_HEAD:
        body_part = "head";
        break;

        case A_R_ARM:
        body_part = "right arm";
        break;

        case A_L_ARM:
        body_part = "left arm";
        break;

        case A_LEGS:
        body_part = "legs";
        break;

        default:
        body_part = "body";

        }

    Enemy->reduce_hit_point(damage);

    if (Enemy->query_hp() < 1)

        {

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type +
            " tree and crushes " + QTNAME(Enemy) + "!\n",
            ({Enemy}));

        Enemy->catch_msg(capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and crushes you!\n");

        tell_room(Tree_Room,
            capitalize(LANG_THESHORT(Item)) +
            " crushes and kills " + QTNAME(Enemy) + "!\n");

        Enemy->do_die(Player);

        }

    else

        {

        tell_room(Ground_Room,
            capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and " + damage_text +
            " " + QTNAME(Enemy) + "'s " + body_part + "!\n",
            ({Enemy}));

        Enemy->catch_msg(capitalize(LANG_ASHORT(Item)) +
            " falls from the " + tree_type + " tree and " + damage_text +
            " your " + body_part + "!\n");

        tell_room(Tree_Room,
            capitalize(LANG_THESHORT(Item)) + " " + damage_text +
            " " + QNAME(Enemy) + "'s " + body_part + "!\n",
            ({Player}));

        Player->catch_msg(capitalize(LANG_THESHORT(Item)) +
            " " + damage_text +
            " " + QTNAME(Enemy) + "'s " + body_part + "!\n");

        }

    log_file("forest_events",
        sprintf("%-12s%-20s%7ihp%7idm(%4i - %7i)",
        Enemy->query_name(),
        "was hit.",
        Enemy->query_max_hp(),
        damage,
        damage_min,
        damage_max) + "\n");

    }

// Function:  start_dropping(player, item, enemy, ground_room, tree_room)

/*

Purpose:  starts the dropped object toward its target.

Arguments:  Values for the five global variables.

Returns:  nothing.

*/

void
start_dropping(object input_player, object input_item, object input_enemy,
    object input_ground_room, object input_tree_room)

    {

    object temp_location = find_object(FOREST_FALL_ROOM);

    if (!objectp(temp_location)) temp_location->load_me();

    Player = input_player;
    Item = input_item;
    Enemy = input_enemy;
    Ground_Room = input_ground_room;
    Tree_Room = input_tree_room;

    Player->catch_msg("You take careful aim and release " +
        LANG_THESHORT(Item) + ".\n");

    tell_room(Tree_Room,
        QCTNAME(Player) + " drops " + LANG_ASHORT(Item) + ".\n", ({Player}));

    tell_room(Tree_Room,
        capitalize(LANG_THESHORT(Item)) + " falls to the ground.\n");

    Item->move(temp_location);
    set_alarm(2.0, 0.0, hit_someone);
    set_alarm(2.1, 0.0, remove_object);

    log_file("forest_events",
        Player->query_name() + " dropped " + Item->query_short() +
        " on " + Enemy->query_name() +
        "\n    (" + file_name(Item) + ").\n");

    }

// Function:  drop_stop()

/*

Purpose:  Mask the "drop" command to prevent a player from dropping another
object before the one he already dropped has reached the ground.

Arguments:  none.

Returns: 1.

*/

int
drop_stop()

    {

    write("You're too busy watching the last object you dropped fall" +
        " to the ground.\n");

    return 1;

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

    ::init();

    add_action(drop_stop, "drop");

    }

// OBJECT DEFINITION

create_object()

    {

    set_no_show();
    set_name("_drop_control");
    set_short("_drop_control");
    set_long("_drop_control");

    /*  PROPERTIES  */

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);

    }
