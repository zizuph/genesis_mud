/*
 * /d/Gondor/common/lib/tod_descs.c
 *
 * Extracted from /d/Gondor/common/lib/area_room.c, Gnadnar, June 1998.
 *
 * This will append time-of-day descriptions to the room description,
 * as in:
 *
 *	On the River Anduin.  The Great River rolls southeast,
 *	its waters deep and dark.  The sun is setting in the
 *	west, colouring the sky golden red.
 *
 * or, if you do set_tod_comes_first(1):
 *
 *	On the River Anduin.  The sun is setting in the west, 
 *	colouring the sky golden red.  The Great River rolls 
 *	southeast, its waters deep and dark.
 *
 *
 * and it handles item descriptions for "sky", "sun", "moon", "star"
 * and "stars".
 *
 * To use:
 *   inherit "/d/Gondor/std/room";
 *   inherit "/d/Gondor/common/lib/tod_descs";
 * then, in create_gondor():
 *    set_short("on the River Anduin");
 *    // pass set_tod_long() the long description with no ending newline.
 *    set_tod_long("The Great River rolls southeast, "+
 *        "its waters deep and dark.");
 *    set_tod_landname("the Downs");  	// "Lebennin", "Ithilien", ...
 *    set_tod_landtype("river"); 	// "fields", "forest", ...
 *    // tod_descs is VBFC for room long and sky-related items
 *    set_long(tod_descs);
 *    add_item( ({ "sky", "sun", "moon", "star", "stars" }),
 *	        tod_descs );
 *    set_tod_prependshort(1);	// OPTIONAL -- will prepend 
 *                              // (short() + ". ") to long description.
 *
 * You can set the descriptions for day, night, stars, sun, etc
 * via set_day_desc, set_early_morning_sun_desc, set_morning_sun_desc,
 * set_noon_sun_desc, set_afternoon_sun_desc, set_evening_sun_desc,
 * set_night_desc, set_waxing_crescent_moon_desc,
 * set_waxing_gibbous_moon_desc, set_full_moon_desc,
 * set_waning_gibbous_moon_desc, set_waning_crescent_moon_desc,
 * set_dark_moon, and set_stars_desc all take a string as an argument;
 * VBFC is allowed.
 *
 * Comments -> Gnadnar
 */


#pragma strict_types;

#include "/d/Gondor/defs.h"

/* prototypes */
public string	tod_descs();
public void	set_tod_landname(string name);
public void	set_tod_landtype(string type);
public void	set_tod_long(string long);
public void	set_tod_prependshort(int p);
public void	set_tod_comes_first(int f);
public string	query_tod_landname();
public string	query_tod_landtype();
public string	query_tod_long();
public int	query_tod_prependshort();
public int	query_tod_comes_first();

public void	set_day_desc(string s);
public void	set_early_morning_sun_desc(string s);
public void	set_morning_sun_desc(string s);
public void	set_noon_sun_desc(string s);
public void	set_afternoon_sun_desc(string s);
public void	set_evening_sun_desc(string s);
public void	set_night_desc(string s);
public void	set_waxing_crescent_moon_desc(string s);
public void	set_waxing_gibbous_moon_desc(string s);
public void	set_full_moon_desc(string s);
public void	set_waning_gibbous_moon_desc(string s);
public void	set_waning_crescent_moon_desc(string s);
public void	set_dark_moon_desc(string s);
public void	set_stars_desc(string s);

public string	query_day_desc();
public string	query_early_morning_sun_desc();
public string	query_morning_sun_desc();
public string	query_noon_sun_desc();
public string	query_afternoon_sun_desc();
public string	query_evening_sun_desc();
public string	query_night_desc();
public string	query_waxing_crescent_moon_desc();
public string	query_waxing_gibbous_moon_desc();
public string	query_full_moon_desc();
public string	query_waning_gibbous_moon_desc();
public string	query_waning_crescent_moon_desc();
public string	query_dark_moon_desc();
public string	query_stars_desc();

