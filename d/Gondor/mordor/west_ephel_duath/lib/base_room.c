/*
 * Base room for western ephel duath mountains
 *
 * --Raymundo, March 2020
 */
#pragma strict_types 
 
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";
inherit "/d/Shire/std/room/room_tell";
//inherit "/d/Gondor/common/lib/area_room.c";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <language.h>
#include <tasks.h>
#include <composite.h>
#include "/d/Gondor/defs.h"
//#include "defs.h"
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/common/lib/herb_list.h"

//For the move command in add_mountains_close()
string room;

//For the long description
string time_desc;

//In each room file, include object here = this_object();
object here;
void
create_plains()
{
    


}
void
create_gondor()
{
	set_short("to be filled in");	
	set_long("to bef illed in");
	
	
	set_room_tell_time(90);
	
	
	try_item( ({"moon", "sun"}), "@@exa_moon@@");
    try_item( ({"sky", "clouds", "cloud"}), "@@exa_sky@@");
	try_item( ({"ground", "dirt", "floor", "rocks", "soil"}), 
        "The soil here is rocky and poor. A few herbs grow, clinging "
        + "tenaciously to life despite the harsh and dark environment. "
        + "To the east, the ground rises sharply as it approaches "
        + "Ephel Duath.\n");
    try_item( ({"herb", "herbs"}), "A skilled herbalist would search "
        + "here to find which herbs grow.\n");
    try_item("mordor", "To the east is Mordor, where the Dark Lord's "
        + "influence is strong.\n");
    try_item("dark lord", "The Dark Lord rules this area of Middle Earth "
        + "with an iron fist, his will steadfast, his word supreme.\n");
    try_item(({"durthang", "fortress", "stronghold"}), "Somewhere in the "
        + "mountains is Durthang, once a Gondorian stronghold, but now "
        + "a home to many vicious orcs--and perhaps a few unlucky "
        + "prisoners.\n");
    try_item( ({"star", "stars"}), "@@exa_stars@@");
    try_item( ({"land", "area"}), "This is a forest of twisted trees in "
        + "Ithilien, near the Mountains of Shadow.\n");
    
    add_room_tell("Fell creatures fly overhead, encircling the mountains.");
    add_room_tell("A fell creature swoops by and shrieks, then flies off.");
    add_room_tell("In the distance, the sound of marching and blarig "
        + "trumpets echoes.");
	here = this_object();
	create_plains();
}

string
moonlight()
{
    object  clock = find_object(CLOCK);
    string time = clock->query_moon();
    if(time == "full" || time == "waxing gibbous"|| time == "waning gibbous")
    {
        if (!(clock->query_war()))
        {
        return(" The moon illuminates the landscape in with a bright silvery light. ");
        }
        else
            return("");
        
    }
    else
    {
        return("");
    }
}

string
exa_moon()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_moon();
    if(clock->query_time_of_day() == "night")
    {
        if (!(clock->query_war()))
        {
        return("The moon is " +  time + ". It's fairly visible as it makes "
            + "its way across the night sky." + moonlight() + "\n");
        }
        else
        {
            return("Dark clouds cover the sky, making it impossible to see "
                + "the moon.\n");
        }
    }
    else
    {
        return("It is " + clock->query_time_of_day() + ". The sun illuminates "
            + "the landscape as it marches toward the horizon.\n");
    }
}

string
exa_stars()
{
     object  clock = find_object(CLOCK);
    string  time  = clock->query_moon();
    if(clock->query_time_of_day() == "night")
    {
        if (!(clock->query_war()))
        {
        return("Stars dot the sky like large flakes of salt scattered across "
            + "a table.\n");
        }
        else
        {
            return("Thick billow clouds obscure the night sky, plunging the "
                + "area into complete darkness.\n");
        }
    }
    else
    {
        return("It is " + clock->query_time_of_day() + ". You cannot see the "
            + "stars now!\n");
    }
}
    

string
exa_sky()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_moon();
    if(clock->query_time_of_day() == "night")
    {
        return("The " + time + " moon makes its way lazily across the "
            + "night sky, stars glittering diamond-like behind it." 
            + moonlight() + "\n");
    }
    else
        return("The sun is visible in the sky. The sky is more grey "
            + "than blue here, and begins to look almost black as "
            + "you shift your gaze eastward.\n");
}

void
mountain_herbs_1()
{
	set_up_herbs( ({HERB_DIR + "frostheal",
                    HERB_DIR + "madwort",
                    KRYNN_HERB_DIR + "soapweed",
                    SHIRE_HERB_DIR + "parsley"}));
}

void
mountain_herbs_2()
{
    set_up_herbs( ({KRYNN_HERB_DIR + "bkd_sedge",
                    KRYNN_HERB_DIR + "fireweed",
                    HERB_DIR + "savory",
                    HERB_DIR + "seregon"}));
}

