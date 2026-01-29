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

static int boomerang_taken; /* variable to test if someone's taken the 
                               boomerang out of the bush */

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void create_room()
{
    set_short("Volcano track");

    set_long(DESC("track_long") + DESC("south-west") + "\n" +
	"There's a silver bush growing along the track.\n" +
	BS("Going west you'll walk up to the top of the volcano. " + 
	"Going east you'll walk down to the bottom of the volcano.\n"));
   
#include "track.itm"
#include "south.itm"
#include "west.itm"
    add_item("bush","@@bush_description");

    add_prop(OBJ_S_SEARCH_FUN, "search");

    add_exit(ROOM("track_06"), "north", 0);
    add_exit(ROOM("track_04"), "east", 0);
   
    call_out("reset_room",1);
}

/*****************************************************************************/

/*
 * Function name: bush_description
 * Description:   description of bush depending if the boomerang's in the bush.
                  If the boomerang's still there it is cloned.
 * Arguments:     none
 * Returns:       the description
 */

string
bush_description()
{
    string description;

    seteuid(getuid(TO)); /* uid = 0 in VBFC's and we want to clone. */
    
    if (boomerang_taken)
        description = BS("You've never seen a bush like that. With its silver "
            + "leaves it just looks wonderful. But someone must have been "
            + "here before you because there's a broken branch.\n");
    else {
        description = BS("You've never seen a bush like that. With its silver "
            + "leaves it just looks wonderful.\n"); 
    }
    return description;
}

/*****************************************************************************/

/*
 * Function name: search
 * Description:   search the bush
 * Arguments:    what to search
 * Returns:       the description
 */

string
search(object player, string what)
{
    if((what == "bush") && !boomerang_taken)
    {
        setuid();
	seteuid(getuid(TO));
	clone_object(OBJECTS + "boomerang")->move(player);
	boomerang_taken = 1;
	return("Wow, you find a boomerang.\n");
    }
    else
	return 0;
}

/*****************************************************************************/

void
reset_room()
{
    boomerang_taken = 0;
}

