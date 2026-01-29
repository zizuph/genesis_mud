/* 
 * There is no outdoor room for the UTOA. Not uploaded.
 * Mortis 10.2014
 */
#pragma strict_types

#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include CLOCKH

/* Inherit the Ansalon room */
inherit OR_FILE
inherit TDIR + "smell_world";
inherit TDIR + "palanthas_alley";

#define CREATE "create_palan_room"
#define RESET  "reset_palan_room"

public void        init();
public int         do_smell(string arg);
public int         do_alley(string arg);

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * whether or not the room should be reset.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
    {
        return 1;
    }
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
    ITEM(({"marble", "rock", "stone"}), "The marble used for building in "
    + "Palanthas is translucent appearing almost white in the sun.\n");

    ITEM(({"road", "roads", "street", "streets"}), "The road is paved "
    + "with footlong blocks of translucent marble. It connects with "
    + "alleys and side streets between some of the buildings.\n");

    ITEM(({"alley", "alleys", "side street", "side streets"}), "Smaller "
    + "streets and alleys lead into the shadows between the great "
    + "buildings. You can take one with the alley command.\n");

    ITEM(({"block", "blocks"}), "The blocks of marble used for the top layer of "
    + "the roads in Palanthas are cut from the same translucent marble used throughout "
    + "the city. These blocks show few signs of chisel work, and the marble is so "
    + "translucent that the red clay bricks beneath give it a rosy hue.\n");

    ITEM(({"lamps", "street lamps", "lamp", "street lamp", "glow",
        "yellow glow", "lamp posts", "lamp post"}), "@@get_time_item@@");

    ITEM(({"building", "buildings"}), "Great and very old marble buildings "
    + "fill the inner city of Palanthas some rising three to four stories. "
    + "They share a common architechture, a distinguishing feature of which "
    + "is a band of chiseled reliefs near the top of some and at the borders "
    + "between stories in others. A good many especially near the palatial "
    + "plaza bear gargoyles at their top corners just below the roofs.\n");

    ITEM(({"band", "bands", "relief", "reliefs"}), "Nearly all of the "
    + "buildings in this party of the city are ringed with bands of "
    + "the chiseled images of citizens, warriors, towers and castles, "
    + "fantastic beasts and dragons, and events from the city's history. "
    + "Others bear popular knights of Solamnia and their deeds which "
    + "seem to be popular.\n");

    ITEM(({"gargoyle", "gargoyles"}), "A good many of the older buildings "
    + "bear gargoyles at the corners of their rooftops, created long ago "
    + "it is said to ward off spirits seeking to do harm. Though very old "
    + "they are in sufficient condition to appraise the skill which went "
    + "into their finely chiseled details. All the ones you've seen "
    + "are all generally fat, squating, and winged with long recurving "
    + "claws, flat wide-mouthed faces, and dull drooping eyes.\n");
    
    ITEM(({"mountains", "peaks"}), "High mountains ring the city save for the "
    + "southeast pass to the High Clerist's tower and the bay of Branchala to "
    + "the north.\n");

    ITEM(({"white tower", "tower"}), "The Tower of Lord Amothus Palanthas "
    + "rises a hundred feet if not more above the palace to the east. "
    + "Polished white marble finishes the walls and crenellations of the "
    + "tower. The view from the top is said to be the most splendid in the "
    + "city.\n");

    ITEM(({"squat tower", "square tower", "tower of arms"}), "The Tower of "
    + "Arms rises above you from a thick wood here in the merchants quarter. "
    + "It is the headquarters of the Palanthian Guard, also known as the "
    + "constabulary. It is a five-story, square tower of great marble "
    + "blocks with reinforced edges and a wide open, crenellated top.\n");

    ITEM(({"dark tower", "grey tower", "tower of high sorcery"}),
      "To your south, set deep in the center of a grove of trees here in the "
    + "merchants quarter rises a tower of great and dark grey blocks of "
    + "stone. At its top are visible from this distance several pinnacles "
    + "from which no banners fly. Its shadow somehow spreads across the "
    + "entire darkened grove.\n");

    ITEM(({"hue", "hues", "sunrise"}), "@@get_dawn_hue@@" + "\n");

    ITEM(({"smells", "cooking", "coffee", "breeze"}), 
        "You would get more from that if you used your nose.\n");

    ITEM(({"crowd", "crowds", "people", "shoppers", "citizens"}),
        "@@get_day_crowd@@" + "\n");

    ITEM(({"reveler", "revelers", "reveller", "revellers"}),
        "@@get_night_revel@@" + "\n");

    ITEM(({"streetwasher", "streetwashers", "washer", "washers"}),
        "@@get_morn_streetwashers@@" + "\n");

    ITEM(({"ancient style", "old style"}), "The old style is angular and "
    + "stiff and very official looking with its simplified, unadorned "
    + "lines.\n");
}

public void
init()
{
    ::init();  /* vitally important! never forget this line! */

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect*/
    add_action(do_alley, "alley");
} /* init */


