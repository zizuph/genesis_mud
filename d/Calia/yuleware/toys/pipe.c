// OBJECT:  pipe (bubble)

    /* Calia Domain

    HISTORY

    [99-11-22] Created by Uhclem from [D:\CALIA\YULEWARE\TOYS\PIPE.DOC].

    PURPOSE

    A toy to be found under the Christmas tree in the domain office in the
    Tower of Realms. */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <options.h>
#include <math.h>

// GLOBAL VARIABLES

object Global_Adverbs = find_object("sys/global/adverbs");

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_short("porcelain bubble pipe");
    set_name("pipe");
    add_name("toy");
    add_adj("bubble");
    add_adj("porcelain");

    set_long("The bubble pipe is made of fine white porcelain with" +
        " a long stem and a smooth round bowl. It looks like" +
        " there's plenty of soapy water inside it, so you should" +
        " be able to blow bubbles as often as you want.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 10);

    add_prop(OBJ_M_NO_SELL, "You think you can get some money" +
        " for that little pipe? You must have been inhaling!\n");

    /*
     *  ITEMS    
     */

    add_item(({"porcelain", "white porcelain", "water", "soapy water"}),
        "The white porcelain is crafted into an ingenious shape" +
        " that holds a practically limitless supply of soapy" +
        " water but won't let you accidentally spill or remove" +
        " any of it.\n");

    add_item(({"stem", "long stem", "bowl", "round bowl"}),
        "It looks like the bowl and stem will give you the" +
        " ability to blow bubbles of various shapes and sizes -" +
        " it all depends on how you blow!\n");

}

// FUNCTIONS

// Function:  blow_bubbles

/*

Purpose:  blow a variety of bubbles

Arguments:  string containing 'bubbles' or 'bubble' and optional adverb.

Returns:  0/1

*/

int
blow_bubbles(string str)

{

    object tp = this_player();

    string *sheens = ({"shiny", "clear", "lustrous", "sparkling", "glowing"});
    string *sizes = ({"small", "medium", "large", "huge", "enormous"});
    string *shapes = ({"round", "rotund", "pulsating", "spinning", "wobbly"});
    string *sets = ({"dozens", "streams", "clumps", "clusters", "swarms"});

    string *singles =
        ({"rises and bursts in just a few seconds.",
        "hovers for a few seconds then drifts out of sight.",
        "circles around your head a few times before it pops.",
        "repeatedly darts and zig-zags in a strange pattern" +
        " before it finally pops.",
        "drifts in lazy spirals as it rises above your" +
        " head, then pauses motionless for a short time" +
        " before it bursts."});

    string *multiples =
        ({"collide and pop rapidly.",
        "intertwine and swirl before popping.",
        "spread out in all directions and disappear.",
        "rise in graceful spirals as they gradually break and disappear.",
        "swirl in all directions, then suddenly and mysteriously implode" +
        " all at once with a loud 'pop!'"});

    string *words;
    string adverb = "";
    string how = "";

    if (!stringp(str)) /* Player did not specify what to blow. */

    {

        notify_fail("Blow what?\n");
        return 0;

    }

    words = explode(str, " ");

    if (sizeof(words) > 1)

    {

        adverb = Global_Adverbs->full_adverb(words[sizeof(words)-1]);
        str = implode(words[0..(sizeof(words)-2)], " ");

    }

    if (adverb == "")

    {

        if (wildmatch("bub*", str) || wildmatch("a bub*", str))

        {

            write("Blow bubble[s] how?\n");
            return 1;

        }

        else

        {

            notify_fail("Blow bubble[s] how?\n");
            return 0;

        }

    }

    if (adverb != ".") how = " " + adverb + ".";
    else how = adverb;

    switch (str)

    {

        case "bubble":
        case "a bubble":

        say(QCTNAME(tp) + " puts a porcelain bubble" +
            " pipe to " + tp->query_possessive() + " lips and" +
            " blows a " + sheens[NAME_TO_RANDOM(adverb, 1000, 5)] +
            " " + sizes[NAME_TO_RANDOM(adverb, 2000, 5)] +
            " " + shapes[NAME_TO_RANDOM(adverb, 3000, 5)] +
            " bubble that " + singles[NAME_TO_RANDOM(adverb, 5000, 5)] + "\n");

        write("You blow a bubble" + how +
            " The " + sheens[NAME_TO_RANDOM(adverb, 1000, 5)] +
            " " + sizes[NAME_TO_RANDOM(adverb, 2000, 5)] +
            " " + shapes[NAME_TO_RANDOM(adverb, 3000, 5)] +
            " bubble " + singles[NAME_TO_RANDOM(adverb, 5000, 5)] + "\n");

        return 1;
        break;

        case "bubbles":

        say(QCTNAME(tp) + " puts a porcelain bubble" +
            " pipe to " + tp->query_possessive() + " lips and" +
            " blows " + sets[NAME_TO_RANDOM(adverb, 1000, 5)] +
            " of " + sheens[NAME_TO_RANDOM(adverb, 2000, 5)] +
            " " + sizes[NAME_TO_RANDOM(adverb, 3000, 5)] +
            " " + shapes[NAME_TO_RANDOM(adverb, 5000, 5)] + " bubbles" +
            " that " + multiples[NAME_TO_RANDOM(adverb, 7000, 5)] + "\n");

        write("You blow bubbles" + how +
            " The " + sets[NAME_TO_RANDOM(adverb, 1000, 5)] +
            " of " + sheens[NAME_TO_RANDOM(adverb, 2000, 5)] +
            " " + sizes[NAME_TO_RANDOM(adverb, 3000, 5)] +
            " " + shapes[NAME_TO_RANDOM(adverb, 5000, 5)] + " bubbles" +
            " " + multiples[NAME_TO_RANDOM(adverb, 7000, 5)] + "\n");

        return 1;
        break;

        default:

        notify_fail("You can only blow a bubble or bubbles with this pipe.\n");
        return 0;

    }

}

// Function:  init

/*

Purpose:  define commands available in this object (called by system when
object enters a player's inventory)

Arguments:  none

Returns:  nothing

*/

void
init()

{

    ::init();
    add_action(blow_bubbles, "blow");

}
