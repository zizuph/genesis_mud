#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("A road across the plains");
    set_short("A road across the plains");

    switch(random(4, (Xx+1)*(Yy+1)))
    {
    case 1:
    	set_long("The plains stretch out in all directions from here.\n",);
	break;
    case 2:
    	set_long("The plains are covered with green bushes and trees, "+
		"making it difficult for you to look very far.\n");
    case 3:
	set_long("This is a road across the plains. The plains, covered " +
		"with bushes and an occasional tree stretch out in all directions from here.\n");
	break;
    default:
	set_long("The plains stretch out in all directions from here. The plains " +
		"are covered with green bushes and trees, making it difficult for you to look very far " +
		"in the distance.\n");
    }

    switch(random(2, (Xx+1)*(Yy+1)))
    {
    case 1:
	add_item("road","The road is approximately two metres in width, wide enough so that a cart can " +
			    "easily travel along it. It looks like it was once well travelled, "+
			    "but is now in disrepair and is rather overgrown.\n");
	break;
    default:
	add_item("road","This road is laid out with gravel and it is very dusty and dirty. " +
			      "It is about two metres wide.\n");
    }
    add_item(({"grass","bushes","trees","bush","tree","greenery"}),"The vegetation is fully developed, and " +
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
