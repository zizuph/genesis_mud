// CREATURE:  gifteroo (gift-delivery gopheroo)

/* Calia Domain

HISTORY

[1999-12-06] Created by Uhclem from [C:\CALIA\YULEWARE\GIFTEROO.DOC].
[2000-12-19] Uhclem added CALIA_GIFT_DELIVERED property and related code.
[2001-12-22] Uhclem added holiday room messages.

PURPOSE

A relentless but erratic creature to deliver gifts (wrapped_fruit)
addressed from one player to another.  Deployed by the yule tree in Calia
palace (palace_tree) around Christmas.
*/

// INCLUSIONS AND DEFINITIONS

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <formulas.h>
#include "defs.h"

#define FILTER_ADDRESSED_GIFTS(x) \
    filter((x), &operator(!=)(0) @ &->to_whom())

#define CALIA_GIFT_DELIVERED    "_calia_gift_delivered"

// GLOBAL VARIABLES

object *Curious_Folks = ({});  /*  people who asked gifteroo something  */
object Palace_Tree;            /*  object that cloned this gifteroo     */
string My_Home;                /*  gifteroo home                        */
int Gift_Stage = 0;            /*  controls search and deliver routine  */

// FUNCTIONS

// Function:  search_and_deliver

/*

Purpose:  if gifts are in the inventory, find the recipients and deliver them
in a gopherooish fashion.

Arguments:  none.

Returns:  nothing.

*/

void
search_and_deliver()

