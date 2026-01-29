// OBJECT:  tree_combat

    /* Calia Domain

    HISTORY

    [98-09-23] created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\SPECIALS\TREE_COM.DOC].

    PURPOSE

    When someone starts a fight in the mid- or upper-tree level of most Great
    Central Forest rooms, this object is cloned into the room to add additional
    risks to fighting in the trees: falling down and getting your weapon
    snagged in the branches.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "defs.h"

// GLOBAL VARIABLES

object Snagged_Weapon;
int Difficulty = 0;

// FUNCTIONS

// Function:  free_snagged_weapon()

/*

Purpose:  remove the OBJ_M_NO_GET property from a weapon that has been snagged
by the tree's branches.

Arguments:  none.

Returns:  nothing.

*/

void
free_snagged_weapon()

    {

    Snagged_Weapon->remove_prop(OBJ_M_NO_GET);

    }

// Function:  tree_combat_effect()

/*

Purpose:  select a fighting player and attempt to inflict one 1 of 2 hazards:

(1) Falling from the tree, incurring injury. Stats, skills, and equipment all
play a part in increasing or decreasing his chances.
(2) Snagging his weapon in the branches, incurring an attack delay. Weapon size
and attributes as well as skills and stats are critical.

This function is called every ten seconds by a repeating alarm until combat in
the room ceases, at which point the tree combat object removes itself from the
game.

Arguments:  none.

Returns:  nothing.

*/

