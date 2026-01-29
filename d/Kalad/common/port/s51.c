#include "default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Center of the Port District");
    set_long("You are at the heart of the Port District.\n"+
      "Spreading all around you is the cobblestoned central plaza. Extremely "+
      "large buildings lie to your north, southwest and southeast. A "+
      "narrow road heads west-east while another similar road goes south "+
      "towards the docks. A sign has been placed here.\n");
    set_time_desc("The plaza is filled with the conversations of the "+
      "many people travelling to and fro.\n","The plaza contains just a few "+
      "people and their muffled conversations. Most look like they're "+
      "headed for home.\n");
    add_item(({"cobblestoned central plaza","cobblestoned plaza","central plaza","plaza"}),
      "A large square area where much of the daily traffic of the district "+
      "passes through.\n");
    add_item(({"extremely large buildings","large buildings","buildings","building"}),
      "Gigantic warehouse-type structures that lie about the plaza.\n");
    add_item(({"road"}),"Which road?\n");
    add_item(({"narrow road"}),"A small road that crosses this plaza.\n");
    add_item(({"similar road"}),"A small road that eventually leads "+
      "towards the city docks.\n");
    add_item(({"sign"}),"It has an abundant amount of legible writing on "+
      "it.\n");
    add_cmd_item("sign","read","@@sign");
    add_exit(PORT + "s50", "west");
    add_exit(PORT + "s61", "south");
    add_exit(PORT + "s52", "east");
    set_alarm(25.0,0.0,"room_events");
}

sign()
{
    return "West - Gaming House\n"+
    "East - Tar Shop\n"+
    "South - Docks\n";
}

room_events()
{
    switch(random(5))
    {
    case 0:
	tell_room(TO,"A group of rapacious sailors pass through the plaza.\n");
	break;
    case 1:
	tell_room(TO,"You feel someone bump into you from behind, but when you turn "+
	  "to find the culprit, you see no one.\n");
	break;
    case 2:
	tell_room(TO,"You hear an old man scream: Thief! Thief!!!\n"+
	  "The old man chases after a small figure.\n");
	break;
    case 3:
	tell_room(TO,"A group of rough-looking men pass by.\n");
	break;
    case 4:
	tell_room(TO,"A swarthy female buckaneer arrives.\n"+
	  "The swarthy female buckaneer leaves south.\n");
	break;
    }

    set_alarm(30.0,0.0,"room_events");
}

