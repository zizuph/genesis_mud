#include "/d/Rhovanion/defs.h"
inherit MIRK_DIR+"mirkwood";
#include <stdproperties.h>

static string Dirs_river;
static string Dirs_celduin;

void
create_map_room()
{
    add_std_exits();

    Dirs_river = desc_map_dirs(get_map_dirs("f"));
    Dirs_celduin = desc_map_dirs(get_map_dirs("c"));

    set_short("Men-i-Naugrim");
    set_long("@@my_long@@");

    add_item(({ "tree", "trees" }), "These hideous, twisted ancient trees "+
	     "have cobwebs draped over it.\n");
    add_item(({"webs", "web", "cobweb", "cobwebs" }), "All you can see is "+
	     "that they look like enormous spider webs.\n");

    if (Dirs_celduin != "")
        add_item(({ "bridge", "celduin", "celduin river", "running river" }),
                 "This wide road is blocked by Celduin river. In the past "+
                 "there was a big bridge leading over the river and the "+
                 "road continued further east but now there are only few "+
                 "rotten ruins left from the bridge.\n");
    if (Dirs_river != "")
        add_item("river", "Small river is running along the road towards "+
                 "the east edge of the forest.\n");

    add_prop(ROOM_I_LIGHT, 0);
    add_prop("_room_i_no_me_sun", 1);
}

public int
query_map_fatigue()
{
    return 2;
}

public string
my_long()
{
    string text, time = time_of_day();

    text = "You are on a wide ancient road that goes straight "+
           "in east-west direction. Rumours tell about the "+
           "firstborn elves using it on their way to the land of "+
           "Bliss. During Durin's realm in Khazad-dum it was well "+
           "maintained and since then it is called Men-i-Naugrim. "+
           "But now only fools use is on their way to the death.";

    switch (time)
    {
	case "morning":
	case "noon":
	case "afternoon":
	    text += " Although it is "+time+" now, it is very dark here. "+
		    "You can hear grunts, scufflings and moans in the "+
		    "undergrowth. The nastiest things you see are cobwebs: "+
		    "dark and dense with extraordinarily thick threads, "+
		    "often stretched from tree to tree, or tangled in the "+
		    "lower branches.";
	    break;
	case "early morning":
	case "night":
	case "evening":
	    text += " The grunts, scufflings and moans in the undergrowth "+
		    "seem to be very close now. You can also see many eyes "+
		    "around you in the forest. It seems that animals living "+
		    "here are less afraid now in the "+time+". Among them "+
		    "are also big insectlike eyes. They seem to be watching "+
		    "you and following your movement along the path. But "+
		    "still the nastiest things you see are cobwebs: "+
		    "dark and dense with extraordinarily thick threads, "+
		    "often stretched from tree to tree, or tangled in the "+
		    "lower branches.";
	    break;
    }
    if (Dirs_river != "")
	text += " Way north is blocked by a small river running "+
                "towards the east edge of the Mirkwood forest.";
    if (Dirs_celduin != "")
        text += " Here the road ends blocked by the Celduin river and only "+
                "rotted remains of some bridge show that it was possible "+
                "to go further east long time ago.";
    return text + "\n";
}

