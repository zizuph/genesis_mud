/*
 * Oranea rocky beach file
 * 
 * Ckrik June 1998.
 * Typos and a bit of tweaking -- Amelia July 4, 1998
 * 
 * Some code taken from Finwe's beach.
 */

inherit "/d/Earthsea/std/room.c";
inherit "/d/Earthsea/herbs/specials/hs.c";

#define TIDE "/d/Earthsea/gont/beach/tides.c"

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/filter_funs.h"
#include "/d/Earthsea/sys/properties.h"
#include "/d/Earthsea/sys/terrain_types.h"
#include "/d/Earthsea/lib/room_tell.c"
#include "/d/Earthsea/herbs/herb_sets/beach_herbs.h"

int flag = random(4);

string
tide_dependent();

string
beach_desc();

void
create_beach();

void
create_earthsea_room()
{    
    set_short("A rocky beach");
    set_long(beach_desc());
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SALTBEACH);

    add_item((({"fishermen", "nets"})),
      "A short distance from shore, you see fishermen braving the "+
      "rocky coastline to cast their nets into the sea. You deduce "+
      "that the fishing must be good here.\n");
    add_item("waves", "Dark-blue waves vary in size with the "+
      "changes in tide.\n");
    add_item((({"rocky beach", "beach", "rocks", "gravel"})),
      "The beach is rocky and coarse. Gravel and rocks make " +
      "up the coastline. Rough gravel crunches beneath your feet "+
      "as your walk across it.\n");
    add_item(({"shore","shores","shoreline","coastline","coast"}),
      "The shores of the beach are scattered with bits of " +
      "shells, seaweed, and an occasional piece of driftwood.\n");
    add_item("driftwood", "Pieces of driftwood washed up "+
      "from the sea lie scattered on the beach.\n");
    add_item("boulders", "Large granite boulders fallen from "+
      "higher elevations line the edge of the beach.\n");
    add_item(({"shells", "shell"}), 
      "Shells are scattered here and there across the beach.\n");
    add_item("seaweed", 
      "There are few stray pieces of seaweed washed up on " +
      "the shore.\n");
    add_item((({"mist", "blue mist"})),
      "A light blue haze covers the entire island.\n");
    add_item((({"urchins", "sea urchins", "remains"})),
      "Here and there you see the purple remains of small sea "+
      "urchins that have washed up on the rocks.\n");
    add_item(({"driftwood","wood"}), 
      "A few pieces of driftwood dot the coastline here and " +
      "there.\n");
    add_item("hills", 
      "The hills of the island rise up in solitary defiance of " +
      "the sea. Here and there stray wisps of smoke rise from " +
      "chimneys betraying the existence of a small village "+
      "further inland.\n");
    add_item(({"tide","tides"}),
      "The eternal tides rise and fall at the whim of the " +
      "relentless sea. Why don't you check it?\n");

    add_item(({"tidepool", "tidepools"}),
      "@@show_tide_pool@@");

    set_tell_time(50);
    add_tell("@@tide_tell@@");
    create_beach();
    change_prop(OBJ_S_SEARCH_FUN, "herb_search_tide");
    add_prop(OBJ_I_SEARCH_TIME, 2);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);

    set_up_herbs(this_object()->select_herb_files(BEACH_HERBS), 
      BEACH_LOCATIONS, 3);
}

create_beach()
{}

string
herb_search_tide(object player, string str)
{

    player->catch_msg("you are searching.\n");
    if (TIDE->query_tide_level() > 1)
    {
	player->catch_msg("You don't see any tidepools around here.\n");
	return "";
    }
    //else
    //return herb_search(player, str);
}

string
show_tide_pool()
{
    if (TIDE->query_tide_level() > 1)
    {
	return "Hmm...do you see any tidepools here? " +
	"The tide has covered them up.\n";
    }
    else
    {
	return "You see various strange and beautiful creatures and " +
	"many different kinds of sea vegetation in the " +
	"pool.\n";
    }
}

int
check_tide(string str)
{
    notify_fail("Check what? The tide?\n");
    if(str == "tide" || str == "the tide" || str == "tides" ||
      str == "the tides")
    {
	this_player()->catch_msg("You estimate that it is " +
	  TIDE->query_tide_string() + " right now.\n");
	return 1;
    }
}

