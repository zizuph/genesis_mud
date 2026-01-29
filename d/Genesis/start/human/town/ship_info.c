#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

#define SAVEFILE (TOWN_DIR + "ship_info")

mixed *departures = ({ });

void
create_room()
{
    set_short("Shipping office");
    set_long("\n"+
             "This is the shipping information office.\n"+
             "Here you can find the time table for the different ship lines.\n"+
             "");

    add_item(({"sign","time table" }),"The sign shows the times when the ships depart Sparkle harbour.\n"+
    "");
    add_item(({"room","office" }),"");

    add_exit(TOWN_DIR + "pier2","south");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    restore_object(SAVEFILE);

    add_my_desc("@@sign_desc");
}

string
wizinfo()
{
    return ("This is where you later may add your own departures if you have\n" +
            "a ship travelling the seas. To add a departure,\n" +
            "Call here add_departure berth%%description%%cost\n" +
            "To remove one, Call here remove_departure description.\n\n" + 
            "examples: Call here add_departure 2%%Testing this%%100\n" +
            "          Call here remove_departure Testing this\n");
}

string
sign_desc()
{
    int i;
    string s;

    s  = "A sign on the wall says:\n";
    s += "         +--------------------------------------+\n";
    s += "         |  Berth  Destination          Cost    |\n";
    s += "         |                                      |\n";

    for (i = 0; i < sizeof(departures); i++)
      s += sprintf("         |   %2i   %-19s %4i cp   |\n",
                   departures[i][0], departures[i][1], departures[i][2]);

    s += "         |                                      |\n";
    s += "         |  Tickets are bought at the dock.     |\n";
    s += "         |                                      |\n";
    s += "         |  Due to a strike at our head office  |\n";
    s += "         |  ships will at best arrive at random.|\n";
    s += "         |                                      |\n";
    s += "         |  All the rest of the lines (total of |\n";
    s += "         |  14) are now serviced by Genesis     |\n";
    s += "         |  ShipLines. See their office south   |\n";
    s += "         |  of pier 7.                          |\n";
    s += "         |                                      |\n";
    s += "         |  Due to disagreements between Grosso |\n";
    s += "         |  and Sparkle Port Authorities        |\n";
    s += "         |  the Circle Route Galleon now runs   |\n";
    s += "         |  from Faerie, and in a completely    |\n";
    s += "         |  different route.                    |\n";
    s += "         |                                      |\n";
    s += "         |  Special  Circle  lines  servicing   |\n";
    s += "         |  players  of  size  Great Adventurer |\n";
    s += "         |  and smaller have been established   |\n";
    s += "         |  in the northern part of the harbor. |\n";
    s += "         |  Please see  GSL  office south of    |\n";
    s += "         |  pier 7.                             |\n";
    s += "         +--------------------------------------+\n";

    return s;
}

mixed *
query_departures()
{
    return departures;
}

void
add_departure(int berth, string dest, int cost)
{
    int i;

    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(departures); i++)
    {
        if(departures[i][0] < berth) continue;
        if((departures[i][0] == berth) &&
            (departures[i][1] < dest)) continue;
        break;
    }
    departures = slice_array(departures, 0,i-1) + ({({berth, dest, cost})}) +
        slice_array(departures, i, sizeof(departures));

    save_object(SAVEFILE);
}

void
remove_departure(string dest)
{
    int i;

    seteuid(getuid(this_object()));
    for (i = 0; i < sizeof(departures); i++)
        if (departures[i][1] == dest)
            departures = exclude_array(departures, i, i);
    save_object(SAVEFILE);
}
