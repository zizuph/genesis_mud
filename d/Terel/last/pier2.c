/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

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
	     "making it a little slick in places. The ship from Kalad " +
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

    add_exit(LAST_DIR +"lroad10","west",0);
}
