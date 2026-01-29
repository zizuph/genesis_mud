/*
 * BASEROAD.c
 * Base File for the road which follows the base of both mt.black
 * and the volcano
 */

#include "default.h"

inherit "/std/room";

void create_road();

void
create_road()
{
}

void
create_room()
{
    set_short("Hard, rocky road at the base of the mountains");
    
    add_prop(ROOM_I_INSIDE, 0);

    add_item( ({"up", "sky", "clouds"}),
	     "Peering up into the sky you notice the clouds overhead. Judging "+
	     "from the amount of clouds you can see overhead, it becomes "+
	     "clear to you how this place can have so much moisture and "+
	     "rainfall.\n");

    add_item( ({"mountain", "mountains", "mtblack","mount black", 
		"black mountain"}),
	     "The mountains towering over the east side of the road "+
	     "are staggering. Your gaze starts at the road and follows "+
	     "the mountainside up, and up until your neck is completely "+
	     "craned back and you are squinting to see the peaks. The "+
	     "huge, black mountain is jagged and rough, its peak tall and "+
	     "narrow. It looks like it would be a feat of unbelievable "+
	     "measure to scale the side of that mountain. Resting just "+
	     "behind the black mountain is another mountain of wider and "+
	     "shorter stature. A constant plume of dark smoke drifting up "+
	     "from the flat peak of the mountain indicates it is a "+
	     "volcano.\n");

    add_item( ({"volcano", "plume", "smoke", "black smoke"}),
	     "A dark plume of smoke is constantly drifting up and out "+
	     "of the towering volcano. Most of the view of the volcano "+
	     "itself is obscured by the black mountain. However, some of "+
	     "it appears accessible from the road. The side of the volcano "+
	     "is dull and gray, with small patches of low, green shrubbery "+
	     "returning to life after the last eruption of the monstrous "+
	     "rock formation.\n");

    add_item( ({"shrubbery", "green shrubbery", "low green shrubbery",
		"low shrubbery"}),
	     "The low, green shrubbery on the side of the volcano looks to "+
	     "be vegetation and plant life returning to the surface after "+
	     "the devastation of the previous eruption. Judging from the dull "+
	     "gray color of the side of the volcano, it looks like the "+
	     "eruption must not have been that long ago.\n");

    add_item( ({"down", "ground", "road", "rocks", "stones", "pebbles",
		"rocky road"}),
	     "This close to the base of the mountains, there is very little, "+
	     "if any, room for vegetation or bushes of any kind. As such, "+
	     "the road appears barren, its dark gray, rocky surface only "+
	     "augmenting the barren look.\n");


    create_road();   // call the 'local' or 'inheriting' room's function.
}

