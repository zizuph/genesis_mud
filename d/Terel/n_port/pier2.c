
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
    set_short("Northern port pier - boat to Enchanted Garden");
    set_long("This is a small wooden pier, with a thin film of ice " +
	     "making it a little slick in places.  The ship from Kalad " +
	     "docks here.\n");
    
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
	add_exit(LAST_DIR +"lroad10","west",0);
    create_last_room();
    add_pier_entry(MASTER_OB(TO), "Last", "Cabotage to Enchanted Garden");
    initialize_pier();
}
