// CREATURE:  baby sea turtle

    /* Calia Domain

    HISTORY

    [2002-09-27] Created by Uhclem from [C:\CALIA\WEENWARE\TURTLE.DOC].
    [2008-11-01] Changed enter_env to init_living. add_action is no longer
                 allowed to be used in the same manner. Was causing runtimes
                 during this year's weenware.

    PURPOSE

    This creature was created specifically for the annual Halloween scavenger
    hunt.  It is only deployed around Halloween and should not be incorporated
    into quests or any other year-round functions.  Since it may occur in great
    numbers, it does not contain any alarms lest the entire game be slowed by
    hundreds of repeating alarms.  Instead, its movements are controlled by a
    single alarm in the turtle dispenser, and its emotes are all reactions to
    player emotes controlled by emote_hook().

    The turtle's shell, not the turtle, is the object of the scavenger hunt.
    Players have to interact with the turtle until they discover a way to
    persuade it to part with its shell.  No, they don't have to kill it, and
    attacking it is impossible, but the more they annoy it, the more likely
    they are to get the shell.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/creature";

#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include <composite.h>
#include <const.h>
#include "defs.h"

#define FILTER_FOOD(x)  filter((x), &->query_amount())

// GLOBAL VARIABLES

int Annoyed_Level = 0;  /*  measures how ticked off the turtle is  */

// FUNCTIONS

// Function:  emote_hook(emote, actor, adverb, oblist, cmd_attr, target)

/*

Purpose:  cause the turtle to react to various player emotes.  The system calls
this function whenever a player uses an emote in the turtle's presence.

Arguments:  emote, string whose value comes from query_verb(); actor, object
using the emote; adverb, string containing the adverb used; oblist, array of
objects targeted by the emote; cmd_attr, int result of the emote; target, int
whose value is 1 if the turtle is the target (or one of the targets) of the
emote.

Returns:  nothing.

*/

void
emote_hook(string emote, object actor, string adverb, object* oblist,
    int cmd_attr, int target)

