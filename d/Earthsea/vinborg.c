inherit "/std/room.c";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_room()
{
    set_short("West Pier");
    set_long(break_string("You are standing on the West Pier"+
	" stretching out into the bay of Gont Port and"+
	" everywhere around you can see different kinds of"+
	" ships anchored. This is a very busy harbour with"+
	" a forest of masts swaying back and forth in the"+
	" breeze coming in from the sea. At this pier"+
	" there are mostly traders, but also a few"+
	" passenger ships with far distant destinations."+
	" You hear the sound of hawsers creaking against"+
	" woodwork when the ships rock in the small waves."+
	" A salty smell of sea and fish is in the air. "+
	"This is the pier to Vinborg!\n", 70));

    add_item("pier", "The pier is built from sturdy timber"+
      " logs, stretching far out in the bay. There are"+
      " many ships anchored along the side, coming from"+
      " different places of the Archipelago.\n");
    add_item("ships","A great number of ships are anchored"+
      " in Gont Port with masts swaying back and forth in"+
      " the small waves coming in. You see galleys, sloops,"+
      " caravels and many other types.\n");
    add_item("masts","The masts are swaying back and forth"+
      " in the breeze.\n");
    add_item("harbour","This is the Port of Gont, a busy"+
      " trading harbour with many ships visiting every"+
      " year.\n");
    add_item("waves","The waves are very small here, finding"+
      " their way through the narrow canal between the Armed"+
      " Cliffs.\n");
    add_item("cliffs","Almost straight south are the Armed"+
      " Cliffs, and between them the canal leading into the"+
      " secluded bay.\n");
      
    add_exit("/d/Earthsea/ships/ansalon_line/west_pier2", "west");  
}      