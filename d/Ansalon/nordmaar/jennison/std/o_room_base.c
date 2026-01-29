/*
 *
 *    The outside base file for the Port city of Jennison.
 *
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/nordmaar/jennison/local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include DL_CLOCK

/*
 *    Inherit the Ansalon outside room
 */
inherit AOR_FILE

/*    
 *    create_<areaname>_room
 *
 *    These functions must be added to each of the rooms
 *    in the given area. These two functions replace the
 *    standard functions create_room() and reset_room(),
 *    these are called from the Krynn base room file.
 *
 */
#define CREATE "create_jennison_room"
#define RESET  "reset_jennison_room"
    
/*
 *    Determine if a player can see Nuitari
 */
int
player_can_see_nuitari(object player)
{
    if (player->query_prop("_i_can_see_nuitari"))
        return 1;

    return 0;
}


/*
 *    Time of day descriptions to add to rooms in this area
 */
string
tod_descr1()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
            str = "It is midnight in Nordmaar. ";
            break;
        case NIGHT:
            str = "It is night in Nordmaar. ";
            break;
        case EARLY_MORNING:
            str = "It is morning in Nordmaar. ";
            break;
        case MORNING:
            str = "It is day in Nordmaar. ";
            break;
        case NOON:
            str = "It is day in Nordmaar. ";
            break;
        case AFTERNOON:
            str = "It is day in Nordmaar. ";
            break;
        case EVENING:
            str = "It is evening in Nordmaar. ";
            break;      
    }

    return str;
}

string
tod_descr2()
{
    string str;

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
            str = "The stars and the moons are shining brightly from "
                + "the deep black Nordmaarian night sky. ";
            break;
        case NIGHT:
            str = "The stars and the moons are shining from the "
                + "dark blue Nordmaarian night sky. ";
            break;
        case EARLY_MORNING:
            str = "The stars and the moons fade and darkness retreats, "
                + "as a thin line of light on the eastern horizon "
                + "heralds the coming of a new day. ";
            break;
        case MORNING:
            str = "The sun is burning hot from the eastern sky as it "
                + "slowly ascends towards zenith. ";
            break;
        case NOON:
            str = "The scorching midday sun is burning from a clear "
                + "blue sky. ";
            break;
        case AFTERNOON:
            str = "The scorching sun is burning from a clear blue sky, "
                + "its slow descent westwards promising relief in the "
                + "approaching sunset. ";
            break;
        case EVENING:
            str = "The sun is slowly setting in the west, bathing the "
                + "western horizon in a soft red light. ";
            break;      
    }

    return str;
}

/*
 *    Seasonal description to add to rooms in this area
 */
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
            str = "";
            break;
        case AUTUMN:
            str = ""; 
            break;
        case WINTER:
            str = "";
            break;
    }

    return str;
}

/*
 *    Item descriptions that are common to all outside rooms
 */
string
sky_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str = "Here at night, the dark sky above Nordmaar is "
                + "covered with a myriad of bright shining stars.";
            break;
        case EARLY_MORNING:
            str = "The dark sky is slowly turning blue as the sun is "
                + "rising in the east.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "Only a very few clouds can be seen on the clear blue "
                + "sky above you.";
            break;
        case EVENING:
            str = "The sky is slowly turning dark as the sun is setting "
                + "in the west.";
            break;      
    }

    str = str + "\n";

    return str;
}

string
cloud_descr()
{
    string str;

    str = "The clouds are thin and very far between.\n";

    return str;
}

string
sun_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str = "The sun is not visible at night.";
            break;
        case EARLY_MORNING:
            str = "A thin line of light on the eastern horizon is all that "
                + "can be seen of the sun.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "The sun is burning mercilessly from a clear blue sky.";
            break;
        case EVENING:
            str = "The sun is slowly setting in a sea of soft red light "
                + "on the western horizon."; 
            break;      
    }

    str = str + "\n";

    return str;
}

string
star_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str = "The stars are shining bright from the Nordmaarian "
                + "night sky.";
            break;
        case EARLY_MORNING:
            str = "As the sun is rising in the east the stars slowly "
                + "fade and dissapear.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "The stars are not visible at daytime.";
            break;
        case EVENING:
            str = "As the sun is setting in the west an occasional star "
                + "twinkles on the darkening eastern sky.";
            break;      
    }

    str = str + "\n";

    return str;
}


string 
moon_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
            str = "The moons Solinari and Lunitari are shining bright "
                + "from the Nordmaarian night sky.";
            if (player_can_see_nuitari(TP))
                str = str + " As a dark shadow the black moon, Nuitari, "
                    + "has taken its place among its brethren.";
            break;
        case EARLY_MORNING:
            str = "As the sun is rising in the east the moons slowly "
                + "fade and dissapear.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "The moons are not visible at daytime.";
            break;
        case EVENING:
            str = "As the sun is setting in the west the moons of Krynn "
                + "slowly awakens on the darkening eastern sky.";
            break;      
    }

    str = str + "\n";

    return str;
}

