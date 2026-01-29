/*
 * Forest path leading to Wild Elves Guild
 * By Finwe, July 2001
 */
 
#include "/d/Shire/cypress/sys/defs.h" 
#include "/d/Shire/cypress/thalandrone/local.h"

//inherit "/d/Shire/cypress/thalandrone/base_road.c";
inherit FOREST_BASE;

#define POUCH_SEARCH    "_glen_money_pouch_searched_"
//string road_type = "path";
int hidden_pouch;


void
create_forest_room()
{
    set_vbfc_extra(road_desc1);

    add_my_desc("The "+road_type+" runs north and south in a " +
    "straight line. Some rotting logs lie in a pile alongside the road.\n");

    /*routines to search for money pouch */
    hidden_pouch = 0; /*pouch not found*/
    add_prop(POUCH_SEARCH,0); /*player not found pouch */
    add_cmd_item(({ "rotting logs", "log", "logs"}), 
                 (({"look", "exa", "examine"})),
                    "@@search_log@@");

    reset_cypress_room();

    add_exit(GLEN_DIR + "path08", "north");
    add_exit(GLEN_DIR + "path10", "south");

}

void reset_cypress_room()
{
    hidden_pouch = 0; /*reset pouch search */
}

search_log()
{
    if(query_prop(POUCH_SEARCH)) /*player searched log successfully*/
    {
        TP->catch_msg("You find nothing but rotted leaves and " +
            "twigs insidie the rotting log.\n");
        say(QCTNAME(TP)+" searches inside a rotted log and " +
            "finds nothing.\n");

      return 1;
    } 
    TP->catch_msg("Looking under the rotting leaves, you find " +
        "a small moldy leather pouch that looks like it has " +
        "fallen there by a traveller. Quickly, you take it and hide it " +
        "in your pocket.\n");
    say(QCTNAME(TP)+" finds something inside a rotting log.\n");
    clone_object(OBJ_DIR + "pouch")->move(TP);
    add_prop(POUCH_SEARCH,1); /* searched */
    
  return 1;
}