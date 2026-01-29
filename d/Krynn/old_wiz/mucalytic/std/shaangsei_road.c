/* Standard road room for Sha'ang'sei. ~mucalytic/std/shaangsei_road */

inherit "/std/room";

#include "/sys/macros.h"
#include "/sys/language.h"
#include "../shaangsei/defs.h"
#include "/sys/stdproperties.h"

int found;

void create_room()
{
    set_short("A road in Sha'ang'sei");
    set_long("You see an unconfigured road here.\n");

    add_prop(ROOM_I_HIDE, 10);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(OBJ_S_SEARCH_FUN, "search_obj");
    add_prop(ROOM_I_LIGHT, "@@light_cond_for_time_of_day");

    add_item(({"wall", "walls", "city walls", "walls of the city"}),
        break_string("The city walls are as thick and tall as mountains - "+
        "in fact they are so high that their tops are almost lost in the "+
        "clouds. You can barely see small ant-like guards striding "+
        "puposefully along the battlements. No army could ever hope to "+
        "gain them.\n", 75));

    add_item(({"road", "cobblestoned road"}), break_string("The road is "+
        "rather dirty and scruffy from the passing of countless travellers "+
        "and the general day-to-day use by the citizens of the city. The "+
        "cobblestones are made from an unblemishable dark-red stone from "+
        "the dwarven quarries in the mountains to the far south-west.\n", 75));
}

int light_cond_for_time_of_day()
{
    int hour, diff;

    hour = atoi(extract(ctime(time()), 11, 12));

    if(!hour || hour == 12)
        diff = 12;
    else
        diff   = ftoi(pow(pow(itof(12 - hour), 2.0), 0.5));

    if(diff > 6)
        diff = 6;

    return(100 - (15 * diff)); // Light level = 100 to 10 per cent.
}

mixed search_obj(object player, string str)
{
    int ran;
    object stone;

    ran = random(3);

    if(str != "road" && str != "cobblestoned road")
        return 0;

    if(!ran && !found)
    {
        found = 1;
        stone = clone_object(OBJECTS + "stone");

        stone->move(TO);

        tell_room(E(player), QCTNAME(player)+" finds "+
            LANG_ADDART(stone->short())+"!\n", player);

        return "You find "+LANG_ADDART(stone->short())+"!\n";
    }
    return 0;
}
