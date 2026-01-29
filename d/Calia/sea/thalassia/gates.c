
/* 	Thalassian City Gates

    coder(s):   Jaacar

    history:    15. 7.03    room coded                      Jaacar

*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/sys/water.h"
#include "defs.h"

inherit "/d/Calia/std/water_room";

void
create_water_room()
{
    set_short("At the gates");
    set_long("You are swimming through a tunnel that form a passageway "+
        "before you. Far through the passageway to the northwest "+
        "you see some buildings, between which looks to be your only "+
        "way into the vast city that appears to stretch out beyond it. "+
        "To the southeast lies the whale's mouth gates, beyond which "+
        "lies the thalassian sea.\n");

    add_item("tunnel","The tunnel is constructed from stone bricks "+
        "forming a complete circle around you and appear to be quite "+
        "thick and strong. The tunnel forms a passageway off to the "+
        "northwest.\n");
    add_item(({"passage","passageway"}),"The passageway appears to "+
        "stretch out to the northwest for a while then curves gently "+
        "to the north.\n");
    add_item(({"building","buildings"}),"The buildings seem to be "+
        "constructed from the same stone bricks that the walls are "+
        "made from.\n");
    add_item(({"city","vast city"}),"Details about the city are "+
        "hard to make out from this vantage point. It appears "+
        "to be quite large in size and formed of three seperate "+
        "rings, each inside of the other.\n");
    add_item(({"ring","rings","three rings","seperate rings",
        "three seperate rings"}),"These three rings form the "+
        "entire city, each ring even more beautiful than the "+
        "last.\n");
    add_item(({"gate","gates","mouth gate","mouth gates",
        "whale's mouth gate","whale's mouth gates",
        "whales mouth gate","whales mouth gates"}),"The gates are "+
        "fashioned in the shape of a whale's mouth and lead back "+
        "out into the dark Thalassian sea beyond them. You could "+
        "probably 'enter gates' if you wanted to go beyond them.\n");

    add_swim_exit(THAL+"path1","northwest");
    // Do not remove the next lines, they are to load the various rooms
    // so that there are actually wandering creatures around the 
    // city instead of them bulk loading when a player enters the
    // room for the first time.
    (THALM+"major4")->teleledningsanka();
    (THALM+"major9")->teleledningsanka();
    (THALM+"major18")->teleledningsanka();
    (THALM+"major20")->teleledningsanka();
    (THALM+"major39")->teleledningsanka();
    (THALM+"major48")->teleledningsanka();

    (THALL+"lesser6")->teleledningsanka();
    (THALL+"lesser7")->teleledningsanka();
    (THALL+"lesser16")->teleledningsanka();
    (THALL+"lesser24")->teleledningsanka();

    (THALC+"citadel2")->teleledningsanka();
    (THALC+"citadel6")->teleledningsanka();
    (THALC+"citadel10")->teleledningsanka();
    (THALC+"citadel14")->teleledningsanka();
}

void
init()
{
    ::init();
    add_action("enter_gates","enter");
}

int
enter_gates(string str)
{
    notify_fail("Enter what? The gates?\n");
    if (str == "gates")
    {
        write("\nAs you approach the gates, they open allowing "+
            "you to swim through to the other side.\n\n");
        tell_room(environment(TP), QCTNAME(TP) +
            " swims up to the gates.  They open, allowing "+
            TP->query_objective()+" to swim through to the "+
            "other side.\n", TP);
        this_player()->move_living("M",OUTSIDE+"wr_13_1_3",0);
        tell_room(environment(TP), QCTNAME(TP) +
            " arrives through the gates.\n", TP);
        return 1;
    }
    return 0;
}
