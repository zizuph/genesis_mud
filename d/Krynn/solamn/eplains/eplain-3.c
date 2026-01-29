#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("A track across the plains");
    set_short("A track across the plains");

    switch(random(4, (Xx+1)*(Yy+1)))
    {
    case 1:
    	set_long("This is a track across the plains. Greenery extends in all " +
			    "directions around you except directly on the track.\n");
	break;
    case 2:
    	set_long("You are on a dirty track on the plains. Green bushes and " +
			      "trees extend in all directions, the ground is covered with grass.\n");
    case 3:
    	set_long("Greenery extends in all directions around you except directly on the track.\n");
	break;
    default:
    	set_long("You are on a dirty track on the plains. Green bushes and " +
		"trees extend in all directions, the ground is covered with grass.\n");
    }

    add_item(({"track","road"}),"It's a dirty track, about one metre wide, enveloped by green vegetation all " +
			    "around.\n");
    add_item(({ "grass","bushes","trees","bush","tree","greenery"}),"The vegetation is fully developed, and " +
			    "the only thing disturbing the rich greenery is the track here.\n");

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
    return 1;
}
