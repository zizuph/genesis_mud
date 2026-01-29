#include "local.h"
#include "describe.h"
inherit TDIR+"plain_base";

public void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("In a valley");

    set_short("In a valley");

    switch(random(2, (Xx+1)*(Yy+1)))
    {
    case 1:
	set_long("Hills are on both sides of you, enclosing the cozy valley " +
		"you are in. A few bushes and trees are around and it is easily " +
		"possible to continue along the valley.\n");
	break;
    default:
	set_long("You are in a small valley enclosed by hills on two sides. " +
			"It is easily possible to walk along the valley.\n");
    }

    add_item(BUSH_TREE);
    add_item(GRASS);
    add_item(VEGETATION);
    add_item(HILLS);

    add_std_exits();
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
