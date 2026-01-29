/*
 * Forest near Rivendell
 * By Finwe, August 1998
 * Palmer Jan 2003 - Added query_race("horse") to check_person to let horses pass
 */

#pragma strict_types

#include "local.h"

inherit FOREST_BASE;

int check_players = 1;

void
create_forest_room()
{
    set_vbfc_extra(forest_desc4);
    set_extraline("The ford of the river Bruinen is west.");

    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows lazily to the west from the mountains. " +
        "It looks clear and fresh.\n");
    add_item(({"ford", "river ford", "ford of the river bruinen"}),
        "The ford is a shallow place in the river, allowing " +
        "people to usually cross the river safely.\n");
    
    set_add_white_stone("top center", "left edge");

    clone_object("/d/Shire/rivendell/obj/boulder")->move(this_object(), 1);
    reset_shire_room();
    add_forest_herbs();

//    add_std_herbs("stream");

    add_exit(FOREST_DIR + "forest43", "north",0,4, check_person);
    add_exit(FOREST_DIR + "forest61", "south",0,4, check_person);
    add_exit(FOREST_DIR + "forest53", "east",0,4, check_person);
    add_exit(RIVER_DIR + "in_ford",   "west",0,4, check_person);
    add_exit(FOREST_DIR + "forest42", "northwest",0,4, check_person);
    add_exit(FOREST_DIR + "forest44", "northeast",0,4, check_person);

}

void init()
{
    ::init();
    add_action("drink_it", "drink");
//    add_action("enter_bushes", "enter");
//    add_action("enter_bushes", "pass");
}

int drink_it(string s)
{

int amount;

   if(s=="water" || s=="water from river")
       {
           amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
           if (TP->drink_soft(amount))
           {
           TP->catch_msg("You kneel before the river, dipping " +
                "your cupped hands into the river and get a " +
                "drink of the clear icy water. Its taste " +
                "refreshes your mind and body.\n");

           say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");

           }
           else
           {
           write("You cannot drink more water.\n");
           }

            return 1;
        }
    else
            NF("Drink what?\n");
}


void reset_shire_room()
{
    set_searched(0);

}

/*
string
exa_leaves()
{
    if(CHECK_STATS)
    {   
        TP->add_prop(LEAF_PROP,1);
        return "Hidden between the leaves you find a white stone.";
    }
    else
       return "";
}
*/