{

    object room = environment();
    object turtle_shell;
    string actor_name = actor->query_real_name();

    /*
     *  Ignore emotes from NPCs.    
     */

    if (!interactive(actor))

    {

        return;

    }

    /*
     *  In general, using any emote that doesn't directly annoy the turtle 
     *  calms it.  The effect simulates the passage of time, during which the
     *  turtle forgives and forgets insults.  A series of several annoying
     *  emotes in a row will push the turtle over the edge.    
     */

    if (Annoyed_Level > 0)

    {

        Annoyed_Level -= 1;

    }

    if (living(room))

    {

        room = environment(room);

    }

    if (target)  /* process emotes that target the turtle directly */

    {

        switch (emote)

        {

            case "admire":
            case "bat":
            case "love":

            command("blush");

            break;

            case "back":

            tell_room(room,
                "The " + short() + " approaches " +
                QTNAME(actor) + adverb + ".\n",
                actor);

            actor->catch_msg("The " + short() +
                " approaches you" + adverb + ".\n");

            break;

            case "beckon":

            command("eyebrow " + actor_name + " inquisitively");

            break;

            case "caress":
            case "pat":
            case "pet":

            tell_room(room, "The " + short() +
                " wags its tail exuberantly.\n");

            break;

            case "comfort":

            tell_room(room, "The " + short() +
                " appears calm and content.\n");

            break;

            case "cuddle":
            case "fondle":
            case "nuzzle":
            case "snuggle":

            command("drool blissfully");

            break;

            case "curl":

            tell_room(room,
                "The " + short() + " strains and groans under the" +
                " weight of " + QTNAME(actor) + ".\n",
                actor);

            actor->catch_msg("The " + short() +
                " strains and groans under your weight.\n");

            break;

            case "dance":

            command("confused");

            break;

            case "explode":
            case "grope":
            case "growl":
            case "pinch":
            case "poke":
            case "pounce":
            case "spank":
            case "tackle":

            Annoyed_Level += 1;

            tell_room(room,
                "The " + short() + " suddenly pulls in its head," +
                " legs, and tail and shuts its shell with a loud" +
                " 'snap!' A few seconds later, it gingerly opens" +
                " up again and glares indignantly at " + QTNAME(actor) +
                ".\n",
                actor);

            actor->catch_msg("The " + short() +
                " suddenly pulls in its head," +
                " legs, and tail and shuts its shell with a loud" +
                " 'snap!' A few seconds later, it gingerly opens" +
                " up again and glares at you indignantly.\n");

            break;

            case "french":
            case "kiss":

            command("gag");

            break;

            case "glare":
            case "point":
            case "scold":
            case "snarl":
            case "stare":

            tell_room(room, "The " + short() + " " +
                ({
                "looks around with a wide-eyed innocent expression" +
                " as if to say, 'who, me?'",
                "gets as low to the ground as possible and tries" +
                " to make itself inconspicuous.",
                "raises its head high with its nose pointed" +
                " haughtily in the air and and" +
                " emits an indignant 'hmph!'"
                })[random(3)] +
                "\n");

            break;

            case "greet":

            tell_room(room, "The " + short() + " acknowledges the" +
                " greeting in the traditional manner of a turtle.\n");

            break;

            case "grovel":

            command("pat " + actor_name);

            break;

            case "hold":
            case "hug":

            tell_room(room,
                "The " + short() + " reacts to the unfamiliar pressure" +
                " of " + QTNAME(actor) + "'s " + emote +
                " by grimacing and furrowing its brow" +
                " in an unambiguous display of turtle anxiety.\n",
                actor);

            actor->catch_msg("The " + short() +
                " reacts to the unfamiliar pressure" +
                " of your " + emote + " by grimacing and furrowing" +
                " its brow in an unambiguous" +
                " display of turtle anxiety.\n");

            break;

            case "ignore":

            command("sulk");

            break;

            /*
             *  Ordinarily I don't reward bad behavior, but for Halloween I'll 
             *  make an exception.    
             */

            case "kick":
            case "knee":
            case "puke":
            case "slap":
            case "spit":

            /*
             *  Three or four consecutive emotes from the list above will send 
             *  the turtle ballistic (yes, it's a medieval term).    
             */

            Annoyed_Level += (3 + random(2));

            if (Annoyed_Level > 9)

            {

                tell_room(room, "The " + short() + " " +
                    ({
                    "stands up on its hind legs in" +
                    " a distinctly un-turtle-like manner",
                    "pounds its little turtle-fists against the ground",
                    "shakes its little turtle-fist at the heavens"
                    })[random(3)] +
                    " and wails: " +
                    ({
                    "Gruntfuttock!",
                    "Oy!",
                    "Blimey!",
                    "Begorrah!"
                    })[random(4)] +
                    " " +
                    ({
                    "I don't get paid enough to take this abuse!",
                    "Uhclem didn't say anything about this kind of" +
                    " abuse when he hired me!",
                    "If you want the damned shell that" +
                    " bad, take it!"
                    })[random(3)] +
                    "\n" +
                    "The " + short() + " takes off its shell to reveal" +
                    " that it is really a tiny " +
                    ({
                    "goblin",
                    "gremlin",
                    "demon"
                    })[random(3)] +
                    " wearing a turtle costume, " +
                    ({
                    "flings the shell on the ground in disgust",
                    "discards the shell with an angry kick",
                    "drops the shell disdainfully"
                    })[random(3)] +
                    ", and disappears.\n");

                turtle_shell = clone_object(TURTLE_SHELL);
                turtle_shell->move(room);
                remove_object();

            }

            else

            {

                /*
                 *  Since Annoyed_Level must be three or greater when this 
                 *  routine is invoked, the first three elements of the array
                 *  should never be used, but I put 'ack' in those positions
                 *  anyway to cover any unexpected values that may arise due to
                 *  later changes.    
                 */

                command(({"ack", "ack", "ack", "wince", "grumble",
                    "glare " + actor_name,
                    "scowl " + actor_name,
                    "snarl " + actor_name,
                    "steam", "fume"})[Annoyed_Level]);

            }

            break;

            case "lick":
            case "nibble":

            command("back " + actor_name);

            break;

            case "listen":

            tell_room(room, "The " + short() +
                " improvises a little tap-dance so" +
                " that " + QTNAME(actor) + " will have" +
                " something to listen to.\n",
                actor);

            actor->catch_msg("The " + short() +
                " improvises a little tap-dance so that you" +
                " will have something to listen to.\n");

            break;

            case "nudge":

            command("wink " + actor_name + " knowingly");

            break;

            case "ruffle":
            case "shake":

            command("confused");

            break;

            case "squeeze":

            Annoyed_Level += 1;

            tell_room(room,
                "The " + short() + " grimaces and strains" +
                " in a determined attempt to maintain" +
                " self-control, but the force of the squeeze is" +
                " too much, and the turtle abruptly releases a" +
                " stream of urine that splashes all" +
                " over " + QTNAME(actor) + "!\n",
                actor);

            actor->catch_msg("The " + short() +
                " grimaces and strains" +
                " in a determined attempt to maintain" +
                " self-control, but the force of the squeeze is" +
                " too much, and the turtle abruptly releases a" +
                " stream of urine that splashes all" +
                " over you!\n");

            break;

            case "startle":

            command("hiccup");

            break;

            case "tap":

            command("listen " + actor_name);

            break;

            case "tease":

            command("ignore " + actor_name);

            break;

            case "tickle":
            case "touch":

            command("watch " + actor_name + " suspiciously");

            break;

            case "wink":

            command("nudge " + actor_name);

            break;

            default:

            /*
             *  Any other emote targeted at the turtle suggests that a player 
             *  is trying to figure out the puzzle.  Occasionally I'll give him
             *  a hint.    
             */

            if (!random(5))

            {

                command("peer hungrily " + actor->query_real_name());

            }

        }

    }

    else

    {

        switch(emote)  /* process non-targeted emotes */

        {

            case "ack":
            case "fart":
            case "hiccup":
            case "roar":
            case "scream":

            command("hiccup");

            break;

            case "rolleyes":

            command("agree " + actor_name);

            break;

            case "strut":

            tell_room(room, "The " + short() + " seems unimpressed.\n");

            break;

            case "yodel":

            command("ack");

            /*
             *  There is no default action for other non-targeted emotes.    
             */

        }

    }

}

