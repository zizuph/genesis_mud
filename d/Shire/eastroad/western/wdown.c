/*
 * /d/Shire/eastroad/western/wdown.c
 *
 * Fixed search routine and cleaned up descriptions
 * Finwe, Feb 2019
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Shire/std/room";

#include "local.h"
#define MIN_AWARE 15

int item_found = 0;
object item;

void
create_room() 
{
   set_short("Below the well");
   set_long("You stand at the bottom of the well in the Shire. It has " +
        "dried up. There aren't even any puddles of water here. The " +
        "ground is covered with smooth rocks and dirt. A beam of light " +
        "comes down the well as your only source of light. A tunnel " +
        "heads north.\n");
   
    add_item(({"rocks", "smooth rocks"}),
        "The rocks are dark and smooth from years of water rushing " +
        "over them. Now they are dry and half buried in the dirt.\n");
    add_item(({"ground"}),
        "The ground is covered covered with dirt and smooth rocks. It " +
        "is dry and dark colored.\n");
    add_item(({"dirt"}),
        "The dirt is fine sand. It covers the ground and full of smooth " +
        "rocks.\n");
    add_item(({"walls", "shaft", "well shaft"}),
        "The walls of the well are irregular in shape. It looks like " +
        "they were once lined with smooth stones, but now most of " +
        "those have fallen off or have been taken away, making it easier " +
        "to climb out of the well.\n");
    add_prop(OBJ_I_SEARCH_TIME, 3);
    add_prop(OBJ_S_SEARCH_FUN,"do_search");
    
//    add_exit(EAST_R_DIR + "wdown_01", "north", "@@block_room@@");

    reset_shire_room();
}

void
reset_shire_room() 
{
    ::reset_shire_room();
    object torch;

    item_found = 0;

//  	if(!present("torch"))
//    {
//        torch = clone_object("/d/Shire/common/obj/shoptorch")->move(this_object());
//
//    }
}

void
init()
{
    ::init();
    add_action("do_climb","climb");
}

int
do_climb(string str)
{
    if (!str)
    {
        write("Climb what?\n");
        return 1;
    }

    if ((str != "walls") && (str != "wall") && (str != "shaft") && 
        (str != "out") && (str !="out of the well") && (str != "well") )
    {
        write("Climb where?\n");
        return 1;
    }

    write("With a great deal of effort, you climb up the well's shaft " +
        "and out of the well.\n");
    SAYBB(" climbs out of the well.");
    TP->move_living("M",EAST_R_DIR + "wplace",1,0);
    SAYBB(" arrives from inside the well.");
    return 1;
}

mixed
do_search(object searcher, string str)
{
    int awareness;

    awareness = searcher->query_skill(SS_AWARENESS);
    if(awareness < MIN_AWARE + random (MIN_AWARE)) return 0;

    if(str=="rocks" || str=="ground" || str=="dirt" || str=="sand")
    {
        if(item_found == 1)
        {
            return "You found nothing in " +str + "\n";
        }
        else
        {
            seteuid(getuid(TO));
            item = clone_object("/d/Shire/scav_hunt/skillet");
            item->move(searcher,1);
            say(QCTNAME(searcher)+ " finds something in the " + str + ".\n");
            item_found = 1;
            return "You find a " + item->short() + " in the " + str + ".\n";
        }

      return "You found nothing in the " + str + "!\n";
    }
    else
    {
        return ;
    }
}


int
block_room()
{
    if (this_player()->query_wiz_level()) 
    {
        write("\n\nYou enter an area that is not open to mortals.\n\n\n");
        return 0;
    }

    write("The tunnel has collapsed, blocking anyone from going north.\n");
    return 1;
}
