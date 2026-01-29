/*
 * gh.c
 *
 * This is the standard room to inherit for rooms surrounding the
 * Grey Havens.
 *
 * 1997/06/01 Last update
 * 2011/08/04 Lavellan - Fixed typo "magnificient", etc. A lot could be
 *                       improved here.
 *                     - Removed break_string.
 */

#include "defs.h"
#include <stdproperties.h>

inherit "/d/Shire/std/room";

create_gh() {}
reset_gh() {}

void
create_shire_room()
{
    add_item(({"sky", "heaven", "stars", "sun", "horizon"}),
	"@@exa_sky@@\n");
    add_item(({"blue mountains", "mountains", "ered luin"}),
	"@@exa_blue_mountains@@\n");

    add_prop(ROOM_I_INSIDE, 0);
    create_gh();
}

void
reset_room()
{
    reset_gh();
}

/*
 * Examining the Blue Mountians.
 */
string
mountains_day_night()
{
    int hour = CLOCK->query_hour();
    string how;

    switch(hour)
    {
	case EARLY_MORNING:
//	    return "shine magnificiently in the early morning light";
	    return "shine magnificently in the early morning light";
	case MORNING:
	    return "stand there shining as the morning Sun sparkles "
		 + "the land";
	case NOON:
	    return "loom in the distance as you notice that the Sun "
		 + "stands at her top in the South";
	case AFTERNOON:
	    return "shine in a hue of blue as the Sun slowly travels "
		 + "westwards towards the Land of Bliss";
	case EVENING:
	    return "darken slowly as the western horizon reddens and "
		 + "the first stars appear in the clear eastern sky";
	case EARLY_NIGHT:
	    return "can be outlined as a dark line under the bright "
		 + "stars of Middle-Earth";
	case LATE_NIGHT:
	    return "can be seen silhouetted against the star-bright "
		 + "night in Middle-Earth";
    }
}

string
exa_blue_mountains()
{
    return BS("The Blue Mountains, or the Ered Luin, " + 
	      mountains_day_night() + ".\n")
//    + BS("    Once upon the time, this mountain range was a single "
    + BS("Once upon the time, this mountain range was a single "
    + "row of mountains stretching from the far north to the White Mountains "
    + "in the south, but in the end of the First Age, some thousands years "
//    + "ago, the Gods from the West battled a great War against the Great "
    + "ago, the Gods from the West fought a great War against the Great "
//    + "Enemy, Morgoth, of which Sauron was but a Leutenant. During "
    + "Enemy, Morgoth, of which Sauron was but a Lieutenant. During "
    + "this battle of Gods, the Blue Mountains was divided in two, and "
    + "now the Gulf of Lune separates the two mountain ranges.");
}

/*
 * Examining the sky.
 */
string
exa_sky()
{
    int hour = CLOCK->query_hour();

    switch (hour)
    {
	case EARLY_MORNING:
	    return
	      BS("The Sun slowly climbs up in the eastern horizon and the "
	       + "fresh morning light enbraces your spirit and warms your "
	       + "soul.");
	case MORNING:
	    return
	      BS("Birds chirp happily as the morning light enlivens creatures "
	       + "of the Middle-Earth.");
	case NOON:
	    return
		BS("The Sun stands at her zenith in the South. She shines "
//		 + "magnificiently in this bright day in the area around "
		 + "magnificently in this bright day in the area around "
		 + "Grey Havens, and life sizzles and buzzes around you.");
	case AFTERNOON:
	    return
		BS("It is now afternoon in Middle-Earth, and here in the Grey "
		 + "Havens area, birds and animals are slowly getting more "
		 + "silent and insects getting less active.");
	case EVENING:
	    return 
		BS("The Sun has now travelled west and she is slowly entering "
//		 + "the magnificient red sky in the western horizon.");
		 + "the magnificent red sky in the western horizon.");
	case EARLY_NIGHT:
	    return
		BS("Still early night, the bright stars of the heaven sparkle "
		 + "in many colours. The Sickle can clearly be seen and "
		 + "the Crown of Durin glimmer as beautiful constellations "
		 + "of Stars in the heaven.");
	case LATE_NIGHT:
	    return
		BS("It is now late night, and still the stars shine over you "
//		 + "reminding you of the magnificient Elbereth Githoniel, "
		 + "reminding you of the magnificent Elbereth Githoniel, "
		 + "Queen of the Heavens, for she created the Stars, kindled "
		 + "the Two Lamps, illuminated the Two Trees, blessed the "
		 + "Silmarils, and filled the vessels which became the "
		 + "Sun and the Moon.");
    }
}


