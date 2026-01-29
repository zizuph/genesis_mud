/*
 * Kitchen of the farmhouse in Anduin
 * By Finwe, November 2005
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "local.h"
 
inherit BASE_HOUSE;

void
create_house_room()
{
    set_short("A comfortable bedroom");
    set_long("This large bedroom is comfortable looking. A large bed sits " +
        "against one wall and a small bed against another. A large rug " +
        "covers most of the floor. There are windows set in the walls. " +
        "Beneath a window is a dresser. In a corner of the room is a " +
        "wardrobe. Lamps hang from the ceiling casting a warm glow to " +
        "the room.\n");

    reset_shire_room();

    add_exit("great_room1", "west");
    set_add_bedroom();
    set_add_rug("rectangular");
    set_extra_window("");
    set_extra_floor("A rectangular rug covers the floor.");
    set_large_bed();
    set_add_kids_bed();
    
    num_of_windows = 3;

}


void
reset_shire_room()
{
}
