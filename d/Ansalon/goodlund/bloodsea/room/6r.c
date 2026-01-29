#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit BLOODSEA_OUT;

#define HARD_TO_SWIM 20

void
reset_bloodsea_room()
{
    return;
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"karthay","coastline", "isle of karthay","isle","island","beach",
               "sandy beach"}), "The rocky coastline of the isle of Karthay " +
               "opens up here to a stretch of sandy beach to the north. " +
               "The water is calm enough here for a skilled swimmer to swim " +
               "to shore.\n");
    add_item(({"water", "sea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. Rumour has it that the colour "+
               "is the result of the blood of many victims who lost their "+
               "lives during Krynn's most terrible hour, though it "+
               "could be the clay stirred up from the sea bottom by the "+
               "maelstrom.\n");

    add_row_exit(BROOM + "7r", "west", 0, 1);
    add_row_exit(BROOM + "5r", "east", 0, 1);
    add_row_exit(BROOM + "5s", "northeast", 0, 1);
    add_row_exit(BROOM + "6q", "south", 0, 1);

    add_cmd_item(({"north","to shore","shore","beach","to beach"}),"swim",
      "@@swim_sea");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);

    reset_bloodsea_room();

}

string
swim_sea()
{
 
 
    if(this_player()->query_skill(SS_SWIM) < HARD_TO_SWIM)
    {
        write("You try and swim towards the sandy beach, however the current is too strong for you " +
          "and drags you back!\n");
        say(QCTNAME(this_player()) + " tries to swim to the sandy beach, however the current is too " +
          "strong.\n");
        return "";
    }
    write("You skillfully swim to the sandy beach on the isle of Karthay.\n");
    TP->move_living("swims to the beach",
      "/d/Ansalon/goodlund/bloodsea/island/beach",1,0);
 
    return "";
}

int
no_go()
{
    write("You try and sail in that direction, however the current and wind created by a " +
       "mighty storm agressively drives you back!\n");
    return 1;
}

void
set_sink_path(string sp)
{
    sink_path = "/d/Ansalon/balifor/flotsam/room/bottom_of_bay";
}

string
short_descr()
{
    return bloodsea_short() + ", near a sandy beach on the isle of Karthay";
}
 
string
long_descr()
{
    return "The rocky coastline of the isle of Karthay opens up here to a " +
        "stretch of sandy beach to the north. " + bloodsea_desc()+ "\n";
}