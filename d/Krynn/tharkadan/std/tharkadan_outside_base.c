#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/clock/clock.h"

/* Inherit the Ansalon room */
inherit OR_FILE

#define CREATE "create_tharkadan_room"
#define RESET "reset_tharkadan_room"

string
season_descr()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	str = "";
	break;
    case SUMMER:
	str = "dusty ";
	break;
    case AUTUMN:
	str = "";
	break;
    case WINTER:
	str = "snow-covered ";
	break;
    }
    return str;
}

string
short_mountain_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
    case TOD_DAWN:
    case TOD_DAY:
    case TOD_TWILIGHT:
	str = C(season_descr()+ "trail winding through the Tharkadan " +
            "Mountains");
    break;
    }
    return str;
}

string
short_forest_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        str = "dark and shadowy forest in a valley in the Tharkadan " +
            "Mountains";
    break; 
    case TOD_DAWN:
    case TOD_DAY:
        str = "alpine forest in a valley in the Tharkadan Mountains";
    break;
    case TOD_TWILIGHT:
        str = "shadowy forest in a valley in the Tharkadan Mountains";
    break;
    }
    return str;
}

string
short_hopeful_vale_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
        str = "night in a secluded valley in the Tharkadan Mountains";
    break; 
    case TOD_DAWN:
    case TOD_DAY:
        str = "a secluded valley in the Tharkadan Mountains";
    break;
    case TOD_TWILIGHT:
        str = "twilight in a secluded valley in the Tharkadan Mountains";
    break;
    }
    return str;
}

string
long_mountain_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You stand on a trail that winds through the " +
            "Tharkadan Mountain Range. With the arrival of spring the " +
            "winter snows have melted, once again allowing passage. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand on a dark and dusty trail that winds " +
            "through the Tharkadan Mountain Range. While the night " +
            "provides welcome relief from the summer heat of the day, " +
            "you are well aware the darkness hides many dangers. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand on a dark and dusty trail that winds " +
            "through the Tharkadan Mountain Range. The darkness begins " +
            "to retreat as the sun rises in the east, promising a " +
            "warm summer day ahead of you. ";
	    break;
	case MORNING:
	case NOON:
	case AFTERNOON:
	    str = "You stand on a dusty trail that winds through " +
            "the Tharkadan Mountain Range. The summer sun beats down " +
            "upon you mercilessly, and the thin mountain air " +
            "makes for exhausting travels. ";
	    break;
	case EVENING:
	    str = "You stand on a dusty trail that winds through " +
            "the Tharkadan Mountain Range. The setting sun casts long " +
            "shadows around you. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You stand on a trail that winds through the " +
            "Tharkadan Mountain Range. A cool change to the wind " +
            "indicates autumn has arrived, and that time is running " +
            "out for the pass to remain open before the winter snow " +
            "arrives. ";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "You stand on a snow-covered trail that winds through " +
            "the Tharkadan Mountain " +
            "Range. A bitterly cold wind howls through the mountains, " +
            "and the deep snow covering the slopes makes you feel " +
            "unsure how long this trail will remain passable. ";
	    break;
	}
	break;
    }
    return str;
}

string
long_forest_desc()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "With the arrival of spring the winter snows have melted, " +
            "and the cold night air is filled with the fresh scent of " +
            "pine and fir. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	    str = "It is morning in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. With the arrival of spring the winter snows have " +
            "melted, and the air is filled with the fresh scent of pine " +
            "and fir. ";
	    break;
	case NOON:
	    str = "It is midday in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "With the arrival of spring the winter snows have melted, " +
            "and the air is filled with the fresh scent of pine and fir. ";
	    break;
	case AFTERNOON:
	    str = "It is afternoon in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. With the arrival of spring the winter snows have " +
            "melted, and the air is filled with the fresh scent of pine " +
            "and fir. ";
	    break;
	case EVENING:
	    str = "It is evening in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. With the arrival of spring the winter snows have " +
            "melted, and the air is filled with the fresh scent of pine " +
            "and fir. ";
	    break;
	}
	break;
    case SUMMER:
	switch (GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "The warm summer night's air is filled with the fresh scent " +
            "of pine and fir. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	    str = "You are in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "The night's shadows retreat into the depths of the forest " +
            "as the sun rises, and the air is filled with the fresh " +
            "scent of pine and fir. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "It is day in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "The forest canopy protects you from the heat of the " +
            "summer sun, and you notice the air is filled with the " +
            "fresh scent of pine and fir. ";
	    break;
	case EVENING:
	    str = "It is evening in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. The shadows here begin to grow as night approaches, " +
            "and you notice the air is filled with the fresh scent of " +
            "pine and fir. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "The autumn air is cold, with the leaves of the pine and " +
            "fir trees already with snow. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	    str = "It is morning in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. The autumn air is cold, with the leaves of the " +
            "pine and fir trees already with snow. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "It is day in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "The autumn air is cold, with the leaves of the pine and " +
            "fir trees already with snow. ";
	    break;
	case EVENING:
	    str = "It is evening in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. The autumn air is cold, with the leaves of the " +
            "pine and fir trees already with snow. ";
	    break;
	}
	break;

    case WINTER:
	switch(GET_TIME_STRING)
	{
	case MIDNIGHT:
	case NIGHT:
	    str = "It is night in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "A bitterly cold wind blows through the forest, coating the " +
            "ground and trees with a thick layer of snow. ";
	    break;
	case EARLY_MORNING:
	case MORNING:
	    str = "It is morning in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. A bitterly cold wind blows through the forest, " +
            "coating the ground and trees with a thick layer of snow. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "It is day in an alpine wood, known as 'the Fallen " +
            "Forest', within a valley of the Tharkadan Mountain Range. " +
            "A bitterly cold wind blows through the forest, coating the " +
            "ground and trees with a thick layer of snow. ";
	    break;
	case EVENING:
	    str = "It is evening in an alpine wood, known as 'the " +
            "Fallen Forest', within a valley of the Tharkadan Mountain " +
            "Range. A bitterly cold wind blows through the forest, " +
            "coating the ground and trees with a thick layer of snow. ";
	    break;
	}
	break;
    }
    return str;
}

