/*
 * /d/Genesis/std/sling.c
 *
 * The default sling. To create a sling, simply inherit this object and call
 * create_sling() to configure.
 *
 * Author: Mercade
 * Date  : July 12 1999
 */

// Add proper hit / hitloc messages.
// Add chance to miss.
// Hide ammo on miss.
// Effects on armours / clothing.
// Add slight damage.

#pragma strict_types

inherit "/std/container";
inherit "/lib/holdable_item";
 
#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TMP_SLING_CHECKED "_tmp_sling_checked"

/*
 * Function name: create_sling
 * Description  : Constructor. Redefine this function when you want to make
 *                your own custom sling. Please remember to add instructions
 *                to the long description of the sling.
 */
void
create_sling()
{
    set_adj("small");
    set_name("sling");
    set_short("small sling");
    set_long("It is a small sling. Before you can fling something at a " +
        "person or object, you must first load the sling with a small " +
        "pebble or rock. Then you can swing your sling and hurl it at the " +
        "target.\n");

    add_prop(OBJ_I_VALUE, 50);
}

/*
 * Function name: create_container
 * Description  : Constructor. By default the sling will weigh 100 grams and
 *                be able to swing items of 500 grams and with a volume of
 *                500 ml. Also, the sling can be held in either hand. If you
 *                want to change these values, and want to give the sling a
 *                personal touch, redefine create_sling().
 */
nomask void
create_container()
{
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_WEIGHT, 100);
    add_prop(CONT_I_MAX_VOLUME, 600);
    add_prop(CONT_I_MAX_WEIGHT, 600);

    set_slots(W_ANYH);

    create_sling();
}

/*
 * Function name: reset_container
 * Description  : To reset this sling, redefine this function and make a call
 *                to enable_reset() from your create_sling() routine.
 */
void
reset_sling()
{
}

/*
 * Function name: reset_container
 * Description  : To reset this sling, redefine reset_sling() and make a call
 *                to enable_reset() from your create_sling() routine.
 */
nomask void
reset_container()
{
    reset_sling();
}

/*
 * Function name: sling_access
 * Description  : Filter function used in NORMAL_ACCESS() to see whether the
 *                item is in the sling.
 * Arguments    : object obj - the item to test.
 * Returns      : int 1/0 - in the sling, or not.
 */
int
sling_access(object obj)
{
    return objectp(obj) && (environment(obj) == this_object());
}

