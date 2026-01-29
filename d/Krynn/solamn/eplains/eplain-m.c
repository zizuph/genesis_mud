#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("Foot of the mountains");
    set_short("Foot of the mountains");

    switch(random(2, (Xx+1)*(Yy+1)))
    {
    case 1:
	set_long("You are standing at the reaches of the Dargaard Mountains " +
		"which rise up high to your east. It is impossible to travel the rugged cliffs and " +
		"step slopes of these mountains. To you north and west, the Plains of Solamnia " +
		"stretch out as far as you can see, the higher elevation at the foot of the mountains " +
		"allow a view across the landscape.\n");
	break;
    default:
	set_long("These are the foothills of the Dargaard Mountains which rise up high to your east. " +
		"The Plains of Solamnia stretch out to your north and west, while the impassable cliffs " +
		"and steep slopes of the mountains block your way east.\n");
    }

    add_item(({"plains","landscape"}),"You can see several hundreds of metres, but the view is all the " +
		"same. Greenery, trees, bushes mark the area.\n");
    add_item(({"bushes","bush","tree","trees","greenery"}),"You cannot see anything special about it.\n");
    add_item(({"mountains","dargaard mountains","foothills","cliffs","slopes"}),"The Dargaard Mountains " +
		"loom above you, dark and sinister. A scent of evil hangs in the air.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "mountains", "hills", }) );
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
