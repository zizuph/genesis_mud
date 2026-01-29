/*
 * Inheritable standard room for the back entrance
 * that leads from the edge of the chasm to inside 
 * the fort.
 *
 *    Lilith June 2004
 *
 */
inherit "/std/room";
inherit "/d/Avenir/inherit/room_tell"; // room tells (tm) by Aridor.

#include "outpost.h"

static mapping opp = 
    ([ "north" : "south", "east" : "west",
       "south" : "north", "west" : "west",
       "northwest" : "southeast", "northeast" : "southwest",
       "southeast" : "northwest", "southwest" : "northeast",
       "up" : "down", "down" : "up"
     ]);
 
static string east, west;

string
tunnel_exits()
{
    return COMPOSITE_WORDS(query_exit_cmds());
}

string
descending()
{
    string *strs, desc;

    if(sizeof(strs = query_exit_cmds()) < 2)
       return "";

    desc = ONEOF(({ "narrow path", "foot-wide ledge", "crack in the wall" }));

    return ONEOF(({ " The " + desc + " descends precariously "
      + strs[1] + ", and rises up to the " + strs[0] + ".",
        " The " + desc + " rises to the " + strs[0] + " and descends sharply "
      + "to the " + strs[1] + "."}));

}

string
ascending()
{
    string *strs, desc;

    if(sizeof(strs = query_exit_cmds()) < 2)
       return "";

    desc = ONEOF(({ "narrow path", "foot-wide ledge", "crack in the wall" }));

    return ONEOF(({ " The " + desc + " ascends impossibly "
      + strs[0] + ", and descends to the " + strs[1] + ".",
      " The " + desc + " ascends to the " + strs[1] + " and drops sharply "
      + "to the " + strs[0] + "."}));

}

varargs string
eastern(string where, string efunc)
{
    object there;

    if((there = find_object(where)) || 
        (there = find_object(OUTPOST +"secret/" + where)))
        east = opp[there->get_west()];

    if(!east)
        east = ONEOF(({"northeast","southeast"}));

    add_exit(where, east, efunc);

    return east;

}

string
get_east()
{
    return east;
}

varargs string
western(string where, string efunc)
{
    object there;

    if((there = find_object(where)) || 
       (there = find_object(OUTPOST +"secret/"+ where)))
        west = opp[there->get_east()];

    if(!west)
        west = ONEOF(({"northwest","southwest"}));

    add_exit(where, west, efunc);

    return west;

}

string
get_west()
{
    return west;
}

/* Start up the room tells now */
void
enter_inv(object ob, object from)
 {
    ::enter_inv(ob, from);

    start_room_tells();
    set_tell_time(150);
}

