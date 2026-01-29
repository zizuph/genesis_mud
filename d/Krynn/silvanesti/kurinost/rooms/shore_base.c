/*
 * shore_base.c
 *
 * Basefile for the rocky shores of the Silvanesti forest area near
 * Kurinost.
 *
 * Copyright (C): Kellon, november 2010
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
#include "local.h"

// I N H E R I T E D   F I L E S
inherit OR_FILE
inherit HERBSEARCHNEW

// D E F I N I T I O N S
#define CREATE "create_kurinost_room"
#define RESET  "reset_kurinost_room"

// G L O B A L   V A R S
status gBush = 0, gCactus = 0;
status *gClimb_dir;
int gBerries, gMaxberries;
string gHeight, gPath_desc, gCliff_desc, gVegetation_desc;
string *gExit_desc;
string *herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );

// P R O T O T Y P E S
public int climb_cliff(string arg);
public int pick_berries(string arg);
public string show_me_time_of_day();

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

    KURINOSTMAP;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);

    if (gBush)
    {
        gBerries += SETCAPERRESET;
    }
    else
    if (gCactus)
    {
        gBerries += SETPEARRESET;        
    }

    if (gBerries > gMaxberries)
    {
        gBerries = gMaxberries;
    }

    set_searched(0);
}


/*
 *  FUNCTION : init
 *  Arguments: none
 *  Returns  : void
 * 
 *  Add some actions to this area.
 *
 */