void
init()    
{
    ::init();
    add_action("air","smell");
    add_action(&check_tide(), "check");
}

int
air(string s)
{
    notify_fail("Smell what? The air?\n");
    if(!strlen(s) || !parse_command(s,this_object(),"[the] [sea] 'air'"))
	return 0;
    else
    { 
	this_player()->catch_msg("You breathe the fresh, salty sea "+
	  "air deep in your lungs, tasting it on your"+
	  " lips.\n");
	set_alarm(1.0, 0.0, &write("Mmmm.....\n"));
	set_alarm(2.0, 0.0, &say(QCTNAME(this_player())+ " takes a "+
	    "deep breath, smiling happily.\n"));
	set_alarm(3.0, 0.0, &write("There is no place like"+
	    " the sweet lands of the Archipelago.\n"));
	return 1;
    }
}

string
tide_tell()
{
    if(TIDE->query_tide_level() >= 3)
    {
	return "The ocean water swells and a giant wave comes " +
	"crashing from the sea. It smashes into the " +
	"beach bringing the cold salt water surging " + 
	"to your feet.\n";
    }
    else if(TIDE->query_tide_level() <= 1)
    {
	return "The calmer water of the lower tide brings the " +
	"small beach crustaceans out of their homes.\n";
    }
    else
    {
	return "A wave crashes in and washes up some seaweed " +
	"and shells.\n";
    }
}  



tide_dependent()
{
    switch(TIDE->query_tide_level())
    {
    case 0:
	return "Tidepools are scattered where the water " +
	"meets the coastline. Animals scurry " +
	"about as they try to hide under the rocks. ";
	break;
    case 1:
	return "You can see things moving under the " +
	"rocks and even an occasional tidepool " +
	"as small waves wet rocks bordering " +
	"the sea. ";
	break;
    case 2:
	return "The tidepools are completely covered " +
	"by the water. Waves crash into the rocks " +
	"bringing seaweed and kelp that further entangles " +
	"them with debris. ";
	break;
    case 3:
	return "Large waves strike the rocky beach, driving " +
	"salty water through slim gaps between the " +
	"large standing boulders, creating a salty sea " +
	"mist that smells refreshing to the soul. ";
	break;
    case 4:
	return "Enormous swells driven by the tide send " +
	"gigantic waves ramming into the beach. You are " +
	"sprayed by the cool water of the fierce crashing " +
	"waves. You marvel at the sight of the power of " +
	"relentless sea. Nothing can match its beauty and " +
	"prowess. ";
	break;
    }
}

beach_desc()
{
    switch (random(4))
    {
    case 0:
	return "The terrain of the beach is very rough. " +
	"Pebbles and large rocks cover the coastline " +
	"here. Jagged and rough to the touch, the rocks " +
	"stand guard against the assault of the sea. " +
	"Bits and pieces of shells, seaweed, and " +
	"remains of purple sea urchins lay scattered " +
	"among the rocks. " +
	"@@tide_dependent@@";
	break;
    case 1:
	return "You stand on a rocky beach. The gravel " +
	"crunches under your feet as you walk across it. " +
	"Bits of broken " +
	"shells, driftwood, seaweed, and kelp are scattered " +
	"across the beach. The salty air blows past you as " +
	"while the tide laps at your feet in a rhythmic " +
	"motion. " + "@@tide_dependent@@";
	break;
    case 2:
	return "A strong gale blows off the ocean here. This " +
	"part of the rocky beach is somewhat clean from the tide's " +
	"action. Boulders are at the edge of the beach where " +
	"they have fallen from the hills above. Nevertheless, " +
	"you see still see bits of shells, seaweed, and " +
	"driftwood here. " +
	"@@tide_dependent@@";
	break;
    default:
	return "Gravel and rocks "+
	"cover the beach here. A weak chilling sea wind blows " +
	"off the ocean. It smells salty while it nips at " +
	"your nose. Sea birds fly overhead as they swoop out " +
	"over the water as they look for a catch. " +
	"Small crustaceans move about the " +
	"rocks as the scramble for safety. " + "@@tide_dependent@@";
	break;
    }
}
