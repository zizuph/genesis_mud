/*
* o_room_base.c
*
* This is a standard local room base file for out-door rooms.
* You should change all those XXX to something more appropiate.
* If you are doing an area like Pax Tharkas then a proper 
* replacement for XXX would be 'pax'.
*/

#include "/d/Ansalon/common/defs.h"
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#define CREATE "create_kalaman_room"
#define RESET "reset_kalaman_room"

string
tod_descr1()
{
    string str;
    switch (GET_TIME_STRING)
    {
    case NIGHT:
    case MIDNIGHT:
	str = "Above, the stars shine coldly down from the black, night sky. " + 
	"The two moons Lunitari and Solinari offer some light as you make your " +
	"way through the darkness. ";
	break;
    case EARLY_MORNING:
    case MORNING:
	str = "In the east the sun begins its morning rise into the sky, with nights " +
	"shadows slowly retreating as it ascends into the heavens. ";
	break;
    case AFTERNOON:
    case NOON:
	str = "Fluffy white clouds sail the clear blue skies, and the golden sun continues " +
	"its daily circuit above you. ";
	break;
    case EVENING:
	str = "To the west, the sun begins to disappear behind the horizon, " +
	"creating long shadows all around you. ";
	break;
    }
    return str;
}

string
season_road()
{
    string str;
    switch (GET_SEASON)
    {
    case SPRING:
	str = "A brisk breeze passes through the cobbled streets, bringing " +
	"with it the smells of spring. The cry of a kingfisher can be heard overhead " +
	"as it heads out to its nest on the Vingaard River. ";
	break;
    case SUMMER:
	str = "A slight breeze makes its way down the cobbled streets, " +
	"refreshing you from the uncomfortable summer heat. ";
	break;
    case AUTUMN:
	str = "A mild wind tumbles browned leaves along the cobbled streets, " +
	"a strong reminder that autumn will soon be over, and that " +
	"winter is on its way. ";
	break;
    case WINTER:
	str = "Thick white snow covers the cobbled streets, making travel difficult. " +
	"A chill winter breeze blows past, making you shiver. ";
	break;
    }
    return str;
}

string
season_market()
{
    string str;
    switch(GET_SEASON)
    {
    case SPRING:
	str = "The smell of spring mixes with the smells of the food vendors, "+
	"pleasantly mixed together by a fresh breeze that blows away " +
	"the chill of winter. ";
	break;
    case WINTER:
	str = "While most of the winter snow has been cleared from the marketplace, " +
	"enough of it makes travel slippery at best. People huddle together around booths, " +
	"examining wares while trying to stay warm. ";
	break;
    case SUMMER:
	str = "A slight breeze does little to cool you down amongst the hot and sweaty " +
	"crowd of the market place. ";
	break;
    case AUTUMN:
	str = "A mild breeze ruffles many of the vendors booths here, and dry autumn " +
	"leaves tumble throughout the busy market place. ";
	break;
    }
    return str;
}

string
season_garden()
{
    string str;
    switch(GET_SEASON)
    {
    case SUMMER:
	str = "Here, the shade of the great trees offer some relief from the summer " +
	"heat, as well as allowing those visiting the garden some tranquil peace from " +
	"the hustle of the city. ";
	break;
    case AUTUMN:
	str = "Leaves bronzed by the sun cover the floor of the garden, as " +
	"the deciduous trees here shed their canopy as winter approaches. ";
	break;
    case WINTER:
	str = "Snow blankets everything in the garden, as winter takes control " +
	"of Kalaman and the rest of northern Ansalon. ";
	break;
    case SPRING:
	str = "You are pleasantly assaulted by the colours and smells that spring " +
	"has given rise to here in the garden. Insects buzz busily " +
	"from flower to flower, while birds chirp merrily in the bowers of the trees. ";
	break;
    }
    return str;
}