public void
init()
{
    ::init();

    ADD(climb_cliff, "climb");
    ADD(pick_berries, "pick");
    ADD(pick_berries, "gather");
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
 *  FUNCTION : show_me_berries
 *  Arguments: none
 *  Returns  : string - description of number of berries.
 * 
 *  Returns a string with a description of the number of
 *  capers/cones visible to be picked.
 *
 */
public string
show_me_berries()
{
    string desc = "";
    string fruit;

    if (gBush)
    {
        desc = "The small green capers appear to grow on a shrubby " +
            "bush nearby. Giving the bush";
        fruit = "capers";
    }
    else
    if (gCactus)
    {
        desc = "The purple-red cactus pears grow on a low cactus " +
            "plant nearby. Giving the cactus";
        fruit = "prickly pears";
    }

    desc += " a quick look, you estimate that it holds ";

    switch (gBerries)
    {
    case 1..4:
        desc += "only a few";
        break;

    case 5..10:
        desc += "several";
        break;

    case 11..20:
        desc += "many";
        break;

    case 0:
    default:
        desc += "no";
    }

    desc += " " + fruit + " that can be picked or gathered at " +
        "the moment.\n";

    return desc;
}


/*
 *  FUNCTION : set_height_above_ocean
 *  Arguments: string - height in meters.
 *  Returns  : void
 * 
 *  Specify (in a text string) how high this room is above the ocean.
 *
 */
public void
set_height_above_ocean(string height_above_ocean)
{
    gHeight = height_above_ocean;
}


/*
 *  FUNCTION : set_path_desc
 *  Arguments: string - new path description.
 *             string - new vegetation description.
 *  Returns  : None
 * 
 *  Set the path description for ledge-rooms, where you are not
 *  standing on the normal path and cannot show the normal
 *  descriptions.
 *
 */
public void
set_path_desc(string new_path_desc, string new_vegetation_desc)
{
    gPath_desc = new_path_desc;
    gVegetation_desc = new_vegetation_desc;
}


/*
 *  FUNCTION : show_height
 *  Arguments: none
 *  Returns  : string - description.
 * 
 *  Returns a string describing the view from your height.
 *
 */
public string
show_height()
{
    switch (gHeight)
    {
    case "ten":
    case "fifteen":
    case "twenty":
        return "Having barely left the shore, you have " +
            "climbed almost " + gHeight + " meters up the sides " +
            "of the cliff, giving you a nice view of the shore.";

    case "twentyfive":
    case "thirty":
    case "thirtyfive":
    case "fourty":
        return "Almost halfway up the cliffside, you seem " +
            "to have climbed about " +gHeight + " meters up the " +
            "sides of the cliff, giving you a spectacular view of " +
            "the shore.";

    case "fourtyfive":
    case "fifty":
    case "fiftyfive":
        return "Having climbed more than halfway up the sides of " +
            "the cliff, you are given a spectacular view of the " +
            "shore, some " + gHeight + " meters below you.";

    case "sixty":
    case "sixtyfive":
    case "seventy":
        return "A dizzying drop of atleast " + gHeight + " meters " +
            "is visible below your feet. A spectacular view of " +
            "the shore is revealed before your eyes.";
    }
}


/*
 *  FUNCTION : add_vegetation
 *  Arguments: int - 0 = no vegetation, 1 = bush, 2 = cactus.
 *  Returns  : void
 * 
 *  Adds a bush or cactus plant to this location.
 *
 */
public void
add_vegetation(int vegetation_type)
{
    if (!vegetation_type)
    {
        add_item(({ "patch", "patch of soil", "patches",
            "patches of soil", "plants", "soil", "dirt" }),
            "Barely visible here and there are patches of soil " +
            "allowing small bushes, low cactus plants and other " +
            "smaller plants and mushrooms to grow in this " +
            "inhospitable area.\n");
        add_item(({ "cactus", "cactus plant", "low cactus", "plant",
            "wide cactus", "low cactus plant", "wide cactus plant" }),
            "Scattered about on the steep sides of the cliffs are " +
            "low, wide cactus plants and small bushes.\n");
        add_item(({ "bush", "bushes", "small bush", "small bushes",
            "caper bush", "small caper bush" }), "Scattered about " +
            "on the steep sides of the cliffs are low, wide " +
            "cactus plants and small bushes.\n");

        gVegetation_desc = "";
    }
    else
    if (vegetation_type == 1)
    {
        add_item(({ "bush", "bushes", "small bush", "small bushes",
            "caper bush", "small caper bush" }), "Neatly tucked " +
            "away in a sheltered corner behind a few rocks, you " +
            "notice a small shrubby caper bush with many branches " +
            "and thick, shiny and ovate shaped leaves. Growing out " +
            "of a rather small patch of soil, this plant is known " +
            "to be able to survive almost anywhere. Growing on the " +
            "branches of this kind of bush, are the green flower" +
            "buds known as capers.\n");
        add_item(({ "caper", "capers", "berry", "berries" }),
            show_me_berries);
        add_item(({ "patch", "patch of soil", "patches",
            "pathches of soil" }), "Barely visible here and there " +
            "are patches of soil, like directly below a nearby " +
            "bush.\n");
        add_item(({ "soil", "dirt" }), "Barely visible here and " +
            "there, scattered about on the sides of the granite " +
            "cliffs are small patches of soil. A nearby bush has " +
            "made a living in a small patch of soil but you also " +
            "see other smaller plants and mushrooms growing " +
            "there.\n");
        add_item(({ "cactus", "cactus plant", "low cactus", "plant",
            "wide cactus", "low cactus plant", "wide cactus plant",
            "plants" }),
            "Scattered about on the steep sides of the cliffs are " +
            "low cactus plants and small bushes. None of the " +
            "cactus plants seem to be nearby, but a small bush " +
            "has made a life in a sheltered corner here.\n");
        add_item(({ "sheltered corner", "corner" }), "In a small " +
            "sheltered corner, where the strong ocean winds " +
            "cannot reach, you find a small shrubby bush.\n");

        // A bush will show in the description of the cliffs. Add
        // this text to the cliff description.
        gVegetation_desc = "Neatly sheltered from the strong ocean " +
            "wind, you find a small shrubby bush hidden behind a few " +
            "rocks.";

        gBush = 1;

        setuid();
        seteuid(getuid());

        gMaxberries = SETCAPERAVAIL;
        gBerries = SETCAPERRESET;
    }
    else
    if (vegetation_type == 2)
    {
        add_item(({ "cactus", "cactus plant", "low cactus", "plant", 
            "wide cactus", "low cactus plant", "wide cactus plant",
            "plants" }),
            "Rocking gently in the strong ocean wind, a nearby " +
            "cactus plant has made a living on a small ledge, " +
            "growing out of a patch of soil. Low and wide, " +
            "with many large oval, thorny pads the cactus seems " +
            "to thrive even in these harsh conditions. Quite " +
            "spectacular purple-red prickly pears grow from some " +
            "of the oval pads.\n");
        add_item(({ "pear", "pears", "prickly pear", "prickly pears",
            "purple-red pear", "purple-red pears",
            "purple-red prickly pear", "purple-red prickly pears",
            "fruit" }), show_me_berries);
        add_item(({ "patch", "patch of soil", "patches",
            "pathches of soil" }), "Barely visible here and there " +
            "are patches of soil, like directly below a nearby " +
            "cactus plant.\n");
        add_item(({ "soil", "dirt" }), "Barely visible here and " +
            "there, scattered about on the sides of the granite " +
            "cliffs are small patches of soil. A nearby bush has " +
            "made a living in a small patch of soil, but you also " +
            "see other smaller plants and mushrooms growing " +
            "there.\n");
        add_item(({ "bush", "bushes", "small bush", "small bushes",
            "caper bush", "caper bushes", "small caper bush",
            "small caper bushes" }), "Scattered about " +
            "on the steep sides of the cliffs are low, wide " +
            "cactus plants and small bushes. None of the small " +
            "bushes seem to be nearby, but a low cactus plant is " +
            "growing here.\n");
        add_item(({ "ledge", "small ledge" }), "Stepping to the " +
            "very edge of the cliff, you find a low wide cactus " +
            "plant quite exposed in the ocean wind.\n");

        // A plant will show in the description of the cliffs. Add
        // this text to the cliff destriction.
        gVegetation_desc = "Rocking gently in the ocean wind, " +
            "quite exposed on the very edge of the cliffside is a " +
            "low wide cactus plant with large oval leaves.";

        gCactus = 1;

        setuid();
        seteuid(getuid());

        gMaxberries = SETPEARAVAIL;
        gBerries = SETPEARRESET;
    }

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "soil", "dirt" }), 5);
}


