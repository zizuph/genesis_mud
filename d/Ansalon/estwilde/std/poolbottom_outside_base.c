#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include "/d/Krynn/common/clock/clock.h"

/* Inherit the Ansalon room */
inherit OR_FILE

#define CREATE "create_poolbottom_room"
#define RESET "reset_poolbottom_room"

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
close_school_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "On a path outside the school of High Magic on a " +
	season_descr()+ " night";
	break;
    case TOD_DAWN:
	str = "On a path outside the school of High Magic on a " +
	season_descr()+ " morning";
	break;
    case TOD_DAY:
	str = "On a path outside the school of High Magic on a " +
	season_descr()+ " day";
	break;
    case TOD_TWILIGHT:
	str = "On a path outside the school of High Magic on a " +
	season_descr()+ " evening";
	break;
    }
    return str;
}

string
far_school_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "On a path leading to a large stone building on a " +
	season_descr()+ " night";
	break;
    case TOD_DAWN:
	str = "On a path leading to a large stone building on a " +
	season_descr()+ " morning";
	break;
    case TOD_DAY:
	str = "On a path leading to a large stone building on a " +
	season_descr()+ " day";
	break;
    case TOD_TWILIGHT:
	str = "On a path leading to a large stone building on a " +
	season_descr()+ " evening";
	break;
    }
    return str;
}

string
long_close_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight, and you stand outside the entry to a large " +
            "building, the school of High Magic near Solace. " +
            "Above the silver moon Solinari and the smaller moon Lunitari " +
            "illuminate the stone walls before you, casting eerie shadows. ";
	    break;
	case NIGHT:
	    str = "You stand before the entry to a large building, the school of " +
            "High Magic, on a calm spring night. The silence around you is " +
	    "occasionally broken by the hoot of an owl out on the hunt. Even " +
            "the insects seem to be paying respect to the silence by keeping " +
	    "quiet. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky starts to lighten as the sun sheds its first rays " +
            "for the day on the entry to a large building standing before you, " +
	    "the school of High Magic. A soft breeze stirs around you, " +
            "bringing with it the pleasant fragrance of spring. ";
	    break;
	case MORNING:
	    str = "The sun's morning rays spill down over the entry to a large building " +
            "standing before you, the school of High Magic near Solace. While not " +
	    "quite warm, the fresh, crisp smell of the air alerts " +
	    "you to spring's influence on the land at the moment. ";
	    break;
	case NOON:
	    str = "It is a warm spring day outside the entry to a large " +
            "stone building, the school of High Magic near Solace. " +
	    "A warm breeze stirs around you, bringing with it the pleasant " +
            "fragrance of spring. ";
	    break;
	case AFTERNOON:
	    str = "Shadows lengthen as the sun begins to descend from the heavens. You stand " +
            "before the entry to a large building, the school of High Magic near Solace. " +
	    "A warm breeze stirs around you, bringing with it the pleasant " +
            "fragrance of spring. ";
	    break;
	case EVENING:
	    str = "You stand before the entry to a large building, the school of High Magic " +
            "near Solace. In the west, the evening sun begins its descent beyond the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the sun sets. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night outside the entry to a large stone " +
            "building, the school of High Magic near Solace. " +
            "The warm night air is a pleasant relief following the hot and " +
	    "steamy summer days. A gusty wind blows through the nearby trees, " +
            "creating an agitated whispering from the deep shadows. ";
	    break;
	case EARLY_MORNING:
	    str = "The night's shadows begin to retreat as the sun's first rays appear over " +
            "the horizon. Before you stands a large stone building, the school of High Magic " +
	    "near Solace. A gusty summer wind blows through the nearby trees " +
	    "causing them to stir with disquiet. ";
	    break;
	case MORNING:
	    str = "You stand before the entry to a large building, the school of High Magic " +
            "near Solace. With the rising of the morning sun, the land begins to " +
	    "warm. A gusty summer wind blows through the nearby trees " +
	    "causing them to stir with disquiet. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon your head as you stand " +
            "before the entry to a large building, the school of High Magic " +
            "near Solace. High humidity makes it very uncomfortable, and even a " +
	    "gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING:
	    str = "You stand before the entry to a large stone building, the school of High Magic " +
            "near Solace. With the evening sun beginning its descent " +
	    "behind the horizon, the fierce summer heat and humidity begins to subside much " +
            "to your relief. A gusty wind blows around you, chilling your sweat " +
	    "and bending the nearby trees to its whim. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace, on a windy autumn night. Black clouds gather " +
	    "in the sky to the north, hinting at a storm, while the silver moon Solinari " +
            "and the smaller moon Lunitari illuminate the stone walls before you, " +
            "casting eerie shadows. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace, as the sky begins to grey with sunrise approaching. " +
            "An autumn wind blows through the trees to the north, bringing with it " +
	    "the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. The cool rays of the morning sun shine through " +
	    "holes in the grey clouds that seem to have occupied " +
	    "the heavens. A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic, on a cool autumn day. A chill wind blows through the nearby trees, " +
	    "bringing with it the smell of an approaching storm. ";
	    break;
	case EVENING:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. In the west, the evening sun begins its descent " +
	    "beyond the horizon. A chill autumn wind rises, blowing the " +
	    "nearby trees to and fro and giving the impression that it will be " +
	    "a cold time to be outside this night. ";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic, on a stormy winter's night. A jagged fork of lightning " +
            "illuminates the night sky, briefly revealing roiling black clouds " +
            "above you and the snow-covered ground around you. A mighty clap of thunder " +
	    "echoes off the school's stone walls, and a harsh winter wind howls around " +
            "you, battering the nearby trees in a savage wave of invisible force. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. The nights sky begins to lighten, and the " +
	    "savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the snow-covered land around you. ";
	    break;
	case MORNING:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. The morning air is chill, " +
	    "and even the rising sun does little to remove the biting cold of the winter " +
            "wind that howls around you. With the rise of the sun, the snow-covered " +
	    "school is displayed before you, its grey stone walls standing out " +
	    "starkly in a field of white. ";
	    break;
	case NOON:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. While the middle of the day, billowing storm " +
	    "clouds shadow the snow-covered school, its grey stone walls standing out " +
	    "starkly in a field of white. A cold winter wind blows through the nearby trees, " +
	    "sending them whispering in agitation. ";
	    break;
	case AFTERNOON:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the nearby trees into a wild dance. ";
	    break;
	case EVENING:
	    str = "You stand before the entry to a large stone building, the school of " +
            "High Magic near Solace. In the west, the evening sun shines a hazy " +
	    "red as it begins its descent beyond the horizon. In the distance the echo of " +
            "thunder rolls its way to you from the gathering of angry black clouds in " +
	    "the north, harkening another winter storm on the way. ";
	    break;
	}
	break;
    }
    return str;
}

