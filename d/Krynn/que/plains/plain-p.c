#include "local.h"
#include "describe.h"
inherit TDIR+"plain_base";

public void
create_plains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short(PL1_S);

    set_short(PL1_S);

    switch(random(2, (Xx+1)*(Yy+1)))
    {
    case 1:
	set_long(PL1_L+"\n");
	break;
    default:
	set_long(PL2_L+"\n");
    }

    add_item(BUSH_TREE);
    add_item(GRASS);
    add_item("plains", "They are spreading out everywhere around you.");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "plains", }) );
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
