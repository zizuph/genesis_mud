#pragma strict_types
 
#include "/d/Gondor/defs.h"
#include "../mirk_defs.h"
inherit  "/d/Gondor/common/mirkwood/forest/mirkwood";
#include <ss_types.h>
#include <stdproperties.h>

#define GON_HERB     "/d/Gondor/common/herbs/"
//#define ROK_HERB   "/d/Roke/common/herbs/"
#define SPIDER       "../npc/spider"

int *D_c, *D_f, *D_R, *D_r, *D_m, *D_G;

public void
reset_room()
{
    ::reset_room(); /* defined in Gondor herb file */
    if(!random(10))
    {
        clone_object(SPIDER)->move(this_object());
        if(!random(5))
            clone_object(SPIDER)->move(this_object());
    }
}

public void
create_map_room()
{
    string *herbs = ({ GON_HERB+"angurth",
                       GON_HERB+"bpotato",
                       GON_HERB+"chervil",
                       GON_HERB+"curugwath",
                       GON_HERB+"fennel",
                       GON_HERB+"foxglove",
                       GON_HERB+"garlic",
                       GON_HERB+"handasse",
                       GON_HERB+"hemlock",
                       GON_HERB+"mint",
                       GON_HERB+"morgurth",
                       GON_HERB+"myrtle",
                       GON_HERB+"oregano",
                       GON_HERB+"saffron",
                       GON_HERB+"sumac",
                       GON_HERB+"suranie",
                       GON_HERB+"ungolestel",
/*                       ROK_HERB+"aconite",
                       ROK_HERB+"dragonroot",
                       ROK_HERB+"hajir",

                       ROK_HERB+"humbleleaf",

                      ROK_HERB+"nightshade",
                       ROK_HERB+"nightshade",
                       ROK_HERB+"rutgeldam",
                       ROK_HERB+"sparkweed",
                       ROK_HERB+"wolvesbane",
*/                     });
    int s;

    D_c = get_map_dirs("c");
    D_f = get_map_dirs("f");
    D_R = get_map_dirs("R");
    D_r = get_map_dirs("r");
    D_m = get_map_dirs("m");
    D_G = get_map_dirs("G");

    set_short("Deep in the Mirkwood forest..");
    set_long("@@my_long@@");

    add_item(({ "tree", "trees" }), "These hideous, twisted ancient trees "+
	     "have cobwebs draped over it.\n");
    add_item(({"webs", "web", "cobweb", "cobwebs" }), "All you can see is "+
	     "that they look like enormous spider webs.\n");

    if(sizeof(D_c) && !sizeof(D_f))
        add_item(({"river", "celduin river", "running river"}),
                 "You recognize the swift cold waters of Celduin river, "+
                 "also known as Running river.\n");
    if(sizeof(D_f) && !sizeof(D_c))
        add_item("river", "This river flows from the mountains of "+
                 "Mirkwood until it meets Celduin river on the edge "+
                 "of the forest.\n");
    if(sizeof(D_f) && sizeof(D_c))
    {
        add_item(({"river", "smaller river"}),
                 "This river flows from the mountains of "+
                 "Mirkwood and here it meets waters of Celduin river.\n");
        add_item(({"rivers", "celduin river", "running river"}),
                 "The swift cold waters of Celduin river here swallow "+
                 "smaller river comming from the mountains of Mirkwood.\n");
    }

    if(sizeof(D_G))
        add_item(({"hill", "dark hill", "dol guldur"}),
                 "This dark hill is indeed the feared place known "+
                 "as Dol Guldur.\n");

    if(sizeof(D_m))
        add_item("mountains", "These mountains look even more dark and "+
                 "dangerous than the forest that surrounds them.\n");

    if(sizeof(D_R) && !sizeof(D_r))
        add_item(({"river", "enchanted river",}),
                 "You can sense some evil magic emiting from these slow "+
                 "dark waters of Enchanted river.\n");
    if(sizeof(D_r) && !sizeof(D_R))
        add_item(({"river", "forest river"}),
                 "Cold and fast Forest river flows from the mountains far "+
                 "north through the Mirkwood towards the lake Esgaroth.\n");
    if(sizeof(D_R) && sizeof(D_r))
        add_item(({"river", "rivers", "forest river", "enchanted river"}),
                 "Slow dark waters of Enchanted rivers here mix with "+
                 "cold water of Forest river.\n");

    reset_room();

    add_prop(ROOM_I_LIGHT, 0);
    add_prop("_room_i_no_me_sun", 1);
    add_rel_exits();

    s = sizeof(herbs);
    set_up_herbs( ({ herbs[random(s,      Xx  + (2 * Yy) )], 
                     herbs[random(s, (2 * Xx) + (3 * Yy) )], 
                     herbs[random(s, (3 * Xx) +      Yy  )]
                }) );
    add_prop(OBJ_I_SEARCH_TIME, 6);
}

public int
is_lost()
{
    if(TP->query_skill(SS_LOC_SENSE) < random(70))
    {
        return 1;
    }
    return 0;
}

public int
query_map_fatigue()
{
    return 5;
}

public string
my_long()
{
    string text, time = time_of_day();
    string dir_r = desc_map_dirs(D_r),
           dir_R = desc_map_dirs(D_R),
           dir_f = desc_map_dirs(D_f),
           dir_c = desc_map_dirs(D_c),
           dir_G = desc_map_dirs(D_G),
           dir_m = desc_map_dirs(D_m);

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
                   " now, although you can't see the sky "+
                   "because of the the trees. You can hear grunts, " +
                   "scufflings, and moans in the undergrowth. " +
                   "The nastiest things you see are cobwebs: dark " +
                   "and dense with extraordinarily thick threads, " +
                   "often stretched from tree to tree, or tangled " +
                   "in the lower branches. The air here is quite hot " +
                   "and stuffy.";
            break;
    }

    if(dir_G != "")
        text = text + " It is impossible to go " + dir_G + 
               " because the dark hill there looks absolutely unclimbable.";
    if(dir_m != "")
        text = text + " Dark mountains " + dir_m + 
               " rise high above the forest.";
    if(dir_c != "")
        text = text + " Swift water of Celduin river blocks your way " +
               dir_c + ".";
    if(dir_f != "")
        text = text + " " + CAP(dir_f) + " you see a river whose name " +
               "is not known to you.";
    if(dir_R != "")
        text = text + " Dark evil Enchanted river is " + dir_R + ".";
    if(dir_r != "")
        text = text + " " + CAP(dir_r) + " runs cold Forest river.";

    return text + "\n";
}

