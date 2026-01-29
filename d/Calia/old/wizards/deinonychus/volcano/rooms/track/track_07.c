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

    set_long(DESC("track_long") + DESC("west") + "\n" +
        BS("Going north you'll come to the top of the volcano. " + 
        "Going south you'll come to the bottom of the volcano.\n"));
   
#include "track.itm"
#include "west.itm"

    add_exit(ROOM("track_08"), "north", 0);
    add_exit(ROOM("track_06"), "south", 0);
}
