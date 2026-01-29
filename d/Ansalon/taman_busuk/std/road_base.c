/*
 *    The base file for Taman Busuk roads
 *
 *    road_base.c
 *    -----------
 *
 *    Coded .........: 98/07/03
 *    By ............: Ashlar
 *
 *    Latest update .: 98/07/03
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *         Despite the filename, this base goes for other rooms
 *         along the road.
 *
 *    Changes :
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE
inherit HERBSEARCHNEW;

#define CREATE "create_tbroad_room"
#define RESET  "reset_tbroad_room"

#define TB_MOUNTAIN 0
#define TB_VALLEY   1

static int terrain;
string extra_long_descr = "";
static string *herbs = ({ });

#ifndef ONE_OF
#define ONE_OF(x)   ((x)[random(sizeof(x))])
#endif  ONE_OF

void set_mountain()
{
    terrain = TB_MOUNTAIN;
    herbs = HERB_MASTER->query_herbs( ({ "mountains", }) );
}
void set_valley()
{
    terrain = TB_VALLEY;
    herbs = HERB_MASTER->query_herbs( ({ "conifforest", }) );
}

string
mountain_season()
{
    string str;
    switch(GET_SEASON)
    {
    	case SPRING:
	        str = "The spring air is crisp up here in " +
        	"the mountains. ";
        	break;
    	case SUMMER:
	        str = "Summer has dispelled the last vestiges of " +
	        "snow among the mountains. ";
        	break;
    	case AUTUMN:
	        str = "Autumn chill is in the air, and snow " +
        	"is creeping down from the highest peaks. ";
        	break;
    	case WINTER:
	        str = "The winder cold is intense up here in " +
        	"the mountains, and snow covers everything. ";
        	break;
    }
    return str;
}

string
mountain_tod_descr()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "It is night in the Taman Busuk mountain range. ";
        break;
        case TOD_DAWN:
            str = "It is morning in the Taman Busuk mountain range. ";
        break;
        case TOD_DAY:
            str = "It is day in the Taman Busuk mountain range. ";
        break;
        case TOD_TWILIGHT:
            str = "It is evening in the Taman Busuk mountain range. ";
        break;
    }

    switch(GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str += "The landscape looks stark and barren illuminated " +
            "by the light of the stars. ";
        break;
        case EARLY_MORNING:
            str += "The eastern horizon is ablaze in an amazing " +
            "hue of orange, as the early morning sun rises. ";
        break;
        case MORNING:
        case AFTERNOON:
            str += "The sun casts long shadows among the mountain " +
            "peaks. ";
            break;
        case NOON:
            str += "The noon sunlight feels very strong at this " +
            "altitude. ";
            break;
        case EVENING:
            str += "The sun is sinking below the west horizon, " +
            "shrouding the landscape in shadow. ";
        break;
    }

    return str;
}

string
valley_season()
{
    string str;
    switch(GET_SEASON)
    {
    	case SPRING:
	        str = "Spring brings new life to this " +
        	"mountain valley. ";
        	break;
    	case SUMMER:
        	str = "Summer has brought verdant green " +
        	"growth to the mountain valley. ";
        	break;
    	case AUTUMN:
        	str = "Autumn brings cool winds to this mountain " +
        	"valley. ";
        	break;
	    case WINTER:
        	str = "A blanket of snow covers the mountain valley. ";
        	break;
    }
    return str;
}

string
valley_tod_descr()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
        case TOD_NIGHT:
            str = "It is night in the Taman Busuk mountain range. ";
        break;
        case TOD_DAWN:
            str = "It is morning in the Taman Busuk mountain range. ";
        break;
        case TOD_DAY:
            str = "It is day in the Taman Busuk mountain range. ";
        break;
        case TOD_TWILIGHT:
            str = "It is evening in the Taman Busuk mountain range. ";
        break;
    }

    switch(GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str += "The landscape looks stark and barren illuminated " +
            "by the light of the stars. ";
        break;
        case EARLY_MORNING:
            str += "A soft glow of orange can barely be sensed over " +
            "the eastern edge of the valley. ";
        break;
        case MORNING:
        case AFTERNOON:
            str += "The sun casts long shadows on the valley floor. ";
            break;
        case NOON:
            str += "The noon sunlight feels very strong at this " +
            "altitude. ";
            break;
        case EVENING:
            str += "The sun is sinking below the west horizon, " +
            "shrouding the valley in shadow. ";
        break;
    }

    return str;
}

string
season()
{
    string str;

    switch(terrain)
    {
    	case TB_MOUNTAIN:
	        str = mountain_season();
        	break;
    	case TB_VALLEY:
	        str = valley_season();
        	break;
    }

    return str;
}


string
tod_descr()
{
    string str;

    switch(terrain)
    {
        case TB_MOUNTAIN:
            str = mountain_tod_descr();
            break;
        case TB_VALLEY:
            str = valley_tod_descr();
            break;
    }

    return str;
}

void
set_extra_long(string str)
{
    extra_long_descr = str;
}


string
long_descr()
{
    string str;

    str = tod_descr() + extra_long_descr + " " + season() + "\n";

    return str;
}

string
ground_desc()
{
    string str;

    switch(GET_SEASON)
    {
        case WINTER:
            str = "The ground is covered with a thick layer of " +
            "snow, making travel difficult.";
            break;
        default:
            str = "The ground up here in the mountains is mostly " +
            "rock.";
    }

    return str;
}

string
snow_desc()
{
    string str;
    switch(GET_SEASON)
    {
        case WINTER:
            str = "Everything here is covered with a thick layer of " +
            "cold snow.";
            break;
        default:
            str = "The snow on the mountain peaks is too far away " +
            "examine closely.";
    }
    return str;
}

void
add_mountain_items()
{
    add_item(({"mountain","mountains","mountain range",
        "Taman Busuk mountain range"}),
        "The vast Taman Busuk mountain range stretches out " +
        "like reaching fingers across the land. The immensity " +
        "of the landscape is daunting.\n");

    add_item(({"peaks"}),
        "The highest peaks of the mountain range reach well " +
        "above the clouds.\n");

    add_item(({"clouds"}),
        "A thin layer of clouds surround the highest peaks, making " +
        "them difficult to see.\n");

    add_item(({"ground"}),
        "@@ground_desc@@\n");

    add_item(({"snow"}),
        "@@snow_desc@@\n");

}

void
add_road_items()
{
    add_item(({"road","mountain road","path"}),
        "The road is little more than a cleared path " +
        "through the mountains. It twists and turns, " +
        "following the easiest route.\n");

    add_item(({"roadside","rocks"}),
        "The roadside is consists of clumps of rocks, " +
        "some covered with a growth of moss and " +
        "other hardy plants.\n");

    add_item(({"growth","moss","plants"}),
        "Anything that lives at this altitude must be very " +
        "hardy, able to withstand cold and wind.\n");
}

/*
 * Utility functions
 */

int
mountain_tired()
{
    switch(GET_SEASON)
    {
        case WINTER:
            return 60;
        default:
            return 4;
    }
}

int
road_tired()
{
    switch(GET_SEASON)
    {
        case WINTER:
            return 15;
        default:
            return 1;
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
    set_long("@@long_descr");
    setuid();
    seteuid(getuid());

    call_other(TO, CREATE);

    if (sizeof(herbs))
    {
        set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
            ONE_OF(herbs), ONE_OF(herbs) }), ({ "roadside", "ground",
            "growth", "herb growth" }), 3 );
    }

    reset_room();
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    this_object()->set_searched(random(6)+3);
    call_other(TO, RESET);
}