// Function:  swallow_turtle(turtle)

/*

Purpose:  swallow the turtle.

Arguments:  string indicating this turtle or "all".

Returns:  0/1.

*/

int
swallow_turtle(string str)

{

    object tp = this_player();
    object to = this_object();
    object room = environment(tp);
    object turtle;
    object turtle_helper;

    if ((!stringp(str)
        ||
        !parse_command(str, all_inventory(tp), "%o", turtle)
        ||
        turtle != to)
        &&
        str != "all")

    {

        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;

    }

    tell_room(room,
        QCTNAME(tp) + " tilts back " + tp->query_possessive() +
        " head, opens wide, and swallows the " + short() + " whole!\n",
        tp);

    tp->catch_msg("You tilt back your head, open your mouth" +
        " wide, and swallow the " + short() + " whole!\n");

    turtle_helper = clone_object(TURTLE_HELPER);
    turtle_helper->move(tp);
    remove_object();

    /*
     *  Returning 1 prevents the player from eating any food in his inventory 
     *  even though he may have typed "eat all".  This is a feature, not a bug,
     *  to protect the player who now has a turtle stuck in his throat.    
     */

    return 1;

}

// Function:  remove_shell(shell)

/*

Purpose:  elicit a pitiful reaction from the turtle; the player can't remove
the shell, but we can make him look like a monster for trying.

Arguments:  string mentioning the turtle or its shell.

Returns:  0/1.

*/

int
remove_shell(string str)