/*
 * Examine the White Towers.
 */
void
add_towers()
{
    add_item(({"towers", "white towers"}),
	"@@exa_towers@@\n");
}

string
exa_towers(string text)
{
    return
	BS("This is the Tower Hills, on which three towers, the White Towers, "
	 + "stand gazing westwards toward the Sea. It was once the Watch-towers "
	 + "of the Western border of the lost realm Arnor, of which not many "
	 + "remember or even have heard of.\n");
}

void
add_hills(string text)
{
    add_item(({"hills", "hill", "tower hills"}),
	"@@exa_hills|"+text+"@@\n");
    add_towers();
}

string
exa_hills(string text)
{
    return
	BS(CAP(text) + " "
	 + "This is the Tower Hills, on which three towers, the White Towers, "
	 + "stand. The hill is sloping slowly upwards first, but gets ever "
	 + "increasingly steeper as it gets higher.");
}

void
add_gulf()
{
    add_item(({"gulf", "gulf of lune", "lune", "sea"}),
	"@@do_exa_gulf@@\n");
}

static string *gulf_text = ({
    "you listen to the relaxing sounds of the sea rushing against " + 
    "the shore in this star-lit night by the Gulf of Lune.", 
    
    "you can see your long shadows as the sun has emerged over the " +
    "eastern horizon, and further in the west, you see the waves of " +
    "the Gulf of Lune beat the shores of Middle-Earth.",
    
    "you watch the fresh morning light fill the Gulf of Lune with " +
//    "magnificient blue and green colours as the Sea waves relentlessly " +
    "magnificent blue and green colours as the Sea waves relentlessly " +
    "against the shore.",
    
    "you can see the Gulf of Lune coming in from the Great Sea in the " +
    "West, Belagear, with its green and blue colours and gentle waves " +
    "slowly traversing against the shores of Middle-Earth.",
    
    "you see the Sun passing across the sky ever more westwards and down. " +
    "Soon she will be going down below the horizon and into the Gulf of " +
    "Lune.",
    
    "you can only see half of the Sun in the red horizon. Soon the Sun " +
    "will not shine anymore, hearing only the ever continuing sounds of " +
    "waves from the Gulf of Lune beating against the western shores of " +
    "Middle-Earth.",
    
    "you can hear the Sea rumbling by the shore of the " +
    "Gulf of Lune in the now yet early night."
});

string
exa_gulf()
{
    int hour;
    string *text;

    hour = CLOCK->query_hour();

    switch (hour)
    {
	case LATE_NIGHT:
	    return CAP(gulf_text[0]);
	case EARLY_MORNING:
	    return CAP(gulf_text[1]);
	case MORNING:
	    return CAP(gulf_text[2]);
	case NOON:
	    return CAP(gulf_text[3]);
	case AFTERNOON:
	    return CAP(gulf_text[4]);
	case EVENING:
	    return CAP(gulf_text[5]);
	case EARLY_NIGHT:
	    return CAP(gulf_text[6]);
    }
}

string
do_exa_gulf()
{
    return BS(exa_gulf());
}

void
add_town(string desc)
{
    add_item(({ "town", "harbour", "mithlond", "grey havens", "havens" }),
	"@@exa_town|"+desc+"@@.\n");
}