void
plains_herbs_1()
{
    set_up_herbs( ({ HERB_DIR + "sumac",
                     HERB_DIR + "angurth",
                     HERB_DIR + "bean_lima",
                     HERB_DIR + "marjoram" }));
}

void
plains_herbs_2()
{
    set_up_herbs( ({ HERB_DIR + "angurth",
                    HERB_DIR + "suranie",
                    KRYNN_HERB_DIR + "fiddlehead",
                    KRYNN_HERB_DIR + "tiger_lily",
                    SHIRE_HERB_DIR + "pawnrose",
                    HERB_DIR + "sumac"}));
}

/* Function Name:   time_description()
 * Arguments:       none.
 * Description:     Returns a string describing what the sky looks like
 *                      for outdoor rooms west of Ephel Duath. This close
 *                      to the mountains, the shadows are opressive. The 
 *                      night is dark, and sometimes (because of shadows and 
 *                      clouds), even the day is dark.
 */
                    
public string
time_description()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day();
            

    if (!(clock->query_war()))
    {
        switch (time)
        {
        case "night":
            time_desc = "A sprinkling of Elbereth's stars can be seen " +
		"twinkling high above Middle-Earth. It is night in Ithilien. ";
            switch (clock->query_moon())
            {
            case "full":
                time_desc += "The full moon, fair Ithil, bathes the " +
		    "mountains in an eery glow. "; 
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, 1);
                break;
            case "waxing crescent":
               time_desc += "The crescent moon illuminates the " + 
		   "landscape faintly. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, -1);
                break;
            case "waxing gibbous":
                time_desc += "The moon, now approaching full, casts " +
		    "a silvery light. "; 
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, 1);
                break;
            case "waning gibbous":
                time_desc += "The moon, now past full, still casts a " +
		    "serviceable white light. "; 
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, 1);
                break;
            case "waning crescent":
                time_desc += "The moon tilts its slender upturned " +
		    "horns over the gloomy landscape. "; 
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, -1);
                break;
            case "new":
                time_desc += "The moon is new, showing only a sliver of "
                    + "light in the sky. ";
                here->remove_prop(ROOM_I_LIGHT);
                here->add_prop(ROOM_I_LIGHT, -1);
                break;
                
            default:
                time_desc += "The sky is obscured by dark clouds. ";
                break;
            }
            break;
        case "afternoon":
            time_desc = "Daylight shines across Ithilien, pushing the "
                + "mountains' shadows back toward Mordor. " 
                + "It is afternoon. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, 1);
            break;
        case "morning":
            time_desc = "The sun is rising in the east, causing the mountains "
                + "to cast a long shadow across the land. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, -1);
            break;
        case "noon":
            time_desc = "The sun is almost at its peak on its way " +
                "across the sky. The mountains' shadows have begun to "
               + "recede. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, 1);
            break;
        case "evening":
            time_desc = "The sun is setting in the west, colouring the " + 
                "sky golden red. ";
            here->remove_prop(ROOM_I_LIGHT);
            break;
        case "early morning":
            time_desc = "The sun is rising in the east. The Ephel Duath mountains "
               + "cast long shadows across Ithilien. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, -1);
            break;
        }
    }
    else 
    {
        switch (time)
        {
        case "evening":
        case "night":
        case "early morning":
            time_desc = "Dark clouds fill the sky above the mountains to the "
                + "east. It must be night, because the sky is almost compeltely "
                + "black. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, -2);
            break;
        case "morning":
            time_desc = "Thick clouds cover the sky. Mostly they are black, "
                + "but a few shades of grey shine through, indicating that "
                + "it's morning. ";
            here->remove_prop(ROOM_I_LIGHT);
            here->add_prop(ROOM_I_LIGHT, -1);
            break;
        case "noon":
            time_desc = "A dark mass of clouds seems to be rolling in from " + 
                "the east, covering the sky above you." + 
                "It is not much lighter now than it usually is at " +
                "night, but still you suspect it is the middle of the day.";
            here->remove_prop(ROOM_I_LIGHT);
            break;
        case "afternoon":
            time_desc = "A thick mass of clouds covers the sky, making it " + 
                "difficult to see far. You see light grey patches to the west "
                + "and realize that it must be afternoon.";
            here->remove_prop(ROOM_I_LIGHT);
            break;
        }
    }


    
    return (time_desc);
}

/* Function Name:   mountain_shadows()
 * Arguments:       none
 * Description:     This function makes the description of the shadows for 
 *                      the mountain add_item. Seems a nice touch to have 
 *                      the mountains change a bit with the clock.
 */ 
