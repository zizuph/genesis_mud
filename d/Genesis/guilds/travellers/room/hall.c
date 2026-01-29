#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#define CITY_STREET "/d/Earthsea/gont/gont_city/rooms/city_street/"

void
create_traveller_room() 
{
    set_short("Hallway");
    set_long("The hallway is magnificently adorned, with " +
      "large massive columns reaching to the high arched " +
      "ceiling. An archway at the east end leads outside. "+
      "You notice a small sign by the entrance to the west.\n");

    add_item(({ "arch", "archway" }), 
      "It is as magnificent as the columns\n");
    add_item((({"columns", "massive columns"})),
      "The massive columns are Corinthian in style carved from "+
      "dark granite which has small veins of silver embedded in it.\n");
    add_item((({"sign", "small sign"})),
      "There is a small ornately painted sign here, which "+
      "you can read.\n");

    add_exit("stairs", "west", "@@test_human");
/*
    add_exit(CITY_STREET + "city_road30", "east");
*/
    add_exit(CITY_STREET + "city_road14", "east");
    add_cmd_item(({"sign", "small sign"}), "read", "You read "+
      "the small sign which states: \n" + 
      "\nThe Travellers' Guild.\n"+
      "Only humans may enter here.\n");
}

int
test_human()
{
    object tp = this_player();

    if (tp->query_race_name() != "human")
    {
	tp->catch_msg("Something prevents you from going west.\n");
	return 1;
    }

    return 0;
}
