/*
 * Outside room for the path to the Toron minotaur village
 * Jan 2007. Made to inherit village_base_out.
 *
 * Added herbs, Arman 2017
 *
 * Added fishing, Arman 2021
 */

#include "../local.h"

inherit VILLAGE_BASE_OUT;
inherit "/d/Krynn/std/herbsearch";

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

string *herbs = HERB_MASTER->query_herbs( ({ "riverbank", }) );

void
create_toron_room()
{

    set_location("PATH");
    set_short("old dock");
    set_start_desc("You are standing on an old termite ridden dock. ");
    set_long_desc("It is clear this dock is no longer in service " +
                  "as there are several boards missing and many " +
                  "rusty nails sticking up. ");

    add_path_items();

    add_prop(LIVE_I_CAN_FISH, "freshwater");    
 
    add_item(({"wood","dock","boards"}),
               "It's an old, rotten dock out on Crystalmir lake.\n");

    add_item(({"nails"}),"They're old and rusty, but they still seem to " +
               "hold things together.\n");

    add_item(({"lake", "water"}),"From here you have an excellent view " +
               "of the lake. Through the haze you can make out majestic " +
               "mountains on the other side. \n");  
             
    add_item(({"mountain", "mountains"}),"There is snow on the " +
               "top. \n");
    
    add_exit(ROOM + "lake6","northeast",0,1);

    seteuid(getuid(TO));
    set_up_herbs( ({ ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
       ONE_OF(herbs) }), ({ "lake","lakeshore","water" }), 4);

    reset_room();
}

