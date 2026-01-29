/*
* sail_room_base.c
*
* Based off sailing room code at /d/Ansalon/goodlund/bloodsea/std/
* 
* To be used for sailing rooms outside of that region.
*
* by Arman 8 Feb 2020
*/

#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <composite.h>
#include "/d/Calia/sys/water.h"
#include CLOCKH

#pragma save_binary

/* Inherit the Krynn room */
inherit OR_FILE

/* Global Variables */
string sink_path;
string *row_exits_arg = ({ });
string *row_exits_path = ({ });
int *row_exits_tired = ({ });
mixed *row_exits_check = ({ });

object *boats = ({ }); 

string boat_vista; 

int sailing_difficulty = 0;
mixed sailing_difficulty_message = 0;

#define KRYNN_SAILING_SKILL   143020
#define KRYNN_MAX_BOATS 30

#define CREATE "create_sea_room"
#define RESET "reset_sea_room"

public string
sea_short()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "Midnight on the high seas";
	    break;
	case NIGHT:
	    str = "Spring night on the high seas";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the high seas";
	    break;
	case MORNING:
	    str = "Spring morning on the high seas";
	    break;
	case NOON:
	    str = "Noon on the high seas";
	    break;
	case AFTERNOON:
	    str = "Afternoon on the high seas";
	    break;
	case EVENING:
	    str = "Spring evening on the high seas";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Summer night on the high seas";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the high seas";
	    break;
	case MORNING:
	    str = "Summer morning on the high seas";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "Afternoon on the high seas";
	    break;
	case EVENING:
	    str = "Summer evening on the high seas";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Cloudy autumn night on the high seas";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the high seas";
	    break;
	case MORNING:
	    str = "Cloudy autumn morning on the high seas";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "Cloudy afternoon on the high seas";
	    break;
	case EVENING:
	    str = "Cloudy autumn evening on the high seas";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "A stormy winter night on the high seas";
	    break;
	case EARLY_MORNING:
	    str = "Early winter morning on the high seas";
	    break;
	case MORNING:
	    str = "Windy winter morning on the high seas";
	    break;
	case NOON:
	    str = "A stormy winter day on the high seas";
	    break;
	case AFTERNOON:
	    str = "A stormy afternoon in winter on the high seas";
	    break;
	case EVENING:
	    str = "A stormy winter evening on the high seas";
	    break;
	}
	break;
    }
    return str;
}

public string
turbidus_sea_short()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "Midnight on the Turbidus Ocean";
	    break;
	case NIGHT:
	    str = "Spring night on the Turbidus Ocean";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the Turbidus Ocean";
	    break;
	case MORNING:
	    str = "Spring morning on the Turbidus Ocean";
	    break;
	case NOON:
	    str = "Noon on the Turbidus Ocean";
	    break;
	case AFTERNOON:
	    str = "Afternoon on the Turbidus Ocean";
	    break;
	case EVENING:
	    str = "Spring evening on the Turbidus Ocean";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Summer night on the Turbidus Ocean";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the Turbidus Ocean";
	    break;
	case MORNING:
	    str = "Summer morning on the Turbidus Ocean";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "Afternoon on the Turbidus Ocean";
	    break;
	case EVENING:
	    str = "Summer evening on the Turbidus Ocean";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Cloudy autumn night on the Turbidus Ocean";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the Turbidus Ocean";
	    break;
	case MORNING:
	    str = "Cloudy autumn morning on the Turbidus Ocean";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "Cloudy afternoon on the Turbidus Ocean";
	    break;
	case EVENING:
	    str = "Cloudy autumn evening on the Turbidus Ocean";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "A stormy winter night on the Turbidus Ocean";
	    break;
	case EARLY_MORNING:
	    str = "Early winter morning on the Turbidus Ocean";
	    break;
	case MORNING:
	    str = "Windy winter morning on the Turbidus Ocean";
	    break;
	case NOON:
	    str = "A stormy winter day on the Turbidus Ocean";
	    break;
	case AFTERNOON:
	    str = "A stormy afternoon in winter on the Turbidus Ocean";
	    break;
	case EVENING:
	    str = "A stormy winter evening on the Turbidus Ocean";
	    break;
	}
	break;
    }
    return str;
}


