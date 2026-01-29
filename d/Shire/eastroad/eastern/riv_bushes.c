/*
 * Secret, hidden place for rangers to spy on road at Rivendell crossroad
 * Finwe, July 2004
 */
#pragma save_binary
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "local.h"
#include <composite.h>
#include <filter_funs.h>
 
inherit EAST_ROAD;

#define TROLLSHAW_DIR   "/d/Shire/common/trollsh/"
#define RIVER_DIR       "/d/Shire/eastroad/eastern/"
#define BUSHES          "/d/Shire/eastroad/eastern/riv_bushes"
#define BUSHES_N        "/d/Shire/common/trollsh/mpath6"
#define BUSHES_E        "/d/Shire/eastroad/eastern/imladris_connect"
#define BUSHES_S        "/d/Shire/common/trollsh/mpath4"
#define BUSHES_RIV      "/d/Shire/rivendell/room/river/riverbank"
 
void
create_er_room()
{
    set_area("along");
    set_areaname("the road");
    set_land("Eriador");
    set_areatype(AREATYPE_NONE);
    set_areadesc("foothill");
    
    set_treetype("oak");
 
    set_extraline("The light reflects off the bushes which are thick " +
        "and covered with sharp thorns. The ground is packed hard. The " +
        "grass trampled flat, and the forest grows thick here.");
  
    add_item(({"forest","oak forest","trees"}),
      "The shadow of Misty Mountains envelopes the Great East "+
      "Road here. Ancient oaks look ominous and gloomy as they " + 
      "rise up along the road.\n");
    add_item(({"mountains", "misty mountains", "foothills"}),
      "The tops of the Misty Mountains rise up before you. " +
      "They look forbidding and dangerous as they stand in " +
      "the distance.\n");
    add_item(({"path", "paths"}),
        "One path looks well used as it heads into the " +
        "mountains, skirting the river to the east. Another " +
        "less travelled path runs east to the river.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows east out of the mountains and south " +
        "alongside the road.\n");
    add_item(({"bushes", "shrubs"}),
        "The bushes are tall and thick. They hide you from anyone who " +
        "travels along the road. A path leads east into the bushes.\n");
    add_item(({"path"}),
        "The path is well worn and leads east into the bushes.\n");
    add_item(({"grass", "trampled grass"}),
        "The grass is green but bent over. It is trampled flat by " +
        "countless feet that walk all over it.\n");
    add_item(({"thorns", "sharp thorns"}),
        "The thorns are long, sharp, and painful looking. They grow all " +
        "over the bushes and point in all directions.\n");

    add_prop(ROOM_M_NO_SCRY,1);

    
/*
    add_exit(RIVER_DIR    + "riverbank", "east", "@@no_way@@",2,1);
*/
}



public void
init()
{
    ::init();
    add_action("rglance", "rglance");
    add_action("leave_bushes", "enter");
    add_action("leave_bushes", "exit");
    add_action("tell_remote", "say");
    add_action("tell_remote", "rsay");
    add_action("tell_remote", "'");


}


string
road_desc()
{
    object other_room;
    mixed opeople;
    string views;


// north of the road
    if (!LOAD_ERR(BUSHES_N))
        other_room = find_object(BUSHES_N);
    else
        return "Error with BUSHES_N. Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = "No one is on the road north of here.\n";
    else
        views = " " + COMPOSITE_LIVE(opeople)+" is standing on the road north of here.\n";

// east of the bushes
    if (!LOAD_ERR(BUSHES_E))
        other_room = find_object(BUSHES_E);
    else
        return "Error with BUSHES_E. Contact a Shire wizard.";    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "No one is on the otherside of the bushes.\n";
    else
        views = views + COMPOSITE_LIVE(opeople)+" is on the otherside of the bushes.\n";


//East on the highway
    if (!LOAD_ERR(BUSHES_RIV))
        other_room = find_object(BUSHES_RIV);
    else
        return "Error with BUSHES_RIV. Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "The ford of Bruinen is empty.\n";
    else
        views = views + COMPOSITE_LIVE(opeople)+" is at the ford of Bruinen.\n";

// southeast of the tree 
    if (!LOAD_ERR(BUSHES_S))
        other_room = find_object(BUSHES_S);
    else
        return "Error with BUSHES_S. Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "The road is empty south of here.\n";
    else
        views = views + COMPOSITE_LIVE(opeople)+" is standing on the road south of here.\n";


    views = "Outside the bushes, you see the following:\n" + views;
    return views;
}


int leave_bushes(string str)
{
    if(str=="bushes" || str == "shrub")
    {
        write("You carefully part the bushes and go out to the road.\n");
        say(QCTNAME(TP) + " carefully parts the bushes and goes out to the road.\n");
        TP->move_living("M",RIVER_DIR + "imladris_connect");
    }

    else write("Enter what?\n");
    return 1;
}

int rglance()
{
    write(road_desc() + "\n");
    return 1;
}

void tell_remote()
{
    // anyone on the road will 'hear' the rangers speak via of rustling 
    // bushes and muffled whispers. Best to use rsign here.
    string *msg;
    int x;

    msg = ({"You hear some whispering nearby.",
            "Some muffled voices echo from somewhere.",
            "You sense something watching you.",
            "The bushes rustle beside you.",
            "A startled rabbit dashes out of the bushes and darts in front of you."});

    x = random(sizeof(msg));
    tell_room(TROLLSHAW_DIR + "mpath6.c",  msg[x] + "\n");
    tell_room(RIVER_DIR + "imladris_connect.c",  msg[x] + "\n");
    tell_room(TROLLSHAW_DIR + "mpath4.c",  msg[x] + "\n");

}
