/*
 * camp_base.c
 *
 * Basefile for the draconian camp in Kurinost.
 *
 * Copyright (C): Kellon, august 2012
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

#define TENTNR ({ "three", "four", "five" })
#define SIVAKCHANCE 5
#define BOZAKCHANCE 7
#define HOBGCHANCE  9

// G L O B A L   V A R S
string gLong_base, gLong_add, gPath_desc;
string *herbs;
int gRoom_type;

// P R O T O T Y P E S
public object choose_mob();
// public string search_tiles(object who, string what);

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
 *  FUNCTION : show_tower_light
 *  Arguments: None
 *  Returns  : String - description of light.
 * 
 *  Generates a string based on time of day, showing what light hits
 *  the tower.
 *
 */
public string
show_tower_light()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            return "pale light from the two moons";

        case TOD_DAY:
            return "light from the sun";

        case TOD_DAWN:
            return "pale red light from the rising sun";

        case TOD_TWILIGHT:
            return "brilliant hues of the setting sun";
    }
}


/*
 *  FUNCTION : show_tower_short
 *  Arguments: None
 *  Returns  : String - short description of light.
 * 
 *  Generates a string based on time of day, showing what light hits
 *  the tower.
 *
 */
public string
show_tower_short()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            return "moonlit ";

        case TOD_DAY:
            return "sunlit ";

        case TOD_DAWN:
        case TOD_TWILIGHT:
            return "";
    }
}


/*
 *  FUNCTION : show_time_daynight
 *  Arguments: None
 *  Returns  : String - description of light.
 * 
 *  Generates a string, description of light that hits the tower,
 *  based on time of day.
 *
 */
public string
show_time_daynight()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            return "pale moonlight";

        case TOD_DAY:
            return "golden sunlight";

        case TOD_DAWN:
        case TOD_TWILIGHT:
            return "pale sunlight";
    }
}


/*
 *  FUNCTION : show_camp_season
 *  Arguments: None
 *  Returns  : String - description of smoke and season air.
 * 
 *  Generates a string based on the time of year.
 *
 */
public string
show_camp_season()
{
    switch (GET_SEASON)
    {
        case SUMMER:
            return "slowly through the hot and damp summer air. " +
                "Sheltered from the winds of the coast, no wind " +
                "moves through the encampment, making it hot, " +
                "smelly and wet.";

        case WINTER:
            return "quickly through the cold winter air. Even " +
                "here, sheltered beneath the coastal cliffs, there " +
                "is no refuge against the chilling winds that " +
                "freezes everything in the encampment.";

        case AUTUMN:
            return "slowly towards a layer of scattered clouds. " +
                "Looking cool and grim, the autumn sky covers the " +
                "encampment like a cold and wet blanket.";

        case SPRING:
            return "slowly towards a clear spring sky. Nearby " +
                "woodlands is filling the air in the encampment " +
                "with the scent of blooming trees.";
    }
}


/*
 *  FUNCTION : show_season_air
 *  Arguments: None
 *  Returns  : String - description of air.
 * 
 *  Generates a short desciption of the air in the camp.
 *
 */
public string
show_season_air()
{
    switch (GET_SEASON)
    {
        case SUMMER:
            return "hot and damp";

        case WINTER:
            return "chilling cold";

        case AUTUMN:
        case SPRING:
            return "cold and damp";
    }
}


/*
 *  FUNCTION : show_season_mud
 *  Arguments: None
 *  Returns  : String - description of mud.
 * 
 *  Generates a short desciption of the mud.
 *
 */
public string
show_season_mud()
{
    switch (GET_SEASON)
    {
        case SUMMER:
            return "deep, smelly and wet";

        case WINTER:
            return "frozen and heavy";

        case AUTUMN:
            return "cold and wet";

        case SPRING:
            return "wet and smelly";
    }
}


/*
 *  FUNCTION : show_time_of_day
 *  Arguments: None
 *  Returns  : String - description.
 * 
 *  Returns a description of the sky and time of day.
 *
 */
