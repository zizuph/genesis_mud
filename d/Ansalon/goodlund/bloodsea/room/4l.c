#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit BLOODSEA_OUT;

#define HARD_TO_SWIM  55

void
reset_bloodsea_room()
{
    return;
}

create_bloodsea_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"isle","island","mithas","isle of mithas","coastline"}), 
               "To your east is the coastline of the isle of Mithas, " +
               "an island ruled by the Bloodsea minotaurs.\n");
    add_item(({"volcano","volcanoes","four volcanoes","four great volcanoes"}),
               "Dominating the island of Mithas are four great volcanoes. " +
               "While continuously smoking, they are dormant... like a sleeping " +
               "dragon. The inhabitants of this isle treat them with cautious " +
               "respect.\n");
    add_item(({"karthay","isle of karthay"}), "While not visible to the eye, you " +
               "know the isle of Karthay lies to the north of Mithas.\n");
    add_item(({"water", "sea", "bloodsea"}), "The water within the Bloodsea has "+
               "a strange and reddish colour. You notice that beneath the water here " +
               "just off the coastline of Mithas is a sunken ruin, submerged since " +
               "the days of the cataclysm. By the looks, a powerful current runs " +
               "through these waters. It would take a strong swimmer to be able to " +
               "swim down to the ruins.\n");
    add_item(({"ruin","sunken ruin","cathedral","impressive cathedral"}),
               "Below the water here you can just make out the shadowy shape of a sunken " +
               "ruin. From what you can see, it looks like it was once an impressive cathedral " +
               "to the old gods, however for all its glory it was not spared the wrath of the " +
               "cataclysm!\n"); 
    add_item(({"current","powerful current","strong current"}),
               "A powerful current runs beneath the water here. It would take a strong swimmer " +
               "to be able to pass through it.\n");

    add_row_exit(BROOM + "5l", "west", 0, 1);
    add_row_exit(BROOM + "4m", "north", 0, 1);
    add_row_exit(BROOM + "xx", "east", "@@no_go");
    add_row_exit(BROOM + "5k", "southwest", 0, 1);
    add_invis_exit(BROOM +"uw1", "down", "@@swim_down", 2);

    add_cmd_item(({"down","water","to ruin","to cathedral","ruin","cathedral"}),
         ({"dive","swim"}),"If you want to swim down, just head in that direction!\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);

    reset_bloodsea_room();

}

int
swim_down()
{
    if(this_player()->query_skill(SS_SWIM) > HARD_TO_SWIM)
    {
       write("You dive down towards the ruined cathedral, swimming powerfully through " +
          "the strong current.\n");
       return 0;
    }

    write("You dive down towards the ruined cathedral, however the current hinders your " +
          "progress and you end up having to return to the surface. You'll need to improve " +
          "your swimming if you wish to reach the ruins.\n");
    say(QCTNAME(TP) + " dives down into the water, however returns not long after gasping " +
          "for breath.\n");
    return 1;

}

int
no_go()
{
    write("You notice a rough storm between the islands of Mithas and Karthay. " +
       "You decide it would be wiser to sail in calmer waters, and not have your " +
       "ship blown to pieces!\n");
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
    return "Along the coastline of the isle of Mithas, near a sunken ruin";
}
 
string
long_descr()
{
    return "To your east is the coastline of the isle of Mithas, a fiery " +
    "island whose scrub plains lie in the shadow of four great volcanoes. " +
    "Beneath the water of the Bloodsea you can make out the shadowy shape " +
    "of a sunken ruin. " +
    bloodsea_desc()+ "\n";
}