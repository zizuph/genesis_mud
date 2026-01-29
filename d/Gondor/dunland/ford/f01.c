/*
 *	/d/Gondor/dunland/ford/f01.c
 *
 *	Original version by Zephram.
 *	
 *      Modification log:
 *	20-Nov-1996, Olorin:	Changed inheritance.
 *	28-Jan-1997, Mercade:	Fix for changed roads.c.
 *	5-Aug-98, Gnadnar: 	Make skills consistent so rooms
 *			   	aren't traps, general cleanup
 *      17-Mar-00, Stern :      added OBJ_I_CONTAIN_WATER property
 *                              and drinking ability.
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "ford.h"


// Prototypes:
public void	create_roads();
public void	reset_room();

// Global variables:
static object	Guard1,
		Guard2;


/*
 * Function name:	create_roads
 * Description	:	set up the room
 */
public void
create_roads() 
{
    set_street("gentle slope");
    set_where("northwest");
    set_county("Westfold");
    set_land("Rohan");
    set_mountain("Misty Mountains");
    set_vegetation("long green grass");
    set_extraline("To the northwest flows a swift shallow wide "
        + "rocky river. To the southeast, " + Vegetation
	+ " covers the land of " + County + ". An old "
        + "stone paved road leads towards the river from the "
        + "east, passing close by a stone obelisk.");

    add_exit((DUN_DIR + "ford/f02"), "northwest",
	&swim(HARD_TO_SWIM, HARD_TO_SWIM), HARD_TO_SWIM);
    add_exit((ROH_DIR + "road/wr7"), "east", 0, 5);

    add_item(({"ford", "fords", "fords of isen",}),  BSN(
        "The river Isen or Angren runs swiftly over wide shallows here, "
      + "permitting travellers with a minimum of skill to swim across "
      + "the river here."));
    add_item( ({"river", "stream", "isen", "adorn", }), BSN(
        "The river Isen or Angren is running southwards out of a valley "
      + "between the hills to the north. Here, at the fords where the "
      + "road crosses the river, is a bend, and the river continues "
      + "westwards. In the middle of the stream is a rocky eyot."));
    add_item("water",
        "The water is cool and clear, shallow but flowing swiftly.\n");
    add_item(({"stone","marker","obelisk"}),
        "The marker says, 'Here is established the border of the "
      + "Realm of Rohan.\n" 
      + "By order of Cirion, Lord Steward of Gondor, and King Eorl of "
      + "Rohan.'\n");
    add_item(({"bank", "slope", }), BSN(
	"The road is coming down a gentle slope to the southeast, "
      + "which continues down to the river."));
    add_item(({"island","eyot"}), BSN(
        "In the middle of the stream, there is a small rocky island "
      + "or eyot. The road crosses the river running over this island."));
    add_item( ({"hills", "mountains", "valley", }), BSN(
        "The green gentle hills north of the road are the southern "
      + "foothills of the Hithaeglir, the Misty Mountains. Between "
      + "these southern outliers of that large mountain range lies "
      + "the valley of the Isen, which is also called Nan Curunir."));
    add_item( ({ "road", "street", }),  BSN(
        "The road crosses the river Isen at the ford here, leaving Rohan "
      + "and continuing through Dunland on the other bank of the river."));
    add_prop(OBJ_I_CONTAIN_WATER,-1);
    set_drink_from("river");
    reset_room();
} /* create_roads */


/* 
 * Function name:	reset_room
 * Description	:	clone up guards
 */
public void
reset_room()
{
    Guard1 = clone_npc(Guard1, (ROH_DIR + "npc/borderguard"));
    Guard2 = clone_npc(Guard2, (ROH_DIR + "npc/borderguard"));
    Guard1->team_join(Guard2);
} /* reset_room */

public void
init()
{
    ::init();
    init_drink();
}