/*
 *  FUNCTION : generate_cliffs
 *  Arguments: none.
 *  Returns  : void
 * 
 *  Generates the descriptions of the cliffs.
 *  Adds items to examine.
 *
 */
public void
generate_cliffs()
{
    // Nouns that can always be examined:
    add_item(({ "cliff", "cliffs", "steep cliff", "steep cliffs",
        "dark wall", "wall", "granite wall", "cliffside" }),
        "Rising like a dark grey wall that reaches almost a " +
        "hundred meters towards the sky in some places, the steep " +
        "granite cliffs of the coast are almost barren with only " +
        "a few small bushes and cactus plants growing on the " +
        "cliffside. " + show_height() + " " + gVegetation_desc +
        " Although steep, the cliff is still climbable, " +
        "especially near the path, as it often runs through areas " +
        "where the cliffside has slopes that are more gradual.\n");
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
    add_item(({ "shore", "coast", "shoreline" }), "Stretching " +
        "like a dark wall, the cliffs of the shore disappear far " +
        "away to the northwest and a short way to the east. The " +
        "shore is rugged with large rocks sticking out of the " +
        "water in many places. Only here and there a small " +
        "beach can be spotted.\n");
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
    add_item(({ "beach", "small beach", "beaches", "small beaches" }),
        "Greyish sand cover the few beaches you can see from " +
        "here. Hidden well beneath pillars of granite, a lot of " +
        "climbing would be needed to reach one of those beaches.\n");
    add_item(({ "pillars of granite", "pillars" }), "Stretching " +
        "like tall fingers out of the dark waters, several " +
        "large pillars of granite can be seen along the shore. " +
        "Some are still connected to the cliffside and some " +
        "have been eroded so much by the water that they stand " +
        "free several meters from the shore. Almost hidden " +
        "between the pillars and the rugged cliffside, " +
        "scattered about along the shore, are small beaches " +
        "covered with grey sand.\n");
    add_item(({ "view", "spectacular view", "nice view" }),
        "A strong ocean wind tugs at you as you gaze out over " +
        "the sea. Standing on this spot, some " + gHeight +
        " meters above the ocean, you have a spectacular view " +
        "of the shore as it stretches several kilometers " +
        "northwest and a few hundred meters east, where the " +
        "coast turns south, out of view.\n");
    add_item(({ "seagull", "seagulls", "white seagull",
        "white seagulls", "life", "bird", "birds", "nest",
        "nests" }),
        "Crying seagulls can be heard from all directions and " +
        "often a lone white seagull appears to be suspended in " +
        "midair above the dark granite cliff. Rising winds from " +
        "the ocean keep the seagull high in the air. Looking " +
        "closer, you see that the birds are nested in small " +
        "colonies, resting in their nests on the sides of the " +
        "cliffs.\n");
    add_item(({ "sky", "light" }), show_me_time_of_day);

    // Building the string to add to the long description.
    switch (random(6))
    {
    case 0..2:
        gCliff_desc = "Towering above you, the steep granite " +
            "cliffs of the coast are almost barren, dark and grey.";
        break;

    case 3..4:
        gCliff_desc = "Tall and windswept, the towering cliffs of " +
            "the coast appear almost barren, dark and grey.";
        break;

    case 5:
    default:
        gCliff_desc = "Climbing the currents of the strong ocean " +
            "wind, a lone seagull seem to be suspended in the " +
            "air above the steep granite cliffs of the coast.";
    }
}


