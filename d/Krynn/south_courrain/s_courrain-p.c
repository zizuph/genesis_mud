#include "local.h"
#include CLOCKH
#include "/d/Krynn/guilds/OotS/defs.h"

inherit ROOM_BASE;

string
bloodsea_short()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "Midnight on the Bloodsea of Istar";
	    break;
	case NIGHT:
	    str = "Spring night on the Bloodsea of Istar";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the Bloodsea of Istar";
	    break;
	case MORNING:
	    str = "Spring morning on the Bloodsea of Istar";
	    break;
	case NOON:
	    str = "Noon on the Bloodsea of Istar";
	    break;
	case AFTERNOON:
	    str = "Afternoon on the Bloodsea of Istar";
	    break;
	case EVENING:
	    str = "Spring evening on the Bloodsea of Istar";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Summer night on the Bloodsea of Istar";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the Bloodsea of Istar";
	    break;
	case MORNING:
	    str = "Summer morning on the Bloodsea of Istar";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "Afternoon on the Bloodsea of Istar";
	    break;
	case EVENING:
	    str = "Summer evening on the Bloodsea of Istar";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "Cloudy autumn night on the Bloodsea of Istar";
	    break;
	case EARLY_MORNING:
	    str = "Early morning on the Bloodsea of Istar";
	    break;
	case MORNING:
	    str = "Cloudy autumn morning on the Bloodsea of Istar";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "Cloudy afternoon on the Bloodsea of Istar";
	    break;
	case EVENING:
	    str = "Cloudy autumn evening on the Bloodsea of Istar";
	    break;
	}
	break;
    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "A stormy winter night on the Bloodsea of Istar";
	    break;
	case EARLY_MORNING:
	    str = "Early winter morning on the Bloodsea of Istar";
	    break;
	case MORNING:
	    str = "Windy winter morning on the Bloodsea of Istar";
	    break;
	case NOON:
	    str = "A stormy winter day on the Bloodsea of Istar";
	    break;
	case AFTERNOON:
	    str = "A stormy afternoon in winter on the Bloodsea of Istar";
	    break;
	case EVENING:
	    str = "A stormy winter evening on the Bloodsea of Istar";
	    break;
	}
	break;
    }
    return str;
}