{

    object *my_inventory =
    FILTER_ADDRESSED_GIFTS(all_inventory(this_object()));
    object *new_gifts = ({});
    object recipient;
    int n;

    string *entries =
        ({
        "enters at a full gallop and skids to a stop.",
        "meanders in looking somewhat bewildered.",
        "lopes in and settles down in the lotus position.",
        "ambles in and sniffs around your feet for... well," +
        " nobody really knows what gopheroos sniff for.",
        "arrives from wherever he was only a moment ago.",
        "suddenly lands with a loud PLOP, as if some invisible" +
        " hand had just deposited him here."
        });

    string *exits =
        ({
        "races away at a full gallop.",
        "meanders away headed in no particular direction.",
        "wanders away.",
        "scoots quickly behind you, but when you look to see" +
        " what he's doing back there, he's gone!",
        "crouches down, tenses his muscles, then springs out of" +
        " sight in one mighty leap!",
        "takes a deep breath, leaps into his own" +
        " pouch, and disappears!"
        });

    string *takes_a =
        ({
        "wraps his front paws around",
        "cautiously sniffs",
        "circles a few times around",
        "sits for a moment pondering",
        "gingerly pokes"
        });

    string *takes_b =
        ({
        "picks it up with a loud 'urmph!'",
        "snatches it before it can get away.",
        "seizes it with a lightning-fast movement!",
        "takes it, pausing a moment to press it to his nose" +
        " and savor its aroma.",
        "grabs it and stuffs it into his pouch" +
        " (at least you hope that's a pouch)."
        });

    string *acts_silly =
        ({
        "pulls a slide-ocarina out of his pouch (at" +
        " least you hope that's a pouch), hooks one toe" +
        " into the loop at the end of the slide, and" +
        " tweetles a cheerful yule tune.",
        "dances merrily around you in a wide circular" +
        " pattern, spinning, leaping, and chirping 'nik nik nik'" +
        " in time with his steps.",
        "sits back on his haunches and peers at you from under the" +
        " edge of his striped stocking cap, which has slipped" +
        " down and nearly completely covers his eyes.",
        "thumps the ground loudly with his hind foot and waves" +
        " his front paws wildly to get your attention.",
        "bows exquisitely before you, adding a grand flourish with" +
        " his paws and tilting his head in a manner that" +
        " suggests both good breeding and a year or two of" +
        " training at the Gopheroo Charm Academy.",
        "sticks both front paws in his mouth and blows" +
        " mightily, releasing a shrill, wavering whistle" +
        " that affects you like a hundred fingernails dragged" +
        " across a vast, resonant blackboard."
        });

    /*
     *  If for any reason the tree does not exist, leave the game.    
     */

    if (!Palace_Tree)

    {

        move_living("M", My_Home);
        say(capitalize(LANG_ADDART(short())) + " arrives.\n");
        command("drop all");
        say("The " + short() + " runs away!\n");
        remove_object();
        return;

    }

    switch (Gift_Stage)

    {

        /*
         *  Stage 0: collecting gifts to be delivered.    
         */

        case 0:

        /*
         *  If we're not in the same room with the tree, go to that room.    
         */

        if (file_name(environment()) != My_Home)

        {

            tell_room(environment(),
                capitalize(LANG_ADDART(short())) +
                " " + exits[random(sizeof(exits))] + "\n");

            move_living("M", My_Home);

            tell_room(environment(),
                capitalize(LANG_ADDART(short())) +
                " " + entries[random(sizeof(entries))] + "\n");

        }

        /*
         *  If we are in the room with the tree, pick up gifts until we have a 
         *  full load (20 gifts) or there are no more to be found.    
         */

        else

        {

            new_gifts = FILTER_ADDRESSED_GIFTS(all_inventory(environment()));

            /*
             *  Ignore any gift whose recipient is not currently logged in.    
             */

            while (sizeof(new_gifts) &&
                (!find_player(new_gifts[0]->to_whom()) ||
                find_player(new_gifts[0]->to_whom())->query_linkdead() ||
                find_player(new_gifts[0]->to_whom())->query_invis()))

            {

                new_gifts -= new_gifts[0..0];

            }

            /*
             *  Only make the gifteroo carry 20 gifts at a time.    
             */

            if (sizeof(my_inventory) < 20 && sizeof(new_gifts))

            {

                tell_room(environment(),
                    "The " + short() +
                    " " + takes_a[random(sizeof(takes_a))] +
                    " " + LANG_ADDART(new_gifts[0]->short()) +
                    " and then" +
                    " " + takes_b[random(sizeof(takes_b))] + "\n");

                new_gifts[0]->move(this_object(), 1);

            }

            /*
             *  If none of the above conditions were met, there's nothing left 
             *  to do in stage 0.  If there are gifts to be delivered, move on
             *  to stage 1.  If not, just idle for a while.    
             */

            else

            {

                if (sizeof(my_inventory))

                {

                    Gift_Stage = 1;

                }

            }

        }

        break;

        /*
         *  Stage 1: find the recipient of the first gift in the inventory.    
         */

        case 1:

        recipient = find_player(my_inventory[0]->to_whom());

        /*
         *  Has the recipient logged out?.  Is he sneaking or hiding?  Is he 
         *  in  combat?  Is he a ghost?  Is he linkdead?  If he answers 'yes'
         *  to any of these questions, don't try to deliver the gift.  Take it
         *  back to the tree and let the stage continue with the next gift.    
         */

        if (!recipient ||
            recipient->query_attack() ||
            recipient->query_linkdead() ||
            recipient->query_invis() ||
            recipient->query_prop(LIVE_I_SNEAK) ||
            recipient->query_prop(OBJ_I_HIDE) ||
            recipient->query_ghost())

        {

            /*
             *  If we're not in the same room with the tree, go there.    
             */

            if (file_name(environment()) != My_Home)

        {

            tell_room(environment(),
                "The " + short() +
                " " + exits[random(sizeof(exits))] + "\n");

            move_living("M", My_Home);

            tell_room(environment(),
                capitalize(LANG_ADDART(short())) +
                " " + entries[random(sizeof(entries))] + "\n");

        }

        else

        {

            tell_room(environment(),
                "The " + short() +
                " puts " + LANG_ADDART(my_inventory[0]->short()) +
                " under the tree.\n");

            my_inventory[0]->move(environment());

        }

    }

        /*
         *  If the recipient is in the game and not unduly occupied, go to him. 
         *    
         */

        else if (environment() != environment(recipient))

        {

            tell_room(environment(),
                "The " + short() +
                " " + exits[random(sizeof(exits))] + "\n");

            move_living("M", environment(recipient));

            tell_room(environment(),
                capitalize(LANG_ADDART(short())) +
                " " + entries[random(sizeof(entries))] + "\n");

        }

        /*
         *  Now that we've found the recipient, let's entertain him for a bit 
         *  before we give him his gift.    
         */

        else

        {

            tell_room(environment(),
                "The " + short() +
                " " + acts_silly[random(sizeof(acts_silly))] + "\n");

            Gift_Stage = 2;

        }

        break;

        /*
         *  Stage 2:  deliver the gift.    
         */

        case 2:

        recipient = find_player(my_inventory[0]->to_whom());

        /*
         *  If the recipient is standing here ready to receive his gift, hand 
         *  it to him.    
         */

        /*
         *  New code for Christmas 2000:  I had a bit of trouble delivering a 
         *  gift to Mrpr.  It seems he has a magical way of returning things
         *  that are given to him that bypasses the LIVE_M_NO_ACCEPT_GIVE
         *  property.  My solution is to add a property, CALIA_GIFT_DELIVERED,
         *  when the gift is delivered.  If a gift with this property winds up
         *  in the gifteroo's inventory, he drops it in the vicinity of the
         *  recipient rather than trying to hand it to him.    
         */

        if (my_inventory[0]->query_prop(CALIA_GIFT_DELIVERED))

        {

            recipient->catch_msg("The " + short() +
                " peers at you quizzically, looks down at" +
                " the " + my_inventory[0]->short() +
                ", looks up at you again, and sits for a" +
                " moment scratching his head. Finally he" +
                " shrugs his shoulders and simply drops the gift.\n");

            tell_room(environment(),
                "The " + short() +
                " peers at " + QTNAME(recipient) +
                " quizzically, looks down at" +
                " the " + my_inventory[0]->short() +
                ", looks up at " + QTNAME(recipient) +
                " again, and sits for a" +
                " moment scratching his head. Finally he" +
                " shrugs his shoulders and simply" +
                " drops the gift.\n", recipient);

            my_inventory[0]->move(environment(), 1);

            log_file("yule_deliveries",
                ctime(time()) +
                " " + capitalize(my_inventory[0]->from_whom()) +
                " > " + capitalize(my_inventory[0]->to_whom()) +
                " @ " + file_name(environment()) + " (dropped).\n");

            tell_room(HOLIDAY_ROOM,
                "Gifteroo drops a gift from " +
                capitalize(my_inventory[0]->from_whom()) +
                " at the feet of " +
                capitalize(my_inventory[0]->to_whom()) + ".\n");

        }

        else

        {

            if (recipient &&
                !recipient->query_attack() &&
                !recipient->query_linkdead() &&
                !recipient->query_invis() &&
                !recipient->query_prop(LIVE_I_SNEAK) &&
                !recipient->query_prop(OBJ_I_HIDE) &&
                !recipient->query_ghost() &&
                environment() == environment(recipient))

            {

                my_inventory[0]->move(recipient, 1);
                my_inventory[0]->add_prop(CALIA_GIFT_DELIVERED, 1);

                recipient->catch_msg("The " + short() +
                    " hands you " + LANG_ADDART(my_inventory[0]->short()) +
                    ".\n");

                tell_room(environment(),
                    "The " + short() +
                    " hands " + QTNAME(recipient) +
                    " " + LANG_ADDART(my_inventory[0]->short()) +
                    ".\n", recipient);

                log_file("yule_deliveries",
                    ctime(time()) +
                    " " + capitalize(my_inventory[0]->from_whom()) +
                    " > " + capitalize(my_inventory[0]->to_whom()) +
                    " @ " + file_name(environment()) + ".\n");

                tell_room(HOLIDAY_ROOM,
                    "Gifteroo delivers a gift from " +
                    capitalize(my_inventory[0]->from_whom()) +
                    " to " + capitalize(my_inventory[0]->to_whom()) + ".\n");

            }

            /*
             *  If the recipient is not here, go back to stage 1.    
             */

            else

            {

                Gift_Stage = 1;

            }

        }

        break;

        /*
         *  Since there are only a few statements that change the Gift_Stage 
         *  value, a default is nearly superfluous.  However, just in case
         *  someone makes an error revising this file one day, we'll use it to
         *  put everything back in its starting position.    
         */

        default:

        move_living("M", My_Home);
        say(capitalize(LANG_ADDART(short())) + " races in.\n");
        command("drop all");
        Gift_Stage = 0;

    }

    /*
     *  When we run out of gifts, go back to stage 0.  On the unlikely chance 
     *  that some wizard will play a trick on me and put an unauthorized item
     *  in the gifteroo's inventory, add a drop command to get rid of it.    
     */

    if (!sizeof(FILTER_ADDRESSED_GIFTS(all_inventory(this_object()))))

    {

        Gift_Stage = 0;
        command("drop all");

    }

    /*
     *  Always check for free food!    
     */

    if (present("fruit", environment()))

    {

        command("do take fruits, eat all, drop fruits");

    }

    /*
     *  Set next alarm.  If we are carrying any gifts, then we're in a hurry. 
     *  If not, we take our time.    
     */

    if (present("gift", this_object()))

    {

        set_alarm(5.5, 0.0, search_and_deliver);

    }

    else

    {

        set_alarm(95.5, 0.0, search_and_deliver);

    }

}

