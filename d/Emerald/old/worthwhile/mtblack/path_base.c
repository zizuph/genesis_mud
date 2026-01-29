inherit "/std/room";

void
create_path()
{
}

nomask void
create_room()
{
    set_short("Steep mountain path");
    set_long("   This steep path snakes up the rocky face of the " +
        "mountain, disappearing among the crags high above.\n");

    add_item( ({"up", "sky", "clouds"}),
        "Peering up into the sky you notice the clouds overhead. Judging "+
        "from the amount of clouds you can see overhead, it becomes "+
        "clear to you how this place can have so much moisture and "+
        "rainfall.\n");

    add_item( ({"mountain", "mountains", "mtblack","mount black", 
                "black mountain"}),
    	"The mountains towering before you " +
    	"are staggering. Your gaze starts at the road below and follows "+
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
    	"it appears accessible from the road below. The side of the volcano "+
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
                "rocky road", "path", "steep path" }),
        "Here at the base of the mountains, there is very little, "+
        "if any, room for vegetation or bushes of any kind. The path " +
        "stretches down from the peaks above, winding among boulders " +
        "and crags down to the rocky road below.\n");

    create_path();
}
