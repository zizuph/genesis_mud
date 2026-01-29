/*
 * beach_base.c
 *
 * Basefile for the small beaches of the Silvanesti forest area near
 * Kurinost.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Genesis/gems/gem.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit OR_FILE
inherit HERBSEARCHNEW

// D E F I N I T I O N S
#define CREATE "create_kurinost_room"
#define RESET  "reset_kurinost_room"
#define AMBER  "/d/Genesis/gems/obj/amber"
#define CORAL  "/d/Genesis/gems/obj/coral"

// G L O B A L   V A R S
int gItems = 0, gMaxItems = 3;
string gBeach_desc;
string *herbs = HERB_MASTER->query_herbs( ({ "beach", }) );

// P R O T O T Y P E S
public string show_me_time_of_day();
public string search_beach(object who, string what);

// P U B L I C   F U N C T I O N S
/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);

    set_searched(random(2));

    // Need to update the number of items that can be found on the
    // beach.
    if (gItems < gMaxItems)
    {
        gItems += random(3) + 1;
    }

    if (gItems > gMaxItems)
    {
        gItems = gMaxItems;
    }
}


/*
 *  FUNCTION : enter_inv
 *  Arguments: objects, what entered and from where?
 *  Returns  : void
 * 
 *  Start room tells when someone enters the room.
 *
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        start_room_tells();
    }
}


/*
 *  FUNCTION : generate_cliffs
 *  Arguments: string - beach_desc
 *  Returns  : void
 * 
 *  Generates the descriptions of the cliffs.
 *  Adds items to examine and produces some bushes/cacti plants to
 *  harvest for food.
 *
 */
public void
generate_beach(string beach_desc)
{
    // beach_desc holds information about the wavefront and where
    // you can go from here.
    gBeach_desc = beach_desc;

    // Nouns that can always be examined:
    add_item(({ "cliff", "cliffs", "steep cliff", "steep cliffs",
        "dark wall", "wall", "granite wall" }),
        "Rising like a dark grey wall that reaches almost a " +
        "hundred meters towards the sky in some places, the steep " +
        "granite cliffs of the coast are almost barren with only " +
        "a few small bushes and cactus plants growing on the " +
        "cliffside.\n");
    add_item("granite", "Glistening in many places with moisture, " +
        "the dark grey wall of this cliffside is made of hard and " +
        "tough granite. Rising in tall structures of varying " +
        "heights, the granite is marred in most places by wind " +
        "and water. Appearing dark and foreboding, the dark grey " +
        "granite is covered in spots by small patches of moss.\n");
    add_item(({ "moss", "patch of moss", "patches of moss" }),
        "Like a small soft green blanket, you notice several and " +
        "often large patches of moss covering the moist areas on " +
        "the granite cliff.\n");
    add_item(({ "shore", "coast" }), "Stretching like a dark " +
        "wall, the cliffs of the shore disappear far away to the " +
        "northwest and a short way to the east. The shore is " +
        "rugged with large rocks sticking out of the water in " +
        "many places. Right here, however, the shore has widened " +
        "into a small beach, covered in dark grey sand.\n");
    add_item(({ "water", "bay", "bay of balifor" }), "Dark and " +
        "deep, the Bay of Balifor has a dark shade of blue with " +
        "wavetops whipped to foam here and there, as the strong " +
        "ocean wind blows across the water.\n");
    add_item(({ "sea", "ocean" }), "Strong ocean winds tug at you " +
        "as you gaze out over the bay. Dark and deep, the Bay of " +
        "Balifor stretches to the horizon far to the north and " +
        "northwest. Surrounding the dark blue waters of the bay " +
        "is the rugged shoreline with tall cliffsides. Wavetops " +
        "are whipped to foam here and there, as the strong ocean " +
        "winds blow across the water.\n");
    add_item(({ "beaches", "small beaches" }), "Other than the " +
        "small beach you are currently standing on, you see no " +
        "beaches. Standing quite close to the steep cliffs, your " +
        "view of the nearby area is rather limited. You mostly " +
        "see steep cliffs and the bay of Balifor.\n");
    add_item(({ "view", "spectacular view", "nice view" }),
        "A strong ocean wind tugs at you as you gaze out over " +
        "the sea. From down here on the beach you have a " +
        "spectacular view of the towering dark granite cliffs of " +
        "the coast. Reaching as high as one hundred meters in " +
        "some places, it towers like a dark wall before you.\n");
    add_item(({ "seagull", "seagulls", "white seagull",
        "white seagulls", "life", "bird", "birds" }),
        "Crying seagulls can be heard from all directions and " +
        "often a lone white seagull appears to be suspended in " +
        "midair above the dark granite cliff. Rising winds from " +
        "the ocean keep the seagull high in the air. Looking " +
        "closer, you see that the birds are nested in small " +
        "colonies, resting in their nests on the sides of the " +
        "cliffs.\n");
    add_item(({ "sky", "light" }), show_me_time_of_day);
    add_item(({ "patch", "patch of soil", "patches",
        "patches of soil", "plants", "soil", "dirt" }),
        "Barely visible here and there on the granite cliffs are " +
        "patches of soil, allowing small bushes and low cactus " +
        "plants to grow in this inhospitable area.\n");
    add_item(({ "cactus", "cactus plant", "low cactus", "plant",
        "wide cactus", "low cactus plant", "wide cactus plant" }),
        "Scattered about on the steep sides of the cliffs are " +
        "low, wide cactus plants and small bushes.\n");
    add_item(({ "bush", "bushes", "small bush", "small bushes",
        "caper bush", "small caper bush" }), "Scattered about " +
        "on the steep sides of the cliffs are low, wide " +
        "cactus plants and small bushes.\n");
    add_item(({ "rocks", "larger rocks" }), "Coarse grey sand " +
        "cover most of the small beach, but here and there are " +
        "larger rocks, all of the same dark grey colour as the " +
        "sand, but many of them seem covered in small fungi or " +
        "have a small plant growing next to it.\n");

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
        ONE_OF(herbs) }), ({ "rocks", "larger rocks" }), 5);

    add_cmd_item(({ "cliff", "cliffs" }), ({ "climb" }),
        "Appearing much too steep, you are unable to climb the " +
        "cliffside from this part of the beach.\n");

    // Calls to add_search will have stime increased by +5 seconds.
    // searching the sand takes 5 seconds.
    add_search(({"sand", "beach", "small beach"}), 0,
        "search_beach", 1);

    // As we need to be able to clone items from here, lets set up IDs.
    setuid();
    seteuid(getuid());
}


