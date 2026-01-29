// OBJECT:  guelph

    /* Calia Domain

    HISTORY

    [99-12-17] Created from [D:\CALIA\YULEWARE\FRUITS\GUELPH.DOC] by Uhclem.

    PURPOSE

    It's not really a fruit, it's a vegetable, but I include it in the fruits
    directory since it comes from the palace tree, source of many fine glazed
    fruits.  This particular object is just a joke, an unpleasant item that
    somebody who doesn't care much for yule celebrations hid in the tree.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/food";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include "defs.h"

// FUNCTIONS

// Function:  query_recover()

/*

Purpose:  this vegetable does not deserve to be recovered.

Arguments:  none.

Returns:  0.

*/

int
query_recover()

{

    return 0;

}

// Function:  hit_the_ground()

/*

Purpose:  provide a message to the room when this object is dropped.

Arguments:  none.

Returns:  nothing.

*/

void
hit_the_ground()

{

    string ob_name = LANG_THESHORT(this_object());
    string my_pronoun;
    string s;

    if (!environment()->query_prop(ROOM_I_IS))

    {

        return;

    }

    if (num_heap() == 1)

    {

        s = "s";
        my_pronoun = "it";

    }

    else

    {

        s = "";
        my_pronoun = "they";

    }

    tell_room(environment(), capitalize(ob_name) + " " +
        ({
        "hit" + s + " the ground with a blunt, rubbery" +
        " thud; unfortunately, " + my_pronoun + " survive" + s +
        " the fall.",
        "fall" + s + " to the ground and bounce" + s +
        " a few times before finally sticking in place.",
        "strike" + s + " the ground and stick" + s +
        " immediately like a hunk of fresh raw liver.",
        "ripple" + s  + " and bulge" + s +
        " as " + my_pronoun + " hit" + s + " the ground like" +
        " a heaping handful of room-temperature lard, yet" +
        " " + my_pronoun + " manage" + s + " not to burst" +
        " from the impact. What a pity."
        })[random(4)] + "\n");

}

// Function:  hook_smelled()

/*

Purpose:  add smell characteristics to this object.

Arguments:  none.

Returns:  nothing.

*/

void
hook_smelled()

{

    string *nose_effect =
        ({
        "moves out of the way",
        "closes up",
        "clogs up",
        "refuses to allow any inhalation",
        "ducks into your mouth"
        });

    object tp = this_player();
    string tp_pronoun = tp->query_pronoun();
    int n = random(sizeof(nose_effect));

    write("Your nose instinctly " + nose_effect[n] + " as you" +
        " bring the guelph close to your face. Maybe it" +
        " knows something you don't!\n");

    say(QCTNAME(tp) + "'s nose instinctly " + nose_effect[n] +
        " as " + tp_pronoun + " brings the guelph close" +
        " to " + tp->query_possessive() +
        " face. Maybe it knows something " + tp_pronoun +
        " doesn't!\n");

}

// Function:  enter_env(ob_to, ob_from)

/*

Purpose:  called by system when this object moves to a new environment; used
here to detect when fruit is dropped.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    int n;

    ::enter_env(ob_to, ob_from);

    if (ob_to->query_prop(ROOM_I_IS) &&
        (query_verb() == "drop"  || query_verb() == "$drop"))

    {

        set_alarm(0.0, 0.0, hit_the_ground);

    }

}

// Function:  special_effect(num)

/*

Purpose:  add unpleasant effect to eating a guelph.

Arguments:  number of guelphes (pronounced "guelphies") consumed.

Returns:  nothing.

*/

void
special_effect(int num)

