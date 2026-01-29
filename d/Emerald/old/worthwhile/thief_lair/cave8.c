/* A portion of the caves which make up the bandits lair in the Blackwall
   Mountains.
   Code (c) 1999 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

inherit "/d/Emerald/thief_lair/base_cave.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Emerald/defs.h"

/* VBFC for the long description of the room. Basically, if there are bandits
   in cave9, you will hear them from here.
*/

string
long_descrip()
{ 
    string descrip;
    object main_lair;
    object *bandits;   
    descrip = "Beside an underground stream. The stream flows from "+
	"north to south, with the tunnel appearing to widen into "+
	"larger cavern in both directions.";

    // Make sure the room is loaded.
    LOAD_ERR(THIEF_LAIR_DIR + "cave9");   
    main_lair = find_object(THIEF_LAIR_DIR + "cave9.c");
    bandits = filter(all_inventory(main_lair), &->query_bandit());
    
    if (!sizeof(bandits))
    {
	return (descrip + "\n");
    }

    return (descrip + " You think you can hear the sound of voices carrying "+
	    "through the tunnel from the north.\n"); 
}

void
create_banditcave_room()
{
    set_short("Beside an underground stream.");
    set_em_long("@@long_descrip@@");

    add_item(({"voices", "human voices", "sound", "sound of voices",
		   "sound of humans", "sound of human voices"}),
	     "You pause for a minute and listen carefully for the voices.\n"+
	     "\nIt sounds like there are a number of people, possibly a "+
	     "mixture of elves and humans to the north. "+
	     "They sound rather raucous, as if they were having a good "+
	     "time.\n");

    add_item(({"wall", "walls"}),
	     "The walls of this cavern are composed of black "+
	     "basalt. They are lined with moisture and frequently covered "+
	     "in growths of green moss.\n");

    add_item(({"floor", "ground"}),
	    "You are travelling at the edge of the stream which has "+
	    "carved out this tunnel. The ground is wet and mossy.\n");

    add_item(({"roof", "ceiling"}),
	     "The tunnel roof is a comfortable distance above you. "+
	     "Occasional drips of water fall from it though, every so "+
	     "often landing on you.\n");

    add_item(({"moss", "green moss"}),
	     "It is  a harmless seeming moss, dark-green in color. The "+
	     "sort which commonly carpets the ground in dark, wet "+
	     "places.\n");

    add_cmd_item(({"moss", "green moss"}), ({"eat"}),
             "You carefully pick some of the moss, then stick it "+
	     "cautiously in your mouth.\nYuck! It tastes terrible!\n");

    add_item(({"stream", "water"}),
	     "The tunnel has been carved out by a small, underground "+
	     "stream. The stream flows from north to south, travelling "+
	     "at a good speed. The water is reasonably clear and looks "+
	     "wholesome.\n");

    add_exit(THIEF_LAIR_DIR + "cave9", "north", 0, 1);
    add_exit(THIEF_LAIR_DIR + "cave7", "south", 0, 1);
} 

void
init()
{
    ::init();
    add_action(drink_from_stream, "drink");
}