public string
sea_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight out on the high sea. Above, the " +
	    "night sky shines brightly stars. The silver moon Solinari " +
	    "and the smaller moon Lunitari illuminate the ever shifting ocean " +
            "that surrounds you. ";
	    break;
	case NIGHT:
	    str = "You are surrounded by waters of the high sea " +
	    "on a calm spring night. The silence is beautiful and unbroken, " +
	    "with the brightly shining stars above you your quiet companions, " +
	    "illuminating the sea around you. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to lighten on the horizon as the sun prepares " +
	    "to rise from the calm " +
	    "waters of the high sea. Waves around you rock you " +
	    "gently as you sway slowly to a soft spring breeze. ";
	    break;
	case MORNING:
	    str = "The rising suns morning rays shine down over the " +
	    "high sea. While not " +
	    "quite warm, the spring wind is fresh and salty, reminding you " +
	    "summer is just around the corner. ";
	    break;
	case NOON:
	    str = "It is a warm spring day on Bloodsea of Istar. " +
	    "Surprisingly, it is rather calm at the " +
	    "moment as this savage ocean is renown for its severe " +
	    "weather. ";
	    break;
	case AFTERNOON:
	    str = "The afternoon skies begin to darken and clouds begin to gather " +
	    "as the sun begins to descend from the heavens. The " +
	    "sea rises and falls as a soft breeze blows across the high seas. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent towards the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the " +
	    "sun sets. The sea rises and falls as a soft spring breeze blows across " +
            "the high seas. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "The warm night air here on the high seas " +
	    "is a pleasant relief after the scorching hot " +
	    "summer days out at sea. A gusty wind " +
	    "blows across the waters, sending spray up into the air " +
	    "and cooling you further. ";
	    break;
	case EARLY_MORNING:
	    str = "The cloak of night begins to retreat as " +
	    "the suns first rays appear over the horizon on the " +
	    "high seas. The shrill cry of " +
	    "an albatross far above you can be heard as it searches " +
	    "the sea for a feed of fish. ";
	    break;
	case MORNING:
	    str = "With the rising of the morning sun over the " +
	    "high seas, the air begins to heat up. This seems " +
	    "to encourage a gusty summer wind to blow across the " +
	    "turbulent waters, sending salty sea spray all around. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon " +
	    "your head out on the shadeless high seas" +
            ". High humidity makes it very uncomfortable, and even a " +
	    "gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING:
	    str = "With the evening sun beginning its descent " +
	    "behind the horizon, the fierce summer heat and " +
	    "humidity begins to subside much to your relief. A " +
	    "gusty wind blows around you, chilling your sweat " +
	    "and sending spray up into the air off the waters of the " +
            "high sea. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You are surrounded by the high seas " +
            "on a windy autumn night. Dark clouds gather " +
	    "in the sky, hinting at a storm... you may be in for a " +
            "rough night! ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to grey as sunrise approaches the " +
	    "horizon of the high sea. An autumn wind " +
	    "blows across the waters, bringing with it " +
	    "the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "The cool rays of the morning sun shine through " +
	    "holes in the grey clouds that seem to have occupied " +
	    "the heavens over the high seas. " +
	    "A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You are surrounded by the turbulent waters of the " +
            "high seas on a cool autumn " +
	    "day. A chill wind blows across the waters, " +
	    "bringing with it the smell of an approaching " +
	    "storm. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent " +
	    "beyond the horizon. A chill autumn wind rises, waking the " +
	    "angry waters of the high seas. You get the impression " +
	    "that it will be a rough time on the seas this night. ";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "A jagged fork of lightning illuminates the nights " +
	    "sky, briefly revealing roiling black clouds. A mighty clap of thunder " +
	    "echoes across the high sea, and a " +
	    "harsh winter wind howls around you. The waves rise ominously in savage " +
	    "fury, then battering against you with great force. " +
	    "The seas of winter is truly where the Gods show their fury! ";
	    break;
	case EARLY_MORNING:
	    str = "The nights sky begins to lighten, and the " +
	    "savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the waters of the high sea. ";
	    break;
	case MORNING:
	    str = "The morning air is chill on the high seas " +
	    "and even the rising sun does little to remove " +
	    "the biting cold of the winter wind that howls " +
	    "around you. With the rise of the sun, the seas " +
	    "are displayed before as harsh and unforgiving to all " +
	    "who travel it. ";
	    break;
	case NOON:
	    str = "While the middle of the day, billowing storm " +
	    "clouds shadow the waters " +
            "casting a dark pall over the agitated seas. " +
	    "A cold winter wind howls around you, spraying you with " +
	    "icy water that freezes your skin. ";
	    break;
	case AFTERNOON:
	    str = "The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the waters " +
	    "of the high sea rolling. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun shines a hazy " +
	    "red as it begins its descent behind the horizon. " +
	    "In the distance the echo of thunder rolls its way " +
	    "to you from the gathering of angry black clouds in " +
	    "the distance, harkening another winter storm on the " +
	    "high seas. ";
	    break;
	}
	break;
    }
    return str;
}

