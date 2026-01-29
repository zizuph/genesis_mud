/*
 * Throtyl base room using Mapserver created by Arman
 */
#pragma save_binary
#pragma strict_types

#include "local.h"
#include CLOCKH

inherit "/d/Ansalon/std/map_serv";
inherit HERBSEARCHNEW

#define CREATE "create_throtyl_room"
#define RESET  "reset_throtyl_room"

string gExtra_night_long, gSpecial_short;
string *herbs = 0;
static string *throtyl_rooms = ({ "P", "E", "K", "T", "f", "m", "v", 
                                  "1", "2", "3", "4", "5" });

/* Function name: query_file_with_map
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return path to the file containing map
 */
public nomask string
query_file_with_map()
{
    return TDIR + "throtyl_map";
}

/* Function name: query_base_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where base-files are located
 */
public string
query_base_dir()
{
    return TDIR;
}

/* Function name: query_room_dir
 * Note:	  This function is _NECESSARY_ to redefine (it is redefined now)
 * Returns:	  Should return directory where room-files are located
 */
public string
query_room_dir()
{
    return TDIR + "rooms/";
}

/* Function name: is_room
 * Description:	  Test if letter on map corresponds to a room.
 * Argument:	  arg - letter corresponding to rooms
 * Returns:	  1 if room    else 0
 * Note:	  _ALWAYS_ make " " return 0
 */
public int
is_room(string arg)
{
    if (member_array(arg, throtyl_rooms) != -1)
	return 1;

    return 0;
}

/* Function name: exit_not_obvious
 * Description:	  Test if exit from one room to another should be not obvious
 * Argument:	  from - letter corresponding to from room
 *		  dest - letter corresponding to dest room
 * Returns:	  1 if not obvious    else 0 - exit will be obvious
 */
public int
exit_not_obvious(string from, string dest)
{
    string *paths = ({ "1", "2", "3", "4", "5", "P" });
    if (member_array(from, paths) != -1 && member_array(dest, paths) != -1) // path is obvious
	return 0;
    return 1; // all other are not obvious
}

/*
 * This function is called from the main Krynn room. It checks
 * weather or not the room should be reseted.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    return Check;
}

/* Function name: do_not_remove
 * Description:	  Decide if file with this room should be kept
 *		  (for security it is sometime usefull to keep the file)
 *		  Redefine it in ROOM base file or in room file.
 * Returns:	  0 - file can be removed, 1 - keep the file
 */
public int
do_not_remove()
{
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_map_room()
{
    int a,b,c,s,i;

    if (!Check)
	return;

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    call_other(TO, CREATE);
    if (s = sizeof(herbs))
    {
    	i = (Xx+1)*(Yy+1);
	a = random(s, i);
	b = random(s, i + a + random(i + a, i + a + (a * i)));
	c = random(s, i + a + b + random(i + a + b, i + a + b + (b * i)));
	set_up_herbs( ({ herbs[a], herbs[b], herbs[c] }),
			({"bushes","trees","ground","brush"}));
    }

    set_area_handler(TDIR + "throtyl_placer");

    TO->reset_krynn_room();
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    if (!Check)
	return;

    call_other(TO, RESET);
    set_searched(random(3));
}


public void
set_night_long(string str)
{
    gExtra_night_long = str;
}

public void
set_special_short(string str)
{
    gSpecial_short = str;
}

public string
long_desc(string long)
{
    string str, desc;

    str = (gSpecial_short ? gSpecial_short : short()) +
      ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The sun is making its way up in the sky, " +
		     "illuminating the grey rain clouds above you. " + long;
              break;
	case TOD_DAY:
              desc = "Rays of sunlight break through the rain clouds above " +
                     "you, breaking up the dreary weather with the occasional " +
                     "rainbow. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking below the horizon, causing " +
                  "the grey rain clouds above you to darken and cast shadows " +
                  "across the Throtyl moors. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
                  " and " + C(LUNITARI) + ", breaks through the dark rain clouds " +
                  "hanging over the Throtyl moors, allowing you to see your " +
                  "surroundings. " + (gExtra_night_long ? gExtra_night_long : long);
	      break;
    }

    str += desc;

    return str;
}

varargs public mixed
long(string str)
{
    string new_long = ::long(str);

    if (!str)
      new_long = long_desc(new_long);

    return new_long;
}

