#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#define CREATE "create_estwilde_room"
#define RESET "reset_estwilde_room"

string
season_descr()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	str = "warm spring";
	break;
    case SUMMER:
	str = "hot and humid summer";
	break;
    case AUTUMN:
	str = "cool autumn";
	break;
    case WINTER:
	str = "cold winter";
	break;
    }
    return str;
}

string
tod_descr1()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "On the rugged plains of Estwilde on a " +
	season_descr()+ " night";
	break;
    case TOD_DAWN:
	str = "On the rugged plains of Estwilde on a " +
	season_descr()+ " morning";
	break;
    case TOD_DAY:
	str = "On the rugged plains of Estwilde on a " +
	season_descr()+ " day";
	break;
    case TOD_TWILIGHT:
	str = "On the rugged plains of Estwilde on a " +
	season_descr()+ " evening";
	break;
    }
    return str;
}

string
plain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight on the plains of Estwilde. Above, the " +
	    "night sky shines brightly stars. The silver moon Solinari " +
	    "and the smaller moon Lunitari illuminate the dry grasslands " +
	    "and rugged foothills that extend before you. ";
	    break;
	case NIGHT:
	    str = "You stand amongst the tall dry grasses of the " +
	    "Estwilde plains on a calm spring night. The silence " +
	    "of the plains is only sometimes broken by the hoot " +
	    "of an owl out on the hunt, and even the insects " +
	    "seem to be paying respect to the silence by keeping " +
	    "quiet. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to lighten as the sun prepares " +
	    "to shed its first rays for the day on the rugged " +
	    "land of Estwilde. Tall dry grasses that cover most " +
	    "of these hilly plains sway slowly to a soft breeze. ";
	    break;
	case MORNING:
	    str = "The suns morning rays spill down over the " +
	    "harsh plains and foothills of Estwilde. While not " +
	    "quite warm, the fresh, crisp smell of the air alerts " +
	    "you to springs influence on the land at the moment. ";
	    break;
	case NOON:
	    str = "It is a warm spring day on the rugged plains of " +
	    "Estwilde. Surprisingly, it is rather calm at the " +
	    "moment as this savage land is renown for its severe " +
	    "weather. ";
	    break;
	case AFTERNOON:
	    str = "Shadows lengthen across the plains of Estwilde " +
	    "as the sun begins to descend from the heavens. The " +
	    "long dry grasses that stretch across the hilly lands " +
	    "sway slightly as a soft breeze blows through this rugged land. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent beyond the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the " +
	    "sun sets. The long dry grasses that grow here " +
	    "sway to a soft breeze that blows across the rugged " +
	    "plains of Estwilde. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "The warm night air here on the rugged plains " +
	    "of Estwilde is a pleasant relief after the hot and " +
	    "steamy summer days this land suffers. A gusty wind " +
	    "blows through the hilly plains sending the long dry " +
	    "grasses that grow here whispering in agitation. ";
	    break;
	case EARLY_MORNING:
	    str = "The nights shadow begins to retreat as " +
	    "the suns first rays appear over the horizon onto the " +
	    "hilly plains of Estwilde. The lonely cry of " +
	    "an eagle far above you can be heard as it hunts " +
	    "the dry grasslands for rodents. ";
	    break;
	case MORNING:
	    str = "With the rising of the morning sun, the " +
	    "rugged plains and foothills of Estwilde begin to " +
	    "warm. A gusty summer wind blows through the " +
	    "grasslands from the north, tossing the dry brown " +
	    "grasses around. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon " +
	    "your head as you stand out among the long dry grasses " +
	    "of the hilly lands of Estwilde. High humidity makes " +
	    "it very uncomfortable, and even a " +
	    "gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING:
	    str = "With the evening sun beginning its descent " +
	    "behind the horizon, the fierce summer heat and " +
	    "humidity begins to subside much to your relief. A " +
	    "gusty wind blows around you, chilling your sweat " +
	    "and bending the long dry grass of the Estwilde " +
	    "plains to its whim. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand amongst the tall dry grasses of the " +
	    "Estwilde plains on a windy autumn night. Clouds gather " +
	    "in the sky, hinting at a storm, although by the looks of " +
	    "the dry plant life around you, you doubt any rain will " +
	    "result. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky begins to grey as sunrise approaches the " +
	    "rugged hills and plains of Estwilde. An autumn wind " +
	    "blows through the long dry grasses, bringing with it " +
	    "the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "The cool rays of the morning sun shine through " +
	    "holes in the grey clouds that seem to have occupied " +
	    "the heavens, onto the dry and rugged lands of Estwilde. " +
	    "A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You stand amongst the long dry grasses of " +
	    "the rugged plains of Estwilde on a cool autumn " +
	    "day. A chill wind blows through the foothills around " +
	    "you, bringing with it the smell of an approaching " +
	    "storm. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun begins its descent " +
	    "beyond the horizon. A chill autumn wind rises, blowing the " +
	    "dry brown grasses that grow sparsely on these rugged plains of Estwilde " +
	    "to and fro, giving the impression that it will be " +
	    "a cold time on the plains this night. ";
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
	    "echoes across the hilly plains of Estwilde, and a " +
	    "harsh winter wind howls around you, battering the dry " +
	    "grasses down before it in a savage wave of invisible force. " +
	    "This is truly a land where the Gods show their fury! ";
	    break;
	case EARLY_MORNING:
	    str = "The nights sky begins to lighten, and the " +
	    "savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the rugged plains of Estwilde. ";
	    break;
	case MORNING:
	    str = "The morning air is chill on the plains of " +
	    "Estwilde, and even the rising sun does little to remove " +
	    "the biting cold of the winter wind that howls " +
	    "around you. With the rise of the sun, the rugged " +
	    "foothills and dry grasslands are displayed before " +
	    "you, a land truly harsh and unfriendly to all " +
	    "who travel it. ";
	    break;
	case NOON:
	    str = "While the middle of the day, billowing storm " +
	    "clouds shadow the rugged plains and foothills of " +
	    "Estwilde, casting a dark pall over the harsh land. " +
	    "A cold winter wind sends the long dry grasses " +
	    "whispering in agitation around you. ";
	    break;
	case AFTERNOON:
	    str = "The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the long dry " +
	    "grasses of the plains of Estwilde into a wild dance. ";
	    break;
	case EVENING:
	    str = "In the west, the evening sun shines a hazy " +
	    "red as it begins its descent beyond the horizon. " +
	    "In the distance the echo of thunder rolls its way " +
	    "to you from the gathering of angry black clouds in " +
	    "the distance, harkening another winter storm on the " +
	    "plains of Estwilde. ";
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
	"echo of the thunders deep growl rolls past you along " +
	"the plains, and a wild, biting wind harkens the storms "+
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

