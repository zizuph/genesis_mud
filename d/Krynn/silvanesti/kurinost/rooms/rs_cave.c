/*
 * rs_cave.c
 *
 * A hidden cave somewhere near Kurinost.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit INSIDEBASE;
inherit HERBSEARCHNEW

// D E F I N I T I O N S

// G L O B A L   V A R S
string *herbs = HERB_MASTER->query_herbs( ({ "cave" }) );
object gNagrogh;

// P R O T O T Y P E S
public string show_longdesc();
public void setup_tells();
public string show_cave();
public string show_entrance();
public string show_ledge();
public string show_ceiling();
public int drink_water(string arg);

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Reset the room.
 *
 */
public void
reset_kurinost_room()
{
    set_searched(0);

    if (!gNagrogh)
    {
        gNagrogh = clone_object(RSLIVING + "nagrogh");
        gNagrogh->set_no_show_composite(1);
        gNagrogh->move(TO);
    }
}


/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Create the room.
 *
 */
public void
create_kurinost_room()
{
    set_short("dark cave");
    set_long(show_longdesc);

    add_item(({ "walls", "cave walls" }), "The rough and uneven " +
        "cave floor quickly rises into walls around the edges. " +
        "Most of the walls continue into the darkness above or " +
        "beyond your range of sight. Echoes of falling waterdrops " +
        "seem to emmanate from the western wall and your senses " +
        "tell you that there might be some kind of ledge on top " +
        "of the eastern cave wall.\n");

    add_item(({ "west wall", "western wall", "wet wall" }),
        "Rough, slippery and wet, the western wall is covered in " +
        "running water comming from the darkness above. As you " +
        "lean closer to the face of the wall, you notice several " +
        "fungi and small mushrooms on the wall. From the darkness " +
        "above, large drops of water falls into a dark pool near " +
        "southern end of the wall.\n");
    add_item(({ "fungi", "mushrooms", "small mushrooms", "fungus" }),
        "Covering parts of the wet and slippery western wall, the " +
        "fungi and small mushrooms appear to be growing there.\n");
    add_item(({ "water", "pool", "dark pool" }), "Near the " +
        "southern end of the western wall large drops of water " +
        "fall out of the darkness above to gather in a small dark " +
        "pool.\n");
    add_item(({ "south wall", "southern wall" }), "Rising into " +
        "the utter darkness above you, the southern wall seems " +
        "quite smooth, but much too steep to climb. Something " +
        "might be looming in the darkness high above, but you are " +
        "unable to see it or get to it from here.\n");

    // These items need to show the light from the entrance or
    // the hobgoblin on the ledge:
    add_item(({ "cave", "cavern" }), show_cave);
    add_item(({ "entrance", "crack" }), show_entrance);
    add_item(({ "east wall", "eastern wall", "ledge" }), show_ledge);
    add_item(({ "darkness", "ceiling" }), show_ceiling);

    add_cmd_item(({ "walls", "cave walls" }), ({ "climb" }),
        "Please specify what wall you want to climb. East, west " +
        "or south.\n");
    add_cmd_item(({ "west wall", "western wall", "wet wall" }),
        ({ "climb" }), "Water drips down the sides of the western " +
        "wall, making it much to slippery to climb.\n");
    add_cmd_item(({ "south wall", "southern wall" }), ({ "climb" }),
        "The southern wall appears much to steep and smooth to be " +
        "climbable. You have to give up as you cannot find any " +
        "handholds to get you started up the wall.\n");
    add_cmd_item(({ "east wall", "eastern wall", "ledge" }),
        ({ "climb" }), "Even though the eastern wall does not " +
        "appear to be much higher than three meters, its upper " +
        "edge is leaning into the cave, making it quite " +
        "impossible to climb.\n");

    add_exit(RSROOMS + "sandy_beach3", "out", 0, 3);

    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs) }),
        ({ "west wall", "western wall", "wet wall" }), 5);

    setuid();
    seteuid(getuid());

    setup_tells();
    KURINOSTMAP;

    reset_room();
}


/*
 *  FUNCTION : init
 *  Arguments: None
 *  Returns  : void
 * 
 *  Adds actions to the room, making it more interesting to explore.
 *
 */
public void init()
{
    ::init();

    ADD(drink_water, "drink");
}


/*
 *  FUNCTION : show_light
 *  Arguments:
 *  Returns  :
 * 
 *  Returns a string with the light that enters the cave.
 *
 */
public string
show_light()
{
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        return "pale moonlight";

    case TOD_DAWN:
        return "faint sunlight";

    case TOD_DAY:
        return "glittering sunlight";

    case TOD_TWILIGHT:
        return "fading sunlight";
    }
}


