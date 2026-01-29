/*
 * Hidden treetop lookout in Bree
 * By Finwe, June  2001
 *
 * Revision History:  May 2012 - removed shelves, see comment (Gorboth)
 *      Finwe, Feb 2020 - Added entrance to top of tree top. Only full
 *          rangers are allowed there.
 */

#pragma strict_types
inherit "/d/Shire/eastroad/std/er_base";

#include "/d/Shire/sys/defs.h"
#include "/d/Gondor/guilds/rangers/rangers.h"
#include "defs.h"
#include <stdproperties.h>
#include <std.h>
#include <composite.h>
#include <filter_funs.h>

#define BELOW_HI    "/d/Shire/bree/rooms/road/nroad01"
#define BELOW_NE    "/d/Shire/bree/rooms/road/nroad02"
#define BELOW_S     "/d/Shire/bree/rooms/road/crossroad"
#define BELOW_SW    "/d/Shire/eastroad/western/er29"
#define BELOW_SE    "/d/Shire/bree/rooms/road/road01"
#define BELOW_AREA  "/d/Shire/bree/rooms/road/treetop_glade"
#define BELOW_FIELD "/d/Shire/eastroad/western/er29n"
#define BELOW_AMBSH "/d/Gondor/guilds/rangers/ambush/ambush_1_top"

//inherit ROAD_BASE;

string road_desc();
int rglance();
object shelf;

public int query_prevent_snoop() {return 1;}

// create_road_room()
void create_er_room()
{
/*
    set_areadesc("tree");
    set_area("somewhere in a");
    set_areaname("forest");
    set_land("Eriador");
*/
    object  jar;
    areadesc = "tree";
    area = "somewhere in a";
    areaname = "forest";
    land = "Eriador";
    areatype = 0;


    extraline = "Its branches are large and covered with leaves.";
    add_item(({"tree"}),
        "The tree is tall and stands away from the road. Its branches " +
        "are long and spread out over the road. They are covered with " +
        "many large leaves, and hide you from prying eyes below.\n");
    add_item(({"branches", "gnarled branches"}),
        "The branches are large and smooth. They grow out and over the " +
        "road, and are covered with large green leaves. Carved into a " +
        "branch are these instructions: '<rglance> will help you observe " +
        "what happens below.' One large branch has been carved to hold a " +
        "jar for herbs.\n");
    add_item(({"leaves", "large green leaves", "green leaves"}),
        "The leaves are oval shaped, about the size of a large hand. " +
        "They are a deep green color and grow all over the branches, " +
        "hiding you from the road below.\n");
    add_item( ({ "large branch", "branch" }),
        "The large branch curves alongside the platform upon which you"
      + " stand, and has been carved to hold an herb jar in place that"
      + " has been fixed here for the use of the two companies.\n");
    add_item( ({ "platform" }),
        "A platform has been built up among the branches of this tree"
      + " that can support the weight of numerous men.\n");

    set_room_tell_time(480);
    add_room_tell("A breeze blows through the tree.");
    add_room_tell("A bird flies in and lands on a branch.");
    add_room_tell("The leaves rustle in the breeze.");
    add_room_tell("A group of travellers come down the Greenway.");
    add_room_tell("Some travellers head east towards Bree.");
    add_room_tell("Some travellers from Bree head south down the Greenway.");


object board;
if (!objectp( board) )
{
    board = clone_object("/d/Shire/std/board");
// board->set_long("This is a general board for all rangers. Rangers " +
// "are welcome to post notes of interest for both companies.\n");
    board->set_short("bulletin board");
    board->set_num_notes(30);
    board->set_board_name( ROAD_DIR + "treetop_board");
    board->move(this_object());
}

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_M_NO_SCRY,1);

    jar = clone_object("/d/Gondor/guilds/rangers/obj/racks/tree_herbjar");
    jar->add_prop(OBJ_M_NO_GET, "The jar has been fixed in place"
      + " along the branch, and cannot be taken.\n");
    jar->move(this_object());
    jar->set_no_show_composite(1);

    room_add_object("/d/Gondor/guilds/rangers/obj/racks/tree_crate");
}



