/*
 * This is the main room for 'all' outdoor rooms in Krynn.
 */

#pragma save_binary

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/clock/clock.h"

inherit R_FILE

#define WEATHER "/d/Krynn/rastlin/weather_object"

nomask public void
setup_o_krynn_room()
{
    OUTSIDE;

    add_item("sun", "@@sun_desc");
    add_item(({"moons", "moon"}), "@@moon_desc");
    add_item("solinari", "@@solinari_desc");
    add_item("lunitari", "@@lunitari_desc");
    add_item("nuitari", "@@nuitari_desc");
}

/*
 * Function name: long
 * Description:   Describe the room and possibly the exits
 * Arguments:     str: name of item or 0
 * Returns:       A string holding the long description of the room.
varargs public mixed
long(string str)
{
    int i;
    mixed lg;
    string s, ret;

    lg = ::::long(str);
    if (str)
        return lg;
    if (!lg)
        lg = "";

    if (!WEATHER->query_day(this_object()))
    {
        if (!(s = WEATHER->query_moon_string(this_object())))
            ret = "It is night and the moon is not up.\n";
        else if (WEATHER->cloud_index(this_object()) > 20)
            ret = "It is night and the " + s + " is hidden by the clouds.\n";
        else
            ret = "The land is lit up by the eerie light of the " + s + ".\n";

        ret += lg;
      }
    else
        ret = lg;

    ret += WEATHER->weather_string(this_object()) + ".\n";

    while ((i = member_array(0, room_descs)) >= 0)
        room_descs = exclude_array(room_descs, i, i + 1);

    if (room_descs)
        for (i = 1; i < sizeof(room_descs); i += 2)
            ret = ret + check_call(room_descs[i]);

    if (room_no_obvious)
        return ret;

    return ret + this_object()->exits_description();
}
*/

public string
sun_desc()
{
    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            return "The sun is hanging low in the northern sky.\n";
	    break;
        case TOD_TWILIGHT:
	    return "The sun is sinking into the northern sky.\n";
            break;
        case TOD_NIGHT:
            return "There is no sun to be seen.\n";
	    break;
	case TOD_DAY:
            return "The sun is shining brightly in the daytime sky.\n";    
            break;
    }
}

public string
moon_desc()
{
    if (GET_TIMEOFDAY != TOD_DAY)
        return "You can see two moons in the sky, they are Solinari and Lunitari.\n";
    else
        return "You can't see any moons in the daylight.\n";
}

public string
solinari_desc()
{
    if (GET_TIMEOFDAY != TOD_DAY)
        return "Solinari is a " + GET_MOON_PHASE(SOLINARI) + " silver moon.\n";
    else
        return "Solinari is not visible in daylight.\n";
}

public string
lunitari_desc()
{
    if (GET_TIMEOFDAY != TOD_DAY)
        return "Lunitari is a red " + GET_MOON_PHASE(LUNITARI) + " moon.\n";
    else
        return "Lunitari is not visible in daylight.\n";
}

public string
nuitari_desc()
{
    if (!TP->query_prop("_i_can_see_nuitari"))
      return 0;
    if (GET_TIMEOFDAY != TOD_DAY)
        return "Nuitari is a black " + GET_MOON_PHASE(NUITARI) + " moon.\n";
    else
        return "Nuitari is not visible in daylight.\n";
}