/*
 * Function name:        do_smell
 * Description  :        allow the player to smell the air
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[the] 'air' / 'here' / 'area' [of] [the] [city]"))
    {
        return 0; /* the player used syntax we don't agree with */
    }

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
     *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     */


    smell_world(this_player());
    return 1;
} /* do_smell */

/*
 * Function name:        do_alley
 * Description  :        allow the player to enter a hidden alley
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 *
 */

public int
do_alley(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[n] / [north] / [s] / [south] / [e] / [east] / [w] / [west] / [ne] / [northeast] / [se] / [southeast] / [sw] / [southwest] / [nw] / [northwest]"))
    {
        write("Which alley are you trying to enter?\n");
        return 1; /* the player used syntax we don't agree with */
    }

    palanthas_alley(arg);
    return 1;
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

string get_time_item()
{
    string ilamp;
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    ilamp = "Tall, grey lamp posts are arranged neatly along the streets "
    + "throughout the merchants quarter.  They are unlit now, but at night "
    + "the area is well-lit thanks to them.\n";
    break;

    case TOD_DAY:
    ilamp = "Tall, grey lamp posts are arranged neatly along the streets "
    + "throughout the merchants quarter.  They are unlit now, but at night "
    + "the area is well-lit thanks to them.\n";
    break;

    case TOD_TWILIGHT:
    ilamp = "Tall, grey lamp posts are arranged neatly along the streets "
    + "throughout the merchants quarter.  City lampiers are out with their "
    + "long candlestaves lighting the lamps before darkness falls.\n";
    break;

    case TOD_NIGHT:
    ilamp = "Oil lamps atop tall, grey lamp posts glow yellow combining with "
    + "starlight to evenly illuminate the streets of the merchants quarter "
    + "at night.\n";
    break;
    default:
    break;
    }
    return ilamp;
}

string
get_dawn_hue()
{
    string dhue = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    dhue += one_of_list(({"The sun rising above the eastern peaks spreads "
    + "soft hues of purple fading to orange in the long, wispy clouds "
    + "sailing slowly across the morning sky.", "The sun rising above the "
    + "eastern peaks spreads tendrils of pink and orange fading to purple "
    + "in the long, wispy clouds sailing slowly across the morning sky.",
      "The sun rising above the eastern peaks spreads tendrils of pink "
    + "grey fading to purple in the long, wispy clouds sailing slowly "
    + "across the morning sky."}));
    break;

    case TOD_DAY:
    dhue += "Sunrise has passed. You will have to wait another day.";
    break;

    case TOD_TWILIGHT:
    dhue += "Sunrise has passed. You will have to wait another day.";
    break;

    case TOD_NIGHT:
    dhue += "You'll have to wait a little while longer for the sunrise.";
    break;
    default:
    break;
    }
    return dhue;
}

string
get_day_crowd()
{
    string dcrowd = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    dcrowd += "The crowds have not yet filled the plazas and shopping "
    + "districts though the early shoppers, deliverers, and messengers are "
    + "already going about their business. Watchful constables scan the "
    + "area from the Tower of Arms.";
    break;

    case TOD_DAY:
    dcrowd += "Crowds of people throng the streets, plazas, and shopping "
    + "districts in the midday sun eating, drinking, and looking for the "
    + "best deals to be found in the various quarters and districts. "
    + "Constables mill about the battlements of the Tower of Arms.";
    break;

    case TOD_TWILIGHT:
    dcrowd += "The crowds of people milling about the merchant quarter have "
    + "thinned since afternoon leaving it easier to make your way about the "
    + "streets.  The evening crowd now mixes with the hustling, bustling "
    + "afternoon shoppers though twilight activities seem more prevalent "
    + "elsewhere in the city. Watchful constables scan the horizon from "
    + "the Tower of Arms.";
    break;

    case TOD_NIGHT:
    dcrowd += "Though most people have retired for the night, constables, "
    + "merchants selling wares, and revelers heading for the next tavern "
    + "still make their way through the streets. A constable leaning on "
    + "a spear watches from the Tower of Arms.";
    break;
    default:
    break;
    }
    return dcrowd;
}

string
get_morn_streetwashers()
{
    string swasher = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
    swasher = "Dressed in long, white tunics and stocking caps, the "
    + "streetwashers of Palanthas are a well paid, industrious crew. At "
    + "present they are vigorously sweeping and scrubbing the streets and "
    + "sidewalks, polishing and refilling the lamp posts, and picking up "
    + "litter from the night's revelries.";
    break;

    default:
    swasher = "The streetwashers are only out at daybreak.";
    break;
    }
    return swasher;
}

string
get_night_revel()
{
    string drevel = "";
 
    switch(GET_TIMEOFDAY)
    {
    case TOD_TWILIGHT:
    drevel += "There won't be anymore revelers out this early";
    break;

    case TOD_NIGHT:
    drevel += "Having drinks and socializing is a common pasttime in the "
    + "palatial plaza and other districts but not so much here though a few "
    + "merchants and common citizens pass through here on their way to "
    + "various inns and taverns.  A few shoppers are out taking advantage "
    + "of the shops that never close.";
    break;
    
    default:
    drevel += "There aren't any revelers left.";
    break;
    }
    return drevel;
}