string
turbidus_sea_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight out on the Turbidus Ocean. Above, the " +
	    "night sky shines brightly stars. The silver moon Solinari " +
	    "and the smaller moon Lunitari illuminate the ever shifting ocean " +
            "that surrounds you. ";
	    break;
	case NIGHT:
	    str = "You are surrounded by waters of the Turbidus Ocean " +
	    "on a calm spring night. The silence is beautiful and unbroken, " +
	    "with the brightly shining stars above you your quiet companions, " +
	    "illuminating the sea around you. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to lighten on the horizon as the sun prepares " +
	    "to rise from the calm " +
	    "waters of the Turbidus Ocean. Waves around you rock you " +
	    "gently as you sway slowly to a soft spring breeze. ";
	    break;
	case MORNING:
	    str = "The rising suns morning rays shine down over the " +
	    "high sea. While not " +
	    "quite warm, the spring wind is fresh and salty, reminding you " +
	    "summer is just around the corner. ";
	    break;
	case NOON:
	    str = "It is a warm spring day on Turbidus Ocean. " +
	    "Surprisingly, it is rather calm at the " +
	    "moment as this savage ocean is renown for its severe " +
	    "weather. ";
	    break;
	case AFTERNOON:
	    str = "The afternoon skies begin to darken and clouds begin to gather " +
	    "as the sun begins to descend from the heavens. The " +
	    "sea rises and falls as a soft breeze blows across the Turbidus Ocean. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent towards the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the " +
	    "sun sets. The sea rises and falls as a soft spring breeze blows across " +
            "the Turbidus Ocean. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "The warm night air here on the Turbidus Ocean " +
	    "is a pleasant relief after the scorching hot " +
	    "summer days out at sea. A gusty wind " +
	    "blows across the waters, sending spray up into the air " +
	    "and cooling you further. ";
	    break;
	case EARLY_MORNING:
	    str = "The cloak of night begins to retreat as " +
	    "the suns first rays appear over the horizon of the " +
	    "Turbidus Ocean. The shrill cry of " +
	    "an albatross far above you can be heard as it searches " +
	    "the sea for a feed of fish. ";
	    break;
	case MORNING:
	    str = "With the rising of the morning sun over the " +
	    "Turbidus Ocean, the air begins to heat up. This seems " +
	    "to encourage a gusty summer wind to blow across the " +
	    "turbulent waters, sending salty sea spray all around. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon " +
	    "your head out on the shadeless Turbidus Ocean" +
            ". High humidity makes it very uncomfortable, and even a " +
	    "gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING:
	    str = "With the evening sun beginning its descent " +
	    "behind the horizon, the fierce summer heat and " +
	    "humidity begins to subside much to your relief. A " +
	    "gusty wind blows around you, chilling your sweat " +
	    "and sending spray up into the air off the waters of the " +
            "Turbidus Ocean. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You are surrounded by the Turbidus Ocean " +
            "on a windy autumn night. Dark clouds gather " +
	    "in the sky, hinting at a storm... you may be in for a " +
            "rough night! ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to grey as sunrise approaches the " +
	    "horizon of the Turbidus Ocean. An autumn wind " +
	    "blows across the waters, bringing with it " +
	    "the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "The cool rays of the morning sun shine through " +
	    "holes in the grey clouds that seem to have occupied " +
	    "the heavens over the Turbidus Ocean. " +
	    "A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You are surrounded by the turbulent waters of the " +
            "Turbidus Ocean on a cool autumn " +
	    "day. A chill wind blows across the waters, " +
	    "bringing with it the smell of an approaching " +
	    "storm. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent " +
	    "beyond the horizon. A chill autumn wind rises, waking the " +
	    "angry waters of the Turbidus Ocean. You get the impression " +
	    "that it will be a rough time on the seas this night. ";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "A jagged fork of lightning illuminates the nights " +
	    "sky, briefly revealing roiling black clouds. A mighty clap of thunder " +
	    "echoes across the Turbidus Ocean, and a " +
	    "harsh winter wind howls around you. The waves rise ominously in savage " +
	    "fury, then battering against you with great force. " +
	    "The seas of winter is truly where the Gods show their fury! ";
	    break;
	case EARLY_MORNING:
	    str = "The nights sky begins to lighten, and the " +
	    "savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the waters of the Turbidus Ocean. ";
	    break;
	case MORNING:
	    str = "The morning air is chill on the Turbidus Ocean " +
	    "and even the rising sun does little to remove " +
	    "the biting cold of the winter wind that howls " +
	    "around you. With the rise of the sun, the seas " +
	    "are displayed before as harsh and unforgiving to all " +
	    "who travel it. ";
	    break;
	case NOON:
	    str = "While the middle of the day, billowing storm " +
	    "clouds shadow the waters " +
            "casting a dark pall over the agitated Turbidus Ocean. " +
	    "A cold winter wind howls around you, spraying you with " +
	    "icy water that freezes your skin. ";
	    break;
	case AFTERNOON:
	    str = "The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the waters " +
	    "of the Turbidus Ocean rolling. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun shines a hazy " +
	    "red as it begins its descent behind the horizon. " +
	    "In the distance the echo of thunder rolls its way " +
	    "to you from the gathering of angry black clouds in " +
	    "the distance, harkening another winter storm on the " +
	    "Turbidus Ocean. ";
	    break;
	}
	break;
    }
    return str;
}

