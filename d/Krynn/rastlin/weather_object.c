/*
 * The weather object
 */

inherit "/std/object";

void
create_object()
{
    set_name("weather");
    set_short("weather controller extrodinare");
    set_long("The weather controller, at least this one is always right!\n");
}

public int
query_day(object env)
{
    return 0;    /* 0 - Night, 1 - Day */
}

public string
query_moon_string(object env)
{
    int mooncycle = 1;

    /* If the moon is not up */
/*    return 0;
*/

    return ({ "full moon",
	      "waning three quarter moon",
	      "waning half moon",
	      "waning quarter moon",
	      "waning cresent moon",
	      "new moon",
	      "waxing cresent moon",
	      "waxing quarter moon",
	      "waxing half moon",
	      "waxing three quarter moon" }) [mooncycle];
}

public int
cloud_index(object env)
{
    return 10; /* More or less than 20 */
}

public string
temperature_string(object env)
{
    int inten = 10;

    return ({
		"Its one of those baking eggs on the ground days",
		"So hot that the sun feels like its right next door",
		"Damn hot",
		"Very hot",
		"Hot",
		"Hot",
		"Reasonably hot",
		"Very warm",
		"Warm",
		"Pleasantly warm",
		"Average temperature",
		"A little chilly",
		"A slight nip in the air",
		"Chilly",
		"Very chilly",
		"Cold",
		"Cold",
		"Very cold",
		"Damn cold",
		"Incredibly cold",
		"Freezing cold"
	   }) [inten];
}

public string
cloud_string(object env)
{
    int cloud = 3;

    return ({
		"a beatifully clear sky",
		"a few high level sirius clouds",
		"scattered puffy clouds",
		"very thin complete cloud cover",
		"light cloud cover",
		"medium cloud cover",
		"dense cloud cover",
		"packed cloud cover",
		"packed cloud cover",
		"heavy black clouds",
		"thick heavy clouds"
	   }) [cloud];
}

public string
rain_string(object env)
{
    int cloud = 3, temp = 3;
    string tempstr1, tempstr2;

    tempstr1 = ({ "very hot ",
		  "hot ",
		  "warm ",
		  "nice ",
		  "cold ",
		  "",
		  "" }) [temp];
    tempstr2 = ({ " rain",
		  " rain",
		  " rain",
		  " rain",
		  " rain",
		  " hail",
		  " snow" }) [temp];

    return "\n" + capitalize(tempstr1 + ({
		"very light",
		"light", 
		"medium",
		"heavy",
		"very heavy",
		"torrential" }) [cloud] + tempstr2);
}

public string
weather_string(object env)
{
    return temperature_string(env) + " with " + cloud_string(env) +
	   rain_string(env);
}