public void
init()
{
    ::init();
    add_action("do_climb", "climb");
    add_action("rglance", "rglance");
}

string
road_desc()
{
    object other_room;
    mixed opeople;
    string views;


// Under the tree
    if (!LOAD_ERR(BELOW_AREA))
        other_room = find_object(BELOW_AREA);
    else
        return "Error with BELOW_AREA. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = "   No rangers are standing under the tree.\n";
    else
        views = "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is standing under the tree.\n";

// Northeast of the tree on the old highway
    if (!LOAD_ERR(BELOW_NE))
        other_room = find_object(BELOW_NE);
    else
        return "Error with BELOW_NE. Contact a Shire wizard.";
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "   The old highway is empty northeast of here.\n";
    else
        views = views + "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is standing north of here.\n";


//East on the highway
    if (!LOAD_ERR(BELOW_HI))
        other_room = find_object(BELOW_HI);
    else
        return "Error with BELOW_HI. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "   The old highway is empty east of here.\n";
    else
        views = views + "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is standing on the old highway.\n";

// southeast of the tree
    if (!LOAD_ERR(BELOW_SE))
        other_room = find_object(BELOW_SE);
    else
        return "Error with BELOW_SE. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "   The road is empty southeast of here.\n";
    else
        views = views + "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is southeast of here.\n";

// southwest of the tree
    if (!LOAD_ERR(BELOW_SW))
        other_room = find_object(BELOW_SW);
    else
        return "Error with BELOW_SW. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "   The road is empty southwest of here.\n";
    else
        views = views + "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is southwest of here.\n";

// southwest of the tree
    if (!LOAD_ERR(BELOW_FIELD))
        other_room = find_object(BELOW_FIELD);
    else
        return "Error with BELOW_FIELD. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "   The field is empty west of here.\n";
    else
        views = views + "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is in the field west of here.\n";

/*
// ambush area of tree
    if (!LOAD_ERR(BELOW_AMBSH))
        other_room = find_object(BELOW_AMBSH);
    else
        return "Error with BELOW_AMBSH. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "The hidden area is empty.\n";
    else
        views = views + COMPOSITE_LIVE(opeople)+" is hidden near the crossroads.\n";
*/
// crossroads of the tree
    if (!LOAD_ERR(BELOW_S))
        other_room = find_object(BELOW_S);
    else
        return "Error with BELOW_S. Contact a Shire wizard.";

    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views = views + "   The Crossroads are empty.";
    else
        views = views + "   " + CAP(COMPOSITE_LIVE(opeople)) +
        " is at the Crossroads.";

    views = "\nBelow, you see the following:\n" + views;
    return views;
}


int do_climb(string str)
{
    if(str=="down" || str == "down the tree" || str == "down the ladder")
    {
        write("You carefully climb down out of the tree.\n");
        say(QCTNAME(TP) + " carefully climbs out of the tree.\n");
        set_dircmd("tree");
        TP->move_living("M",ROAD_DIR + "treetop_glade");
    }
/*
    else if(str=="up" || str == "up tree" || str == "up ladder")
    {

        if( NORTH_MEMBER(this_player() || 
            ITHILIEN_MEMBER(this_player)))

//        if(this_player()->query_wiz_level())
        {
            write("You carefully up the ladder.\n");
            say(QCTNAME(TP) + " carefully climbs up the ladder.\n");
            set_dircmd("tree");
            TP->move_living("M",ROAD_DIR + "treetop_fort");
        }
        else
        {
            write("A Ranger from above blocks you and says, " +
//            Apprentices are not allowed up here.\n");
                "It is not safe for you to be up here yet.\n");
            return 1;
        }
    }
*/
    else write("Climb down tree?\n");
  
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