public string
show_time_of_day()
{
    string seasontxt = ", you clearly see";

    if (GET_SEASON == AUTUMN)
    {
        // Scattered autumn clouds alter the text.
        seasontxt = " towards the scattered clouds, you can " +
            "barely see";
    }

    switch (GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            return "As you turn your gaze up" + seasontxt + " the " +
                "stars on the black night sky. Glowing like a " +
                "ghostly torch in the darkness, the slender white " +
                "tower above the camp is lit up by pale moonlight " +
                "from above the coastal cliffs.\n";

        case TOD_DAWN:
            return "Brilliant hues cross the morning sky as the " +
                "light of the rising sun slowly increases to " +
                "chase away the darkness of night. Though you " +
                "cannot see the sun from here, you notice that " +
                "the sun has risen, as the golden rays of " +
                "sunlight hit the slender elven tower above the " +
                "camp on the western side.\n";
            
        case TOD_DAY:
            return "Lit by brilliant sunlight, the slender " +
                "tower stands like a tall golden torch high " +
                "above the camp, a bright contrast to the eternal " +
                "shadow of the rest of the camp.\n";

        case TOD_TWILIGHT:
            return "Deep reddish hues cross the evening sky and " +
                "the pale rays of sunlight reflecting from the slender " +
                "white tower slowly dim. With the growing " +
                "darkness, the stars begin to show in the sky.\n";
    }
}


/*
 *  FUNCTION : show_camp
 *  Arguments: none
 *  Returns  : string - description of camp, smoke and time of year/day.
 * 
 *  Builds the description of the camp/encampment, based on input
 *  from the room, the time of day and the season.
 *
 */
public string
show_camp()
{
    switch (gRoom_type)
    {
        case DCAMP_MUDDYPIT:
            return "Gathering like a dark cloud above you, the " +
                "smoke of burning wood stings in your lungs and " +
                "adds to the stench of decaying meat and refuse " +
                "that rises into the " + show_season_air() +
                " air. Nestled close beneath the coastal cliffs, " +
                "the camp rests in eternal shadow from the " +
                show_time_daynight() + " and this smoke-covered " +
                "pit seems darker still. You feet are sinking into " +
                "the " + show_season_mud() + " mud of the central " +
                "depression around you, making it hard to walk " +
                "anywhere. Piled up almost everywhere in the pit " +
                "are heaps of garbage, decaying meat, old " +
                "discarded equipment and other filthy remains. " +
                "Being stuck down here amongst piles of garbage " +
                "makes it hard to estimate on the size of the " +
                "encampment. The pit itself seems to be about " +
                "thirty meters across. Barely visible, high above " +
                "the smoke on the western side of the camp, a " +
                "slender white tower reaches high enough to catch " +
                "the " + show_tower_light() + ". " + gLong_add + "\n";

        case DCAMP_BROKENPATH:
            return "Pillars of smoke from a few scattered " +
                "campfires rise " + show_camp_season() +
                " Burning in your lungs, the fires add to the " +
                "stench of decaying meat and refuse coming from " +
                "the central pit of this crude circular " +
                "encampment. Nestled close beneath the coastal " +
                "cliffs, hidden in eternal shadow, the camp " +
                "stretches out before you. Crunching lightly " +
                "beneath your feet are the broken remains of an " +
                "ancient paved path that runs along the outer " +
                "edges of the camp, between the crude wooden " +
                "palisade and the central pit. " +
                "Through the shadow of the encampment, you " +
                "estimate that the entire camp is about fourty " +
                "meters across, with the central pit being the " +
                "largest at about thirty meters across. Reaching " +
                "high above the shade of the camp, a slender " +
                "white tower stands tall enough to catch " +
                show_tower_light() + ". " + gLong_add + "\n";

        case DCAMP_TENTCAMP:
            return "Filling the " + show_season_air() + " air " +
                "with dark smoke, a nearby campfire does little " +
                "to light up the darkness of the camp that " +
                "stretches out before you. Three crude grey tents " +
                "surround a small burning campfire, a few paces " +
                "distant. Crunching lightly beneath your feet are " +
                "the broken remains of an ancient paved path. " +
                "Through the shadow of the encampment, you " +
                "estimate that the entire camp is about fourty " +
                "meters across, with the central pit being the " +
                "largest at about thirty meters across. Nestled " +
                "close to the coastal cliffs this crude circular " +
                "encampment hides in eternal shadow, a dark " +
                "contrast to the slender " + show_time_daynight() +
                " tower that rises on the western side of the " +
                "camp. " + gLong_add + "\n";
    }
}