string
long_far_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	    str = "It is midnight, and you stand on a cobbled path leading in a " +
            "northerly direction to a large stone building. " +
            "Above the silver moon Solinari and the smaller moon Lunitari " +
            "illuminates the path before you, casting eerie shadows. ";
	    break;
	case NIGHT:
	    str = "It is a calm spring night, and you stand on a cobbled path leading " +
            "in a northerly direction to a large stone building. The silence around you is " +
	    "occasionally broken by the hoot of an owl out on the hunt. Even " +
            "the insects seem to be paying respect to the silence by keeping " +
	    "quiet. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky starts to lighten as the sun sheds its first rays " +
            "for the day on a cobbled path that leads in a northerly direction to a large " +
            "stone building. A soft breeze stirs around you, " +
            "bringing with it the pleasant fragrance of spring. ";
	    break;
	case MORNING:
	    str = "The sun's morning rays spill down over the cobbled path you stand on, " +
            "that leads in a northerly direction to a large stone building " +
            "standing just outside of Solace. While not " +
	    "quite warm, the fresh, crisp smell of the air alerts " +
	    "you to spring's influence on the land at the moment. ";
	    break;
	case NOON:
	    str = "It is a warm spring day on a cobbled path leading in a " +
            "northerly direction to a large stone building standing just outside of Solace. " +
	    "A warm breeze stirs around you, bringing with it the pleasant " +
            "fragrance of spring. ";
	    break;
	case AFTERNOON:
	    str = "Shadows lengthen as the sun begins to descend from the heavens. You stand " +
            "on a cobbled path leading in a northerly direction to a large stone building " +
            "standing just outside of Solace. " +
	    "A warm breeze stirs around you, bringing with it the pleasant " +
            "fragrance of spring. ";
	    break;
	case EVENING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. In the west, the evening sun begins its descent beyond the " +
	    "horizon. Above, the sky displays a beautiful array of colours ranging " +
	    "from oranges to soft pinks to deep purple as the sun sets. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night on a cobbled path leading in a " +
            "northerly direction to a large stone building standing just outside of Solace. " +
            "The warm night air is a pleasant relief following the hot and " +
	    "steamy summer days. A gusty wind blows through the nearby trees, " +
            "creating an agitated whispering from the deep shadows. ";
	    break;
	case EARLY_MORNING:
	    str = "The night's shadows begin to retreat as the sun's first rays appear over " +
            "the horizon. You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. A gusty summer wind blows through the nearby trees " +
	    "causing them to stir with disquiet. ";
	    break;
	case MORNING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. With the rising of the morning sun, the land begins to " +
	    "warm. A gusty summer wind blows through the nearby trees " +
	    "causing them to stir with disquiet. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon your head as you stand " +
            "on a cobbled path leading in a northerly direction to a large " +
            "stone building. High humidity makes it very uncomfortable, and even a " +
	    "gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. With the evening sun beginning its descent " +
	    "behind the horizon, the fierce summer heat and humidity begins to subside much " +
            "to your relief. A gusty wind blows around you, chilling your sweat " +
	    "and bending the nearby trees to its whim. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building on a windy autumn night. Black clouds gather " +
	    "in the sky to the north, hinting at a storm, while the silver moon Solinari " +
            "and the smaller moon Lunitari illuminate the path before you, " +
            "casting eerie shadows. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building, as the sky begins to grey with sunrise approaching. " +
            "An autumn wind blows through the trees to the north, bringing with it " +
	    "the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. The cool rays of the morning sun shine through " +
	    "holes in the grey clouds that seem to have occupied " +
	    "the heavens. A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building, on a cool autumn day. A chill wind blows through the nearby trees, " +
	    "bringing with it the smell of an approaching storm. ";
	    break;
	case EVENING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. In the west, the evening sun begins its descent " +
	    "beyond the horizon. A chill autumn wind rises, blowing the " +
	    "nearby trees to and fro and giving the impression that it will be " +
	    "a cold time to be outside this night. ";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building, on a stormy winter's night. A jagged fork of lightning " +
            "illuminates the night sky, briefly revealing roiling black clouds " +
            "above you and the snow-covered ground around you. A mighty clap of thunder " +
	    "echoes off in to the distance, and a harsh winter wind howls around " +
            "you, battering the nearby trees in a savage wave of invisible force. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. The nights sky begins to lighten, and the " +
	    "savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the snow-covered land around you. ";
	    break;
	case MORNING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. The morning air is chill, " +
	    "and even the rising sun does little to remove the biting cold of the winter " +
            "wind that howls around you. ";
	    break;
	case NOON:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. While the middle of the day, billowing storm " +
	    "clouds shadow the lands around you. A cold winter wind blows through the nearby trees, " +
	    "sending them whispering in agitation. ";
	    break;
	case AFTERNOON:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the nearby trees into a wild dance. ";
	    break;
	case EVENING:
	    str = "You stand on a cobbled path leading in a northerly direction to a large " +
            "stone building just outside of Solace. In the west, the evening sun shines a hazy " +
	    "red as it begins its descent beyond the horizon. In the distance the echo of " +
            "thunder rolls its way to you from the gathering of angry black clouds in " +
	    "the north, harkening another winter storm on the way. ";
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
	"echo of the thunders deep growl rolls past you, " +
	"and a wild, biting wind harkens the storms "+
	"potent fury.\n";
	break;
    case SUMMER:
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
add_item_snow()
{
    string str;
    switch(GET_SEASON)
    {
    case WINTER:
	str = "It is winter, and the lands surrounding Solace are covered with snow.\n";
	break;
    case SUMMER:
    case SPRING:
    case AUTUMN:
	str = "You see no snow.\n";
	break;
    }
    return str;
}