string
add_item_forest_snow()
{
    string str;
    switch(GET_SEASON)
    {
    case WINTER:
	str = "It is winter, and the rugged high passes of the " +
          "Tharkadan Mountain Range are filled with snow. The pine and " +
          "fir trees of the forest are thickly covered with it.\n";
	break;
    case SUMMER:
    case SPRING:
	str = "You can see no snow.\n";
        break;
    case AUTUMN:
	str = "The pine and fir trees are already dusted with snow, " +
           "indicating a cold winter to come.\n";
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
	str = "It is winter, and the rugged high passes of the " +
          "Tharkadan Mountain Range are filled with snow.\n";
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
    if(TO->query_prop("_no_path_tharkadan"))
       return "There is no trail here.\n";

    string str;
    switch(GET_SEASON)
    {
    case WINTER:
	str = "You stand on a rugged path running through the Tharkadan " +
        "Mountain Range. Winter's snow lies deep around you, making " +
        "passage through the high passes difficult and dangerous. On " +
        "either side of the path loom snow-covered peaks and " +
        "ridgelines.\n";
	break;
    case SUMMER:
    case SPRING:
    case AUTUMN:
	str = "You stand on a rugged path running through the Tharkadan " +
        "Mountain Range. In the Age of Dreams this was once a road " +
        "running from Pax Tharkas to Thorbardin, although very little " +
        "remains of such a thoroughfare now. On either side of the " +
        "path loom peaks and ridgelines of the mighty mountain range.\n";
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
	    str = "The shadows of night surround you, eerily difficult " +
               "to penetrate.\n";
	    break;
	case EARLY_MORNING:
	case MORNING:
	case NOON:
	case AFTERNOON:
	case EVENING:
	    str = "Shadows are cast down by the mountain peaks and " +
               "ridgelines around you, although you see nothing of " +
               "interest in them.\n";
	    break;
    }
    return str;
}

string
add_item_mountains()
{
    string str;
    switch(GET_SEASON)
    {
    case WINTER:
	str = "Looming on either side of you are the snow-covered peaks " +
           "and ridgelines of the Tharkadan range, part of the mighty " +
           "Kharolis Mountains running from the western Redstone Bluffs " +
           "to the Newsea in the east. This mountain range provides " +
           "the only navigable pass from Thorbardin to Qualinost.\n";
	break;
    case SUMMER:
    case SPRING:
    case AUTUMN:
	str = "Looming on either side of you are the high peaks and " +
           "ridgelines of the Tharkadan range, part of the mighty " +
           "Kharolis Mountains running from the western Redstone " +
           "Bluffs to the Newsea in the east. This mountain range " +
           "provides the only navigable pass from Thorbardin to " +
           "Qualinost.\n";
	break;
    }
    return str;
}

int
snow_blocked()
{
    int snow;

    switch (GET_SEASON)
    {
    case SPRING:
    case SUMMER:
    case AUTUMN:
	snow = 0;
	break;
    case WINTER:
        write("The winter snow is too deep here, and the road is " +
           "impassable. You will need to wait for the warmer seasons " +
           "to pass this way.\n");
        say(QCTNAME(TP)+ " tries to push through the winter snow " +
           "covering the road, but it is too deep.\n");
	snow = 1;
	break;
    }
    return snow;
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

    add_item(({"shadows","shadow","deep shadows","eerie shadows",
	"night's shadows","darkness"}),
      "@@add_item_shadows");
    add_item(({"mountains","tharkadan mountains","mountain", "ridgeline",
        "ridegelines","tharkadan mountain range","kharolis mountains",
        "peaks","mountain range","tharkadan range","mountain ranges"}),
      "@@add_item_mountains");

    add_item("pax tharkas","You cannot see Pax Tharkas, however it " +
      "would be somewhere to your northwest.\n");
    add_item("thorbardin","You cannot see Thorbardin, however it would " +
      "be somewhere to your southeast.\n");

}

/*
* This function is called from the main Krynn room.
*/
public void
reset_krynn_room()
{
    call_other(TO, RESET);
}




