/* This room takes care of the weather in Krynn.
 * for each area the weather is updated and can
 * be accessed through makroed function calls
 * (which will be put) in /d/Krynn/common/defs.h
 *
 * Note: Temperature is measured in degrees Celsius!
 *       Humidity is measured in %
 *
 * Aridor 09/96
 */



inherit "/std/room";

#define AREALIST    (["solace":({}) \
		      "solamn":({})])
/* This is the format of the mapping:
 *     "area":({x-coord, y-coord, Temperature offset, Humidity offset})
 */

mapping weather = ([]);
/* This is the format of the mapping:
 *     "area":({temperature,humidity,winddirection,windspeed})
 */

void
create_room()
{
    set_short("Weather room");
    set_long("You are in the clouds! At the same time, the sun is shining " +
	     "while rains pours down on you. A little off you can see it " +
	     "snowing and a wind batters you from all sides and none at " +
	     "the same time.\n");
    add_exit("/d/Krynn/workroom","out");

    set_alarm(600.0,600.0,"update_weather");
    set_alarm(0.0,0.0,"reload_weather");
}


void
reload_weather()
{
    restore_object(SAVE_FILE);
}

void
update_weather()
{
    
  
  save_object(SAVE_FILE);
}


void
add_new_area(string area)
{

}