string
add_item_storm()
{
    string str;
    switch(GET_SEASON)
    {
    case WINTER:
	str = "Angry black storm clouds roil madly overhead. The " +
	"echo of the thunders deep growl rolls across " +
	"the sea, and a wild, biting wind harkens the storms "+
	"potent fury.\n";
	break;
    case SUMMER:
	str = "Clouds in the sky. How surprising. Want to count " +
	"grass next?\n";
	break;
    case SPRING:
	str = "Clouds in the sky. How surprising. Want to count " +
	"grass next?\n";
	break;
    case AUTUMN:
	str = "Clouds gather in the heavens above you, " +
	"hinting at a storm.\n";
	break;
    }
    return str;
}



/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 1; 
}

void
boat_enter(object b)
{
    boats = filter(boats, objectp); 
    boats += ({ b }); 
}


void
boat_exit(object b)
{
    boats = filter(boats, objectp); 
    boats -= ({ b }); 
}


object 
*query_boats()
{
    boats = filter(boats, objectp); 
    return boats; 
}


void
set_boat_vista(string s)
{
    boat_vista = s; 
}


string
query_boat_vista()
{
    return boat_vista;
}


/* Returns the appropriate desc to be added for the row exits */
string
row_exit_desc()
{
    string desc;

    desc = "";
    if (sizeof(row_exits_arg))
        desc += ("You may sail: " + COMPOSITE_WORDS(row_exits_arg)+".\n");

    return desc;
}

/* Set the path to the room where things will sink to, if any. 
   Non living objects will automatically sink to that exit. 
   You don't have to set this if you want things to sink "down", as
   this is done by default if you add a swim exit for that direction. */
void
set_sink_path(string sp)
{
    sink_path = sp;
}


string
query_sink_path()
{
    return sink_path;
}

/* Code to check the sailing skill requirement of the sailor for
 * this particular room.
 */

