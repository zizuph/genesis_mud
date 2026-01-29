/*
 * Path in Bree orc camp
 * By Finwe, July 2000
 */

#pragma strict_types

#include "local.h"

inherit CAMP_BASE;

void
create_camp_room()
{
    set_extraline("This is a well trodden path leading north. " +
        "Loud noises can be heard from that direction, snarls " +
        "and guttural sounds. Two tall dark standards have " +
        "been set into the ground here, marking the entrance to " +
        "a camp.");
    add_item(({"large standard", "standard"}),
        "These grisly poles are sunk deep into the ground " +
        "on either side of the path. Black banners hang from " +
        "each standard.\n");
    add_item(({"flags", "banners", "black banners"}),
        "The banners are large and completely black with a red " +
        "eye crudely painted in the center. They hang from the " +
        "tops of the poles.\n");
    add_item(({"poles", "pole", "grisly poles", "grisly pole"}),
		"The poles are about three times as tall as a human, " +
        "and rough looking. They are sunk deep into the ground " +
        "and decorated with black banners.\n");

    add_exit(CAMP_DIR + "path25", "northeast");
//    add_exit("/d/Shire/common/bree/northgate","bushes");
    add_exit("/d/Shire/bree/rooms/road/nhedge08", "bushes");
    
    reset_shire_room();
}