{

    object tp = this_player();
    object room = environment(tp);

    /*
     *  The most logical command is "pry/remove shell from turtle", but since I 
     *  never let the player succeed in this effort, I'm not too picky about
     *  syntax.    
     */

    if (!str
        ||
        !wildmatch("*turtle*", str)
        ||
        !wildmatch("*shell*", str))

    {

        if (query_verb() == "remove")

        {

            notify_fail("Remove what from what?\n");

        }

        else

        {

            notify_fail("Pry what off what?\n");

        }

        return 0;

    }

    tell_room(room,
        "The " + short() + " " +
        ({
        "shrieks in terror",
        "flails its arms and legs and screams for help",
        "writhes in pain and cries out pitifully"
        })[random(3)] +
        " as " + QTNAME(tp) + " " +
        ({
        "tries to pry its shell off its body",
        "grabs it by the head and tries to yank it out of its shell",
        "tries to wrench it out of its shell"
        })[random(3)] +
        ", but " +
        ({
        "after a short struggle",
        "with the aid of a few well-placed kicks to the throat and face",
        "drawing upon unnatural forces known only to turtlefolk"
        })[random(3)] +
        ", " +
        ({
        "it manages to wriggle free and jump to the ground",
        "it breaks free of " + tp->query_possessive() + " grip",
        "it overpowers " + tp->query_objective() + " and escapes"
        })[random(3)] +
        ".\n",
        tp);

    tp->catch_msg("The " + short() + " " +
        ({
        "shrieks in terror",
        "flails its arms and legs and screams for help",
        "writhes in pain and cries out pitifully"
        })[random(3)] +
        " as you " +
        ({
        "try to pry its shell off its body",
        "grab it by the head and try to yank it out of its shell",
        "try to wrench it out of its shell"
        })[random(3)] +
        ", but " +
        ({
        "after a short struggle",
        "with the aid of a few well-placed kicks to the throat and face",
        "drawing upon strange forces known only to turtlefolk"
        })[random(3)] +
        " " +
        ({
        "it manages to wriggle free and jump to the ground",
        "it breaks free of your grip",
        "it overpowers you and escapes"
        })[random(3)] +
        ".\n");

    tp->command("$drop " + short());

    return 1;

}

// Function:  devour_all(foods)

/*

Purpose:  make the turtle look like it's devouring unlimited amounts of food;
in actuality, the food is sent to the Calian wizards holiday room.

Arguments:  foods, array of food objects.

Returns:  nothing.

*/

void
devour_all(object *foods)

{

    object room;
    object player;
    string player_name = "";

    /*
     *  Abort processing if the array is empty.    
     */

    if (!foods ||
        !sizeof(foods))

    {

        return;

    }

    setuid();
    seteuid(getuid());
        
    room = environment();

    if (living(room))

    {

        player = room;
        room = environment(player);
        player_name = player->query_name();

    }

    tell_room(room,
        "The " + short() + " " +
        ({"greedily", "eagerly", "impetuously"})[random(3)] +
        " devours " + COMPOSITE_DEAD(foods) + ".\n");

    while (sizeof(foods))

    {
        foods[0]->move(HOLIDAY_ROOM);

        if (player_name != "")

        {

            tell_room(HOLIDAY_ROOM,
                player_name + " donates " + foods[0]->short() +
                " to the Calia Halloween party.\n");

        }

        else

        {

            tell_room(HOLIDAY_ROOM,
                foods[0]->query_prop(CALIA_S_RECEIVED_FROM) +
                " donates " + foods[0]->short() +
                " to the Calia Halloween party.\n");

        }

        foods -= ({foods[0]});

    }

}

// Function:  turtle_trick_or_treat()

/*

Purpose:  It would be unseemly for wizards to walk around Genesis with
trick-or-treat bags, so we let the turtle do the collecting for us.

Arguments:  none.

Returns:  nothing.

*/

void
turtle_trick_or_treat()

{

    object *treats;
    object tp = environment();
    object room;

    if (!living(tp))  /* player may have dropped turtle quickly */

    {

        return;

    }

    devour_all(FILTER_FOOD(all_inventory(tp)));

}

// Function:  catch_me_if_you_can()

/*

Purpose:  allow turtle to be taken only by a player with food in his inventory.

Arguments:  none.

Returns:  0 or string; 0 allows, string prevents taking the turtle.

*/

mixed
catch_me_if_you_can()

{

    object tp = this_player();
    object room = environment();

    if (present("food", tp))

    {

        set_alarm(1.1, 0.0, turtle_trick_or_treat);
        return 0;

    }

    tell_room(room,
        "The " + short() + " scrambles around " + QTNAME(tp) +
        "'s feet, eluding all " + tp->query_possessive() +
        " attempts to catch it.\n",
        tp);

    return "The " + short() + " scrambles around your feet," +
        " eluding all your attempts to catch it.\n";

}

// Function:  eat_and_drop()

