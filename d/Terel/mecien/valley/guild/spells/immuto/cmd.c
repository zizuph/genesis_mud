#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>

/*
 * Function name: desc_vbfc
 * Description  : This function takes an object and returns the macro QTNAME
 *                applied to it. We need this map function because it is not
 *                possible to treat macros like functionpointers.
 * Arguments    : object ob - the living object.
 * Returns      : string - the macro QTNAME applied to the object.
 */
string
desc_vbfc(object ob)
{
    return QTNAME(ob);
}

/*
 * Function name: desc_many
 * Description  : Gives the player dependant descriptions of all objects
 *                adressed by the actor. In short, it maps objects to the
 *                macro via desc_vbfc and then makes a composite string.
 * Arguments    : object *oblist - the objects to process and link.
 * Returns      : string - a compound description.
 */
string
desc_many(object *oblist)
{
    return COMPOSITE_WORDS(map(oblist, desc_vbfc));
}

/*
 * Function name: target
 * Description  : Print the message that the target of an action gets. Note
 *                that a newline is automatically added.
 * Example      : target(" hugs you.", oblist);
 *
 *                Someone hugs you.
 *                Mrpr hugs you.
 *                The darkly robed human wizard hugs you.
 *
 * Arguments    : string str     - the message to print.
 *                object *oblist - the people to get the message.
 *                string adverb  - the optional adverb is one was used.
 */
varargs void
target(string str, object *oblist, string adverb = "")
{
    int index = -1;
    int size;
    object *npcs;

    npcs = oblist - FILTER_PLAYERS(oblist);
    if (sizeof(npcs))
    {
        npcs->emote_hook(query_verb(), this_player(), adverb);
/*        oblist -= npcs; */
    }

    size = sizeof(oblist);
    while(++index < size)
    {
        if (!CAN_SEE_IN_ROOM(oblist[index]) ||
            !CAN_SEE(oblist[index], this_player()))
        {
            tell_object(oblist[index], UNSEEN_NAME + str + "\n");
        }
        else if (oblist[index]->query_met(this_player()))
        {
            tell_object(oblist[index], METNAME + str + "\n");
        }
        else
        {
            tell_object(oblist[index], TART_NONMETNAME + str + "\n");
        }
    }
}

/*
 * Function name: targetbb
 * Description  : Same as the function target(), though if the target cannot
 *                see the actor, nothing is printed.
 * Example      : targetbb(" smiles happily.", oblist);
 * Arguments    : see target().
 */
varargs void
targetbb(string str, object *oblist, string adverb = "")
{
    int index = -1;
    int size;
    object *npcs;

    oblist = FILTER_CAN_SEE_IN_ROOM(oblist);
    oblist = FILTER_IS_SEEN(this_player(), oblist);
    npcs = oblist - FILTER_PLAYERS(oblist);
    if (sizeof(npcs))
    {
        npcs->emote_hook(query_verb(), this_player(), adverb);
/*        oblist -= npcs; */
    }

    size = sizeof(oblist);
    while(++index < size)
    {
        if (oblist[index]->query_met(this_player()))
        {
            tell_object(oblist[index], METNAME + str + "\n");
        }
        else
        {
            tell_object(oblist[index], TART_NONMETNAME + str + "\n");
        }
    }
}

/*
 * Function name: all
 * Description  : Print the message that all onlookers get when there is
 *                only one person acting. Ie. those who are watching someone
 *                do something alone. Note that a newline is automatically
 *                added.
 * Example      : all(" screams loudly.");
 *
 *                Someone screams loudly.
 *                Fatty screams loudly.
 *                The big fat gnome wizard screams loudly.
 *
 * Arguments    : string str    - the message to print, starting with a space.
 *                string adverb - the optional adverb if one was used.
 */
varargs void
all(string str, string adverb = "")
{
    int index = -1;
    int size;
    object *oblist;
    object *npcs;

    oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
    npcs = oblist - FILTER_PLAYERS(oblist);
    if (sizeof(npcs))
    {
        npcs->emote_hook(query_verb(), this_player(), adverb);
/*        oblist -= npcs; */
    }

    size = sizeof(oblist);
    while(++index < size)
    {
        if (!CAN_SEE_IN_ROOM(oblist[index]) ||
            !CAN_SEE(oblist[index], this_player()))
        {
            tell_object(oblist[index], UNSEEN_NAME + str + "\n");
        }
        else if (oblist[index]->query_met(this_player()))
        {
            tell_object(oblist[index], METNAME + str + "\n");
        }
        else
        {
            tell_object(oblist[index], TART_NONMETNAME + str + "\n");
        }
    }
}