public string	query_sun_desc();
public string	query_moon_desc();


/* external variables */
static string	Tod_landname = "Gondor";
static string	Tod_landtype = "land";
static string	Tod_long;
static int	Tod_prepend;
static int	Tod_comes_first;

static string Day =
	"@@query_sun_desc@@";
static string Early_morning_sun =
	"The sun is rising in the east, casting long shadows across "+
	"@@query_tod_landname@@.";
static string Morning_sun =
	"The sun is on its way up in the morning sky to the east.";
static string Noon_sun =
	"The sun is almost at its peak on its way across the sky. "+
	"It is noon in @@query_tod_landname@@.";
static string Afternoon_sun =
	"Daylight shines across @@query_tod_landname@@. It is "+
	"afternoon.";
static string Evening_sun =
	"The sun is setting in the west, colouring the sky golden red.";
static string Night =
	"@@query_stars_desc@@ It is night in @@query_tod_landname@@"+
	". @@query_moon_desc@@";
static string Waxing_crescent_moon =
	"The crescent moon illuminates the @@query_tod_landtype@@"+
	" faintly.";
static string Waxing_gibbous_moon =
	"The moon, now approaching full, casts a silvery light."; 
static string Full_moon =
	"The full moon, fair Ithil, bathes the @@query_tod_landtype@@"+
	" in liquid silver light."; 
static string Waning_gibbous_moon =
	"The moon, now past full, still casts a serviceable white light."; 
static string Waning_crescent_moon =
	"The moon tilts its slender upturned horns over the gloomy landscape."; 
static string Dark_moon =
	"";
static string Stars =
	"A sprinkling of Elbereth's stars can be seen twinkling high "+
	"above Middle-Earth.";



/*
 * Function name:	tod_desc
 * Description  :	return time-dependent desc for room long
 *			or sky items (e.g., sun, moon, stars)
 * Returns      :	the description
 *
 * if Exa_arg is set, then the player did "exa sun/sky/stars/moon ...".
 * if Exa_arg is not set, then the player did "look".
 *
 */
public string
tod_descs()
{
    string	desc = "",
		tmpstr,
		exad = TO->query_exa_arg();

    if (TO->tod() == "night")
    {
	if (!strlen(exad) ||
	    exad == "sky")
	{
            desc += TO->check_call(Night);
	}
	else if (exad == "star" ||
		 exad == "stars")
	{
            desc += TO->check_call(Stars);
	}
	else if (exad == "moon")
    	{
	    if (strlen(tmpstr = query_moon_desc()))
	    {
		desc += tmpstr;
	    }
	    else
	    {
		desc += "Only stars are visible in the night sky.";
	    }
	}
	else if (exad == "sun")
	{
	    return "The sun is not visible at night.\n";
	}
    }
    else	/* daytime */
    {
	if (!strlen(exad) ||
	    exad == "sky")
	{
	    desc += TO->check_call(Day);
	}
	else if (exad == "sun")
	{
	    desc += query_sun_desc();
	}
	else if (exad == "moon")
	{
	    return "The moon is not visible during the day.\n";
	}
	else if (exad == "star" ||
	    exad == "stars")
	{
	    return "The stars are not visible during the day.\n";
	}
    }

    if (desc == "")
    {
	desc = "Clouds obscure the sky.";
    }
    if (!strlen(exad))
    {
	if (strlen(Tod_long))
	{
	    if (!Tod_comes_first)
	    {
		desc = Tod_long + " " + desc;
	    }
	    else
	    {
		desc = desc + " " + Tod_long;
	    }
	}
	if (Tod_prepend)
	{
	    desc = CAP(TO->short())+". "+desc;
	}
    }
    return BSN(desc);
} /* tod_descs */


