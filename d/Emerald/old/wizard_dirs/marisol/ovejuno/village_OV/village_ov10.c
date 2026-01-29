
/* Re Albi village. Village's path X.
 * Coded by Marisol (12/15/97)
 * Modified by Marisol (07/28/98) to be used in the village of
 * Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
#include "/d/Emerald/sys/macros.h"
#define MDOOR DOORS+"moss_in"
inherit OV_VILLAGE;

object door;


void
create_ov_room()
{

    set_long("A village path in Ovejuno. The Sage Femme's hut looms "+
        "here at the end of the path. Some red hens and brown chickens "+
        "are scratching the ground for food. One of the hens has "+
        "chicks, all yellow puffs trailing behind her. There are not "+
        "houses in this part of the village. A small trail veers to the "+
        "left around the house. In the distance, you can see frolicking "+
        "lambs in the high pastures. Blue-grey smokes drift "+
        "lazily in the cool wind, and high in the sky, a hawk flies "+
        "proudly with the mountain breeze.\n");

    add_item("sheep",
        "The sheep are grazing placidly in the steep meadow where the "+
        "communal pastures are located. Some frolicsome lambs "+
        "play unconcern under the watchful eyes of their elders.\n");

    add_item("hawk",
        "A hungry lucking hawk flies around in circles over the "+
        "nervous eyes of the chickens and hens.\n");

    add_item(({"pastures", "meadows"}),
        "The green meadow with wildflowers rise to the hill that "+
        "hovers over the village. In this communal pastures, sheep "+
        "and their lambs roam and graze placidly.\n");

    add_item(({"hens", "hen", "chick", "chicks", "chicken", "chickens"}),
        "The hens and chicken scratch the ground looking for food. "+
        "The little chicks are following their mommy and cheeping "+
        "happily. Some of the hens move restless and peer up "+
        "nervously to the hawk circling over them.\n");

    add_item(({"sage femme's hut", "hut"}),
        "Here is the hut of the Sage Femme of Ovejuno. She is "+
        "a kind of healer that sell herbs and potions to the sick. "+
        "Her hut is small and simple. It is thatched with straw and "+
        "the walls are wooden sticks. It has a hole in the roof "+
        "where blue smokes rise to the sky.\n");


door = clone_object(MDOOR);
door ->move(TO);

    add_exit("village_ov09.c", "southwest");
    add_exit("herb_garden01.c", "northwest");


}                                                                        
