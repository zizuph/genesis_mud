/*
 * /d/Sparkle/area/jade/obj/wheelbarrow.c
 * Wheelbarrow for the Runaway quest
 * Created 2017-03-01 by Martin Berka (Mar) for Genesis MUD
 */

#pragma strict_types

#include "../defs.h"

inherit "/std/container" container;
inherit OBJ_DIR + "burden" burden;
inherit OBJ_DIR + "shared_functions"; //Common knowledge for quest

#include "../bandit_quest_constants.h"
#include <money.h> //Quest reward
#include <stdproperties.h>
#include <wa_types.h> //For holding

/* Definitions */
#define MIN_VOL     65000   /*Contents smaller than this fall out*/
#define MAX_VOL     200000
#define MAX_WEIGHT  230000
/*Needs to be large for large players (heavy Family)*/

/* Global variables */
int     delayed_inv; //Flag for appropriate sequence of inventory-related evens
string  *restrain_paths; //Set of paths on which wheelbarrow is allowed to exist

/* Prototypes */
void self_destruct();

/*
 * Function name: create_container
 * Description  : Constructor
 */
void
create_container()
{
    set_name("wheelbarrow");
    set_adj( ({"aged", "wooden"}) );
    set_long("The wheelbarrow is made of brown, rotten wood. Only a few "
        + "skeletal planks remain of the barrow, most replaced by gaps. "
        + "The wooden wheel is nearly hexagonal and the right handle threatens "
        + "to split apart along its length. Only the most desperate of users "
        + "would entrust anything to this dying construct.\n");
    add_name("barrow");
    add_name(QUEST_BURDEN);

    set_slots(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 10000);     //When it is obviously too much
    add_prop(OBJ_I_VOLUME, 50000);      //Obviously too big
    add_prop(CONT_I_MAX_WEIGHT, query_prop(OBJ_I_WEIGHT) + 2 * MAX_WEIGHT);
    add_prop(CONT_I_MAX_VOLUME, query_prop(OBJ_I_VOLUME) + 2 * MAX_VOL);
    add_prop(CONT_I_REDUCE_WEIGHT, 400); //Wheelbarrow quadruples load.
    add_prop(CONT_I_REDUCE_VOLUME, 25);

    restrain_paths = ({WILD_DIR, "/w/mar", "*jade"});
}


/*
 * Function name: check_evil_completion
 * Description  : Says whether player has kidnapped the right family member
 */