void
add_item_hill()
{
    add_item(({"hill","steep hill"}),
      "To your south rises a steep hill of considerable size. " +
      "The base of the hill is rocky and covered with wiry " +
      "brush and bushes, making it impossible to climb here, " +
      "while the hills pinnacle far above you seems quite barren.\n");

    add_item(({"brush","bushes","rocks","wiry brush"}),
      "Wiry brush and bushes cover the base of the steep hill, " +
      "adding to the rocky and steep slope, making it impossible to climb " +
      "at this point.\n");
    add_item(({"pinnacle","structure","stone structure"}),
      "Looking up at the pinnacle of the steep hill, you notice a " +
      "lonely stone structure squatting a top the " +
      "barren hilltop, although you can make out little " +
      "else about it.\n");
}

void
add_item_chasm()
{
    add_item(({"great chasm","chasm"}),
      "Before you is a great chasm that has been " +
      "rent in these plains, probably during the times " +
      "of chaos known as the cataclysm. The chasm stretches " +
      "for miles to the northeast and southwest, and downwards " +
      "into darkness and beyond. The other side of the rift can " +
      "be seen twenty metres away.\n");
    add_item("down",
      "Looking down, you cannot see the bottom of the chasm.\n");


}

void
near_walls()
{
    add_item(({"walls","stone walls","kalaman"}),
      "To the north you can see the stone walls of the " +
      "port city of Kalaman rise up before you.\n");
}

void
near_kalaman()
{
    add_item("kalaman",
      "To the north you can just make out the city of Kalaman, " +
      "lying on the banks of the Vingaard River.\n");
    add_item(({"river","vingaard river"}),
      "Running to the west into the distance you make out " +
      "the Vingaard River, the longest river in Ansalon.\n");
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
public void
create_krynn_room()
{
    call_other(TO, CREATE);

    add_item(({"clouds","storm clouds","black clouds","storm",
	"billowing storm clouds","black storm clouds",
	"angry black clouds","grey clouds"}),
      "@@add_item_storm");
    add_item(({"rugged plains","plains","estwilde","grasslands",
	"foothills","hilly plains"}),
      "Occupying the broad, hilly basin between the Dargaard Mountains " +
      "and the northeastern Khalkists are the plains of Estwilde, " +
      "a land consisting of dry grasslands and rugged " +
      "foothills.\n");
    add_item("dargaard mountains",
      "Far to the west rises the Dargaard Mountain range, seperating " +
      "the plains of Solamnia with the lands of Estwilde.\n");
    add_item(({"khalkist mountains","khalkists","northeastern khalkists"}),
      "Far to the southeast rise the northeastern most " +
      "branch of the Khalkist Mountain range.\n");
    add_item(({"long dry grasses","tall dry grasses","dry grass",
	"dry grasses","grasses","grass"}),
      "Across the plains of Estwilde grow hardy grasses " +
      "that have been parched brown by the harsh environment " +
      "it lives in.\n");
}

/*
* This function is called from the main Krynn room.
*/
public void
reset_krynn_room()
{
    call_other(TO, RESET);
}