/*
 *  FUNCTION : show_camp_smoke
 *  Arguments:
 *  Returns  :
 * 
 *  Generates a description of the campfires and the smoke.
 *
 */
public string
show_camp_smoke()
{
    return "Pillars of smoke from a few scattered campfires rise " +
        show_camp_season() + " Though most of the smoke rises " +
        "away from the camp, some of it seems to settle like a " +
        "dark cloud over the camp, and especially over the " +
        "central pit. Surrounded by a simple palisade of thick " +
        "wooden beams, the camp is roughly circular and " +
        "bowl-shaped with a muddy pit in the center. Along the " +
        "northern and sourthern parts of the palisade, crude grey " +
        "tents have been erected into four small camps along the " +
        "path, each group close to a small campfire.\n";
}


/*
 *  FUNCTION : show_path_mud
 *  Arguments: None.
 *  Returns  : String - the description.
 * 
 *  Returns a description of the path.
 *
 */
public string
show_path_mud()
{
    if (gRoom_type == DCAMP_MUDDYPIT)
    {
        return "Your feet are sinking into the " + show_season_mud() +
            " mud of the central pit around you, making it hard " +
            "to walk anywhere. Varying slightly in depth, the " +
            "thick mud seems to be almost 20 centimeters deep in " +
            "some places, but mostly it is about half of that. " +
            "The stench of refuse and rotting meat is all around " +
            "you here in the pit, adding to the smell of burning " +
            "wood that also hangs in the air. From here it is " +
            "possible to go " + gPath_desc + "\n";
    }
    else
    {
        return "Unable to find any mud right here, you take a " +
            "quick look around and quickly notice the thick layer " +
            "of mud down in the central depression of the camp. " +
            "Surely at this time of the year the mud down there " +
            "must be " + show_season_mud() + ".\n";
    }
}


/*
 *  FUNCTION : show_path
 *  Arguments: None
 *  Returns  : String - the description.
 * 
 *  Show a description of the path.
 *
 */
public string
show_path()
{
    if (gRoom_type == DCAMP_MUDDYPIT)
    {
        return "Your feet are sinking into the " +
            show_season_mud() + " mud of the central pit around " +
            "you, making it hard to walk anywhere. Though you are " +
            "barely able to see any usable path through the mud, " +
            "you are certain that you can go " + gPath_desc +
            " Smoke from a few scattered campfires rise " +
            show_camp_season() + " Above the central pit, you see " +
            "the path that leads in a wide circle around the " +
            "center of the camp, up towards the slender white " +
            "tower west from here. In a few places you find some " +
            "small hardy plants growing out of the mud.\n";
    }
    else
    {
        return "Crunching lightly beneath your feet are the " +
            "broken remains of a paved path that leads " +
            gPath_desc + " Running in a wide circle around the " +
            "center of the camp, the path leads up towards the " +
            "slender white tower on the western side of the camp. " +
            "Smoke from nearby campfires rise " + show_camp_season() +
            " Next to the path you notice a light undergrowth of " +
            "small plants.\n";
    }
}


/*
 *  FUNCTION : show_path_tiles
 *  Arguments: None.
 *  Returns  : String - description of the paved path, depening
 *             on where you are.
 * 
 *  Returns a description of the paved path.
 *
 */
