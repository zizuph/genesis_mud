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

    set_extraline("The path runs along the back side of the " +
        "cottage. On either side of the path grow healthy fruit " +
        "trees and fruit bushes. Peeking beyond the willow trees " +
        "are the Downs with their rolling hills. South is a large " +
        "stable.");

    add_item(({"stable"}),
        "The stable is a large building made of wood. It is " +
        "rectangular and houses horses that belong to the owner " +
        "of the cottage.\n");
    add_item(({"plants"}),
        "Growing in the garden are all kinds of fruit trees and " +
        "fruit bushes. Some you can identify are blueberries, " +
        "apples, strawberries, and plums as well as grapes, " +
        "gooseberries, boysenberries, currants, dandelions, " +
        "raspberries. They grow both against the house and " +
        "alongside the path.\n");
    add_item(({"apples"}),
        "The apple trees grow on either side of the path. They are " +
        "old trees with gnarled trunks and laden with sweet fruit.\n");
    add_item(({"plums"}),
        "These smooth barked trees grow on either side of the path. " +
        "Their fruit are large and and a deep burgandy color. The " +
        "plums look ready to split as they hang from the branches.\n");    
    add_item(({"blueberries"}),
        "The blueberry bushes grow against the house. They are " +
        "large and full of clusters of bright blue berries which " +
        "glisten in the @@light_type@@ light.\n");
    add_item(({"strawberries"}),
        "The strawberries grow on vining plants that hug the " +
        "ground. The plants grow under many of the plants and are " +
        "laden with bright red fruits.\n");
    add_item(({"dandelions"}),
        "The dandelions grow scattered against the house. Their " +
        "leaves are tall and green with yellow flowers.\n");
    add_item(({"fruit bushes"}),
        "The fruit bushes grow either side of the path. There are " +
        "many of them, but some you recognize are blueberries, " +
        "grapes, gooseberries, and raspberries. The " +
        "bushes look tall and healthy, and full of sweet fruit.\n");
    add_item(({"grapes"}),
        "The vining plants grow in a separate area of the garden " +
        "that is away from the path. The plants grow on some long " +
        "trellises tht support the vines and provide protection to " +
        "the plants. The large green leaves hide the bunches of " +
        "fruit that grow on the vines. The thickness of the vines " +
        "show that these are old plants but they still yield a lot " +
        "of fruit.\n");
    add_item(({"gooseberry", "gooseberries"}),
        "The gooseberries are medium high bushes that grow " +
        "alongside the house. The canes are full of green leaves " +
        "and laden with small, round, ruby red fruits.\n");
    add_item(({"raspberries", "raspberry"}),
        "The raspberries grow on trellises away from the path. The " +
        "tall prickly canes are covered with small green leaves. " +
        "Bunches of small red fruits grow on long thin stems that " +
        "lie hidden behind the leaves.\n");
    add_item(({"trellis", "wooden trellises", "trellises"}),
        "The trellises are sturdy frames that are placed away from " +
        "the path. They are made from strong pieces criss-crossed " +
        "wood and provide something for the grapes and raspberries " +
        "to grow on. The trellises are barely visible from the " +
        "abundant grow vines and canes growing on them.\n");
    add_item(({"criss-crossed wood"}),
        "They are square pieces of wood that make up the trellises.\n");
    add_item(({"canes", "fruit canes"}),
        "The canes are tall slender stems that grow up from the " +
        "ground. Some are prickly, like the raspberry canes, while " +
        "others are smooth or with joints like the gooseberry " +
        "canes. They are all covered with a multitude of growth " +
        "and look well tended.\n");
    add_item(({"raspberry canes"}),
        "The raspberry canes are tall stems that grow along " +
        "trellises. They are prickly and covered with leaves and " +
        "fruit.\n");
    add_item(({"gooseberry canes"}),
        "The gooseberry canes are medium height and grow alongside " +
        "the house. They are smooth and are covered with leaves " +
        "and golden fruit.\n");

    add_exit(ROOMS_DIR + "path07", "north");
    add_exit(ROOMS_DIR + "path10", "southwest");
}