string
solinari_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
        case EARLY_MORNING:
        case EVENING:
            str = "The bright white, almost silvery, Solinari is shining "
                + "down upon you from the Nordmaarian night sky. The moon "
                + "is in its " + GET_MOON_PHASE(SOLINARI) + " phase.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "Solinari is not visible at daytime.";
            break;
    }

    str = str + "\n";

    return str;
}

string
lunitari_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
        case EARLY_MORNING:
        case EVENING:
            str = "The small red moon, Lunitari, is shining down upon "
                + "you from the Nordmaarian night sky. The moon is in "
                + "its " + GET_MOON_PHASE(LUNITARI) + " phase.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "Lunitari is not visible at daytime.";
            break;
    }

    str = str + "\n";

    return str;
}

string
nuitari_descr()
{
    string str; 

    switch (GET_TIME_STRING)
    {
        case MIDNIGHT:
        case NIGHT:
        case EARLY_MORNING:
        case EVENING:
            str = "The black moon, Nuitari, looms high above you, barely "
                + "visible against the black Nordmaarian night sky. The "
                + "moon is in its " + GET_MOON_PHASE(NUITARI) + " phase.";
            if (!player_can_see_nuitari(TP))
                str = "You do not seem to be able to locate Nuitari.";
            break;
        case MORNING:
        case NOON:
        case AFTERNOON:
            str = "Nuitari is not visible at daytime.";
            break;
    }

    str = str + "\n";

    return str;
}

/*
 *    Common descriptions used in the city of Jennison.
 *
 *        Piers
 *        Bay
 */

void
add_pier_descriptions()
{
    add_item(({"pier", "piers", "wooden pier", "wooden pier"}), ""
        + "The piers are built of large planks framed by wooden beams, "
        + "bolted to a series of massive wooden pillars rising from "
        + "the waters of the harbour. Large wooden cross beams lends "
        + "extra support and stability to the construction.\n");
     
    add_item(({"pillars", "wooden pillars", "wooden pillar",
          "pillar"}), "Massive tar-drenched wooden pillars, solidly "
        + "planted deep into the harbour basin, support the wooden "
        + "piers.\n");

    add_item(({"plank", "planks", "wooden plank", "wooden planks"}), 
          "Rugged wooden planks securely nailed to, and resting upon, "
        + "a large frame of heavy wooden beams. The planks have been "
        + "worn by many years of frequent use.\n");

    add_item(({"beam", "beams", "wooden beam", "wooden beams"}), ""
        + "Heavy wooden beams bolted to a series of massive wooden "
        + "pillars. Large wooden planks are securely nailed to, and "
	+ "rests upon, these heavy wooden beams.\n");

    add_item(({"cross beam", "cross beams", "wooden cross beam",
          "wooden cross beams"}), "Heavy wooden cross beams are "
        + "bolted to the massive wooden pillars, lending extra "
        + "support and stability to the piers.\n");

    add_item(({"basin", "harbour basin"}), "The harbour basin is "
        + "enclosed on three sides by the wooden piers. The water "
        + "in the basin seems deep enough the support rather large "
        + "ships.\n");
     
    add_item(({"water"}), "The water in the harbour basin is quiet "
        + "and clear. It seems deep enough the support rather large " 
        + "ships.\n");

}

void
add_bay_descriptions()
{
    add_item(({"bay", "small bay"}), "The small bay almost perfectly "
        + "braces the port city of Jennison. Natural jetties protect "
        + "the harbour from the waters of the Courrain Ocean.\n");
  
    add_item(({"jetties", "natural jetties", "natural jetty",
          "jetty"}), "Two natural jetties embraces the small port "
        + "city of Jennison. A thin stretch of land flows from the "
        + "north and southwards where it almost meets with a similar "
        + "stretch of land reaching from the south and northwards. "
        + "Only a narrow passage of open water keeps Jennison a port "
        + "city.\n");

    add_item(({"ocean", "courrain ocean"}), "The Courrain Ocean lies "
        + "just beyond the natural jetties protecting the port city "
        + "of Jennison. A narrow passage between the Jetties allow "
        + "ships easy access to the bay.\n");

    add_item(({"passage", "narrow passage"}), "A narrow strip of open "
        + "water between the natural jetties protecting the harbour, "
        + "allows easy access to the bay and the city of Jennison.\n");

}


/*
 *    IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 *    This function is called from the main Krynn room. It 
 *    checks whether or not the room should be reset. This 
 *    function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
        return 1;
    return 0;
}

/*
 *    This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);

    /* remove items before replacing them. */
    remove_item("sun");
    remove_item("moon");    
    remove_item("moons");
    remove_item("solinari");
    remove_item("lunitari");
    remove_item("nuitari");

    add_item(({"sky", "eastern sky", "western sky"}), "@@sky_descr");
    add_item(({"cloud", "clouds"}), "@@cloud_descr");
    add_item(({"sun"}), "@@sun_descr");
    add_item(({"star", "stars"}), "@@star_descr");
    add_item(({"moon", "moons"}), "@@moon_descr");
    add_item(({"solinari"}), "@@solinari_descr");
    add_item(({"lunitari"}), "@@lunitari_descr");
    add_item(({"nuitari"}), "@@nuitari_descr");
}

/*
 *    This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}