/*
 *  FUNCTION : show_longdesc
 *  Arguments:
 *  Returns  :
 * 
 *  Show the longdescription of the room, based on time of day.
 *
 */
public string
show_longdesc()
{
    string cave_light = show_light();

    return capitalize(cave_light) + " from the cave entrance does " +
        "little to light up the cave. Echoes from dripping water " +
        "bounce off the cave walls, giving an impression of a " +
        "cave that is much larger than you can see through the " +
        "darkness.\n";
}


/*
 *  FUNCTION : show_ledge
 *  Arguments:
 *  Returns  :
 * 
 *  Show the ledge.
 *
 */
public string
show_ledge()
{
    string cave_light = show_light();
    string show_figure = " A faint rustle somewhere inside the " +
        "cave suggests to you that you are not alone in here. If " +
        "only you were better at hunting down illusive prey, then " +
        "you might spot whatever it is that is lurking in the " +
        "darkness.";

    if (TP->query_skill(SS_HUNTING) > 9)
    {
        show_figure = " Well hidden in the darkness near the " +
            "southern end of the ledge, you can just see a dark " +
            "figure moving slightly.";
    }

    return "Hidden in the darkness, just out of reach about three " +
        "meters up the side of the eastern wall you find some " +
        "kind of ledge. Even the " + cave_light + " from the cave " +
        "entrance cannot light up that part of the cave and it " +
        "seems impossible to estimate the size of the ledge from " +
        "down here." + show_figure + "\n";
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
    set_tell_time(420);

    // add_tell("");

    add_tell("Faint wailings of seagulls carry through the " +
        "entrance to the cave.\n");

    add_tell("Drip! Drip! Echoes of large drops falling into a " +
        "pool carry through the cave.\n");

    add_tell("Faint thunders of waves crashing onto the shore " +
        "outside carries into the cave, echoing from wall to " +
        "wall.\n");
}


/*
 *  FUNCTION : show_cave
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Show the cave desription.
 *
 */
public string
show_cave()
{
    string cave_light = show_light();

    return capitalize(cave_light) + " from the cave entrance does " +
        "little to light up the cave, that only seems to be about " +
        "five meters wide and eight meters long. Echoes from " +
        "dripping water bounce off the cave walls, giving an " +
        "impression of a cave that is much larger than you can " +
        "see through the darkness. The rough cave floor is fairly " +
        "even in the middle of the cave, but quickly becomes " +
        "uneven along the edges, that rise into rough walls of " +
        "varying sizes. Especially atop the eastern wall you " +
        "think you see some kind of ledge about three meters " +
        "above the cave floor.\n";
}


/*
 *  FUNCTION : show_entrance
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Show the entrance description.
 *
 */
public string
show_entrance()
{
    string cave_light = show_light();

    return "Nothing more than a crack in the cave wall, the " +
        "entrance is barely large enough for a person to enter. " +
        capitalize(cave_light) + " is seeping through the crack, " +
        "allowing a little light to enter the cave. If you want " +
        "to leave the cave, the crack is the way out.\n";
}


/*
 *  FUNCTION : show_ceiling
 *  Arguments: none
 *  Returns  : string - the description.
 * 
 *  Show the cave ceiling.
 *
 */
public string
show_ceiling()
{
    string cave_light = show_light();

    return "The " + cave_light + " seeping into the cave through " +
        "the entrance does little to light up the interior of the " +
        "cave. Most of the cave walls reach up out of the light " +
        "and the ceiling is lost in utter darkness.\n";
}


/*
 *  FUNCTION : drink_water
 *  Arguments: string, what to drink.
 *  Returns  : int, 1 if success, 0 if failed.
 * 
 *  Evaluation of the drink command.
 *
 */
public int drink_water(string arg)
{
    if ((arg == "water") || (arg == "from pool") ||
        (arg == "water from pool") || (arg == "from dark pool")
        || (arg == "water from dark pool"))
    {
        if (TP->drink_soft(TP->drink_max() / 16,0))
        {
            write("You kneel by the dark pool and carefully scoop " +
                "up a handfull of water. It is a bit stale, but " +
                "you are refreshed by the water.\n");
            say(QCTNAME(TP) + " kneels by a pool near the western " +
                "wall and drinks from the water.\n");
        }
        else
        {
            write("You glance at the dark and murky water in the " +
                "pool and turn away, satisfied that your thirst " +
                "has been quenched.\n");
        }

        return 1;
    }

    NF("Drink what?\n");
    return 0;
}