/*
 * Function name: allbb
 * Description  : Same as all(), but people who cannot see the person
 *                performing, won't see it happen.
 * Example      : allbb(" smiles happily.");
 * Arguments    : see all().
 */
varargs void
allbb(string str, string adverb = "")
{
    int index = -1;
    int size;
    object *oblist;
    object *npcs;

    /* Since the function can_see_in_room() is only defined in livings, the
     * filter FILTER_CAN_SEE_IN_ROOM will only return true for livings, so
     * we don't have to test that ourselves.
     */
    oblist = FILTER_CAN_SEE_IN_ROOM(all_inventory(environment(this_player())) -
                                    ({ this_player() }) );
    oblist = FILTER_IS_SEEN(this_player(), oblist);
    npcs = oblist - FILTER_PLAYERS(oblist);
    if (sizeof(npcs))
    {
        npcs->emote_hook(query_verb(), this_player(), adverb);
/*        oblist -= npcs; */
    }

    size = sizeof(oblist);
    while(++index < size)
    {
        if (oblist[index]->query_met(this_player()))
        {
            tell_object(oblist[index], METNAME + str + "\n");
        }
        else
        {
            tell_object(oblist[index], TART_NONMETNAME + str + "\n");
        }
    }
}

/*
 * Function name: all2act
 * Description  : Print the message that all onlookers get when two players
 *                interact. A newline is always added. If the second,
 *                optional argument is omitted, a period is also added.
 *                Observe the way spaces are added.
 * Example      : all2act(" tackles", oblist);
 *
 *                Someone tackles Mrpr.
 *                Fatty tackles the darkly robed human wizard.
 *                Fatty tackles someone.
 *                The big fat gnome wizard tackles Mrpr.
 *                (etc for the other unseen/met/nonmet combinations)
 *
 *                all2act(" kicks", oblist, " in the groin.");
 *
 *                Fatty kicks the darkly robed human wizard in the groin.
 *                (etcetera.)
 *
 * Arguments    : string str     - the first part of the message to print.
 *                object *oblist - the targets of the emotion, NOT the people
 *                                 who are watching.
 *                string str1    - the optional second part of the message.
 *                string adverb  - the optional adverb if one was used.
 */
varargs void
all2act(string str, object *oblist, string str1, string adverb = "")
{
    object *livings;
    object *npcs;

    livings = FILTER_OTHER_LIVE(all_inventory(environment(this_player())) -
                                oblist);
    npcs = livings - FILTER_PLAYERS(livings);
    if (sizeof(npcs))
    {
        npcs->emote_hook_onlooker(query_verb(), this_player(), adverb, oblist);
    }

    /* Only bother if there are interactive players in the room left. */
/*    if (sizeof(livings - npcs)) */
    if (sizeof(livings))
    {
        say(QCTNAME(this_player()) + " " + str + " " + desc_many(oblist) +
            (strlen(str1) ? (str1 + "\n") : ".\n"),
            (oblist + npcs + ({ this_player() }) ));
    }
}

/*
 * Function name: all2actbb
 * Description  : This is to be used when people cannot see who is doing the
 *                action. I.e. you shouldn't see that someone smiles if you
 *                cannot see that person. For more information. See all2act.
 * Arguments    : See all2act.
 */
varargs void
all2actbb(string str, object *oblist, string str1, string adverb = "")
{
    object *livings;
    object *npcs;

    /* This filter will also reject non-livings because non-livings cannot
     * see in the room.
     */
    livings =
        FILTER_CAN_SEE_IN_ROOM(all_inventory(environment(this_player())) -
        oblist - ({ this_player() }) );
    npcs = livings - FILTER_PLAYERS(livings);
    if (sizeof(npcs))
    {
        npcs->emote_hook_onlooker(query_verb(), this_player(), adverb, oblist);
    }

    /* Only bother if there are players left in the room. */
/*    livings -= npcs; */
    if (sizeof(livings))
    {
        livings->catch_msg(QCTNAME(this_player()) + " " + str + " " +
                           desc_many(oblist) +
                           (strlen(str1) ? (str1 + "\n") : ".\n"));
    }
}