public void
set_sailing_difficulty(int skill)
{
    sailing_difficulty = skill;
}

public int
query_sailing_difficulty()
{
    return sailing_difficulty;
}

public void
set_sailing_difficulty_message(string msg)
{
    sailing_difficulty_message = msg;
}

public mixed
query_sailing_difficulty_message()
{
    return sailing_difficulty_message;
}

public string
query_sailing_difficulty_desc()
{
    int difficulty = query_sailing_difficulty();

    switch(difficulty)
    {
        case 0..29:
            return "";
        case 30..50:
            return "The waters here are tricky to navigate. ";
        case 51..75:
            return "The waters here are challenging to navigate. ";
        case 76..90:
            return "The waters are extremely challenging to navigate. ";
        case 91..100:
            return "The waters here are near impossible to navigate. ";
        default:
            return "";
    }

}



/*
* IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
*/

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

    add_item(({"clouds","storm clouds","black clouds","storm",
	"billowing storm clouds","black storm clouds",
	"angry black clouds","grey clouds"}),
      "@@add_item_storm");

    set_sink_path("/d/Ansalon/balifor/flotsam/room/bottom_of_bay");
   
}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
   call_other(TO, RESET);
}

string
dir_alias(string str)
{
    switch (str) { 
        case "n" : return "north"; 
                   break;
        case "s" : return "south"; 
                   break;
        case "e" : return "east"; 
                   break;
        case "w" : return "west"; 
                   break;
        case "nw" : return "northwest"; 
                   break;
        case "ne" : return "northeast"; 
                   break;
        case "se" : return "southeast"; 
                   break;
        case "sw" : return "southwest"; 
                   break;
        case "u" : return "up"; 
                   break;
        case "d" : return "down"; 
                   break;
     }
     return str;
}


/*
 * This is the function which checks the rowing action and makes 
 * the call to carry out the row if it's possible. 
 * It is called from the inside of the rowing boat itself when a 
 * player does an action there. 
 */

int
try_row(string str)
{
    int i, tired, tmp;
    object tp = this_player();
    object row_to; 

    if (!str)
    {
	notify_fail("Sail where?\n");
	return 0;
    }

    str = dir_alias(str);

    i = member_array(str, row_exits_arg);

    if (i == -1)
    {
	notify_fail("You can't sail in that direction.\n");
	return 0;
    }

    if (this_object()->check_call(row_exits_check[i])) 
        return 1;

    tired = row_exits_tired[i]; 

    if (tp->query_fatigue() < tired) {
        notify_fail("You are too tired to sail anywhere at the moment. " +
            "You decide to drift where you are.\n"); 
        return 0;
    }

    if (sizeof(row_exits_path[i]->query_boats()) >= KRYNN_MAX_BOATS) {   
        notify_fail("Oh dear! It seems there are too many ships " +
                    "over there and your ship won't fit!\n"); 
        return 0;
    } 

    if (tp->query_skill(KRYNN_SAILING_SKILL) < 
        row_exits_path[i]->query_sailing_difficulty())
    {
        notify_fail("The conditions in that direction are beyond " +
            "your sailing skill to navigate through!\n"); 
        return 0;
    }

    if (row_exits_path[i]->query_sailing_difficulty_message())
        tp->catch_tell(row_exits_path[i]->query_sailing_difficulty_message());

    tp->add_fatigue(-tired);
    environment(tp)->carry_out_row(str, row_exits_path[i]); 
    return 1;
}

/*
 * Function name: add_swim_exit
 * Description:   Add one swim exit to the room. 
 */
varargs void
add_swim_exit(string place, string cmd, mixed efunc, mixed tired, 
              mixed non_obvious)
{
    if ((cmd == "down") && (!stringp(query_sink_path())))
        set_sink_path(place); 

    add_exit(place, cmd, efunc, tired, non_obvious);  
}

/*
 * Function name: add_wade_exit
 * Description:   Add one wade exit to the room. 
 */
add_wade_exit(string place, string cmd, mixed efunc, mixed tired,
              mixed non_obvious)
{
    add_exit(place, cmd, efunc, tired, non_obvious); 
}