/*
 *  FUNCTION : generate_season
 *  Arguments: none
 *  Returns  : string - description.
 * 
 *  Generates a string of text for the long_description based on the
 *  time of year on Krynn.
 *
 */
public string
generate_season()
{
    switch (GET_SEASON)
    {
    case SPRING:
        return "Gentle winds from the north carry the sweet scent " +
            "of spring to the coast.";

    case SUMMER:
        return "Warm ocean wind carries the sweet scent of " +
            "summer to the shore, where scores of seagulls tend " +
            "their nests in the high cliffs.";

    case AUTUMN:
        return "Filled with clouds, the sky is cool and grim, " +
            "marking the coming of fall.";

    case WINTER:
        return "A chilling winter wind rolls over the beach and " +
            "all is quiet, except for the distant cries of a few " +
            "seagulls.";
    }
}


/*
 *  FUNCTION : show_me_day
 *  Arguments: none
 *  Returns  : string - description.
 * 
 *  Generates a description based on the time of day on Krynn.
 *
 */
public string
show_me_day()
{
    string night_desc = "Pale ";

    if (GET_TIMEOFDAY == TOD_NIGHT)
    {
        if (GET_MOON_PHASE(SOLINARI) == "full" ||
            GET_MOON_PHASE(LUNITARI) == "full")
        {
            night_desc = "Dominated by the light of the full ";

            if (GET_MOON_PHASE(SOLINARI) == "full")
            {
                night_desc += "silver moon, Solinari, pale ";
            }
            else
            if (GET_MOON_PHASE(LUNITARI) == "full")
            {
                night_desc += "red moon, Lunitari, pale ";
            }
        }

        night_desc += "reddish light from the two moons ripple " +
            "across the Bay of Balifor, bathing the beach in a " +
            "ghostly light.";

        if (GET_MOON_PHASE(SOLINARI) == "full" &&
            GET_MOON_PHASE(LUNITARI) == "full")
        {
            night_desc = "Dominating the night sky, the two full " +
                "moons Solinari and Lunitari, spread pale reddish " +
                "light out across the Bay of Balifor, bathing the " +
                "beach in a bright ghostly light.";
        }

        return night_desc;
    }

    switch (GET_TIMEOFDAY)
    {
    case TOD_DAWN:
        return "Splashing the morning sky with brilliant hues, " +
            "the sun is slowly rising from its rest below the " +
            "horizon.";

    case TOD_DAY:
        return "Resting high in the sky, the bright sun throws " +
            "its rays down across the small beach.";

    case TOD_TWILIGHT:
        return "Deep reddish hues cross the evening sky as the " +
            "sun sets beneath the horizon.";
    }
}


/*
 *  FUNCTION : show_me_time_of_day
 *  Arguments: none
 *  Returns  : string - description
 * 
 *  Returns a description of the sky and time of day.
 *
 */
