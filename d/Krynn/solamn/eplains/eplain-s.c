#include "local.h"

inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    int *from, *to = get_map_dirs("s");
    from = to - ({ 5,6,7,0 });
    from += get_map_dirs("Q");
    from += get_map_dirs("T");
    to -= ({ 1,2,3,4 });
    to += get_map_dirs("X");
    to += get_map_dirs("W");
    
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(OBJ_I_CONTAIN_WATER, -1);

    set_special_short("A stream on the plains of Solamnia");
    set_short("A stream on the plains of Solamnia");

    set_long("Before you is a small stream leading from "+
	(sizeof(from) == 1 ? Std_dir[from[0]] : "FFFFFF")+" to "+
	(sizeof(to) == 1 ? Std_dir[to[0]] : "TTTTTT")+
	" across the Plains of Solamnia. Bushes and " +
	"grass surround you and the plains continue in all directions.\n");

    add_item("bushes", "Hardy yet vibrant bushes are common throughout the plains of Solamnia.\n");
    add_item("grass", "A thick carpet of green grass grows out of the rich soil of the Solamnia plains.\n");
    add_item("stream", "This is a small stream, barely more than a trickle, bubbling " +
			"merrily along through the plains.\n");

    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );
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
