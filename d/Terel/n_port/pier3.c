/* Used by circle Line - Tapakah, 05/2009 */

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR + "last_room";
inherit "/d/Genesis/gsl_ships/lib/pier";

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Northern port pier");
    set_long("This is a small wooden pier, with a thin film of ice " +
	     "making it a little slick in places. The ship arriving from Sarn Ford " +
	     "and departing to Sparkle docks here.\n");
    
    add_item(({"pier", "northern port", "this pier"}),
	"It's made of wooden boards and poles. It looks very " +
	"robust so it will withstand even the worst of storms.\n");
    
    add_item(({"bay"}), "Out on the bay some fishing boats have anchored.\n");
    
    add_item(({"sea", "water"}),
	     "The sea looks cold and blue. It covers the whole " +
	     "eastern horizon. Gazing east you see no trace of " +
	     "land - only a few sailing ships that are struggling in " +
	     "the brisk and icy wind, as well as a few icebergs.\n");

    add_prop(ROOM_S_MAP_FILE, "town_last.txt");
	add_exit("/d/Terel/last/lroad10a",    "west", 0);

    add_pier_entry(MASTER_OB(TO), "Last", "Newbie Line A");
    initialize_pier();
}


	  