void
tree_combat_effect()

    {

    object en = environment(this_object());
    object *livings = FILTER_LIVE(all_inventory(en));
    object *weapons;
    object victim;
    object ob;
    int test_value;
    int m;

    /*  The following global variable is increased with each execution of this
        function so that eventually everyone in the fight will be affected
        regardless of their stats and skills. */

    Difficulty += 10;

    /*  Look for someone who is actually being attacked. */

    while (sizeof(livings))

        {

        m = random(sizeof(livings));
        victim = livings[m]->query_attack();

        if (victim)

            {

            livings = ({});

            }

        else

            {

            livings -= ({livings[m]});

            }

        }

    if (!victim)  /* Fight is over. */

        {

        remove_object();
        return;

        }

    if (environment(victim) != en) return;  /* Victim has just wimpied! */

    if (random(2))

        {

        /*  Fall effect:
            The test_value is contrived so that when (Difficulty == 0) a player
            with values of 100 in dex, str, climb, and acrobat will never fall
            from the tree if he has no burden or panic and has at least one
            hand free (not wielding a weapon). */

        test_value = 100
            + victim->query_stat(SS_DEX)
            + victim->query_stat(SS_STR)
            + victim->query_skill(SS_CLIMB)
            + victim->query_skill(SS_ACROBAT)
            - victim->query_panic()
            - victim->query_encumbrance_weight() * 2
            - Difficulty;

        if (victim->query_weapon(W_LEFT) && victim->query_weapon(W_RIGHT))

            {

            test_value -= 100;

            }

        if (test_value < random(500))

            {

            /*  Because the Elementals are so active in Calia, there is a
                chance that one will save you from falling.  Your skill in air
                elemental magic determines how likely it is that Lady Aeria
                will save you from falling.  If she doesn't save you, there's
                always a chance that Lady Gu will soften the patch of ground
                where you land (controlled by the falling_object) to reduce the
                potential injury.  The chance of either rescue is never greater
                than 50%.  */

            if (victim->query_skill(SS_ELEMENT_AIR) > random(200))

                {

                tell_object(victim,
                    "Your foot slips off the branch upon" +
                    " which you were standing! You struggle for a moment" +
                    " to regain your footing, and just as you feel" +
                    " that you are about to fall, a sudden gust" +
                    " of wind nudges you back into a stable position.\n");

                tell_room(en,
                    QCTNAME(victim) + " loses " +
                    victim->query_possessive() +
                    " balance for a moment but manages to regain" +
                    " a stable position on the branches.\n",
                    ({victim}));

                victim->add_attack_delay(3, 1);

                }

            else

                {

                tell_object(victim,
                    "Your feet slip off the branch upon" +
                    " which you were standing! You struggle for a moment" +
                    " to regain your footing but fail.\n");

                tell_room(en,
                    QCTNAME(victim) + " loses " +
                    victim->query_possessive() +
                    " balance and struggles for a moment to regain" +
                    " a stable position on the branches.\n",
                    ({victim}));

                ob = clone_object(FOREST_FALLING_OBJECT);
                ob->move(victim);
                ob->start_falling();

                }

            }

        else

            {

            switch (test_value)

                {

                case 0..100:

                tell_object(victim, "You nearly slip and fall from the" +
                    " tree! It takes all your strength and skill" +
                    " just to maintain your position.\n");

                tell_room(en,
                    QCTNAME(victim) + " nearly slips and falls" +
                    " from the tree!\n",
                    ({victim}));

                victim->add_attack_delay(5, 1);
                break;

                case 101..200:

                tell_object(victim, "You lose your footing on the branches" +
                    " for just a second but manage to return" +
                    " to a stable position.\n");

                tell_room(en,
                    QCTNAME(victim) + " stumbles momentarily but" +
                    " manages to avoid from falling from the tree.\n",
                    ({victim}));

                victim->add_attack_delay(2, 1);
                break;

                case 201..300:

                tell_object(victim, "Your foot slips off a branch but" +
                    " you regain your equilibrium so quickly" +
                    " that nobody notices but you.\n");

                break;

                /*  Values greater than 300 get no messages at all. */

                }

            }

        }

    else

        {

        /*  Snag effect:
            Weapons are least likely to snag if they are small and are made to
            impale. The test_value is contrived so that when (Difficulty == 0)
            a player with values of 100 in wis, dex, parry, and the appropriate
            weapon skill can use an impaling weapon of up to 1 liter in volume
            (such as a knife) and never get it snagged.

            Magic weapons are exempt! I figure they must be smart enough to
            avoid the branches. */

        weapons = victim->query_weapon(-1);

        if (!sizeof(weapons)) return;

        weapons[0] = weapons[random(sizeof(weapons))];

        if (weapons[0]->query_prop(OBJ_I_IS_MAGIC_WEAPON))

            {

            if (victim->query_stat(SS_WIS) > random(100))
                tell_object(victim, "Your " + weapons[0]->query_short() +
                " seems to glide magically through the tree's" +
                " branches without being snagged or slowed" +
                " in any way.\n");

            return;

            }

        test_value = 100
            + victim->query_skill(weapons[0]->query_wt())
            + victim->query_skill(SS_PARRY)
            + victim->query_stat(SS_DEX)
            + victim->query_stat(SS_WIS)
            - victim->query_panic()
            - (weapons[0]->query_prop(OBJ_I_VOLUME) / 10)
            - Difficulty;

        if (weapons[0]->query_dt() == W_IMPALE)

            {

            test_value += 100;

            }

        if (test_value < random(500))

            {

            tell_object(victim, "Your " + weapons[0]->query_short() +
                " gets hopelessly snagged by tree's branches!\n");

            tell_room(en,
                QCTNAME(victim) + "'s " + weapons[0]->query_short() +
                " gets hopelessly snagged by the tree's branches!\n",
                ({victim}));

            Snagged_Weapon = weapons[0];
            Snagged_Weapon->move(en);

            Snagged_Weapon->add_prop(OBJ_M_NO_GET,
                "The branches have a tight grip on the weapon," +
                " but you feel it move slightly. Maybe if you" +
                " try again you will be able to get it.\n");

            set_alarm(5.0, 0.0, free_snagged_weapon);

            /*  Note:  the tree_combat_effect function executes every 10
                seconds, so freeing the weapon after 5 seconds means that we
                never have to concern ourselves with handling multiple snagged
                weapons. */

            }

        else

            {

            switch (test_value)

                {

                case 0..100:

                tell_object(victim, "Your " + weapons[0]->query_short() +
                    " gets snagged by one of the tree branches! After" +
                    " a few seconds you manage to disentangle it.\n");

                tell_room(en,
                    QCTNAME(victim) + "'s " + weapons[0]->query_short() +
                    " gets snagged by one of the tree branches! After" +
                    " a few seconds " + victim->query_pronoun() +
                    " manages to disentangle it.\n",
                    ({victim}));

                victim->add_attack_delay(5, 1);
                break;

                case 101..200:

                tell_object(victim, "Your " + weapons[0]->query_short() +
                    " gets snagged in the tree branches but you" +
                    " pull it free with ease.\n");

                tell_room(en,
                    QCTNAME(victim) + " gets " + victim->query_possessive() +
                    " " + weapons[0]->query_short() + " snagged" +
                    " in the tree branches but quickly pulls it free.\n",
                    ({victim}));

                victim->add_attack_delay(2, 1);
                break;

                case 201..300:

                tell_object(victim, "You just barely manage to" +
                    " keep your " + weapons[0]->query_short() +
                    " from getting snagged in the tree's branches.\n");

                break;

                /*  Values greater than 300 get no messages at all. */

                }

            }

        }

    }

// OBJECT DEFINITION

create_object()

    {

    set_no_show();
    set_name("_tree_combat_control");
    set_short("_tree_combat_control");
    set_long("_tree_combat_control");

    /*  PROPERTIES  */

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);

    /*  ALARM  */

    set_alarm(10.0, 10.0, tree_combat_effect);

    }