string
add_item_path()
{
    string str;
    switch(GET_SEASON)
    {
    case WINTER:
	str = "You stand on a cobbled path currently covered with snow, leading to a large stone building.\n";
	break;
    case SUMMER:
    case SPRING:
    case AUTUMN:
	str = "You stand on a cobbled path leading to a large stone building.\n";
	break;
    }
    return str;
}

string
add_item_near_walls()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The darkness of night hides most of the details of the walls of the school " +
             "from you.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "The walls of the school of High Magic are of a dark grey sandstone, mined " +
                  "from quarries near Pax Tharkas.\n";
	    break;
    }
    return str;
}

string
add_item_shadows()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "The shadows of night surround you, eerily difficult to penetrate.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You see nothing of interest in the shadows around you.\n";
	    break;
    }
    return str;
}

string
add_item_far_building()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "In the distance, outlined against the darkness of night, you can make out a large stone building, " +
              "dimly illuminated by lights high up in a number of second storey windows.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "In the distance you can make out a large two storey stone building, with " +
                  "two wings extending to the east and west of the main structure.\n";
	    break;
    }
    return str;
}

string
add_item_far_windows()
{
    string str;
    switch(GET_TIME_STRING)
    {
	case MIDNIGHT:
	case NIGHT:
	    str = "In the distance a number of windows twinkle like beacons in the night " +
               "from the dim outline of a large building.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "A number of windows can be made out high up on the second storey of the " +
               "large building.\n";
	    break;
    }
    return str;
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
	"billowing storm clouds","black storm clouds", "sky",
	"angry black clouds","grey clouds"}),
      "@@add_item_storm");

    add_item(({"snow","snow-covered","snow-covered ground",
	"snow-covered school","field of white",
	"white","snow-covered land"}),
      "@@add_item_snow");

    add_item(({"path","cobbled path"}),
      "@@add_item_path");

    add_item(({"shadows","shadow","deep shadows","eerie shadows",
	"night's shadows"}),
      "@@add_item_shadows");


    add_item(({"trees","nearby trees","tree","vallenwoods",
        "vallenwood trees", "vallenwood tree"}),
      "To the southeast you can make out great vallenwood trees native to the Solace region. " +
      "Amongst the many and varied native trees on Ansalon, few are as impressive as " +
      "the vallenwoods, growing up to two to three hundred feet in height.\n");

    add_item("solace","While out of sight, to your southeast resides the hamlet of Solace.\n");

}

/*
* This function is called from the main Krynn room.
*/
public void
reset_krynn_room()
{
    call_other(TO, RESET);
}




