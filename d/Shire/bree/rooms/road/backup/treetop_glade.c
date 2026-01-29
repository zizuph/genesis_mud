/*
 * Road in Bree
 * By Finwe, June  2001
 *
 * Modification:
 *
 *   2008-05-02, Toby: Added set_dircmd("east bushes") 
 *                     and allow team to follow.
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"
#include <composite.h>
#include <filter_funs.h>

inherit ROAD_BASE;

#define NEED_CLIMB_SKILL    30
#define TREETOP     "/d/Shire/bree/rooms/road/treetop"
#define HIGHWAY     "/d/Shire/bree/rooms/road/nroad01"
#define FIELDS      "/d/Shire/eastroad/western/er29n"

string road_desc();

public int query_prevent_snoop() {return 1;}

void create_road_room()
{
    set_areadesc("cleared area");
    set_area("behind some bushes");
    set_areaname("near a large tree");
    set_land("Eriador");

    set_extraline("It is surrounded by bushes that line the roads to " +
        "the east and south. The green grass beneath the tree is well " +
        "trampled by constant use.\n");
    add_item(({"green grass", "grass"}),
        "The grass is healthy and green. It is trampled by countless " +
        "feet that come this way from the road and up the tree.\n");
    add_item(({"bushes", "tall bushes"}),
        "They are tall and overgrown, and grow around the tree and " +
        "alongside the road. The bushes grow close together, but a path " +
        "leads east through the bushes to the old highway. \n@@road_desc@@\n");
    add_item(({"path"}),
        "It is a well worn trail that leads east through the bushes.\n");
    add_item(({"sturdy ladder", "ladder"}),
        "The ladder leads up into the ancient tree. It is sturdy and " +
        "attached to the side of the tree.\n");
    add_item(({"ancient trees"}),
        "The ancient trees that originally grew here look like they were " +
        "planted ages ago and survived many battles. They are larger than " +
        "the tall trees. Scars and gashes can be seen in the trunks of " +
        "the trees.\n");
    add_item(({"scars", "gashes"}),
        "The gashs and scars in the trees are deep, left over from battles " +
        "that were fought here.\n");
    add_item(({"tree", "large tree"}),
        "It is one of the tallest and oldest trees growing here. A sturdy " +
        "ladder leads up the side of it." + road_desc() + "\n");

    add_exit(ROAD_DIR + "br1_04", "north");
    add_prop(ROOM_M_NO_SCRY,1);
    reset_shire_room();
    
}


public void
init()
{
    ::init();
    add_action("enter_bushes", "enter");
    add_action("climb_tree", "climb");

}

void
up_tree()
{
    write("You climb the sturdy ladder up into the tree.\n");
    TP->move_living("M",ROAD_DIR + "treetop", 1);
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
}


int climb_tree(string str)
{
    int player_climb_skill;

    player_climb_skill = TP->query_skill(SS_CLIMB);


        if (this_player()->query_prop(LIVE_O_STEED))
        {
            write("You must dismount your steed before climbing the tree.\n");
            return 1;
        }


        if(str =="tree" || str == "branch" || str == "tree" 
            || str == "up" || str == "ladder")
        {
            write("You climb the sturdy ladder up into the tree.\n");
            set_dircmd("tree");
            TP->move_living("M",ROAD_DIR + "treetop");
            tell_room(ENV(TP), QCTNAME(TP) + " arrives from below.\n",TP);
            return 1;
        }
        else 
        {
            write("Climb tree?\n");
            return 1;
        }
    
}

int enter_bushes(string str)
{
    if(str =="east bushes" || str == "east path" || str == "east shrubs")
    {
        write("You enter the bushes and disappear.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " disappears into the east bushes.\n",TP);
        set_dircmd("east bushes");
        TP->move_living("M",ROAD_DIR + "nroad01");
        return 1;
    }
    else if(str =="west bushes" || str == "west path" || str == "west shrubs")
    {
        write("You enter the bushes and disappear.\n");
        tell_room(ENV(TP), QCTNAME(TP) + " disappears into the west bushes.\n",TP);
        set_dircmd("west bushes");
        TP->move_living("M","/d/Shire/eastroad/western/er29n");
        return 1;
    }
    else 
    {
        write("Enter what, the east or west bushes?\n");
        return 1;
    }
    
}

string tree_top_descr()
{
    object other_room;
    mixed opeople;
 
    if (!LOAD_ERR(TREETOP))
        other_room = find_object(TREETOP);
    else
        return "Some sort of magic is plaguing the treetop. Contact " +
            "a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        return " No one is visible in the large tree.";
    else
        return " Up in the tree, you see hidden "+COMPOSITE_LIVE(opeople)+
            " watching your every move.";
}

string
road_desc()
{
    object other_room;
    mixed opeople;
    string views;

// East on the old highway view
    if (!LOAD_ERR(HIGHWAY))
        other_room = find_object(HIGHWAY);
    else
        return "Error with HIGHWAY. Contact a Shire wizard.";
    
    opeople = FILTER_LIVE(all_inventory(other_room));
    if (!sizeof(opeople))
        views =  "The old highway is empty east of here.\n";
    else
        views =  COMPOSITE_LIVE(opeople)+" is standing on the old highway.\n";

// West in the fields
    if (!LOAD_ERR(FIELDS))
        other_room = find_object(FIELDS);
    else
        return "Error with FIELDS. Contact a Shire wizard.";    
    opeople = FILTER_LIVE(all_inventory(other_room));

    if (!sizeof(opeople))
        views = views + "The fields are empty west of here.\n";
    else
        views = views + COMPOSITE_LIVE(opeople)+ " is in the fields " +
        "west of here.\n";

    views = "\nPeering through the bushes you see the following:\n" + views;
    return views;

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
        "the bushes. They shoot a flurry of arrows at the enemy and " +
        "chase it away. The rangers disappear back into the bushes.\n");
        return;
    }
}
