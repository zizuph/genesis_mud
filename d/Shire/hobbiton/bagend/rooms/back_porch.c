/*
 * Back porch of Bag End
 * By Finwe, May 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"

inherit BASE_OUTSIDE;

//int lawn_cut = 0;

void create_outside_room()
{
    set_areadesc("back porch");
    set_area("outside");
    set_areaname("a large smial");
    set_land("Hobbiton");
    set_areatype(0);

    set_long("@@long_desc");

    set_extraline("This is a small area outside a back door. Flagstones are set in the ground outside a round blue door, and a large roof extends over the porch. A path leads west through a gate hidden by tall sunflowers and east to the front. A small window is set to the left of the door.");

    add_item(({"window", "small window"}),
        "It is round and set on the left side of the door. The window " +
        "is made of panes of glass. Each glass pane is held in the " +
        "window with narrow strips of lead.\n");

    add_item(({"small area", "porch", "area", "ground"}),
        "This is a small place outside the back door. Flagstones are arranged in the ground in a circular shape.\n");
    add_item(({"flagstones", "flagstone", "stones"}),
        "They are grey colored and roughly cut. The stones are irregular shaped and set in the ground.\n");
    add_item(({"large roof", "roof"}),
        "The roof is rouned, like the door, and extends out over the porch. A wind chime hangs from a corner.\n");
    add_item(({"path"}),
        "The path is made of flagstones. It runs northwest around the hill, and east past the front of the burrow. \n");
    add_item(({"grass", "lawn"}),
        "XXX \n");
    add_item(({"sunflowers", "tall sunflowers"}),
        "They are tall and grow in front of the fence to the west. The flowers grown on top of thick stems. Each flower is round with multiple yellow petals that surround a large, brown center.\n");
    add_item(({"stems", "sunflower stems"}),
        "The sunflower stems are green and slightly prickly. The are tall and topped with sunflowers.\n");
    add_item(({"sunflower petals", "petals"}),
        "They are yellow and pointed, and grow on the sunflowers.\n");
    add_item(({"wind chime", "chimes"}),
        "It is made from six pointed flower card from wood and painted red. From each point hangs a thin metal tube of various lengths.\n");
    add_item(({"tubes", "thin tubes", "metal tubes", "metal tube", "tube"}),
        "The tubes are both long and short. They hang from the wooden flower and create a gentle chime when a breeze blows past them. \n");
    add_item(({"wooden flower", "six pointed flower", "red wooden flower"}),
        "It is expertly carved of wood and painted red. From each point hangs a metal tube.\n");
    add_item(({"fence"}),
        "XXX \n");
        
    room_add_object(BE_OBJ + "bporch_door");
    room_add_object(BE_OBJ + "bp_gate");



//    add_bagend_front();
//    add_bagend_garden();
    add_windows();

    reset_shire_room();

    add_exit(BE_ROOMS + "path15", "east");
    add_exit(BE_ROOMS + "path16", "northwest");
    add_exit(BE_ROOMS + "lawn02", "south");
}

void reset_shire_room()
{
    ::reset_shire_room();
    set_searched(0);
    lawn_status(-1);
}
