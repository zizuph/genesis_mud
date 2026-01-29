/*
 *    The outside base file for the city of Sanction.
 *
 *    o_room_base.c
 *    -------------
 *
 *    Coded .........: 95/10/11
 *    By ............: Jeremiah
 *
 *    Latest update .: 97/08/17
 *    By ............: Ashlar
 *
 *
 *    Notes ..:
 *
 *    Changes :
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/* Inherit the Ansalon room */
inherit AOR_FILE

#define CREATE "create_sanction_room"
#define RESET  "reset_sanction_room"


string extra_long_descr = "";


string
season()
{
    string str;

    switch(GET_SEASON)
    {
    case SPRING:
	str = "Though spring normally brings life and "
	+ "newness to Ansalon, this place seems to "
	+ "be an exception. ";
	break;
    case SUMMER:
	str = "The temperature and the humidity in "
	+ "this place is very high, even for summer. ";
	break;
    case AUTUMN:
	str = "The normally cool autumn winds of the "
	+ "Khalkist mountains never seem to reach "
	+ "this infernally hot place. ";
	break;
    case WINTER:
	str = "Even though the winter in the Khalkist "
	+ "mountains can be very cold, this place does "
	+ "not seem affected by the season. ";
	break;
    }

    return str;
}


string
tod_short_descr()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "It is night in the city of Sanction. ";
	break;
    case TOD_DAWN:
	str = "It is morning in the city of Sanction. ";
	break;
    case TOD_DAY:
	str = "It is day in the city of Sanction. ";
	break;
    case TOD_TWILIGHT:
	str = "It is evening in the city of Sanction. ";
	break;
    }

    return str;
}


string
tod_long_descr()
{
    string str;

    switch(GET_TIME_STRING)
    {
    case MIDNIGHT:
    case NIGHT:
	str = "Here at night the city looks truely hellish " 
	+ "as the lava glow is reflected by the low hanging "
	+ "smoke clouds, casting the scene in a blood-red "
	+ "fiery light. ";
	break;
    case EARLY_MORNING:
	str = "The light from the rising sun fails to "
	+ "penetrate the heavy carpet of low hanging "
	+ "smoke clouds, leaving the city in a strange "
	+ "twilight. ";
	break;
    case MORNING:
    case NOON:
    case AFTERNOON:
	str = "The grayish-brown sunlight that makes it "
	+ "through the heavy low hanging clouds "
	+ "illuminates this twilight city. ";
	break;
    case EVENING:
	str = "The sky seems to start glowing as the daylight "
	+ "disappears with the setting sun, and the glow "
	+ "from the red hot lava begins to reflect in the "
	+ "low hanging smoke clouds. ";
	break;
    }

    return str;
}


string
volcanoes()
{
    string feeling;
    int    align = TP->query_alignment();

    switch(align)
    {
    case -1200..-600:
	feeling = " delightfully sinister ";
	break;
    case -599..199:
	feeling = " sinister ";
	break;
    case 200..1200:
	feeling = " nightmarish ";
	break;
    }

    return "Lava flows and smoke billows from three volcanoes "
    + "looming ominously above the rooftops of this" + feeling
    + "city. ";
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

    str = tod_short_descr() + volcanoes() + tod_long_descr()
    + extra_long_descr + " " + season() + "\n";

    return str;
}


void
add_harbour_items()
{
    add_item(({"harbour", "harbour basin"}),
      "The harbour stretches out between the breakwaters and the " +
      "piers. There are numerous smaller ships in the harbour " +
      "area.\n");

    add_item(({"city","sanction","Sanction"}),
      "The city of Sanction lies to the east, beneath the stern gaze " +
      "of the three volcanoes.\n");

    add_item(({"pier", "piers"}),
      "Although the piers of Sanction harbour are built of sturdy "
      + "timber solidly based in huge granite socles embedded deeply "
      + "into the bottom of the harbour, the tremors from the erupting "
      + "volcanoes have left the otherwise unyielding construction "
      + "shaky and seemingly a bit unsafe. This does, however, not "
      + "appear to keep people away from here. Randomly scattered "
      + "across the harbour area are numerous smaller ships.\n");

    add_item(({"ships", "small ships", "smaller ships"}),
      "Numerous smaller ships, most of them fishing vessels, "
      + "the lot nestled in the harbour between two natural break"
      + "waters formed of hardened lava.\n");

    add_item(({"breakwater", "breakwaters", "hardened lava"}),
      "Natural breakwaters created by the lava hardening as it "
      + "flows into the dark waters of Sanction harbour. Beyond the "
      + "breakwaters to either side, north and south of the harbour, "
      + "sprawls flat steaming deltas of fiery fury, boiling water "
      + "hissing away from contact with the slowly expanding shelf "
      + "of liquid rock.\n");
}