public string
mountain_shadows()
{
    object  clock = find_object(CLOCK);
    string  time  = clock->query_time_of_day(); 
    string shadow;
    
    switch (time)
        {
    case "night":
        shadow = "The mountains are bathed in moonlight, making their "
            + "peeks look like jagged teeth. ";
        break;
    case "early morning":
        shadow = "A faint orange glow shines behind the mountains, forcing "
            + "a dark shadow toward the West. ";
        break;
    case "morning": 
        shadow = "The mountains cast a long shadow over the land, like "
            + "the Dark Lord himself is gazing down upon you. ";
        break;
    case "noon":
        shadow = "The shadows have retreated to the East, encroaching only "
            + "slightly into Ithilien. ";
        break;
    case "afternoon":
        shadow = "The shadows, so prominent in the morning, are but a distant "
            + "memory now, as they can only been seen on the mountains "
            + "themselves. ";
        break;
    case "evening":
        shadow = "The mountains are bathed in oranges, reds, and yellows; the "
            + "only shadows visible are in the deepest craigs. ";
        break;
    default:
        shadow = "The mountains are shrowded in shadow, looking at once "
            + "mysterious and deadly. ";
        break;
        }

    return shadow;
}

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    time_description();
    ::enter_inv(ob, from);
}


//add_items for mountains.
void
add_mountains()
{
    try_item( ({"mountain", "mountains", "ephel duath", "wall", "fence"}), 
        "The Ephel Duath range towers above "
        + "you. " + "@@mountain_shadows@@" + "They tower over you almost like "
        + "a wall of rock.\n");
    try_item( ({"shadow", "shadows"}), "The shadows are dark and black, "
        + "extending from Mordor toward the west.\n");
}

/* Function Name:       add_mountains_close()
 * Arguments:           direction - the direction the path is
 *                      compared to the mountain. For example,
 *                      'up' or 'east'.
 *                      location - the file name of the mountain room
 *                      the player will go to.
 * Description:         Makes add_items and room_tells for the
 *                      Ephel Duath mountains when you're close
 *                      to them.
 */

void
add_mountains_close(string direction, string location)
{
    try_item( ({"mountain", "mountains", "ephel duath"}),
        "You are so close to the mountains that you can't even see the "
        + "peaks of the tallest ones. They are rugged and intimidating "
        + "up close. Boulders and shrubs dot the sides of the mountains "
        + "and from time to time, you can see small mountain goats or "
        + "ground squirrels moving about.\n");
    try_item( ({"rock", "rocks", "boulder", "boulders", "shrub", "shrubs"}),
        "The boulders are quite large, way too big for even an ogre to "
        + "lift. Small shrubs, perhaps a meter high, grow here and there "
        + "amongst the boulders. You can see what could be a path "
        + "disappearing between two boulders.\n");
    try_item( ({"path", "trail", "road", "track"}),
        "It is a path! There is a dirt trail heading " + direction 
        + " into the mountains. You could likely try to follow the path.\n");
    add_cmd_item( ({"path", "trail", "road", "track"}), 
        ({"follow", "climb", "go"}), "@@follow_path@@");
    add_room_tell("A ground squirrel ducks between two boulders on the side "
        + "of the mountains.");
    add_room_tell("A squirrel runs across the path on the mountain.");
    add_room_tell("A goat carefully climbs the rocks on the side of the mountain.");
    add_room_tell("A raven perches on a boulder. It seems to be watching you.");
    room = location;
}

//Moves the player onto the path 
int
follow_path()
{
    if( ( (TP->query_fatigue() / TP->query_max_fatigue()) >= 8/10) && ( (TP->query_skill(SS_CLIMB) + TP->query_skill(SS_AWARENESS)) >= 75))
    {
        tell_room( (ED_W_ROOM + room), QCTNAME(TP) + " arrives following the path.\n", TP);
        write("You follow the path into the mountains.\n");
        TP->move_living("M", (ED_W_ROOM + room));
        say(QCTNAME(TP) + " follows the path into the mountains.\n");
        return 1;
    }
    else
    {
        write("You try to follow the path into the mountains but lose "
            + "your way.\n");
        say(QCTNAME(TP) + " tries to follow the path into the "
            + "mountains but becomes "
            + "disoriented.\n");
        return 1;
    }
}
 
void 
add_forest_floor()
{
    try_item("forest", "There enough trees here to call this a forest. They "
        + "are numerous, but they also look bent and twisted, as if a heavy "
        + "load weighs upon them.\n");
    try_item( ({"tree", "trees"}), "Each tree is about as tall as two trolls "
        + "standing one atop the other. The grain in their trunks looks tight, "
        + "showing that they grow slowly. The trees are twisted and bent toward "
        + "the west and away from the east, as if something heavy weighs on "
        + "them.\n");
    try_item( ({"leaf", "leaves"}), "The trees have leaves on them. From a "
        + "distance the leaves look green, but the edges are starting to turn "
        + "brown.\n");
    add_prop(ROOM_S_DARK_LONG, "A forest near the Mountains of Shadow.\n");
    add_room_tell("A cold wind blows, rustling the leaves in the trees.");
    add_room_tell("The trees creek in the wind.");
    add_room_tell("A raven perches in the high branches of a tree, watching you.");
    add_room_tell("High in the sky, a huge winged creature flies toward Minas Morgul.");
    add_room_tell("You hear a bone chilling screech from high in the sky.");
}