string
exa_town(string desc)
{
    int hour;

    if (!strlen(desc))
//	desc = "you see that the magnificient town Mithlond, or Grey Havens "
	desc = "you see that the magnificent town Mithlond, or Grey Havens "
	     + "in the Common Language, is";

    hour = CLOCK->query_hour();

    switch(hour)
    {
	case EARLY_NIGHT:
	    return CAP(desc) + " twinkling with lights in the early night";
	case LATE_NIGHT:
	    return CAP(desc) + " lying silent during the night";
	case EARLY_MORNING:
	    return CAP(desc) + " shining in the early morning light";
	case MORNING:
	    return CAP(desc) + " bathing in the morning light";
	case NOON:
	    return CAP(desc) + " shining as the sun stands at its zenith";
	case AFTERNOON:
	    return CAP(desc) + " filled with life now, as it is the " +
		"afternoon and the Sun will soon set";
	case EVENING:
	    return CAP(desc) + " standing in long shadows in the late " +
		"evening light";
    }
}

varargs void
add_area(string area, string landscape)
{
    if (!area)
	area = "";
    if (!landscape)
	landscape = "";

    add_item(({"area", "surroundings", "birds", "sea-birds", "grass",
	       "landscape", "ground", "wild-life", "life", "view"}),
	     "@@exa_area|"+area+"|"+landscape+"@@\n");
}

varargs string
exa_area(string area, string landscape)
{
    string ret;
    int hour = CLOCK->query_hour();

    if (!strlen(area))
	area = "The surrounding area";
    if (!strlen(landscape))
	landscape = "the weather-beaten landscape by "
		  + "the western shores of Middle-Earth";

    switch (hour)
    {
	case EARLY_MORNING:
	    ret = area + " sizzles with life in this beautiful morning in "
		+ landscape + " of Middle-Earth. Birds chirp wildly and the "
		+ "wind gets ever more gentle.";
	    break;
	case MORNING:
	    ret = area + " is full of life now in the morning. "
		+ CAP(landscape) + " of Middle-Earth warms up by the Sun "
		+ "standing ever more high in the south-east.";
	    break;
	case NOON:
	    ret = area + " is beautiful in colours as the Sun stands high "
		+ "in the southern horizon. " + CAP(landscape) + " is "
		+ "gently kissed by a calm wind of salt water from the west.";
	    break;
	case AFTERNOON:
	    ret = area + " is still warm as soft winds from the west gently "
		+ "embraces " + landscape + ". Sea-birds soar high up in the air "
		+ "untouched by mortal struggles and the Sun sinks ever lower "
		+ "in the western horizon.";
	    break;
	case EVENING:
	    ret = area + " is now slowly getting darker as the Sun sinks into "
//		+ "the Sea in the west. The life at " + CAP(landscape)
		+ "the Sea in the west. The life at " + landscape
//		+ " dies out and the sea-gulls seems to have hidden themself "
		+ " dies out and the sea-gulls seem to have hidden themselves "
//		+ "in shelters during the forth-coming night.";
		+ "in shelters for the forthcoming night.";
	    break;
	case EARLY_NIGHT:
	    ret = area + " is now dark, and you can not see far. The salt wind "
		+ "from the west gets stronger and " + landscape + " is "
		+ "silent and seems to be empty of life.";
	    break;
	case LATE_NIGHT:
	    ret = area + " is now dark, lit only by a cold magical light from "
		+ "the Stars and the Moon in the Heaven. " + CAP(landscape)
		+ " is utterly silent, and only the ever blowing wind from "
		+ "the Sea in the west can be heard rustling the grass around "
		+ "you.";
	    break;
    }
//    return break_string(ret, 76);
    return ret;
}

string
exa_wind()
{
//    return break_string("A gentle salt wind blows from the western Sea.", 78);
    return "A gentle salt wind blows from the western Sea.";
}