void
slum_descriptions()
{
    add_item(({"slum","teeming slum"}),
      "As with the rest of the slums of Sanction, this " +
      "crowded area of ramshackle buildings is teeming " +
      "with all sorts of vile characters, from thieves " +
      "to drunken troops of the dragonarmies.\n");
    add_item(({"drunken troops","troops","thieves",
	"vile characters"}),
      "Adding to the hellish aspect of this city, the streets and " +
      "slums of Sanction are teeming with thieves and evil soldiers.\n");
    add_item(({"buildings","filthy buildings","ramshackle buildings"}),
      "Closely packed together, these filthy buildings are rude " +
      "and temporary looking. They fill the slums of Sanction, " +
      "creating a maze of winding alleys.\n");
    add_item(({"alley","winding alleys","alleys"}),
      "The many ramshackled buildings packed together create " +
      "a maze of alleys throughout the slums of Sanction.\n");

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


string
add_item_moons()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "You cannot see the moons through the seemingly "
	+ "blood-red glowing smoke clouds covering the night "
	+ "sky above Sanction.\n";
	break;
    case TOD_DAWN:
	str = "You cannot see the moons through the low hanging "
	+ "smoke clouds, turning dull grey as the sun slowly "
	+ "rises.\n";
	break;
    case TOD_DAY:
	str = "It is day. There are no moons to be seen. It "
	+ "would probably not be possible to see the moons "
	+ "anyways through the carpet of low hanging clouds "
	+ "covering the sky above Sanction.\n";
	break;
    case TOD_TWILIGHT:
	str = "You cannot see the moons through the low "
	+ "hanging smoke clouds covering the sky above "
	+ "Sanction.\n";
	break;
    }

    return str;
}


string
add_item_sun()
{
    string str;

    switch(GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str = "It is night. There is no sun to be seen.\n";
	break;
    case TOD_DAWN:
	str = "The low hanging smoke clouds slowly turning "
	+ "dull grey is the only sign of the rising sun.\n";
	break;
    case TOD_DAY:
	str = "The sun can only barely be seen as a pale "
	+ "round plate, barely shining through the heavy "
	+ "carpet of low hanging smoke clouds.\n";
	break;
    case TOD_TWILIGHT:
	str = "The dull light of the setting sun is slowly "
	+ "replaced by the glow from the red-hot lava "
	+ "rivers reflecting in the low hanging carpet of "
	+ "smoke clouds.\n";
	break;
    }

    return str;
}


string
add_item_sky()
{
    string str = "Huge smoke clouds forming a low hanging almost "
    + "impenetrable carpet covering the sky above "
    + "Sanction.";

    switch(GET_TIMEOFDAY)
    {
    case TOD_NIGHT:
	str += " The clouds glow fiery-red reflecting the blaze "
	+ "from the large masses of red-hot lava flowing "
	+ "through the city.\n";
	break;
    case TOD_DAWN:
	str += " The clouds are turning from fiery-red to dull "
	+ "grey as the sun slowly rises.\n";
	break;
    case TOD_DAY:
	str += "\n";
	break;
    case TOD_TWILIGHT:
	str += " The clouds slowly begin to glow reflecting the "
	+ "fiery-red light from the lava rivers flowing through "
	+ "the city.\n";
	break;
    }

    return str;
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    set_long("@@long_descr");

    call_other(TO, CREATE);

    add_item(({"volcano", "volcanoes", "lords", "Lords",
	"lords of doom", "Lords of Doom", "large volcano",
	"large volcanoes"}),
      "Ominously looming above the city rooftops are the three "
      + "large volcanoes, known as the Lords of Doom, that are "
      + "dominating the mountains surrounding the city. Lava flows "
      + "continually from each of the Lords, and dark smoke pours "
      + "into the sky above the city.\n");

    add_item(({"sky", "clouds", "smoke clouds"}),
      "@@add_item_sky");

    add_item(({"smoke", "dark smoke"}),
      "Dark ash-grey smoke is pouring into the sky from each of "
      + "the large volcanoes, leaving a heavy carpet of low "
      + "hanging smoke clouds covering the sky above Sanction.\n");

    add_item(({"lava flow", "lava river", "lava rivers"}),
      "The lava flows continually from each of the three large "
      + "volcanoes looming in the mountains surrounding this "
      + "abyssmal city. The lava forms rivers of red-hot molten "
      + "rock slowly snaking its way through the city towards the "
      + "harbour area.\n");

    add_item("lava", "Red-hot molten rock flowing in rivers of "
      + "fire from each of the three large volcanoes rising in "
      + "the mountains surrounding the city.\n");

    remove_item("moons");
    remove_item("lunitari");
    remove_item("solinari");

    add_item(({"moon", "moons", "solinari", "lunitari"}),
      "@@add_item_moons");

    remove_item("sun");

    add_item("sun", "@@add_item_sun");
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
