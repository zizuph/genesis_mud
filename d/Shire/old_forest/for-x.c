#include "/d/Shire/old_forest/defs.h"
inherit OLD_FOR_DIR+"old_forest";
#include <ss_types.h>
#include <stdproperties.h>

#define GON_HERB   "/d/Gondor/common/herbs/"
#define RABBIT     (OLD_FOR_DIR+"rabbit")

int *D_H, *D_f, *D_R, *D_r, *D_m, *D_g;

public void
reset_room()
{
    ::reset_room(); /* defined in Gondor herb file */
    if(!random(10))
    {
        clone_object(RABBIT)->move(this_object());
        if(!random(5))
            clone_object(RABBIT)->move(this_object());
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
                     });
    int s;

    D_H = get_map_dirs("H");
    D_r = get_map_dirs("r");
    D_g = get_map_dirs("g");
    D_R = get_map_dirs("R");

    set_short("Deep in the Old Forest..");
    set_long("@@my_long@@");

    add_item(({"tree","trees" }), "These hideous, twisted ancient trees "+
        "seems to watch every step you take. Its quite " +
        "obviuos they dont like you beeing here.\n");

    if(sizeof(D_H))
    {
        add_item(({"hedge"}),
                "Behind the trees stands a large hedge.\n");
    }

    if(sizeof(D_g))
        add_item(({"gate", "small gate"}),
            "The small gate is the gate leading out of the forest.\n");

    if(sizeof(D_r) && !sizeof(D_R))
        add_item(({"river", "withywindle"}), "The river is dark with " +
                "brown water flowing lazily through the forest.\n");
 
    if(sizeof(D_R) && !sizeof(D_r))
    add_item(({"river", "brandywine"}), "A wide golden-brown " + 
            "colored river runs at the edge of the forest.\n");
 
    if(sizeof(D_r) && sizeof(D_R))
    add_item(({"river", "rivers", "withywindle", "brandywine"}), "The " +
            "Brandywine and Withywindle flows together here. Beeing " +
           "bigger, the Brandywines gold-brown water takes over and " +
            "the two streams continue in a southern direction from here.\n");


    reset_room();

    add_prop(ROOM_I_LIGHT, 1);
    add_prop("_room_i_no_me_sun", 1);
    add_std_exits();

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
    if(this_player()->query_skill(SS_LOC_SENSE) < random(70))
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
           dir_g = desc_map_dirs(D_g),
           dir_R = desc_map_dirs(D_R),
           dir_H = desc_map_dirs(D_H);

    text = "You are lost somewhere in the Old Forest. ";
    switch (time)
    {
        case "early morning":
        case "night":
        case "evening":
            text = text + "It is " + time +
                   " now and you can hardly see your hands. " +
                   "Menacing gloomy trees, with black leaves, " +
                   "loom everywhere around you, and you feel very " +
                   "uncomfortable.";
            break;
        case "morning":
        case "noon":
        case "afternoon":
            text = text + "Menacing gloomy trees, shaking their leaves, " +
                   "loom everywhere around you. You guess it is " + time +
                   " now, although you can't see the sky "+
                   "because of the trees. You hear grunts, " +
                   "scufflings, and moans from the undergrowth. ";
            break;
    }

    if(dir_g != "")
        text = text + " To the " + dir_g + " there is a small gate " +
            "in the hedge.";
    if(dir_r != "")
        text = text + " " + CAP(dir_r) + " runs the Withywindle.";
    if(dir_H != "")
        text = text + " Through the trees to the " + dir_H + " stands " +
                "the huge hedge between Buckland and the Old Forest.";
    if(dir_R != "")
        text = text + " The Brandywine runs " + dir_R + " from here.";

    return text + "\n";
}

