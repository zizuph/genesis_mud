/*
 *  /d/Gondor/guilds/rangers/ithilien/tunnel/thicket_entrance.c
 *
 *  A secret entrance for Ithilien hideout
 *
 *  Coded by Tigerlily, April 14, 2004
 *
 *
 */
inherit "/d/Gondor/common/lib/area_room.c";



#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>

#include "/d/Gondor/defs.h"

#include "../../rangers.h"
#include "../exit.c"

#define RANGER_I_SCANNED_EXIT "_ranger_i_scanned_exit"

//prototypes
string        see_ranger_exit();
int           lift_rock(string str);
int           ranger_exit();
int           scan_thicket(string str);
public string do_search(object actor, string str);

int torch_found = 0;

public void
create_area_room()
{

    set_areatype(7);
    set_areadesc("thicket");
    set_area("northern");
    set_areaname("Druedain Forest");
    set_land("Anorien");
    set_grass("soft, green");
    set_treetype("tall oak");
    set_forest_density(50);
    set_extraline("This is an enclosed spot sheltered from " +
        "view behind the trees.");
    add_my_desc("A large rock.\n");

    add_item(({"rock", "large rock"}), &see_ranger_exit());
    add_item(({"leaves", "dry leaves"}), "Something about the dry leaves " +
        "attracts your attention.\n");

    add_exit(DRUEDAIN_DIR + "forest11", "west", &ranger_exit());
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_M_NO_SCRY, 1);
    reset_room();
}

void
init()
{
    ::init();
    add_action(&lift_rock(), "lift");
    add_action(&scan_thicket(), "scan");
}

int
lift_rock(string str)
{
    object tp = this_player();

    if (!RANGERS_FULL_MEMBER(tp))
    {
        notify_fail("What ?\n");
        return 0;
    }

    if (str != "rock" && str != "large rock")
    {
        notify_fail("Lift rock?\n");
        return 0;
    }
    write("You exert yourself to lift the rock. " +
        "Suddenly a hole opens below your feet, and you fall into an " +
        "underground passageway.\n");
    tell_room(environment(tp), QCTNAME(tp) + " strains mightily and " +
        "lifts the large rock.\n" + QCTNAME(tp) + " disappears " +
        "from view.\n", ({tp}));
    tp->move_living("M", RANGERS_ITH_TUNNEL + "tunnelg09", 1, 0);
    tell_room(this_object(), "The rock falls heavily " +
         "with a thud.\n", ({tp}));
    return 1;
}

string
see_ranger_exit()
{
    if (!RANGERS_FULL_MEMBER(TP))
    {
        return "The large rock, lying among some dry leaves, " +
            "is weathered with age.\n";
    }
    //else
    return "The large rock, lying among dry leaves, is weathered " +
        "with age and looks very heavy. But upon closer inspection, " +
        "you think you might be able to lift it, since you are " +
        "very strong.\n";
}

int
scan_thicket(string str)
{
    object actor = this_player(), *items;
    string outside, surroundings;

    if (!strlen(str))
    {
        notify_fail("Scan what?\n");
        return 0;
    }


    switch (str)
    {
    case "thicket":
    case "the thicket":
    case "the thicket to the west":
    case "west":
        outside = DRUEDAIN_DIR + "forest11.c";
        outside->teleledningsanka();
        if (!objectp(find_object(outside)))
        {
            surroundings = "Shadows obscure the view " +
                "and prevent you from scanning the area.\n";
            return 1;
        }
        surroundings = (find_object(outside))->long();

        items = FILTER_CAN_SEE(all_inventory(find_object(outside)), actor);

        if (sizeof(items))
            surroundings += CAP(COMPOSITE_LIVE(items)) + ".\n";

        actor->add_prop(RANGER_I_SCANNED_EXIT, 1);
        write("You peer out through the branches of " 
            + "an oak tree and scan the thicket to the west.\n " 
            + "This is what you see:\n\n" 
            + surroundings
            + "\nYou quickly lean back again so that you do not "
            + "reveal yourself.\n");
        tell_room(environment(actor), QCTNAME(actor) + " leans forward to "
            + "peer between the branches of an oak tree.\n", ({actor}));
        return 1;

    default:
        notify_fail("What do you want to scan? The thicket?\n");
        return 0;
    }
    return 1;
}

int
ranger_exit()
{
    object tp = this_player();

    if (!tp->query_prop(RANGER_I_SCANNED_EXIT))
    {
        write("You should scan the thicket to the west " +
            "to make sure that no enemies are nearby.\n");
        return 1;
    }
    tp->remove_prop(RANGER_I_SCANNED_EXIT);
    return 0;
}
void
reset_room()
{
    torch_found = 0;
}

public string
do_search(object actor, string str)
{
    object torch;

    if(!str)
    {
        write("Search what?\n");
        return "";
    }

    if ((str == "leaves" || str == "dry leaves") && !torch_found)
    {
        torch_found = 1;
        torch = clone_object(OBJ_DIR + "torch");
        torch->move(actor, 1);
        return "You find an old torch in the dry leaves.\n";
    }
    return "You find nothing of interest in the leaves.\n";
}