/*

Purpose:  make the turtle eat food and drop anything else it's given.

Arguments:  none.

Returns:  nothing.

*/

void
eat_and_drop()

{

    /*
     *  Avoid cannibalism, even on Halloween.    
     */

    object cousin = present("turtle");

    if (cousin)

    {

        command("ack");

    }

    else

    {

        devour_all(FILTER_FOOD(all_inventory()));

    }

    command("drop all");

}

// Function:  enter_inv(ob, from)

/*

Purpose:  invoked by system whenever an item enters the turtle's inventory;
used here to invoke the eat_and_drop function.

Arguments:  ob, the object entering inventory; from, its previous environment.

Returns:  nothing

*/

void
enter_inv(object ob, object from)

{

    ::enter_inv(ob, from);

    /*
     *  Tag the incoming item so we know who to thank.    
     */

    ob->add_prop(CALIA_S_RECEIVED_FROM, this_player()->query_name());

    set_alarm(0.0, 0.0, eat_and_drop);

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  invoked by system whenever the turtle enters an object's inventory;
used here to define some commands available to (or inflicted on) a player
holding the turtle.

Arguments:  ob_to, the object turtle moves to; ob_from, the object the turtle
is leaving.

Returns:  nothing.

*/

/*
 * Function name: init_living
 * Purpose:  invoked by system whenever the turtle enters an object's inventory;
 *           used here to define some commands available to (or inflicted on) a player
 *           holding the turtle.
 */
public void
init_living()
{
    ::init_living();
    
    if (interactive(environment(this_object())))
    {
        add_action(swallow_turtle, "eat");
        add_action(swallow_turtle, "swallow");
        add_action(remove_shell, "remove");
        add_action(remove_shell, "pry");
    }
}

// CREATURE DEFINITION

    create_creature()

    {

        string my_adj = ({"quiet", "unobtrusive", "gentle", "placid", "shy",
            "serene", "tranquil", "wary", "alert", "careful", "cautious",
            "nimble", "agile", "wily", "sly"})[random(15)];

        set_name("turtle");
        set_race_name("turtle");
        set_gender(G_NEUTER);
        set_stats(({40,20,4,4,4,4}));
        set_adj(({my_adj, "baby", "sea"}));
        set_short(my_adj + " baby sea turtle");

        set_long("The baby sea turtle's diminutive size suggests" +
            " that it has hatched very recently. Its shell of" +
            " varying shades of green provides good camouflage for" +
            " life in the ocean.\n");

        add_item(({"shell", "turtle shell", "green shell", "top", "bottom"}),
            "The shell is light green on the bottom and dark green" +
            " on the top, as are the turtle's head, legs, and tail.\n");

        add_item(({"head", "leg", "legs", "tail",
            "turtle head", "turtle leg", "turtle legs", "turtle tail"}),
            "The turtle's head, legs, and tail project from the" +
            " shell, but in an emergency it can pull them in" +
            " and close the shell tightly.\n");

        /*
         *  PROPERTIES    
         */

        /*
         *  The extraordinary maximum volume and weight settings allow the 
         *  turtle to receive food of just about any size.  The turtle has a
         *  special appetite routine that allows it to eat unlimited amounts of
         *  food.    
         */

        add_prop(CONT_I_VOLUME, 75);
        add_prop(CONT_I_WEIGHT, 75);
        add_prop(CONT_I_MAX_VOLUME, 10000);
        add_prop(CONT_I_MAX_WEIGHT, 10000);
        add_prop(LIVE_I_NEVERKNOWN, 1);
        add_prop(LIVE_I_NO_ACCEPT_GIVE, 0);
        add_prop(LIVE_I_NO_GENDER_DESC, 1);
        add_prop(NPC_I_NO_LOOKS, 1);
        add_prop(OBJ_M_NO_GET, "@@catch_me_if_you_can@@");

        setuid();  /*  "uid" settings required for cloning. */
        seteuid(getuid());

        add_prop(OBJ_M_NO_ATTACK,
            "The " + short() + " gazes up at you with" +
            " utter trust and affection, as if it believed you" +
            " were its mother. You cannot bring yourself to attack" +
            " such a tiny innocent creature!\n");

    }
