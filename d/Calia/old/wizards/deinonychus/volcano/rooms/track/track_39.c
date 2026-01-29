/*  part of the track leading up to the volcano in the land of the dinosaurs
 
    coder(s):	Deinonychus
 
    history:	DD.MM.YY	what done			who did
		27.02.93	created				Deinonychus
 
    purpose:	none
    exits:	none
 
    objects:	none
    npcs:	none
 
    quests:	none
    special:	none
 
    to do:	none
    bug:	none known
*/
 
 
inherit "/std/room";
#include "track.h"
#include <stdproperties.h>
#include <macros.h>

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void create_room()
{
    set_short("Volcano track");

    set_long(DESC("track_long") + DESC("north-west") + "\n" +
        BS("Going east you'll come to the top of the volcano. " + 
        "Going south you'll come to the bottom of the volcano.\n"));
   
#include "track.itm"
#include "north.itm"
#include "west.itm"

    add_exit(ROOM("track_40"), "east", 0);
    add_exit(ROOM("track_38"), "south", 0);
}