string
bloodsea_desc()
{
    string str;
    switch (GET_SEASON) 
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight out on the Bloodsea of Istar. Above, the " +
	    "night sky shines brightly stars. The silver moon Solinari " +
	    "and the smaller moon Lunitari illuminate the ever shifting ocean " +
            "that surrounds you. ";
	    break;
	case NIGHT:
	    str = "You are surrounded by waters of the Bloodsea of Istar " +
	    "on a calm spring night. The silence is beautiful and unbroken, " +
	    "with the brightly shining stars above you your quiet companions, " +
	    "illuminating the sea around you. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to lighten on the horizon as the sun prepares " +
	    "to rise from the calm " +
	    "waters of the Bloodsea of Istar. Waves around you rock you " +
	    "gently as you sway slowly to a soft spring breeze. ";
	    break;
	case MORNING:
	    str = "The rising suns morning rays shine down over the " +
	    "Bloodsea of Istar. While not " +
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
	    "sea rises and falls as a soft breeze blows across the Bloodsea of Istar. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent towards the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the " +
	    "sun sets. The sea rises and falls as a soft spring breeze blows across " +
            "the Bloodsea of Istar. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "The warm night air here on the Bloodsea of Istar " +
	    "is a pleasant relief after the scorching hot " +
	    "summer days out at sea. A gusty wind " +
	    "blows across the waters, sending spray up into the air " +
	    "and cooling you further. ";
	    break;
	case EARLY_MORNING:
	    str = "The cloak of night begins to retreat as " +
	    "the suns first rays appear over the horizon on the " +
	    "Bloodsea of Istar. The shrill cry of " +
	    "an albatross far above you can be heard as it searches " +
	    "the sea for a feed of fish. ";
	    break;
	case MORNING:
	    str = "With the rising of the morning sun over the " +
	    "Bloodsea of Istar, the air begins to heat up. This seems " +
	    "to encourage a gusty summer wind to blow across the " +
	    "turbulent waters, sending salty sea spray all around. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon " +
	    "your head out on the shadeless high seas of the Bloodsea " +
            "of Istar. High humidity makes it very uncomfortable, and even a " +
	    "gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING: 
	    str = "With the evening sun beginning its descent " +
	    "behind the horizon, the fierce summer heat and " +
	    "humidity begins to subside much to your relief. A " +
	    "gusty wind blows around you, chilling your sweat " +
	    "and sending spray up into the air off the waters of the " +
            "Bloodsea of Istar. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You are surrounded by the Bloodsea of Istar " +
            "on a windy autumn night. Dark clouds gather " +
	    "in the sky, hinting at a storm... you may be in for a " +
            "rough night! ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to grey as sunrise approaches the " +
	    "horizon of the Bloodsea of Istar. An autumn wind " +
	    "blows across the waters, bringing with it " +
	    "the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "The cool rays of the morning sun shine through " +
	    "holes in the grey clouds that seem to have occupied " +
	    "the heavens over the Bloodsea of Istar. " +
	    "A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You are surrounded by the turbulent waters of the " +
            "Bloodsea of Istar on a cool autumn " +
	    "day. A chill wind blows across the waters, " +
	    "bringing with it the smell of an approaching " +
	    "storm. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent " +
	    "beyond the horizon. A chill autumn wind rises, waking the " +
	    "angry waters of the Bloodsea of Istar. You get the impression " +
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
	    "echoes across the Bloodsea of Istar, and a " +
	    "harsh winter wind howls around you. The waves rise ominously in savage " +
	    "fury, then battering against you with great force. " +
	    "The seas of winter is truly where the Gods show their fury! ";
	    break;
	case EARLY_MORNING:
	    str = "The nights sky begins to lighten, and the " +
	    "savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the waters of the Bloodsea of Istar. ";
	    break;
	case MORNING:
	    str = "The morning air is chill on the Bloodsea of Istar " +
	    "and even the rising sun does little to remove " +
	    "the biting cold of the winter wind that howls " +
	    "around you. With the rise of the sun, the seas " +
	    "are displayed before as harsh and unforgiving to all " +
	    "who travel it. ";
	    break;
	case NOON:
	    str = "While the middle of the day, billowing storm " +
	    "clouds shadow the waters of the Bloodsea of Istar, " +
            "casting a dark pall over the agitated seas. " +
	    "A cold winter wind howls around you, spraying you with " +
	    "icy water that freezes your skin. ";
	    break;
	case AFTERNOON:
	    str = "The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the waters " +
	    "of the Bloodsea of Istar rolling. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun shines a hazy " +
	    "red as it begins its descent behind the horizon. " +
	    "In the distance the echo of thunder rolls its way " +
	    "to you from the gathering of angry black clouds in " +
	    "the distance, harkening another winter storm on the " +
	    "Bloodsea of Istar. ";
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

string
short_descr()
{
    return bloodsea_short() + " between the islands of Mithas and Kothas";
}
 
string
long_descr()
{
    return "You are passing through the channel known " +
        "as the Eye of the Bull, the straight that separates the two " +
        "minotaur occupied islands of Mithas and Kothas. " +
        bloodsea_desc()+ "\n";
}

public void
create_sea_room()
{
    ::create_sea_room();

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("@@short_descr");
    set_long("@@long_descr");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
        "a strange and reddish colour. Rumour has it that the colour "+
        "is the result of the blood of many victims who lost their "+
        "lives during Krynn's most terrible hour, though it "+
        "could be the clay stirred up from the sea bottom by the "+
        "maelstrom.\n");
    add_item(({"clouds", "storm"}), "@@add_item_storm");

    add_item(({"mithas","kothas","islands","island"}),
        "You are passing between two islands. To your north is Mithas, " +
        "a fiery island of scrub plains that lie in the shadow of four " +
        "great volcanoes. To your south is Kothas, a rocky isle ruled " +
        "in combination by minotaurs and piratical men.\n");
    add_item(({"eye of the bull","straight","passage","channel"}),
        "Separating the two islands of Mithas and Kothas is the passage " +
        "known as the Eye of the Bull. Cliffs on the Mithas side reflect " +
        "incoming waves, making the waters particularly rough.\n");
    add_item(({"volcanoes","volcano","argon's chain","argons chain"}),
        "A range of four volcanoes known as Argon's Chain stretch across " +
        "the island of Mithas, dominating its eastern side.\n");

    add_std_exits();

    // Set the optional message when sailing into this room.
    set_sailing_fail_message("The passage between the islands of Mithas and " +
        "Kothas is too difficult for you to navigate!\n");
    set_sailing_difficulty_message("You navigate skillfully along the " +
        "channel known as the Eye of the Bull.\n");

    herbs = HERB_MASTER->query_herbs( ({ "oceanfloat", }) );
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
    ::enter_inv(ob, from);
    if (living(ob))
    {
        if(IS_OOTS(ob))
        {
            if(!OOTS_QUERY_REV(TP, "lightbringer"))
            {
                TP->catch_msg("\n\nAs you enter the Bloodsea of Istar you are suddenly " +
                   "provided a divine revelation about a humble mortal of the distant " +
                   "past, beloved of Paladine, who broke the world...\n\n\n");
                OOTS_ADD_REV(TP,"lightbringer","enlightenment - the lightbringer");  
            }
        }
    }
}