// Function:  start_delivery(Palace_Tree)

/*

Purpose:  start the delivery cycle and define the homing object.

Arguments:  object where the gifteroo should look for gifts.  There can be more
than one palace tree, each with its own gifteroo - they will not attempt to
take gifts from each other's territory.

Returns:  nothing.

*/

void
start_delivery(object tree, object room)

{

    Palace_Tree = tree;
    My_Home = file_name(room);
    set_alarm(33.0, 0.0, search_and_deliver);

}

// Function:  react_to_question()

/*

Purpose:  react to being asked a question.

Arguments:  none.

Returns:  nothing.

*/

void
react_to_question()

{

    string *message1;
    string *message2;
    int m;
    int n;

    if (sizeof(Curious_Folks))

    {

        if (Curious_Folks[0] &&
            environment(Curious_Folks[0]) == environment())

        {

            message1 =
                ({
                "peers quizzically at",
                "back cautiously away from",
                "stares briefly at",
                "jumps away from",
                "takes a few quick steps back from",
                "blinks his beady little eyes hard at"
                });

            message2 =
                ({
                "pulls a leatherbound edition of" +
                " \"'Twas the Night Before Armageddon\"" +
                " out of his pouch, stares" +
                " for a moment off into the distance" +
                " with a quizzical expression, then shakes" +
                " his head vigorously and stuffs the book" +
                " back into his pouch",
                "sticks his head in his pouch to look" +
                " around for something, then after several seconds" +
                " pulls it back out with a loud" +
                " 'POP!' looking completely disheveled and" +
                " gasping for breath",
                "then adopts a pensive stance with his head" +
                " resting on his front paw and ponders" +
                " the imponderable, or perhaps it's the" +
                " unthinkable, or maybe it's only the improbable" +
                " - it's so difficult to be certain with gopheroos",
                "clenches his paws into fists, and gnashes his teeth" +
                " in an awful grimace that suggests he is" +
                " wrestling with a truly monumental question, then" +
                " all at once he relaxes as if he has" +
                " completely forgotten what it was he was" +
                " thinking so hard about",
                "turns and looks behind him, his eyes" +
                " darting back and forth as if scanning for" +
                " something dangerous, important, valuable," +
                " or delicious (one can never be certain" +
                " with gopheroos), then turns back and" +
                " gives only a slight shrug",
                "looks down, and anxiously counts his" +
                " toes, then relaxes noticeably when he is" +
                " assured that they are all in" +
                " their proper places",
                "looks down anxiously to check if his" +
                " snowshoes are untied, and then relaxes" +
                " considerably when he sees they are well secured",
                "then checks his snowshoes to see if anything is" +
                " stuck to the bottoms... no, nothing on the" +
                " right, nothing on the left either"
                });

            Curious_Folks[0]->catch_msg(QCTNAME(this_object()) +
                " " + message1[random(sizeof(message1))] +
                " you, " + message2[random(sizeof(message2))] +
                ".\n");

            tell_room(environment(),
                QCTNAME(this_object()) +
                " " + message1[random(sizeof(message1))] +
                " " + QTNAME(Curious_Folks[0]) +
                ", " + message2[random(sizeof(message2))] +
                ".\n", Curious_Folks[0]);

        }

        Curious_Folks -= ({Curious_Folks[0]});

    }

}