string
season_battlements()
{
    string str;
    switch(GET_SEASON)
    {
    case SUMMER:
	str = "A slight breeze coming off the Vingaard River refreshes you somewhat " +
	"from the summer heat that is quite noticeable on this shadeless battlement. ";
	break;
    case AUTUMN:
	str = "A chill autumn breeze blows along the battlements, reminding you that winter " +
	"is on its way. ";
	break;
    case WINTER:
	str = "Snow covers much of the battlement, a blanket of white that makes patrolling " +
	"rather treacherous. A freezing wind blows past you, making sure you don't " +
	"forget it is winter. ";
	break;
    case SPRING:
	str = "A fresh spring breeze blows along the battlements, bringing with it the " +
	"smells of the city. ";
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
	str = "Fluffy white snow lies all over the city of Kalaman.\n";
	break;
    case SUMMER:
	str = "Look at what?\n";
	break;
    case AUTUMN:
	str = "Look at what?\n";
	break;
    case SPRING:
	str = "Look at what?\n";
	break;
    }
    return str;
}

void add_item_city()
{
    add_item(({"city","kalaman","city of kalaman"}),
      "You stand in the city of Kalaman, based on the estuary " +
      "of the Vingaard River, it is one of Solamnias foremost " +
      "ports.\n");

    add_item(({"road","street","cobbled road","cobbled road",
	"cobbled street","roads","cobbled streets","streets"}),
      "You are standing on a cobbled road in the city of Kalaman. " +
      "While it seems to be well used by wagons and pedestrians " +
      "alike, it also seems to be well-maintained.\n");
    add_item(({"wagons","pedestrians"}),"You cannot see any " +
      "at the moment.\n");

    add_item(({"snow","white snow","fluffy white snow"}),"@@add_item_snow");
}

string
east_wall()
{
    return "Over the battlements to your east " +
    "you can see the busy harbour district of Kalaman.\n";
}

string
west_wall()
{
    return "Looking to the west, you can see the Vingaard " +
    "River disappear into the part of Solamnia " +
    "ominously known as Nightlund. Since the time of the " +
    "Cataclysm, Lord Soth the death knight and his " +
    "undead minions have plagued these lands, making " +
    "Nightlund a place of terror after dark.\n";
}

string
south_wall()
{
    return "To the south stretches the hilly and " +
    "dry plains of Estwilde. While seemingly desolate, " +
    "a number of human tribes as well as a few hill dwarf clans " +
    "call these plains their home. It is believed " +
    "the Red Dragonarmy will come through these plains " +
    "when they decide to assault Kalaman.\n";
}

string
north_wall()
{
    return "To your north you see " +
    "the magnificent Vingaard River widen, and open " +
    "up into the Turbidus Ocean.\n";
}

string
east_desc()
{
    return "Looking over the battlements to the east you see " +
    "the busy harbour district of Kalaman.\n";
}

string
west_desc()
{
    return "Looking over the battlements to the west " +
    "you see the Vingaard River disappear into the " +
    "eastern most part of the plains of Solamnia, known ominously " +
    "as Nightlund.\n";
}

string
south_desc()
{
    return "Looking over the battlements to the south " +
    "you make out the hilly and dry plains of Estwilde.\n";
}

string
north_desc()
{
    return "Looking over the battlements to the north, you " +
    "see the estuary of the Vingaard River open up into " +
    "the Turbidus Ocean.\n";
}

void add_item_wall()
{

    add_item(({"snow","fluffy white snow","snow"}),"@@add_item_snow");

    add_item(({"battlements","wall","walls","battlement"}),
      "You stand on the stone battlements on the wall " +
      "surrounding Kalaman. You believe it would offer " +
      "great protection from an attacking army, although " +
      "if the rumours of dragons are true, you have " +
      "your doubts about how effective they would be " +
      "against the Dragonarmy hordes.\n");

    add_item("kalaman","Behind you is the city of Kalaman, " +
      "a city preparing for the advances of the Red Dragonarmy.\n");
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

}

/*
* This function is called from the main Krynn room.
*/
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}