/*
 *  FUNCTION : generate_path
 *  Arguments: string - Direction of the path going up.
 *             string - special information about the path to add.
 *  Returns  : void
 * 
 *  Builds a random generated description of the path that leads up
 *  the cliffs. Also adds items to examine.
 *
 */
public void
generate_path(string path_up_desc, string path_desc)
{
    // Nouns that can always be examined:
    add_item(({ "path", "narrow path", "small path",
        "small narrow path" }), "Climbing uphill towards the " +
        path_up_desc + ", the small narrow path twists and turns " +
        "its way up the side of the cliff like a great black " +
        "snake. " + path_desc + " Peering over the edge, you are " +
        "treated to a spectacular view. Here, some " + gHeight +
        " meters above the ocean, you can see far in all " +
        "directions.\n");
    add_item(({ "bend", "turn" }), "Twisting and turning like a " +
        "great black snake, the small narrow path turns sharply " +
        "several times on its way up the cliff. With each bend, " +
        "the path leads up onto a new shelf that takes the path in " +
        "the opposite direction. Many of the turns appear quite " +
        "steep and dangerous.\n");
    add_item(({ "shelf", "shelves" }), "Like a great black snake, " +
        "the path is twisting and turning on its way up the side " +
        "of the cliff. Near the beach and the pier is a smaller " +
        "shelf going east-west, but above that, two larger " +
        "shelves can be seen. The lower shelf is leading towards " +
        "the east as it climbs and the higher shelf leading back " +
        "west before it turns south into a small pass in the " +
        "cliff on the top.\n");
    add_item("pass", "Barely visible on the top of the cliff, it " +
        "seems the path leads south through a small pass in the " +
        "cliffs.\n");

    switch (random(8))
    {
    case 0..6:
        add_item(({ "rock", "rocks" }), "Varying greatly in " +
            "sizes, from tiny pebbles to huge boulders weighing " +
            "several tons, dark granite rocks can be found " +
            "everywhere.\n");

        gPath_desc = "Climbing uphill towards the " + path_up_desc +
            ", the small narrow path snakes its way towards the " +
            "top of the cliff.";
        break;

    case 7:
        add_item(({ "pile", "pile of rocks", "rock", "rocks",
            "fallen rocks", "pile of fallen rocks" }), "Nearly " +
            "blocking the already quite narrow path, a pile of " +
            "fallen rocks makes passage even more difficult and " +
            "dangerous. Examining your options carefully, you " +
            "find that it is possible to cross the pile of rocks " +
            "without falling down the cliff.\n");

        gPath_desc = "Barely passable around a pile of fallen " +
            "rocks, the small narrow path leads uphill " +
            "towards the " + path_up_desc + ".";
    }
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
            "marking the comming of fall.";

    case WINTER:
        return "A chilling winter wind rolls over the cliff and " +
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
            "across the Bay of Balifor, bathing the cliffs in a " +
            "ghostly light.";

        if (GET_MOON_PHASE(SOLINARI) == "full" &&
            GET_MOON_PHASE(LUNITARI) == "full")
        {
            night_desc = "Dominating the night sky, the two full " +
                "moons Solinari and Lunitari, spread pale reddish " +
                "light out across the Bay of Balifor, bathing the " +
                "cliffs in a bright ghostly light.";
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
            "its rays down across the tall granite cliffs.";

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
            "the waves of the ocean below you.\n";        

    case TOD_DAY:
        return show_me_day() + " Reflected sunlight plays brightly " +
            "across the waves of the ocean below you.\n";

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
    set_tell_time(450);

    add_tell("Harsh wailings from nearby seagulls carry over the " +
        "noise of the ocean below.\n");
    add_tell("Thunderous waves crash on the rocky shore below.\n");
    add_tell("With the sudden fluttering of wings, a group of " +
        "seagulls takes to the skies, squawking loudly at some " +
        "unseen dangers.\n");
    add_tell("A strong gust of wind from the ocean tugs at you.\n");
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
    return gCliff_desc + " " + show_me_day() + " " + gPath_desc +
        " " + generate_season() + "\n";
}


/*
 *  FUNCTION : set_climb_dirs
 *  Arguments: *status - array with 1/0, exit climbable?
 *             *string exit_desc 
 *  Returns  :
 * 
 *  Sets directions to climb, and fail descriptions for unclimbable
 *  exits. You can climb up [0] or down [1].
 *
 */
public void
set_climb_dirs(status *climbable, string *exit_desc)
{
    gClimb_dir = climbable;
    gExit_desc = exit_desc;
}


/*
 *  FUNCTION : climb_cliff
 *  Arguments: string - arguments that follow the climb command.
 *  Returns  : int - 1 if command succeeded, 0 if fail.
 * 
 *  Checks if the cliffs are climbable here and handles the climbing
 *  being attempted.
 *
 */
public int
climb_cliff(string arg)
{
    status direction;
    string climb_desc, say_desc, show_dir;

    if (arg == "up" || arg == "down")
    {
        switch (arg)
        {
        case "up":
            direction = 0;
            show_dir = "from below";
            break;

        case "down":
            direction = 1;
            show_dir = "from above";
        }

        if (!gClimb_dir[direction])
        {
            NF(gExit_desc[direction]);
            return 0;
        }

        climb_desc = "Stepping up to the cliffside, you quickly " +
            "find some handholds and begin ";
        say_desc = QCTNAME(TP) + " steps up to the cliffside and " +
            "begins ";

        switch (direction)
        {
        case 0:
            climb_desc += "pulling yourself up.\n";
            say_desc += "pulling " + HIM(TP) + "self up.\n";
            break;

        case 1:
            climb_desc += "lowering yourself down.\n";
            say_desc += "lowering " + HIM(TP) + "self down.\n";
        }

        write(climb_desc);
        say(say_desc);

        if (TP->resolve_task(TASK_DIFFICULT, ({ TS_CON, SS_CLIMB })))
        {
            say(QCTNAME(TP) + " leaves, climbing " + arg + " the cliffside.\n");

            // Tell the destination room that someone arrived.
            tell_room(RSROOMS + gExit_desc[direction], QCTNAME(TP) +
                " arrives " + show_dir + ", climbing " + arg +
                " the cliffside.\n", ({ TP }), TP);

            TP->move_living("M",
                            RSROOMS + gExit_desc[direction], 1);

            return 1;
        }
        else
        {
            NF("Unable to find some good handholds, you give " +
                "up climbing the cliffside and return to the " +
                "path.\n");
            say(QCTNAME(TP) + " gives up climbing the cliffside " +
                "and returns to the path again.\n");

            return 0;
        }
    }

    NF("Climbing the cliff seems be possible in some places, " +
        "especially near the path that seems to cross through " +
        "terrain where the slopes are more gradual and climbable. " +
        "You could attempt to climb up or down.\n");

    return 0;
}


/*
 *  FUNCTION : pick_berries
 *  Arguments: string - arguments that follow the pick command.
 *  Returns  : int - 1 if command succeeded, 0 if fail.
 * 
 *  Handles the command to pick berries. 
 *
 */
public int
pick_berries(string arg)
{
    object berry;
    string add_txt, berry_type;

    if (!stringp(arg) || arg == "")
    {
        NF("Gather what?\n");

        return 0;
    }

    if (parse_command(arg, TO,
        "[a] [all] [the] [small] [green] %w [from] [the] [small] [bush]",
        berry_type))
    {
        if (berry_type == "caper" && gBush)
        {
            if (!gBerries)
            {
                write("You search the small bush for capers, but " +
                    "all seem to have been picked.\n");
                say(QCTNAME(TP) + " searches through the small " +
                    "bush.\n");

                return 1;
            }

            write("You pick a caper from the small bush.\n");
            say(QCTNAME(TP) + " picks a caper from the small bush.\n");
            gBerries -= 1;

            clone_object(RSOBJS + "caper")->move(TP, 1);

            return 1;
        }

        if (berry_type == "capers" && gBush)
        {
            if (!gBerries)
            {
                write("You search the small bush for capers, but " +
                    "all seem to have been picked.\n");
                say(QCTNAME(TP) + " searches through the small " +
                    "bush.\n");

                return 1;
            }

            if (gBerries > 1)
            {
                add_txt = " capers ";
            }
            else
            {
                add_txt = " caper ";
            }

            write("You search the small bush and pick the rest of " +
                "the capers. You were able to pick " + gBerries +
                add_txt + "from the bush.\n");
            say(QCTNAME(TP) + " picks some capers from the small " +
                "bush.\n");

            berry = clone_object(RSOBJS + "caper");
            berry->set_heap_size(gBerries);
            berry->move(TP, 1);
            gBerries = 0;

            return 1;
        }
    }

    if (parse_command(arg, TO,
        "[a] [all] [the] [purple-red] [cactus] %w [from] [the] [low] [wide] [cactus] [plant]",
        berry_type))
    {
        if ((berry_type == "pear" || berry_type == "cactus") && gCactus)
        {
            if (!gBerries)
            {
                write("You search the low cactus plant for pears, " +
                    "but all seem to have been picked.\n");
                say(QCTNAME(TP) + " searches through the small " +
                    "bush.\n");

                return 1;
            }
        
            write("You pick a purple-red cactus pear from the low " +
                "wide cactus plant.\n");
            say(QCTNAME(TP) + " picks a purple-red cactus pear " +
                "from the low wide cactus plant.\n");
            gBerries -= 1;

            clone_object(RSOBJS + "prickly_pear")->move(TP, 1);

            return 1;
        }

        if ((berry_type == "pears" || berry_type == "cacti") && gCactus)
        {
            if (!gBerries)
            {
                write("You search the low cactus plant for pears, " +
                    "but all seem to have been picked.\n");
                say(QCTNAME(TP) + " searches through the small " +
                    "bush.\n");

                return 1;
            }

            if (gBerries > 1)
            {
                add_txt = " cactus pears ";
            }
            else
            {
                add_txt = " cactus pear ";
            }

            write("You search the low wide cactus plant and pick " +
                "the rest of the purple-red cactus pears. You were " +
                "able to pick " + gBerries + add_txt + "from the " +
                "cactus.\n");
            say(QCTNAME(TP) + " picks some purple-red cactus pears " +
                "from the low wide cactus plant.\n");

            berry = clone_object(RSOBJS + "prickly_pear");
            berry->set_heap_size(gBerries);
            berry->move(TP, 1);
            gBerries = 0;

            return 1;
        }
    }

    NF("Gather what?\n");

    return 0;
}

