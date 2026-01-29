#include "local.h"
#include "describe.h"
inherit TDIR+"plain_base";

public void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("Burnt Plains");

    set_short("Burnt Plains");

    set_long("You are standing among ashes. The plains have been burnt here and " +
	"there is nothing left except black soot.\n");

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
    return 2;
}
