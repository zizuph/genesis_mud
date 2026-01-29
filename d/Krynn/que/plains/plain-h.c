#include "local.h"
#include "describe.h"
inherit TDIR+"plain_base";

public void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("In the hills");

    set_short("In the hills");

    set_long("You are surrounded by hills. Trees and bushes cover " +
	"everything, so you are unable to see far. The ground " +
	"is covered with shrubs and grass and the occasional " +
	"animal runs about.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "hills", }) );
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
