/*
 * Path in Tom Bombadill's Clearing
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;
 
void
create_path_room()
{
    set_areadesc("light");
    set_area("path east of");
    set_areaname("a cottage");
    set_land("the Old Forest");
    set_areatype(0);

    set_extraline("The path runs along the back side of the cottage. " +
        "It winds its way past a vegetable garden growing along " +
        "the wall. Tall trees block surround the valley, but to the " +
        "west tall rolling hills can be seen in a wide valley " +
        "beyond the trees.");
    add_item(({"vegetables"}),
        "Many vegetables grow alongside the house and on both sides " +
        "of the path. Some you recognize as gourds, beans, carrots, " +
        "cucumbers, and potatoes. Others are unknown but look rather " +
        "tasty. The vegetables are all healthy and look ready to pick.");
    add_item(({"gourds"}),
        "The gourds grow along the ground. The fruits are buried " +
        "beneath large green leaves. The fruits are varied in size " +
        "and shapoe. Some are large and round, while others are " +
        "long with crook necks. Still others are rectangular in " +
        "length and smooth looking. The fruits are all colours, " +
        "but mostly orange, yellow, green.\n");
    add_item(({"beans"}),
        "The beans grow on long vines up the side of the house. " +
        "The fruits are green and long, bulging where each bean " +
        "is at. The beans hang down from the vines and look ready " +
        "to pick.\n");
    add_item(({"carrots"}),
        "The carrots grow alongside the path. The leaves are " +
        "feathery and very tall and a deep green color. Barely " +
        "peeking out from beneath the soil you see large orange " +
        "roots, ready for picking.");
    add_item(({"cucumbers"}),
        "The plants grow along the ground, sprawling everywhere " +
        "they go. Like the other plants in the garden, They are " +
        "healthy with long, green fruits ready for harvesting.\n");
    add_item(({"taters", "potatoes"}),
        "The potatoes are tall, bushy plants growing in tall " +
        "mounds of brown soil. The spuds are buried in the soil " +
        "but are probabably very large and healthy.\n");

    add_exit(ROOMS_DIR + "path01", "north");
    add_exit(ROOMS_DIR + "path08", "south");


}
