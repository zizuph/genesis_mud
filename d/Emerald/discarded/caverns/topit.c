/*
 * TOPIT.c
 * This is the inside of the bottom of the pit in the center of the
 * island. Leads up to the island in island_pit.c
 *  -  Alaron September 13, 1996
 */

#include "defs.h"
#include <stdproperties.h>

inherit "/std/room.c";

void
create_room()
{
    set_short("Bottom of pit");
    set_long("   You stand at the base of a dark pit walled by rocks and "+
	     "black mud. As it winds its way up into the faint glow which "+
	     "represents the sun above, you notice water dripping from "+
	     "the cracks between each of the dark rocks and occasional "+
	     "pieces of mud slipping out of the wall and onto the ground. "+
	     "The dark, gloomy pit opens up onto an equally intimidating "+
	     "cave heading southeast.\n\n");

    add_item( ({"wall", "walls", "mud", "black mud", "rocks", "dark rocks"}),
	     "The dark rocks which line the entire wall of the dark pit "+
	     "are dripping with salty moisture as they jut out of the "+
	     "black mud base of the wall behind them.\n");

    add_item(({"pit","bottom","bottom of pit"}),
	     "This is a pit walled by rocks. The cave which opens up "+
	     "to the southeast doesn't appear all that natural. In fact, "+
	     "it looks as though the rocks surrounding the cave opening "+
	     "were moved from that spot, as if the cave had been "+
	     "opened by digging.\n");

   add_item(({"cave","cave opening","opening", "southeast"}),
	    "The cave which opens up to the southeast is dark and "+
	    "gloomy. You can hear the sound of dripping water echoing "+
	    "through the tunnel, but can see nothing more than "+
	    "pitch blackness.\n");

    
    add_exit(THIS_DIR + "main12", "southeast");
/*
    add_exit(ISLAND_DIR+"island_pit", "up");
*/
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);
    if(!living(ob))
	return;
    if(file_name(from) != CAVERNS_DIR+"main12")
	return;

    ob->catch_msg("Your eyes adjust to the light streaming into "+
		  "the pit from above.\n");
    return;
}