/*
 * Function name: add_row_exit
 * Description:   Add one ROW exit (for rowing boats) to the room. 
 * Arguments:     path: The filename of the room to move to
 *                arg:  The argument given after "row" e.g.
 *                       "north", "cave"
 *                check: A check to see if can move in that direction,
 *                       often uses vbfc. Possible values are: 
 *                       0: Direct move to destination
 *                       1: Can not move in this dir, do not try others
 *                tired: How much more tired the player should become from
 *                       rowing in that direction. Default is 1.
 */

varargs void
add_row_exit(string path, string arg, mixed check, int tired)
{
    row_exits_path += ({ path });

    row_exits_arg += ({ arg });

    row_exits_check += ({ check });

    if (!tired)
        tired = 1;
    row_exits_tired += ({ tired });
}


/*
 * Function name: remove_row_exit
 * Description:   Remove one row exit from the room.
 * Arguments:     arg:   The argument given after "row" for the exit to be 
 *                       removed.
 */
public int
remove_row_exit(string arg)
{
    int i;

    if (query_prop(ROOM_I_NO_EXTRA_EXIT))
        return 0;

    i = member_array(arg, row_exits_arg);
    if (i == -1) 
        return 0;

    row_exits_arg = exclude_array(row_exits_arg, i, i);
    row_exits_path = exclude_array(row_exits_path, i, i);
    row_exits_check = exclude_array(row_exits_check, i, i);
    row_exits_tired = exclude_array(row_exits_tired, i, i);

    return 1;
}


/* An object sinks */
void
sink(object ob)
{
    string sp, sv;

    if (!objectp(ob)) 
        return;

    if (!objectp(present(ob, this_object())))
        return;

    if (!stringp(sp = query_sink_path()))
        return;

    sv = ((ob->num_heap() > 1) ? "sink" : "sinks"); 
    tell_room(this_object(), capitalize(LANG_THESHORT(ob)) + 
                             " " + sv + " downwards.\n");
    ob->move(sp);
    tell_room(sp, capitalize(LANG_THESHORT(ob)) + " " + sv + " in.\n");
}


int
deep_water_room(object r)
{
    if ((r->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) || 
        stringp(r->query_sink_path())) 
        return 1;
    else
        return 0;
}


/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *                We need to add the drown object to livings who enter.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
     object d; 

     ::enter_inv(ob, from);

     if ((!living(ob)) && !ob->query_prop(OBJ_I_FLOAT)) 
     {
         set_alarm(2.0, 0.0, &sink(ob));
         return;
     }

     /* Burn out torches dropped into water */ 
     if (ob->query_lit(0) == -1) {    
         ob->burned_out();  
         return;
     }

     if (!interactive(ob) || ob->query_prop(LIVE_I_GILLS))
         return;

     if (query_standard_water_room()) { 
         if (!objectp(d = ob->query_prop(LIVE_O_DROWN_OB))) { 
             d = clone_object(DROWN_OBJECT);
             d->move(ob); 
         }
         d->reset_trap_move(); 
         /* Burn out torches held by player when in deep water */ 
         if (deep_water_room(this_object()) && 
             !deep_water_room(from)) 
             d->extinguish_lights(); 
    }
}



/*
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 *                We need to remove the drown object from livings who exit.
 * Arguments:     ob: The object that just left this inventory
 *                to: Where it went.
 */
public void
leave_inv(object ob, object to)
{
    object dob;

    ::leave_inv(ob, to);

    if (!living(ob))
        return;

    /* quitting */
    if (!objectp(to)) 
        return;

    dob = ob->query_prop(LIVE_O_DROWN_OB);
    if (!objectp(dob)) 
        return;

    /* If they've gone linkdead, we'll not remove the drown object. */ 
    if (file_name(to) == OWN_STATUE) 
        return;

    /* Otherwise, if they're gone into a room which isn't one of 
       our standard underwater rooms, get rid of the drown object. */ 
    if (!to->query_standard_water_room()) 
        dob->remove_object();

    /* Another possibility is if you've swum to the surface, in which 
       case catch your breath but retain the drown object. */ 
    if (!(to->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER))
        dob->reset_oxygen_debt(); 
}