public string
show_path_tiles()
{
    if (gRoom_type == DCAMP_MUDDYPIT)
    {
        return "Your feet are sinking into the " + show_season_mud() +
            " mud of the central pit, making it very difficult " +
            "indeed to see if there even are any tiles here.\n";
    }
    else
    {
        return "Crunching lightly beneath your feet are the " +
            "broken remains of a paved path. What might once have " +
            "been a beautiful white pavement is now a barely " +
            "visible path with small broken grey and black " +
            "tiles. Here and there you can make out some symbols " +
            "or motif, but mostly it is impossible to tell " +
            "what might have been on the tiles.\n";
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
    set_tell_time(400);

    add_tell("Smoke silently drifts through the air of the camp, " +
        "stinging your lungs.\n");
    add_tell("A silent breeze carries the stench of garbage piles " +
        "from the central depression of the camp.\n");
    add_tell("Piercing the thick air of the camp, the scream from " +
        "a dying hobgoblin is followed by the hoarse laughter of " +
        "draconians.\n");
    add_tell("A large seagull flies over the camp and starts " +
        "descending towards the garbage piles of the central pit.\n");
    add_tell("Far above the pass through the cliffs, a lone " +
        "seagull seems to be suspended in the air, floating on " +
        "the rising wind from the ocean.\n");
    add_tell("Far above the cliffs, a group of seagulls fly " +
        "northeast towards the coast, quickly disappearing from " +
        "sight.\n");
}


/*
 *  FUNCTION : show_long_desc
 *  Arguments: none
 *  Returns  : string - long description of the room.
 * 
 *  Returns the current longdescription based on season and
 *  pre-generated strings from cliffs and path.
 *
 */
public string
show_long_desc()
{
    return gLong_base;
}


/*
 *  FUNCTION : show_camp_shade
 *  Arguments: None
 *  Returns  : String - the description.
 * 
 *  Returns a description of the shadow of the camp.
 *
 */
public string
show_camp_shade()
{
    return "Rising like a dark grey wall above of you, the entire " +
        "encampment is placed so close beneath the coastal cliffs " +
        "that the " + show_time_daynight() + " cannot ever reach " +
        "the camp. While the sky shows clearly when it is day or " +
        "night, the camp itself rests in shadow. Only the slender " +
        "white tower on the highest point of the camp is reaching " +
        "high enough above the coastal cliffs to catch the " +
        show_tower_light() + ".\n";
}


/*
 *  FUNCTION : generate_camp
 *  Arguments: int - room type (0-2)
 *             string - additional roomdescription.
 *  Returns  : void
 * 
 *  Set up base descriptions of the camp.
 *
 */
public void
generate_camp(int room_type, string room_desc)
{
    string tents = ONE_OF(TENTNR);

    gRoom_type = room_type;
    gLong_add = room_desc;

    // We need to be able to clone herbs and other stuff here:
    setuid();
    seteuid(getuid());

    // Generate longdescription for the room, based on room type.
    if (gRoom_type == DCAMP_MUDDYPIT)
    {
        switch (random(3))
        {
            case 0..1:
                gLong_base = "Dark smoke of burning wood gathers " +
                    "like a thick cloud above you, adding to the " +
                    "stench of decaying meat and refuse that rises " +
                    "into the " + show_season_air() + " air from " +
                    "several nearby garbage piles. Standing in the " +
                    show_season_mud() + " mud of the central " +
                    "depression of a crude encampment, the outer " +
                    "parts of the camp rises on all sides around " +
                    "you. Nestled close beneath the coastal " +
                    "cliffs, the camp rests in eternal shade from " +
                    "the " + show_time_daynight() + ", a dark " +
                    "contrast to a slender " + show_tower_short() +
                    "tower, high above you on the western side " +
                    "of the camp.\n";
            break;

            case 2:
                gLong_base = "Dark smoke engulfs you, making it " +
                    "difficult to breathe the " + show_season_air() +
                    " air. Decaying meat and other garbage are " +
                    "piled up in the " + show_season_mud() +
                    " mud, adding strongly to the stench of " +
                    "burning wood. On all sides around you, rising " +
                    "up through the dark smoke, a crude encampment " +
                    "can be seen. Nestled close beneath the " +
                    "coastal cliffs, the camp rests in eternal " +
                    "shade from the " + show_time_daynight() +
                    ", a dark contrast to a slender " +
                    show_tower_short() + "tower high above you, " +
                    "on the western side of the camp.\n";
        }
    }
    else
    if (gRoom_type == DCAMP_BROKENPATH)
    {
        switch (random(3))
        {
            case 0..1:
                gLong_base = "Guarding the path through the " +
                    "coastal cliffs, a slender white tower " +
                    "reaches for the sky, cathing the " +
                    show_tower_light() + ". Nestled close beneath " +
                    "the cliffs in eternal shade, a crude " +
                    "circular encampment stretches out before " +
                    "you. Smoke from a few scattered campfires " +
                    "rise through the " + show_season_air() +
                    " air, burning your lungs and adding to the " +
                    "stench of decaying meat and refuse from the " +
                    "central pit.\n";
                break;

            case 2:
                gLong_base = "Pillars of smoke from a few " +
                    "scattered campfires rise slowly through the " +
                    show_season_air() + " air, burning your " +
                    "lungs. Nestled close beneath the coastal " +
                    "cliffs, hidden in eternal shade, a rougly " +
                    "circular encampment stretches out before " +
                    "you, bustling with activity. Reaching high " +
                    "above the shadow and smoke of the camp, a " +
                    "slender white tower stands tall enough to " +
                    "catch the " + show_tower_light() + ".\n";
        }
    }
    else
    if (gRoom_type == DCAMP_TENTCAMP)
    {
        switch (random(3))
        {
            case 0..1:
                gLong_base = "Filling the " + show_season_air() +
                    " air with dark smoke, a nearby campfire does " +
                    "little to light up the darkness of the camp " +
                    "that stretches out before you. " +
                    capitalize(tents) + " crude grey tents " +
                    "surround the campfire, a few paces distant. " +
                    "Nestled close to the coastal cliffs this " +
                    "crude circular encampment hides in eternal " +
                    "shade, a dark grey contrast to a slender " +
                    show_tower_short() + "tower that rises on the " +
                    "western side of the camp.\n";
                break;

            case 2:
                gLong_base = "Rising into the " + show_season_air() +
                    " air, smoke from a small nearby campfire adds " +
                    "to the darkness of the crude circular " +
                    "encampment that stretches out before you, a " +
                    "dark contrast to the slender " +
                    show_tower_short() + "tower that rises on " +
                    "the western side of the camp. Nestled close " +
                    "to the coastal cliffs, the camp is hidden in " +
                    "eternal shadow and the campfire does little " +
                    "to light up the " + tents + " crude grey " +
                    "tents a few paces from the campfire.\n";
        }
    }

    // Following nouns depend on your location.
    switch (gRoom_type)
    {
        case DCAMP_MUDDYPIT:
            add_item(({ "tent", "tents", "crude tent", "crude tents",
                "grey tent", "grey tents", "crude grey tent",
                "crude grey tents" }), "Along the northern and " +
                "southern parts of the wooden palisade, crude " +
                "grey tents have been erected in four small " +
                "groups. You are not close enough to discern many " +
                "details. The tents appear to be large enough to " +
                "hold a few soldiers atleast.\n");

            add_item(({ "pile", "piles", "refuse pile", "depression",
                "central depression", "pit", "refuse", "refuse pit",
                "refuse piles", "garbage pile", "garbage piles" }),
                "Only the slightest breeze is enough to draw the " +
                "attention to the pile of garbage and refuse you " +
                "have found here. Everything not used by the army " +
                "is thrown into this pile, it seems. Old broken " +
                "weapons, torn rags, charred lumps of meat, some " +
                "of them half decomposed and what appears to be " +
                "hobgoblin droppings.\n");

            break;

        case DCAMP_BROKENPATH:
            add_item(({ "tent", "tents", "crude tent", "crude tents",
                "grey tent", "grey tents", "crude grey tent",
                "crude grey tents" }), "Along the northern and " +
                "southern parts of the wooden palisade, crude " +
                "grey tents have been erected in four small " +
                "groups. You are not close enough to discern many " +
                "details. The tents appear to be large enough to " +
                "hold a few soldiers atleast.\n");

            add_item(({ "pile", "piles", "refuse pile",
                "refuse piles", "garbage pile", "garbage piles" }),
                "While the stench of refuse is heavy in the air, " +
                "you cannot see any piles right here, but as you " +
                "take a quick look around, you quickly notice the " +
                "piles of garbage down in the central depression " +
                "of the camp.\n");

            break;

        case DCAMP_TENTCAMP:
            add_item(({ "tent", "tents", "crude tent", "crude tents",
                "grey tent", "grey tents", "crude grey tent",
                "crude grey tents" }),
                "Barely more than tattered rags made from cotton, " +
                "sewn together with crude stiches and mismatched " +
                "patches, the crude grey tents seem very simple. " +
                "Each of the " + tents + " tents seem capable of " +
                "providing space for two or three living beings " +
                "about the same size as an average person. The " +
                "nearest of the tents appears to have a wide flap " +
                "at the front end that seems open, while the rest " +
                "of the tents appears to have been tied shut.\n");

            add_item(({ "pile", "piles", "refuse pile",
                "refuse piles", "garbage pile", "garbage piles" }),
                "While the stench of refuse is heavy in the air, " +
                "you cannot see any piles right here, but as you " +
                "take a quick look around, you quickly notice the " +
                "piles of garbage down in the central depression " +
                "of the camp.\n");
    }

    // General nouns that can always be examined here!
    add_item(({ "sky", "light" }), show_time_of_day);

    add_item(({ "camp", "shady camp", "encampment", "fortified encampment",
        "shady encampment", "dragonarmy encampment" }), show_camp);

    add_item(({ "shore", "coast" }), "Even if it is impossible to " +
        "see from here, the coast is nearby. Large numbers of " +
        "seagulls build their nests in the coastal cliffs north " +
        "of the encampment.\n");

    add_item(({ "cliff", "cliffs", "steep cliff", "steep cliffs" }),
        "Rising like a dark grey wall that reaches almost a " +
        "hundred meters towards the sky in some places, the steep " +
        "granite cliffs of the coast are almost barren with only " +
        "a few patches of green showing scattered plantlife up " +
        "there. Tugged closely beneath the cliffs, this " +
        "encampment is hidden in eternal shadow, as no sunlight " +
        "ever reach over the cliffs and down into the camp " +
        "itself. Only the slender white tower on the western side " +
        "of the camp reaches high enough to catch the rays of the " +
        "sun or faint glow from the moons.\n");

    add_item(({ "pass", "pass through cliffs" }), "Climbing only " +
        "about twenty meters, the road heading north out of the " +
        "camp quickly disappears into a narrow pass, going " +
        "through the top of the coastal cliffs. While the main " +
        "part of the camp is hidden in eternal shadow, the " +
        "slender white tower rises above the cliffs, as if rising " +
        "to guard the pass.\n");

    add_item(({ "shade", "shadow", "shadows" }), show_camp_shade);

    add_item("granite", "Glistening in many places with moisture, " +
        "the dark grey wall of the cliffside is made of hard and " +
        "tough granite. Rising in tall structures of varying " +
        "heights, the granite is marred in most places by the " +
        "wind. Appearing dark and foreboding, the dark grey " +
        "granite is covered in spots by small patches of moss.\n");

    add_item(({ "moss", "patch of moss", "patches of moss" }),
        "Like a small soft green blanket, you notice several and " +
        "often large patches of moss covering the moist areas on " +
        "the granite cliff.\n");

    add_item(({ "seagull", "seagulls", "white seagull",
        "white seagulls", "life", "bird", "birds" }),
        "Crying seagulls can be heard from all directions and " +
        "often a lone white seagull appears to be suspended in " +
        "midair above the dark granite cliff. Rising winds from " +
        "the ocean keep the seagull high in the air.\n");

    add_item(({ "forest", "silvanesti forest", "elven kingdom", "kingdom",
        "immense forest", "immense silvanesti forest", "silvanesti" }),
        "Like a vast green blanket, the immense forest of " +
        "Silvanesti is visible in all directions, except north. " +
        "From the western horizon, as far south as your eyes can " +
        "see, to the far eastern horizon. Trees everywhere! " +
        "Except for the usual variations, with spots of higher or " +
        "lower trees, there is nothing else to see but the trees. " +
        "No buildings, no open areas and no roads.\n");

    add_item(({ "pillars", "smoke", "pillars of smoke",
        "campfire", "campfires" }), show_camp_smoke);

    add_item(({ "tower", "elven tower", "white tower",
        "slender tower", "slender white tower" }), "Towering " +
        "above the encampment, the slender tower is the only part " +
        "of the camp that reaches high enough to catch the " +
        show_tower_light() + ". At first glance, the tower seemed " +
        "white and perfect, but that might be the fact that it is " +
        "always tall enough to reach the light, whereas the camp " +
        "itself is hidden below the coastal cliffs in eternal " +
        "shadow. Careful examination reveals that the tower is " +
        "greyed from exposure to weather and ages of disrepair " +
        "has worn down the tower and it now stands decayed and " +
        "partly broken. Most of the upper part, the roof and " +
        "northern side of the tower has collapsed into a heap at " +
        "the base of the tower, just outside the camp. Reaching " +
        "almost fifteen meters into the air, the tower must have " +
        "been almost double the size before it fell apart.\n");

    add_item(({ "palisade", "crude palisade", "crude wooden palisade",
        "wooden palisade", "wall" }), "Surrounded entirely by a " +
        "crude wooden palisade, the encampment seems well " +
        "protected. Thick wooden beams, some up to five meters " +
        "long, have been dug into the rough ground, side by side. " +
        "Each trunk has been cut at the top, giving it a " +
        "sharpened tip and all the beams seems to have been " +
        "blackened by fire.\n");
}


/*
 *  FUNCTION : generate_path
 *  Arguments: string - special information about the path to add.
 *  Returns  : void
 * 
 *  Builds a description of the path you can walk from here.
 *
 */
public void
generate_path(string path_desc)
{
    gPath_desc = path_desc;

    add_item(({ "path", "paved path", "road", "paved road",
        "pavement" }), show_path);

    add_item(({ "mud", "frozen mud", "wet mud", "hot mud",
        "hot wet mud" }), show_path_mud);

    add_item(({ "tiles", "broken tiles", "symbol", "symbols",
        "motif", "grey tiles", "black tiles" }), show_path_tiles);

    if (gRoom_type == DCAMP_MUDDYPIT)
    {
        herbs = HERB_MASTER->query_herbs( ({ "swamp", }) );

        add_item(({ "plants", "small plants", "plant",
            "small plant" }), "Growing out of the mud in a few " +
            "places, you notice a few hardy plants.\n");

        set_up_herbs(({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs)}),
            ({ "mud", }), 7);
    }
    else
    {
        herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );

        add_item(({ "undergrowth", "light undergrowth" }),
            "Growing out of the ground right next to the path, " +
            "you notice a light undergrowth of small plants.\n");

        set_up_herbs(({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
            ONE_OF(herbs)}), ({ "undergrowth", }), 5);
    }
    
/*
    // Enable this part when story is done!!
    if (gRoom_type == DCAMP_BROKENPATH ||
        gRoom_type == DCAMP_TENTCAMP)
    {
        add_search(({ "tiles", "broken tiles", "symbol", "symbols",
            "motif", "grey tiles", "black tiles" }), 0,
                   "search_tiles", 1);
    }
*/
}


/*
 *  FUNCTION : choose_mob
 *  Arguments: None - based on defines.
 *  Returns  : object - the object that has been clone.
 * 
 *  Randomly select a mob to clone.
 *
 */
public object
choose_mob()
{
    object tmob;
    int chance = random(10);

    if (chance <= SIVAKCHANCE)
    {
        tmob = clone_object(DRACONIANBASE + "sivak");
        tmob->set_color("green");
    }
    else
    if (chance <= BOZAKCHANCE)
    {
        tmob = clone_object(DRACONIANBASE + "bozak");
        tmob->set_color("green");
    }
    else
    if (chance <= HOBGCHANCE)
    {
        tmob = clone_object(RSLIVING + "hobgoblin");
        tmob->arm_me();
    }

    return tmob;
}
