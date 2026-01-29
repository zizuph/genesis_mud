#pragma strict_types
 
#include "/d/Gondor/defs.h"
#include "../mirk_defs.h"
inherit  "/d/Gondor/common/mirkwood/forest/mirkwood";
#include <stdproperties.h>

int *D_G, *D_p;

public void
create_map_room()
{
    D_G = get_map_dirs("G");
    D_p = get_map_dirs("p") - ({1,3,5,7});

    set_short("Tiny path in Mirkwood forest");
    set_long("@@my_long@@");

    add_item(({ "tree", "trees" }), "These hideous, twisted ancient trees "+
	     "have cobwebs draped over it.\n");
    add_item(({"webs", "web", "cobweb", "cobwebs" }), "All you can see is "+
	     "that they look like enormous spider webs.\n");

    if(sizeof(D_G))
    {
        add_item(({ "dol guldur", "gates", "hill" }), "The great gates "+
                 "leading into the feared Dol Guldur are closed.\n");
        add_cmd_item("gates", "open", 
                     "Strong magic does not let you even aproach the gate.\n");
    }

    add_prop(ROOM_I_LIGHT, 0);
    add_prop("_room_i_no_me_sun", 1);
    add_rel_exits();
}

public int
query_map_fatigue()
{
    return 3;
}

public string
my_long()
{
    string text, time = time_of_day();
    string dir_G = desc_map_dirs(D_G);
    string dir_p = desc_map_dirs(D_p);

    text = "You are lost somewhere in the Mirkwood forest. ";
    switch (time)
    {
        case "early morning":
        case "night":
        case "evening":
            text = text + "It is " + time +
                   " now and you can hardly see your hands. " +
                   "Menacing gloomy trees, with black leaves, " +
                   "loom everywhere around you. You can hear grunts, " +
                   "scufflings, and moans in the undergrowth. " +
                   "You also see many eyes around you in forest. Some " +
                   "of them look like eyes of insects, but they are bigger.";
            break;
        case "morning":
        case "noon":
        case "afternoon":
            text = text + "Menacing gloomy trees, with black leaves, " +
                   "loom everywhere around you. You guess it is " + time +
                   "now, although you can't see the sky "+
                   "because of the the trees. You can hear grunts, " +
                   "scufflings, and moans in the undergrowth. " +
                   "The nastiest things you see are cobwebs: dark " +
                   "and dense with extraordinarily thick threads, " +
                   "often stretched from tree to tree, or tangled " +
                   "in the lower branches. The air here is quite hot " +
                   "and stuffy.";
            break;
    }
    text += " The tiny path you stand on continues " + dir_p +
            " and may hopefully lead you out of this forest.";
    if(dir_G != "")
        text += " There are great gates leading into the Dol Guldur are " +
                dir_G + " from here.";
    return text + "\n";
}

