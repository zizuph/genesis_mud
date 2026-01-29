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

// G L O B A L   V A R S
string gLong_base, gLong_add, gPath_desc;
string *herbs;
int gRoom_type;

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
forest_path_short_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "On a path leading towards the forest of Silvanesti on a " +
	season_descr()+ " night";
	break;
    case TOD_DAWN:
	str = "On a path leading towards the forest of Silvanesti on a " +
	season_descr()+ " morning";
	break;
    case TOD_DAY:
	str = "On a path leading towards the forest of Silvanesti on a " +
	season_descr()+ " day";
	break;
    case TOD_TWILIGHT:
	str = "On a path leading towards the forest of Silvanesti on a " +
	season_descr()+ " evening";
	break; 
    }
    return str;
}

string
forest_short_desc()
{
    string str;
    switch (GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "within the forest of Silvanesti on a " +season_descr()+ " night";
	break;
    case TOD_DAWN:
	str = "within the forest of Silvanesti on a " +season_descr()+ " morning";
	break;
    case TOD_DAY:
	str = "within the forest of Silvanesti on a " +season_descr()+ " day";
	break;
    case TOD_TWILIGHT:
	str = "within the forest of Silvanesti on a " +season_descr()+ " evening";
	break; 
    }
    return str;
}

public string
show_light()
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
	    str = "It is midnight, and you stand before the fabled forest of " +
            "Silvanesti. Above the silver moon Solinari and the smaller moon Lunitari " +
            "cast eerie shadows amongst the feet of the aspen " +
            "trees like dark water flowing beneath the keel of a boat. ";
	    break;
	case NIGHT: 
	    str = "You stand before the fabled forest of Silvanesti in the darkness " +
            "of night. Above the silver moon Solinari and the smaller moon Lunitari " +
            "cast eerie shadows amongst the feet of the aspen " +
            "trees like dark water flowing beneath the keel of a boat. ";
	    break;
	case EARLY_MORNING:
	    str = "The sky starts to lighten as the sun sheds its first rays " +
            "for the day on the fabled forest of Silvanesti. A soft breeze stirs " +
            "around you, bringing with it the pleasant fragrance of spring. ";
	    break;
	case MORNING:
	    str = "The sun's morning rays spill down over the fabled forest of " +
            "Silvanesti. While not quite warm, the fresh, crisp smell of the air alerts " +
	    "you to spring's influence on the land at the moment. ";
	    break;
	case NOON:
	    str = "It is a warm spring day before the fabled forest of Silvanesti. " +
	    "A warm breeze stirs around you, bringing with it the pleasant " +
            "fragrance of spring. ";
	    break;
	case AFTERNOON:
	    str = "You stand before the fabled forest of Silvanesti. " +
            "Shadows lengthen as the sun begins to descend from the heavens. " +     
	    "A warm breeze stirs around you, bringing with it the pleasant " +
            "fragrance of spring. ";
	    break;
	case EVENING:
	    str = "You stand before the fabled forest of Silvanesti. In the west, the " +
            "evening sun begins its descent beyond the " +
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
	    str = "It is night here before the fabled forest of Silvanesti. " +
            "The warm night air is a pleasant relief following the hot and " +
	    "steamy summer days. A gusty wind blows through the nearby aspen trees, " +
            "creating an agitated whispering from the deep shadows. ";
	    break;
	case EARLY_MORNING:
	    str = "The night's shadows begin to retreat as the sun's first rays " +
            "appear over the horizon. Before you stands the fabled forest of Silvanesti. " + 
            "A gusty summer wind blows through the nearby aspen trees causing them to " +
            "stir with disquiet. ";
	    break;
	case MORNING:
	    str = "You stand before the fabled forest of Silvanesti. With the rising " +
            "of the morning sun, the land begins to warm. A gusty summer wind blows " +
            "through the nearby aspen trees causing them to stir with disquiet. "; 
	    break;
	case NOON:
	case AFTERNOON:
	    str = "The relentless summer sun beats harshly upon your head as you stand " +
            "before the fabled forest of Silvanesti. High humidity makes it very " +
            "uncomfortable, and even a gusty wind does little to relieve the muginess. ";
	    break;
	case EVENING:
	    str = "You stand before the fabled forest of Silvanesti. With the evening " +
            "sun beginning its descent behind the horizon, the fierce summer heat and " +
            "humidity begins to subside much to your relief. A gusty wind blows around " +
            "you, chilling your sweat and bending the nearby trees to its whim. ";
	    break;
	}
	break;
    case AUTUMN:
	switch(GET_TIME_STRING)
	{ 
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand before the fabled forest of Silvanesti on a windy " +
            "autumn night. Black clouds gather in the sky to the north, hinting at " +
            "a storm, while the silver moon Solinari and the smaller moon Lunitari " +
            "illuminate the stone walls before you, casting eerie shadows. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand before the fabled forest of Silvanesti as the sky " +
            "begins to grey with sunrise approaching. An autumn wind blows through the " +
            "trees to the north, bringing with it the dry smell of an approaching storm. ";
	    break;
	case MORNING:
	    str = "You stand before the fabled forest of Silvanesti. The cool rays of " +
            "the morning sun shine through holes in the grey clouds that seem to have " +
            "occupied the heavens. A chill autumn wind brings with it the impeding " +
	    "smell of an approaching storm. ";
	    break;
	case NOON:
	case AFTERNOON:
	    str = "You stand before the fabled forest of Silvanesti on a cool autumn " +
            "day. A chill wind blows through the nearby aspen trees, bringing with it " +
            "the smell of an approaching storm. ";
	    break;
	case EVENING:
	    str = "You stand before the fabled forest of Silvanesti. In the west, the " +
            "evening sun begins its descent beyond the horizon. A chill autumn wind " +
            "rises, blowing the nearby aspen trees to and fro and giving the impression " +
            "that it will be a cold time to be outside this night. ";
	    break;
	}
	break;
    case WINTER:
	switch(GET_TIME_STRING)
	{ 
	case MIDNIGHT:
	case NIGHT:
	    str = "You stand before the fabled forest of Silvanesti on a stormy " +
            "winter's night. A jagged fork of lightning illuminates the night sky, " +
            "briefly revealing roiling black clouds above you and the ground around " +
            "you. A mighty clap of thunder echoes over the forest, and a harsh winter " +
            "wind howls around you, battering the nearby aspen trees in a savage wave " +
            "of invisible force. ";
	    break;
	case EARLY_MORNING:
	    str = "You stand before fabled forest of Silvanesti. The nights sky begins " +
            "to lighten, and the savage winter storm that howls around you begins to " +
	    "lessen as the sunrise approaches. Above, black storm " +
	    "clouds roll overhead ominously, casting a dark pall " +
	    "over the snow-covered land around you. ";
	    break;
	case MORNING:
	    str = "You stand before the fabled forest of Silvanesti. " +
            "The morning air is chill, and even the rising sun " +
            "does little to remove the biting cold of the winter " +
            "wind that howls around you. With the rise of the sun, " +
            "cold rays flicker across the leaves of the aspen trees. ";
	    break;
	case NOON:
	    str = "You stand before the fabled forest of Silvanesti. " +
            "While the middle of the day, billowing storm " +
	    "clouds shadow the forest, and a cold winter " +
            "wind blows through the nearby aspen trees " +
	    "sending them whispering in agitation. ";
	    break;
	case AFTERNOON:
	    str = "You stand before fabled forest of Silvanesti. " +
            "The day begins to darken as the sun follows " +
	    "its downward path out of the heavens. A biting " +
	    "winter wind rolls past you, sending the nearby aspen " +
            "trees into a wild dance. ";
	    break;
	case EVENING:
	    str = "You stand before the fabled forest of Silvanesti. " +
            "In the west, the evening sun shines a hazy " +
	    "red as it begins its descent beyond the horizon. In " +
            "the distance the echo of thunder rolls its way to " +
            "you from the gathering of angry black clouds in " +
	    "the north, harkening another winter storm on the way. ";
	    break;
	}
	break;
    }
    return str;
}
