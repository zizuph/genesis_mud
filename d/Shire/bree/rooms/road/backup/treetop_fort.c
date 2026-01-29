/*
 * Top of the treetop lookout. 
 * By Finwe, January 2019
 *
 * Added shelves for rqangers, which can be monitored
 */

#pragma strict_types
inherit "/d/Shire/eastroad/std/er_base";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <std.h>
#include <composite.h>
#include <filter_funs.h>

#define BELOW_HI        "/d/Shire/bree/rooms/road/nroad01"
#define BELOW_NE        "/d/Shire/bree/rooms/road/nroad02"
#define BELOW_XR         "/d/Shire/bree/rooms/road/crossroad"
#define BELOW_SW        "/d/Shire/eastroad/western/er29"
#define BELOW_SE        "/d/Shire/bree/rooms/road/road01"
#define BELOW_AREA      "/d/Shire/bree/rooms/road/treetop_glade"
#define BELOW_FIELD     "/d/Shire/eastroad/western/er29n"
#define BELOW_AMBSH     "/d/Gondor/guilds/rangers/ambush/ambush_1_top"

#define BELOW_GATE      "/d/Shire/bree/rooms/road/wgate"
#define BELOW_GW2       "/d/Shire/common/greenway/gw2"

//inherit ROAD_BASE;


string road_desc();
int rglance();
object shelf;

public int query_prevent_snoop() {return 1;}

// create_road_room()
void create_er_room()

{
    set_areadesc("treetop");
    set_area("somewhere in a");
    set_areaname("forest");
    set_land("Eriador");
    areatype = 0;

    extraline = "Its branches are large and covered with leaves.";
    add_item(({"tree"}),
        "The tree is tall and stands away from the road. Its branches " +
        "are long and spread out over the road. They are covered with " +
        "many large leaves, and hide you from prying eyes below.\n");
    add_item(({"branches", "gnarled branches"}),
        "The branches are large and smooth. They grow out and over the " +
        "road, and are covered with large green leaves. Carved into a " +
        "branch are these instructions:\n\n\t<rglance> will help you observe " +
        "what happens below.\n");
    add_item(({"leaves", "large green leaves", "green leaves"}),
        "The leaves are oval shaped, about the size of a large hand. " +
        "They are a deep green color and grow all over the branches, " +
        "hiding you from the road below.\n");
    add_item( ({ "platform" }),
        "A platform has been built up among the branches of this tree"
      + " that can support the weight of numerous men.\n");

    room_add_object("/d/Gondor/guilds/rangers/obj/racks/tree_crate");

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_M_NO_SCRY,1);
}

public void
init()
{
    ::init();
    add_action("do_climb", "climb");
    add_action("rglance", "rglance");
}

string
view_road(string area, string no_one, string travellers)
{
    object other_room;
    mixed opeople;
    string views;

    if (!LOAD_ERR(area))
        other_room = find_object(area);
    else
        return "Error with " + area + ". Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = "   " + no_one + "\n";
    else
        views = "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " " + travellers + "\n";
    return views;
}

string
road_desc()
{
    object other_room;
    mixed opeople;
    string views, road_view;

// Under the tree
    road_view = view_road(BELOW_AREA, 
        "No rangers are standing under the tree.",
        "is standing under the tree.");
// Northeast of the tree on the old highway
    road_view += view_road(BELOW_NE, 
        "The old highway is empty northeast of here.", 
        "is standing north of here.");
//East on the highway
    road_view += view_road(BELOW_HI,
        "The old highway is empty east of here.",
        "is standing on the old highway.");
// southeast of the tree
    road_view += view_road(BELOW_SE,
        "The road is empty southeast of here.",
        "is southwest of here.");
// southwest of the tree
    road_view += view_road(BELOW_SW,
        "The road is empty southwest of here.",
        "is in the field west of here.");
// crossroads of the tree
    road_view += view_road(BELOW_XR,
        "The Crossroads are empty.",
        "is at the Crossroads.");

    views = "\nBelow, you see the following:\n" + road_view + "\n";
    return views;
}

int do_climb(string str)
{
    if(str=="down" || str == "the tree" || str == "the ladder")
    {
        write("You carefully climb down out of the tree.\n");
        say(QCTNAME(TP) + " carefully climbs out of the tree.\n");
        set_dircmd("tree");
        TP->move_living("M",ROAD_DIR + "treetop");
    }
    
    else write("Climb down?\n");
    return 1;
}

int rglance()
{
    write(road_desc() + "\n");
    return 1;
}

public void
enter_inv(object ob, object from)
{
    int n;

    ::enter_inv(ob, from);
    if (ob->id( "craban"))
    {
        set_alarm (0.0, 0.0, &ob->remove_craban());
        tell_room(this_object(),"Suddenly, some rangers step out of " +
        "the shadows and shoot a flurry of arrows at the enemy and " +
        "chase it away. The rangers disappear back into the shadows..\n");
        return;
    }
}