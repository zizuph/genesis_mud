#include "local.h"
#include "describe.h"
inherit TDIR+"plain_base";

public void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("In the woods");
    set_short("In the woods");

    switch(random(2, (Xx+1)*(Yy+1)))
    {
    case 1:
	set_long("Tall trees rise up about you and " +
			"dense underbrush encloses you on all sides. It is " +
			"possible to travel in all major directions, but it " +
			"is tedious.\n");
	break;
    default:
	set_long("You are standing in a forest, with trees blocking out " +
			"most of the sky above you. Shrubbery is all around " +
			"you making travel, which is possible in all main " +
			"directions, much harder.\n");
    }

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 4;
}