void
check_evil_completion()
{
    object kidnapped = present(QUEST_FAMILY, TO);
    if (!kidnapped) //Make sure that there is a family member in the wheelbarrow
    {
        return;
    }

    object player = find_player(burdened);
    object this_room = environment(player);
    object origan = summon_origan(this_room);

    object token = present(QUEST_TOKEN, player);
    int made_offer = 0;
    if (token)
    {
        switch (token->query_prop("TOKEN_I_TEST"))
        {
            case "regrets":
            case "hurt":
                made_offer = 1;
                break;
            default:
                made_offer = 0;
        }
    }
    if (!made_offer || player->DID_RUN_QUEST())
    {
        origan->command("say My, what is that you are carrying? You brought "
            + "one of "
            + "them here? I don't recall asking, but I'll take it from here. "
            + "We are bandits, after all.");
        origan->command("shout Alright boys, prepare our guest a room!");
        tell_room(this_room, "Bandits arrive and drag the now-awake and "
            + "struggling " + QNAME(kidnapped) + " away.\n");
        kidnapped->remove_object();
        origan->command("wave happily");
        remove_origan(origan);
        return;
    }

    object runaway = present(QUEST_RUNAWAY, this_room);

    origan->command("say My, what is that you are carrying? You brought one of "
        + "them here? Let's see.");
    origan->command("peer closely " + kidnapped->query_name());

    int f_index = kidnapped->query_family_index();
    int d_index = runaway_role_index(burdened, DEAREST);
    //string run_name = runaway_name(burdened);

    origan->command("say Recognize this?");
    tell_room(this_room, QCTNAME(origan) + " shows a " + token->query_name()
        + " to " + QTNAME(kidnapped) + ".\n");
    if (f_index != d_index)
    {
        tell_room(this_room, QCTNAME(kidnapped) + " looks blank.\n");
        origan->command("say Hmm, I guess not. Oh well, we can always use "
            + "another pair of hands!");
    }
    else
    {
        tell_room(this_room, QCTNAME(kidnapped) + " gasps.\n");
        origan->command("say As I thought! It wasn't hard to nick.");
    }
    tell_room(this_room, QCTNAME(origan) + " shouts: Alright boys, "
        + "prepare our guest a room!\n"
        + "Bandits arrive and drag the now-awake and "
        + "struggling " + QNAME(kidnapped) + " away.\n");
    kidnapped->remove_object();

    if (f_index == d_index)
    {
        tell_room(this_room, "'In case you were having any second thoughts!', "
            + QTNAME(origan) + " shouts to the stunned "
            + QNAME(runaway) + ".\n");

        player->catch_msg("Origan turns back to you.\n");
        origan->command("say Now, I am a man of my word.");
        tell_room(this_room, QCTNAME(origan) + " gives some coins to "
            + QTNAME(player) + ".\n", player);
        player->catch_msg("Origan gives you three platinum coins.\n");
        MONEY_MAKE_PC(3)->move(player);

        player->catch_msg("Origan whispers in your ear: And since they "
            + "gave you "
            + "trouble - I'll send word that they better get back to their "
            + "farm and let you walk right into that "
            + "orchard any time you want.\n");

        //Set quest bit and XP
        player->set_bit(RUN_Q_GROUP, RUN_Q_BIT);
        player->add_exp_quest(100);

        token->remove_object();
        if (wildmatch( "*jade*", file_name(environment( this_player() )) ))
        {
            //And with the bandits' new leverage, player not shot on sight
            //(the archer NPC otherwise remembers this combat and persists)
            find_object(ARCHER_ROOM)->query_archer()->stop_fighting(
                this_player());
        }
    }

    origan->command("wave happily to " + burdened);
    remove_origan(origan);

    self_destruct();
}


/*
 * Function name: burden_release_effect
 * Description	: Override the burden.c dummy: When released and holding a
 *      something, the wheelbarrow falls to pieces and the load becomes
 *      unavailable to the player.
 * Arguments    : (int) 0 - optional parameter unused
 */
void
burden_release_effect(int repeat = 0)
{
    object *contents = all_inventory(this_object());
    object container = environment(TO);
    if (sizeof(contents))
    {
        foreach(object carried: contents) //Should only have one item
        {
            if (find_player(burdened))
            {
                carried->move(environment(find_player(burdened)), 1);
            }
            else
            {
                carried->move(environment(TO), 1);
            }
            if (living(carried))
            {
                carried->add_stun(); //Prevent sudden attacks
                add_prop(OBJ_M_NO_GET, 1); //Player has to start over

                tell_room(container,
                    QTNAME(carried) + " stands up, rapidly regaining "
                        + "consciousness, and hurriedly staggers away.\n",
                    TO);
                carried->remove_object(); //Needs time to rest; unavailable
            }
        }

        mob_return(wildmatch( "*jade*", file_name(container) ));
        //Send family NPC's home, if outside Jade.
    }

    self_destruct();
}


/*
 * Function name: enter_inv
 * Description	: In the following cases, the object has been allowed to enter
 *      the wheelbarrow, but falls out for various reason.
 * Arguments	: (object) the new object
 *                (object) the new object's previous location
 */