/*
 * Function name: hurl
 * Description  : The actual function to fling, hurl or swing something at
 *                another person, if you dare.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
hurl(string str)
{
    string verb = query_verb();
    string target_str;
    string ammo_str;
    object *targetlist;
    object *ammolist;
    object target;
    object ammo;

    /* Nope, the sling is a toy, not a combat item. */
    if (this_player()->query_attack())
    {
        notify_fail("It is quite impossible to find the time and space " +
            "necessary to prepare to " + verb + " something while you are " +
            "under attack.\n");
        return 0;
    }

    /* Must hold the sling before it can be used. */
    if (!query_held())
    {
        notify_fail("You must hold the " + short() + " before you can use " +
            "it to " + verb + " something.\n");
        return 0;
    }

    /* Prevent use of the sling while submerged. */
    if (environment(this_player())->query_prop(ROOM_I_TYPE) &
        ROOM_UNDER_WATER)
    {
        notify_fail("You cannot use the sling while submerged.\n");
        return 0;
    }

    /* Access failure. No argument. */
    if (!strlen(str))
    {
        notify_fail(capitalize(verb) + " what at whom?\n");
        return 0;
    }

    /* Player didn't use the "hurl x at y" syntax. He may just try to
     * impress people by idly swinging his toy.
     */
    str = lower_case(str);
    if (sscanf(str, "%s at %s", ammo_str, target_str) != 2)
    {
        parse_command(str, this_player(), "[the] %i",
            ammolist);
        ammolist = NORMAL_ACCESS(ammolist, 0, 0);

        /* Nope, player didn't want to swing the sling. Access failure. */
        if ((sizeof(ammolist) != 1) ||
            (ammolist[0] != this_object()))
        {
            notify_fail(capitalize(verb) + " what at whom?\n");
            return 0;
        }

        if (sizeof(all_inventory(this_object())))
        {
            ammo = all_inventory()[0];
            str = (ammo->query_prop(HEAP_I_IS) ?
                ((ammo->num_heap() == 1) ? "it" : "them") : "it");
            write("You spin your " + short() + " with " +
                LANG_ASHORT(ammo) + " around and pretend to " + verb + " " +
                str + ", but you do not release the " +
                LANG_POSS(query_name()) + " load.\n");
        }
        else
        {
            write("You spin your " + short() + " around and pretend to " +
                verb + " something, but there is nothing in the " +
                query_name() + " to release.\n");
        }

        say(QCTNAME(this_player()) + " spins " +
            this_player()->query_possessive() + " " + short() + " around " +
            "and pretends to " + verb + " something, but " +
            this_player()->query_pronoun() + " does not release " +
            "the " + LANG_POSS(query_name()) + " load.\n");
        return 1;
    }

    /* You can only fling what is already in the sling. */
    parse_command(ammo_str, this_object(), "[the] %i", ammolist);
    ammolist = NORMAL_ACCESS(ammolist, "sling_access", this_object());
    switch(sizeof(ammolist))
    {
    case 0:
        /* Help the player with the syntax. If they tried to fling something
         * that they carry, tell them to put it into the sling first.
         */
        parse_command(ammo_str, this_player(), "[the] %i", ammolist);
        ammolist = NORMAL_ACCESS(ammolist, 0, 0);
        if (sizeof(ammolist))
        {
            ammo = ammolist[0];
            /* Allow swinging the sling without releasing. */
            if (ammo == this_object())
            {
                break;
            }

            notify_fail("Before you can " + verb + " " +
                LANG_THESHORT(ammo) + " at someone, you must first put it " +
                "into the " + short() + ".\n");
            return 0;
        }

        /* Ugh, player tried to fling foobar or something like that. */
        notify_fail("What do you want to " + verb + "?\n");
        return 0;
 
    case 1:
        /* Yup, player tried to fling what is in the sling. */
        ammo = ammolist[0];
        break;

    default:
        /* Should never happen. The sling can only contain one item. */
        notify_fail("Please hurl only one item at a time.\n");
        return 0;
    }
 
    /* Find the target of the of the action. */
    targetlist = PARSE_THIS(target_str, "[the] %l");
    switch(sizeof(targetlist))
    {
    case 0:
        notify_fail("Who do you want to " + verb + " " + LANG_THESHORT(ammo) +
            " at?\n");
        return 0;
 
    case 1:
        target = targetlist[0];
        /* Must aim at something in your environment. */
        if (environment(target) != environment(this_player()))
        {
            notify_fail("You cannot " + verb + " " +
                LANG_THESHORT(ammo) + " at something you carry.\n");
            return 0;
        }

        break;
 
    default:
        /* Sure, two birds with the same stone ?!? */
        notify_fail("Aiming for two birds with the same stone? Please " +
            "select only a single target.\n");
        return 0;
    }

    /* Show off... Scare a person, but don't release. */
    if (ammo == this_object())
    {
        if (sizeof(all_inventory()))
        {
            ammo = all_inventory()[0];
            str = (ammo->query_prop(HEAP_I_IS) ?
                ((ammo->num_heap() == 1) ? "it" : "them") : "it");
            write("You spin your " + short() + " with " +
                LANG_ASHORT(ammo) + " around and pretend to " + verb + " " +
                str + " at " + target->query_the_name(this_player()) +
                ", but do not release the " + LANG_POSS(query_name()) +
                " load.\n");
        }
        else
        {
            write("You spin your " + short() + " around and pretend to " +
                verb + " something at " +
                target->query_the_name(this_player()) + ", but there is " +
                "nothing in the " + query_name() + " to release.\n");
        }

        tell_object(target, this_player()->query_The_name(target) +
            " spins " + this_player()->query_possessive() + " " + short() +
            " around and pretends to " + verb + " something at you! " +
            "However, " + this_player()->query_pronoun() + " does not " +
            "release the " + LANG_POSS(query_name()) + " load.\n");
        say(QCTNAME(this_player()) + " spins " +
            this_player()->query_possessive() + " " + short() + " around " +
            "and pretends to " + verb + " something at " + QTNAME(target) +
            ", but " + this_player()->query_pronoun() + " does not release " +
            "the " + LANG_POSS(query_name()) + " load.\n",
            ({ this_player(), target }) );
        return 1;
    }

    str = (ammo->query_prop(HEAP_I_IS) ?
        ((ammo->num_heap() == 1) ? "it" : "them") : "it");
    write("You spin your " + short() + " with " + LANG_ASHORT(ammo) +
        " around and " + verb + " " + str + " at " +
        target->query_the_name(this_player()) + ".\n");
    tell_object(target, this_player()->query_The_name(target) + " spins " +
        this_player()->query_possessive() + " " + short() +
            " around and then " + verb + "s " + LANG_ASHORT(ammo) +
        " at you!\n");
    say(QCTNAME(this_player()) + " spins " +
        this_player()->query_possessive() + " " + short() + " around and " +
        "then " + verb + "s " + LANG_ASHORT(ammo) + " at " + QTNAME(target) +
        ".\n", ({ this_player(), target }) );

    ammo->move(environment(this_player()));
    tell_room(environment(this_player()), capitalize(LANG_THESHORT(ammo)) +
        " bounces onto the floor.\n");

    return 1;
}

/*
 * Function name: init
 * Description  : Links the commands to the player.
 */
void
init()
{
    ::init();

    /* Allow several synonyms. */
    add_action(hurl, "fling");
    add_action(hurl, "hurl");
    add_action(hurl, "swing");
}

/*
 * Function name: prevent_enter
 * Description  : When the sling is already loaded with another object, then
 *                we do not allow the sling to be used.
 * Arguments    : object obj - the object trying to enter.
 * Returns      : int 1/0 - prevent/allow.
 */
int
prevent_enter(object obj)
{
    /* The sling was already checked this round, don't bother again. */
    if (query_prop(TMP_SLING_CHECKED))
    {
        return 1;
    }

    /* Nothing in the sling yet. Go ahead, if it isn't too big. */
    if (!sizeof(all_inventory()))
    {
        return 0;
    }

    /* Mark the sling, so that we don't get spammy fail messages when
     * player tries to load the sling with all his 312 pebbles.
     */
    add_prop(TMP_SLING_CHECKED, 1);
    set_alarm(0.5, 0.0, &remove_prop(TMP_SLING_CHECKED));

    /* But do give one message. */
    write(LANG_THESHORT(this_object()) + " is already loaded with " +
        LANG_ASHORT(all_inventory()[0]) + ".\n");
    return 1;
}

/*
 * Function name: leave_env
 * Description  : We must redefine this function to ensure that the sling is
 *                released when it is dropped while we hold it.
 * Arguments    : object env - the environment we leave.
 *                object to  - the environment we enter.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    /* We have to make sure that the item is released if it is being held. */
    holdable_item_leave_env(env, to);
}
