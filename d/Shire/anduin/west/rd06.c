/*
 * Road in western vales of Anduin.
 * By Finwe, June 2001
 */
 
#pragma strict_types
 
#include "local.h"

inherit VALE_BASE;

#define MISTY_DIR "/d/Shire/misty/" 

void
create_vale_room()
{
    set_area("on the western edge of");
    set_areaname("the Old Forest Road");
    set_land("the Vales of the Anduin");

    set_vbfc_extra(road_desc1);
    add_my_desc("It winds its way past boulders in the " +
        "foothills of the Misty Mountains.\n");
    add_item(({"boulders", "large rocks"}),
        "The boulders are large and some even cracked and split " +
        "in two. They look like they've rolled off the " +
        "mountains and stopped where they landed. Grasses and " +
        "flowers grow up around the boulders.\n");
    add_item("foothills",
        "They are bare, jagged and broken hills at the feet of " +
        "the Misty Misty Mountains. Nothing grows on them as " +
        "they are bare rock.\n");
    
    set_add_river_far();
    set_add_misty_close();
    reset_shire_room();

    add_exit(MISTY_DIR +  "p13", "west");
    add_exit(WEST_DIR + "rd05", "southeast");
 
}

void reset_shire_room()
{
}
