#include "local.h"
#include "describe.h"
inherit TDIR+"plain_base";

public void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("On the shore");
    set_short("On the shore");

    set_long("You are standing far above the water. There is a " +
	"cliff easily 100 feet high reaching down into the water from here.\n");

    add_item(({"cliff","shore","water"}),
	"The shore is far down at the bottom of the cliff, " +
	"and you don't see any chance to reach the water from here.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "shore", }) );
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 3;
}