{

    object tp = this_player();
    string tp_pronoun = tp->query_pronoun();
    string sequence;
    int n;

    for (n = 1; n <= num; n += 1)

    {

        if (num > 1)

        {

            sequence = " " + LANG_WORD(n) + " ";

        }

        else

        {

            sequence = " ";

        }

        write(
            ({
            "The" + sequence + "guelph is",
            "You approach the" + sequence + "guelph with" +
            " trepidation; it turns out to be",
            "You gnaw through the" + sequence + "guelph as best" +
            " you can and find it",
            "The question 'is this meal necessary?' is uppermost" +
            " in your mind as you tackle the" + sequence + "guelph. It's",
            "You plow through the" + sequence + "guelph, and if" +
            " you were hoping this one would be an improvement," +
            " you are sorely disappointed: it's",
            "Undaunted, you sink your teeth into" +
            " the" + sequence + "guelph and find it"
            })[(n - 1) % 6] +
            " " +
            ({"gummy", "sticky", "squishy", "rubbery"})[random(4)] +
            " yet " +
            ({"fibrous", "stringy", "brittle", "crumbly"})[random(4)] +
            ", " +
            ({"chalky", "dry", "spongy", "parched"})[random(4)] +
            " yet " +
            ({"gelatinous", "viscous", "slimy", "greasy"})[random(4)] +
            ", full of " +
            ({
            "quaint red and green bits that seem to" +
            " have been culled from old fruitcakes",
            "spiderweb-like threads that get snagged" +
            " between your teeth and cling to the back of your" +
            " throat as you swallow",
            "little sacs filled with thick liquid that splatters" +
            " all over the inside of your mouth as you chew",
            "adhesive sap that makes chewing difficult and" +
            " swallowing close to impossible",
            "gritty pulp that audibly grinds against your" +
            " teeth and scrapes your palate, tongue, and throat"
            })[random(5)] +
            ", and " +
            ({
            "rather than tasting like a vegetable, it punishes" +
            " your palate with sensations more appropriate to",
            "the flavor conjures up disturbingly" +
            " pungent impressions of",
            "while the texture is sufficiently awful in" +
            " itself, the equally offensive flavor could easily" +
            " pass for an aged extract of",
            "the exquisite burning sensation it leaves in your" +
            " throat is accompanied by a lingering" +
            " aftertaste suggestive of",
            "it releases - nay, unleashes - a flood of" +
            " outlandish flavors and scents that summon vague" +
            " recollections from the recesses of your mind, not of" +
            " any food or drink, but of"
            })[random(5)] +
            " "  +
            ({
            "sawdust",
            "iron filings",
            "boot leather",
            "pine tar",
            "bird droppings"})[random(5)] +
            " and " +
            ({
            "lamp oil",
            "lye soap",
            "furniture polish",
            "swamp water",
            "pond scum"})[random(5)] +
            ".\n");

        say(QCTNAME(tp) + " gags " +
            ({
            "violently",
            "savagely",
            "furiously",
            "viciously",
            "ferociously",
            "gruesomely",
            "hideously",
            "frightfully",
            "repulsively",
            "sensationally"
            })[random(num) % 10] + " as " + tp_pronoun +
            " eats the" + sequence + "guelph.\n");

    }

}

// OBJECT DEFINITION

void
create_food()

{

    object *my_clones;

    /*
     *  DESCRIPTION    
     */

    set_name(({"guelph", "vegetable"}));
    set_pname(({"guelphs", "guelphes", "vegetables"}));
    add_adj(({"dull", "grey", "gray"}));
    set_short("dull grey guelph");

    set_long("This is the infamous guelph of Calia, a vegetable" +
        " largely - and justifiably - ignored in both" +
        " peasant and gourmet cuisine. Since most folks won't" +
        " eat one, the little that's known of them comes from" +
        " legends. The usual story is that it won't kill you, but" +
        " its dull grey skin and unsavory aroma hardly invite" +
        " you to verify that yourself.\n");

    add_item(({"skin", "grey skin", "dull grey skin"}),
        "The skin is covered with prickles and hairs, beneath which" +
        " you can see a fibrous, vein-covered surface.\n");

    add_item(({"prickle", "prickles"}),
        "They look sharp, and there's plenty of them. Perhaps" +
        " they're here to prevent you from spitting out the" +
        " guelph once you've started to eat it.\n");

    add_item(({"hair", "hairs"}),
        "They remind you of a goblin's back. An" +
        " old, unwashed, battle-scarred goblin's back.\n");

    add_item(({"surface", "vein", "veins", "vein-covered surface"}),
        "Hmmm... are they veins, or are they just a little too wiggly" +
        " to be a natural part of this vegetable?\n");

    add_item(({"aroma", "unsavory aroma"}),
        "Yes, it's natural, perhaps even prudent, to try to" +
        " examine the aroma just by looking, but your eyes aren't" +
        " that good. It seems you'll have to smell it.\n");

    /*
     *  PROPERTIES    
     */

    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 550);

}