/* the easy ones */
public void	set_tod_landname(string name)	{ Tod_landname = name; }
public void	set_tod_landtype(string type)	{ Tod_landtype = type; }
public void	set_tod_long(string long)	{ Tod_long = long; }
public void	set_tod_prependshort(int p)	{ Tod_prepend = p;     }
public void	set_tod_comes_first(int f)	{ Tod_comes_first = f;     }
public string	query_tod_landname()		{ return Tod_landname; }
public string	query_tod_landtype()		{ return Tod_landtype; }
public string	query_tod_long()		{ return Tod_long; }
public int	query_tod_prependshort()	{ return Tod_prepend;  }
public int	query_tod_comes_first()		{ return Tod_comes_first;  }

public void set_day_desc(string s)                  { Day = s; }
public void set_early_morning_sun_desc(string s)    { Early_morning_sun = s; }
public void set_morning_sun_desc(string s)          { Morning_sun = s; }
public void set_noon_sun_desc(string s)             { Noon_sun = s; }
public void set_afternoon_sun_desc(string s)        { Afternoon_sun = s; }
public void set_evening_sun_desc(string s)          { Evening_sun = s; }
public void set_night_desc(string s)                { Night = s; }
public void set_waxing_crescent_moon_desc(string s) { Waxing_crescent_moon = s;}
public void set_waxing_gibbous_moon_desc(string s)  { Waxing_gibbous_moon = s; }
public void set_full_moon_desc(string s)            { Full_moon = s; }
public void set_waning_gibbous_moon_desc(string s)  { Waning_gibbous_moon = s; }
public void set_waning_crescent_moon_desc(string s) { Waning_crescent_moon = s;}
public void set_dark_moon_desc(string s)	    { Dark_moon = s; }
public void set_stars_desc(string s)                { Stars = s; }

public string query_day_desc()                  { return Day; }
public string query_early_morning_sun_desc()    { return Early_morning_sun; }
public string query_morning_sun_desc()          { return Morning_sun; }
public string query_noon_sun_desc()             { return Noon_sun; }
public string query_afternoon_sun_desc()        { return Afternoon_sun; }
public string query_evening_sun_desc()          { return Evening_sun; }
public string query_night_desc()                { return Night; }
public string query_waxing_crescent_moon_desc() { return Waxing_crescent_moon; }
public string query_waxing_gibbous_moon_desc()  { return Waxing_gibbous_moon; }
public string query_full_moon_desc()            { return Full_moon; }
public string query_waning_gibbous_moon_desc()  { return Waning_gibbous_moon; }
public string query_waning_crescent_moon_desc() { return Waning_crescent_moon; }
public string query_dark_moon_desc()		{ return Dark_moon; }
public string query_stars_desc()                { return Stars; }


/*
 * Function name:	query_sun_desc
 * Description	:	return the desc of the sun, based on tod
 * Returns	:	string -- the desc
 */
public string
query_sun_desc()
{
    string	desc = "";
    switch(TO->tod())
    {
    case "early morning":
	desc = TO->check_call(Early_morning_sun);
        break;
    case "morning":
	desc = TO->check_call(Morning_sun);
        break;
    case "noon":
	desc = TO->check_call(Noon_sun);
        break;
    case "afternoon":
        desc = TO->check_call(Afternoon_sun);
        break;
    case "evening":
	desc = TO->check_call(Evening_sun);
        break;
    }
    return desc;
} /* query_sun_desc */


/*
 * Function name:	query_moon_desc
 * Description	:	return the desc of the moon, based on phase
 * Returns	:	string -- the desc
 */
public string
query_moon_desc()
{
    string	desc = "";

    switch(CLOCK->query_moon())
    {
    case "waxing crescent":
	desc = TO->check_call(Waxing_crescent_moon);
	break;
    case "waxing gibbous":
	desc = TO->check_call(Waxing_gibbous_moon);
	break;
    case "full":
	desc = TO->check_call(Full_moon);
	break;
    case "waning gibbous":
	desc = TO->check_call(Waning_gibbous_moon);
	break;
    case "waning crescent":
	desc = TO->check_call(Waning_crescent_moon);
	break;
    }
    return desc;
} /* query_moon_desc */