public string
show_me_time_of_day()
{
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        return "Night blankets the coast. Rising like tall black " +
            "giants all around you, the granite cliffs appear " +
            "very daunting. " + show_me_day() + "\n";

    case TOD_DAWN:
        return show_me_day() + " Reflected sunlight plays across " +
            "the waves of the ocean.\n";

    case TOD_DAY:
        return show_me_day() + " Reflected sunlight plays brightly " +
            "across the waves of the ocean.\n";

    case TOD_TWILIGHT:
        return show_me_day() + " Calm and foreboding, the granite " +
            "cliffs around you slowly vanish into the growing " +
            "darkness.\n";
    }
}


/*
 *  FUNCTION : setup_tells
 *  Arguments: none
 *  Returns  : void
 * 
 *  Sets the basic tells of the rocky shores of Silvanesti.
 *
 */
public void
setup_tells()
{
    set_tell_time(360);

    add_tell("Harsh wailings from nearby seagulls carry over the " +
        "noise of the ocean.\n");
    add_tell("Fluttering of wings mixed with squawking calls is " +
        "heard as a group of seagulls take to the skies.\n");
    add_tell("Far above a lone seagull seems to be suspended in " +
        "the air, floating on the rising wind from the ocean.\n");
    add_tell("Rocks loosen from the granite cliffs a few hundred " +
        "meters northwest of you and crash into the ocean below.\n");
    add_tell("Carried forward by the strong ocean winds, a lone " +
        "ship crosses the Bay of Balifor several kilometers north " +
        "of the coast.\n");
}


/*
 *  FUNCTION : show_me_long_desc
 *  Arguments: none
 *  Returns  : string - long description of the room.
 * 
 *  Returns the current longdescription based on season and
 *  pre-generated strings from cliffs and path.
 *
 */
public string
show_me_long_desc()
{
    return gBeach_desc + " " + show_me_day() + " Coarse, dark " +
        "grey sand covers the small and narrow beach. " +
        generate_season() + "\n";
}


/*
 *  FUNCTION : show_items
 *  Arguments:
 *  Returns  :
 * 
 *  Returns a text based on the number of items that can be found
 *  on the beach.
 *
 */
public string
show_items()
{
    if (!gItems || TP->query_skill(SS_AWARENESS) < 10)
    {
        return "";
    }
    else
    {
        return "As your eyes search over the sand on the beach, " +
            "you realize there is something sticking out of the " +
            "sand. ";
    }
}


/*
 *  FUNCTION : search_beach
 *  Arguments: who  - who searched the beach.
 *             what - what did the player search for?
 *  Returns  : string - a description of what happened.
 * 
 *  Search the sand on the beach.
 *
 */
public string
search_beach(object who, string what)
{
    if (!gItems)
    {
        // No items to be found at the moment.
        say(QCTNAME(who) + " searches around in the coarse grey " +
            "sand, but does not find anything.\n");
        return "You search around in the coarse grey sand, but " +
            "find nothing.\n";
    }

    gItems--;

    switch (random(10))
    {
        case 0..6:
            // Give player a piece of driftwood.
            say(QCTNAME(who) + " searches around in the coarse " +
                "grey sand and finds a piece of driftwood!\n");

            clone_object(RSOBJS + "driftwood")->move(who, 1);

            return "You search around in the coarse grey sand and " +
                "manage to find a piece of driftwood!\n";

        case 7..9:
            // A rare item has been found! See below.
            break;
    }

    switch (random(10))
    {
        case 0..1:
            // Give player a rusty old fishing knife.
            say(QCTNAME(who) + " searches around in the coarse " +
                "grey sand and finds an old rusty knife!\n");

            clone_object(RSWEAPON + "rusty_knife")->move(who, 1);

            return "You search around in the coarse grey sand and " +
                "manage to find an old rusty fishing knife!\n";

        case 2..6:
            // Give player a nice seashell.
            say(QCTNAME(who) + " searches around in the coarse " +
                "grey sand and finds a small seashell!\n");

            clone_object(RSOBJS + "seashell")->move(who, 1);

            return "You search around in the coarse grey sand and " +
                "manage to find a nice seashell!\n";


        case 7..8:
            // Give player a small amber gemstone.
            say(QCTNAME(who) + " searches around in the coarse " +
                "grey sand and finds a small stone!\n");

            clone_object(AMBER)->move(who, 1);

            return "You search around in the coarse grey sand and " +
                "manage to find a small yellow amber!\n";


        case 9:
            // Give player a small coral gemstone.
            say(QCTNAME(who) + " searches around in the coarse " +
                "grey sand and finds a piece of coral!\n");

            clone_object(CORAL)->move(who, 1);

            return "You search around in the coarse grey sand and " +
                "manage to find a piece of pink coral!\n";
    }
}
