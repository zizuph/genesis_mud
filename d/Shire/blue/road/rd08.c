/*
 * Road to Blue Mountains
 * - Finwe, July 2002
 *
 *  2006.09.05, Toby: Added add_item field and blossoms
 */

#include "local.h"

inherit BASE_ROAD;

void
create_blue_road()
{
    area = "at the base of";
    areaname = "the Blue Mountains";
    land = "Eriador";
    areatype = 5;
    areadesc = "path";


    extraline = "The rugged path leads north into the Blue Mountains, " +
        "and ancient chain of mountains that run north and south along " +
        "the western edge of Eriador. The path runs southeast through a " +
        "field.";

    add_item(({"grass"}),
        "The grass that grows north in the mountains is brown and sparse. " +
        "It grows in the cracks of the boulders alongside the path. The " +
        "grass in the field south, east and west is green and lush. " +
        "Wildflowers grow straggly in the mountains while in the field, " +
        "they are healthier looking.\n");
    add_item(({"path", "road", "rocky path", "rocky road"}),
        "The path running north disappears behind some boulders. It " +
        "looks rocky and dangerous. It also runs southeast and disappears " +
        "in the grass.\n");
    add_item(({"blue mountains", "mountains", "mountains of the lune",
            "ered luin"}),
        "The Blue Mountains are a tall chain of mountains. They run " +
        "north and south with tall, rugged peaks that reach to the sky.\n");
    add_item(({"wild flower", "wildflowers", "flowers","blossoms","cherry blossoms"}),
        "The wildflowers on the mountain path grow scattered between " +
        "the cracks of the boulders. They dot the area with their cheery " +
        "blossoms. There are thicker and more colourful wildflowers " +
        "in the tall grasses of the field.\n");
    add_item(({"peaks", "mountain peaks"}),
        "The peaks are craggy and obviously very ancient. They are " +
        "various heights, some rising above you, looking like broken towers.\n");
    add_item(({"boulders", "cracked boulders", "rocks", "large rocks"}),
        "They are scattered across the mountain path. Some are cracked " +
        "and different colors.\n");
    add_item("cracks","Wildflowers grow in the cracks of the boulders.\n");
    add_item("field", "The field is covered by green grass all over.\n");

   add_exit(ROAD_DIR + "rd09","north");
   add_exit(ROAD_DIR + "rd07","southeast");
}
