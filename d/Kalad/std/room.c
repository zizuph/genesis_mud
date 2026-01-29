/*
   /d/Kalad/std/room.c

   Standard Kalad room.

   * Rewrote entire code and stripped non-general features
     like day/night descriptions, events, dirty checking for shops,
     and the changing of hide difficulty.
   * Removed dirty exits, it's too much overhead for only one line
     of description in the player. Player can be made dirty by
     objects like pools of mud lying around here and there.
   * query_in_kabal replaced by query_area function.
   * set_area, query_area, set_district, query_district now work
     with ints. (see /d/Kalad/sys/areas.h for a list of defines)
   * Added: time.c checks for ROOM_M_CANNOT_TELL_TIME.
     to see if it is possible to tell the time.
   * Removed the old sign stuff and added an add_sign function.

   Fysix@Genesis, Nov 1997
 */
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/d/Kalad/lib/time";

#include <stdproperties.h>
#include "/d/Kalad/sys/properties.h"
#include "/d/Kalad/sys/files.h"
#include "/d/Kalad/sys/time.h"
#include "/d/Kalad/sys/areas.h"

// Globals
static int	Hear_bell,     // Do we give bell messages in this room?
		Area_id,       // What area is this room in?
		District_id;   // In the area, what district is it?

static string	day_desc,
		night_desc;

// --- Set and query functions --------------------------------------

/* Function name: query_hear_bell
 * Description:   Returns what the room should hear when the bell rings.
 *                (see also /d/Kalad/lib/clock.c)
 * Returns:       int 0    hear no bell
 *                int 1..4 far..close to bell
 */
public int
query_hear_bell()
{
    return Hear_bell;
}

/* Function name: set_hear_bell
 * Description:   Set what the room should hear when the bell rings.
 *                (see also /d/Kalad/lib/clock.c)
 * Arguments:     int 0 hear no bell, 1..4 far..close to bell.
 *                (read /d/Kalad/doc/CLOCK.README)
 */
public void
set_hear_bell(int i)
{
    if (i >= 0 && i <= MAX_HEAR_BELL)
	Hear_bell = i;
}

/* Function name: add_sign
 * Description:   Add a sign. Use function pointers when possible for
 *                the description for the sign.
 * Arguments:     mixed   sign_name: name or array of names
 *                string* read_verbs
 *                mixed   sign_text: the contents of the sign
 */
public void
add_sign(mixed sign_name, string *read_verbs, mixed sign_text)
{
    add_item(sign_name, sign_text);
    add_cmd_item(sign_name, read_verbs, sign_text);
}

/* Function name: set_area
 * Description:   Set the id of the area this room is in.
 * Arguments:     int a unique area id.
 */
public void
set_area(int id)
{
    Area_id = id;
}

/* Function name: query_area
 * Description:   What is the id of the area this room is in?
 * Returns:       int the unique area id.
 */
public int
query_area()
{
    return Area_id;
}

/* Function name: query_area_name
 * Description:   What is the name of the area?
 * Returns:       string
 */
public string
query_area_name()
{
    return AREA_NAMES[Area_id];
}

/* Function name: set_district
 * Description:   Set the id of the district inside the area
 *                this room is in.
 * Arguments:     int a unique district id for this area.
 */
public void
set_district(int id)
{
    District_id = id;
}

/* Function name: query_district
 * Description:   What is the id of the district inside the area
 *                this room is in?
 * Returns:       int a unique district id for this area
 */
public int
query_district()
{
    return District_id;
}

/* Function name: query_district_name
 * Description:   What is the name of the district?
 * Returns:       string
 */
public string
query_district_name()
{
    return DISTRICT_NAMES[Area_id][District_id];
}

// --- Other functions -------------------------------------------------

/* Function name: clone_npcs
 * Description:   Clones and moves npcs to this room. Doesn't
 *                clone npcs when they are already cloned.
 * Arguments:     mixed object/array of objects that contain
 *                  the npcs if they are already cloned.
 *                string the filename of the npc to be cloned
 *                string how (see move_living), defaults to "xxx"
 *                function f, optional function to execute between
 *                  cloning and moving of the npc
 * Returns:       mixed object/array of objects containing the
 *                  cloned npcs
 */
public varargs mixed
clone_npcs(mixed npcs, string file, string how = "xxx", function f = 0)
{
    int i;

    // clone npcs if they are not cloned yet
    if (pointerp(npcs))
    {
	i = sizeof(npcs);

	while (i--)
	    if (!objectp(npcs[i]))
	    {
		npcs[i] = clone_object(file);
		if (functionp(f))
		    f(npcs[i]);
		npcs[i]->move_living(how, this_object());
	    }
    }
    else
    {
	if (!npcs)
	{
	    npcs = clone_object(file);
	    if (functionp(f))
		f(npcs[i]);
	    npcs->move_living(how, this_object());
	}
    }

    return npcs;
}

/* Function name: query_street_desc
 * Description:   Return the street description depending on
 *                the time of day/weather etc.
 * Returns:       string
 */
public string
query_street_desc()
{
    return (DAY ?
      "The streets are quite crowded at the moment.\n" :
      "The streets are rather deserted at the moment.\n");
}

/* Function name: create_kalad_room
 * Description:   Kalad room creation function
 */
public void
create_kalad_room()
{
}

public nomask void
create_room()
{
    create_kalad_room();
}

void
init()
{
    ::init();
    init_time();
}

// Add some extra wizard info
public string
stat_object()
{
    string str;

    str = "Area: " + query_area_name() +
    "\tDistrict: " + query_district_name() + "\n";

    return ::stat_object() + str;
}


/*******************************************************
 *   Function: sign()
 *
 *   Return the string to be read on a sign.
 *   To be redefined in the individual room.
 *   If not redefined, returns "Read what?\n".
 *******************************************************/
public string
sign()
{
    return ("Read what?\n");
}

/*******************************************************
 *   Function: read_sign()
 *
 *   Call this function from add_action and define a
 *   string sign() function for an easy sign.
 *******************************************************/
public int
read_sign(string str)
{
    notify_fail("Read what?\n");
    if (!str || str != "sign")
	return 0;

    write(sign());
    return 1;
}

/****************************************************************
 * Function: set_time_desc()
 * Args: day_desc   - the daytime description
 *       night_desc - the nighttime description
 *
 * Set the day and night time descriptions for your room.
 ****************************************************************/
public void
set_time_desc(string day_str,string night_str)
{
    day_desc = day_str;

    night_desc = night_str;
}