void
enter_inv(object to, object from)
{
    if (!delayed_inv) {
        ::enter_inv(to, from);
        set_alarm(0.2, 0.0, &enter_inv(to, from));
        delayed_inv = 1;
        return;
    }
    else
    {
        delayed_inv = 0;
    }

    if (to->query_prop(OBJ_I_VOLUME) < MIN_VOL)
    {
        tell_room(environment(this_player()),
            (function_exists("query_short", to) ? "The " + to->query_short() :
                QCTNAME(to))
            + " falls through a gaping hole in the bottom of the "
            + this_object()->query_short() + ".\n");
        to->move(environment(this_player()));
        return;
    }

    if (to->query_prop(OBJ_I_VOLUME) > MAX_VOL)
    {
        tell_room(environment(this_player()),
            (function_exists("query_the_name", to) ? QCTNAME(to) :
                "The " + to->query_short())
            + " is very large and topples out of the "
            + this_object()->query_short() + ".\n");
        to->move(environment(this_player()));
        return;
    }

    if (sizeof(all_inventory(this_object())) > 1)
    {
        tell_room(environment(this_player()), "The "
            + this_object()->query_short()
            + " can barely hold even one thing. "
            + (function_exists("query_the_name", to) ? QCTNAME(to) :
                "The " + to->query_short())
            + " topples out.\n");
            to->move(environment(this_player()));
        return;
    }

    if (to->query_prop(OBJ_I_WEIGHT) > MAX_WEIGHT) //Breaks under excess weight
    {
        tell_room(environment(this_player()),
            (function_exists("query_the_name", to) ? QCTNAME(to) :
                "The " + to->query_short()) + " is too much for the "
                + this_object()->query_short() + ". ", 0);
        to->move(environment(this_player()));
        self_destruct();
        return;
    }
}

/*
 * Function name: leave_inv
 * Description  : Effects of removing object from wheelbarrow
 * Arguments    : (object) the object
 *                (object) the object's new location
 */
void
leave_inv(object ob, object destin)
{
    if (!delayed_inv) {
        ::leave_inv(ob, destin);
        set_alarm(0.2, 0.0, &leave_inv(ob, destin));
        delayed_inv = 1;
        return;
    }
    else
    {
        delayed_inv = 0;
    }

    burden_release_effect();
}


/*
 * Function name: enter_env
 * Description  : Wrapper for burden.c
 * Arguments    : (object) the destination
 *                (object) the old location
 */
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    burden_enter_env(dest, old);
}


/*
 * Function name: leave_env
 * Description  : Wrapper for burden.c
 * Arguments    : (object) the destination
 *                (object) the old location
 */
void
leave_env(object dest, object old)
{
    ::leave_env(old, dest);
    burden_leave_env(old, dest);
}


/*
 * Function name: new_room_hook
 * Description  : Hook defined by burden.c. Used to check that location is
 *      permissible and summon family mob.
 * Arguments    : (object) The player with the burden
 *                (object) The previous room
 *                (object) The newly entered room
 */
void
new_room_hook(object last_room, object new_room, object player)
{
    object this_room = environment(player);

    int on_path = 0;
    foreach (string allowed_path: restrain_paths)
    {
        if (wildmatch( allowed_path + "*", file_name(this_room) ))
        {
            on_path = 1;
            break;
        }
    }
    if (!on_path)
    {
        burden_release_effect(); //Dump contents and self-destruct
        return;
    }

    if (!wildmatch("*bandit*", file_name(this_room) ))
    {
        set_alarm(0.5, 0.0, &mob_me( ({NPC_DIR + "family"}),
            query_living_name(player), 5, 3 ));
    }
    else
    {
        if (!wildmatch("*bandit*", last_path ))
        {
            if (m_sizeof(mob_members))
            {
                tell_room(QCTNAME(find_object(mob_members[0]))
                    + "shouts: Argh, too late!"
                    + "Keep an eye out in case we get another chance!\n");
                player->catch_msg("Someone in the mob shouts: Argh, too late!"
                    + "Keep an eye out in case we get another chance!\n");
            }
        }
        if (present(QUEST_RUNAWAY, this_room))
        {
            check_evil_completion();
            return;
        }
    }
}


/*
 * Function name: self_destruct
 * Description  : Makes the wheelbarrow fall apart and spill its contents
 */
void
self_destruct()
{
    tell_room(environment(this_player()), "The wheelbarrow"
        + " falls to pieces, weary planks "
        + "taking a well-earned rest.\n", 0);
    helper->remove_object(); //Removes the paralyzing object
    mob_return(1);
    remove_object();
}


/*
 * Function name: burden_started_hook
 * Description	: Add recurring arrow request when burden is activated
 */
void burden_started_hook()
{
    find_object(ARCHER_ROOM)->request_arrow(find_player(burdened));
    //Summon attack by the attic archer (which handles all the range checks)
    set_alarm(4.0, 0.0, "burden_started_hook");
    //Continue to summon attacks in case anything happens to archer
}
