/*
 * Road in Bree
 * By Finwe, June  2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "defs.h"

inherit ROAD_BASE;

void down_tree();

void
create_road_room()
{   
    setuid();
    seteuid(getuid());

    set_add_orchard();

    apples = 0;
    set_areadesc("northwest");
    set_area("corner in");
    set_areaname("the orchard");
    set_land("Bree");
    add_bree_desc("There is a tree house tucked away in the branches.\n");
    add_exit(ROAD_DIR + "orchard02", "south");
    add_exit(ROAD_DIR + "orchard03", "east");

    add_item(({"treehouse", "tree house"}),
        "It is a playhouse built in the branches of an apple tree. It " +
        "looks like you can climb up into it.\n");
    add_item(({"playhouse"}),
        "It looks like a tree house up in the branches of an apple tree. " +
        "It looks like you can climb up into it.\n");

    reset_shire_room();

}

void
init()
{
    add_action("sniff_air", "sniff");
    add_action("sniff_air", "smell");
    add_action("get_apple", "get");
    add_action("get_apple","pick");
    add_action("do_climb", "climb");

    ::init();
}


int do_climb(string str)
{

    if(str=="up" || str =="tree" || str == "branch")
       {
           down_tree();
       }

    else write("Climb where?\n");
    return 1;
}

void
down_tree()
{
    write("\nYou carefully climb up several branches into the treehouse above.\n\n");
    say(QCTNAME(TP) + " carefully climbs up several branches into the treehouse above.\n\n");
    TP->move_living("M",ROAD_DIR + "treehouse");
    tell_room(ENV(TP), QCTNAME(TP) + " arrives from the orchard below\n\n",TP);
}