// Function:  ask_a_silly_question(str)

/*

Purpose:  get a silly answer.  The gopheroo does not speak or understand words,
but he will react to questions in his own way.

Arguments:  string that contains the living being queried and the query text.

Returns:  0 always.  We let the standard ask function run its course and apply
the gopheroo's reaction with an alarm.

*/

int
ask_a_silly_question(string str)

{

    object ask_whom;
    string ask_what;

    parse_command(str, environment(), "%o %s", ask_whom, ask_what);

    if (ask_whom == this_object())

    {

        Curious_Folks += ({this_player()});
        set_alarm(0.3, 0.0, react_to_question);

    }

    return 0;

}

// Function:  init_living()

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init_living()

{

    ::init_living();
    add_action(ask_a_silly_question, "ask");

}

// CREATURE DEFINITION

void
create_creature()

{

    set_short(
        ({"earnest", "determined", "industrious"})[random(3)] +
        " but " +
        ({"capricious", "unfocused", "scatterbrained"})[random(3)] +
        " gift-gopheroo");

    set_name(({"gifteroo", "gift-gopheroo", "gopheroo"}));
    add_adj(explode(short(), " ") - ({"but", "gift-gopheroo"}));
    set_race_name("gopheroo");

    set_long("This is a Calian gopheroo trained to deliver" +
        " small packages. He is wearing a little" +
        " red and green striped stocking cap and a pair" +
        " of snowshoes that enable him to get around in the" +
        " adverse terrain he encounters on some of" +
        " his travels. Trained gopheroos are fairly" +
        " rare, as their relentless but misguided efforts often" +
        " lead to their - as an old Calian proverb puts it - 'milking" +
        " the cow at both ends.' Still, regardless of the" +
        " meandering route they take, you can generally count on" +
        " them to complete their tasks... eventually.\n");

    add_item(({"snowshoe", "snowshoes"}),
        "Some folks say a gopheroo on snowshoes is a" +
        " 'snowpheroo,' but they're mostly the kind who live way up" +
        " in the hills and marry their cousins.\n");

    add_item(({"cap", "stocking cap"}),
        "It fits the gopheroo's pointy little head perfectly!\n");

    /*
     *  PROPERTIES    
     */

    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_WEIGHT, 5500);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);
    add_prop(LIVE_I_MAX_EAT, 1000000);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_I_ATTACK_THIEF, 0);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);

    /*
     *  Note that the following LIVE property processes the string value by 
     *  appending it to the object's short() description. The OBJ properties
     *  that follow only display the string value as typed.    
     */

    add_prop(LIVE_M_NO_ACCEPT_GIVE,
        " backs away from you and shakes his" +
        " head from side to side so rapidly that for a moment it's" +
        " just a blur. Obviously he is trained not to" +
        " accept gifts from strangers!\n");

    /*
     *  The following warning is adapted from the film "Twelve Monkeys."    
     */

    add_prop(OBJ_M_NO_ATTACK,
        "An apparition of a scroll floating in midair suddenly" +
        " flashes before your eyes, and before it fades away" +
        " you manage to read:\n\n" +
        "           This gopheroo is the trained pet\n" +
        "        of the Wizards of Calia. Anyone caught\n" +
        "       impeding his progress in any way will be\n" +
        "          shaved, sterilized, and destroyed.\n" +
        "                   Happy holidays!\n\n" +
        "You decide not to bother the " + short() + ".\n");

    add_prop(OBJ_M_NO_GET,
        "The " + short() + " scampers around you, dodging and" +
        " weaving to avoid your attempts to pick him up. He seems" +
        " quite happy to play 'keep-away' with you indefinitely!\n");

    set_alignment(0);
    set_stats(({30, 30, 30, 30, 30, 30}));

    /*
     *  EMOTES    
     */

    add_act("smell third thing curiously");
    add_act("smell second thing curiously");
    add_act("peer third thing curiously");
    add_act("peer second thing curiously");
    add_act("confuse thing");
    add_act("confuse second thing");
    add_act("eyebrow third thing");
    add_act("eyebrow second thing");
    add_act("bounce thing");
    add_act("pinch kender bottom");
    add_act("lick third thing affectionately");
    add_act("lick second thing affectionately");
    add_act("emote scratches behind his ear with his hind foot.");
    add_act("emote stares up at you with his beady little eyes.");
    add_act("emote chirps: nik nik nik nik nik nik!");

    add_act("emote trips as his snowshoes get tangled up and falls" +
        " flat on his face!");

    add_act("emote gawks at you with mouth agape, as if" +
        " he'd never seen anything quite like you before.");

    add_act("emote walks around sniffing and peering at everything," +
        " even - it seems - things that aren't really here.");

    add_act("emote ruffles his fur all over, making himself look" +
        " like a big powderpuff.");

    add_act("emote ambles around your legs in a" +
        " figure-eight pattern, nearly tripping you.");

    add_act("emote rolls onto his back and moos like a" +
        " drunken cow: moo, mooooo, mooo-OOO-ooo-OOO!");

    add_act("emote stands up on his hind legs for a moment," +
        " then falls over with a soft thud.");

    add_act("emote sounds as if he is snoring, although he" +
        " is sitting upright and staring straight ahead.");

    add_act("emote straightens his striped stocking cap" +
        " and presses it firmly down on his head so it" +
        " will stay put.");

    add_act("emote swaggers around with a big grin on his" +
        " furry little face, obviously relishing" +
        " his yuletide duties.");

    add_act("emote blinks his beady little eyes and peers" +
        " around quizzically as if he is supposed to do" +
        " something important and can't remember what it is.");

    add_act("emote starts to go in one direction, then turns" +
        " around, starts in the opposite direction, then" +
        " stops and quickly turns around several more times," +
        " making himself too dizzy to go anywhere.");

}
