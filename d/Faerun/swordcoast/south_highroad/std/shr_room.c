/*
* south_highroad/std/shr_room.c
* Standard outdoor room for the Southern High Road and the outskirts of the
* City of Waterdeep
*
*  Created Jan 2021 by Brine
*/
#pragma strict_types
#pragma no_clone

#include "../defs.h"

inherit FAERUN_OUTDOOR_BASE;

#include "road_descriptions.o";

void
create_shr_room()
{
    set_short("Standard outdoor room for the Southern High Road area");
    set_extraline(
        "Long description of the standard outdoor room for the Southern High "
        + "Road area."
    );
}

void
create_faerun_room()
{
    create_shr_room();
}

void
set_area(string area_name)
{
    string desc;

    switch (area_name)
    {
        case MOUNT_SAR:
            desc = "You are on the slopes of Mount Sar";
            break;
        case MOUNT_HELIMBRAR:
            desc = "You are on the slopes of Mount Helimbrar";
            break;
        case RED_ROCKS:
            desc = "You are among the trecherous Red Rocks";
            break;
        case RED_CLIFFS:
            desc = "You are by the Red Cliffs";
            break;
        case WESTWOOD:
            desc = "You are in the woods of Westwood";
            break;
        case ON_ROAD:
            desc = "You are on the southern part of the High Road";
            add_road_messages();
            break;
        case ALONG_ROAD:
            desc = "You are somewhere along the southern part of the High Road";
            break;
        default:
            desc = "You are in the general area of your vicinity";
            break;
    }

    string area_name_known = area_name ? area_name : "Unknown";
    add_prop(SOUTH_HIGHROAD_AREA, area_name_known);
    add_item(({ "area", "general area" }), desc + ".\n");
}

void
set_road(string road_type)
{
    string *items = ({ "ground", "road" });
    string desc = "You are standing on solid, firm ground.\n";

    switch (road_type)
    {
        case DIRT_ROAD:
        items += ({ "dirt road" });
        desc = "You are standing on a dirt road, carving its way through the "
        + "area. Deep ruts tell the tale of a road well travelled.\n";
        add_item(
            ({ "rut", "deep rut", "ruts", "deep ruts" }),
            "The ruts are deep and numerous, made by the wheels of numerous "
            + "carts and carriages passing through.\n"
        );
        break;
        case HIGH_ROAD:
        items += ({
            "paved road", "high road", "highroad", "High Road", "the High Road",
            "the high road", "the highroad", "the Highroad", "Highroad"
        });
        desc = "You are standing on the High Road, the main trade route of "
        + "the northwestern Sword Coast. The road is wide and paved with "
        + "large cobbles. It seems old and well travelled.\n";
        add_item(
            ({
                "paving", "pavings", "stones", "paving stones", "cobbles",
                "tops", "large cobbles", "rectangular shaped paving stones",
                "rectangular stones", "rectangular shaped stones"
            }),
            "They are rectangular shaped paving stones with curved tops. They "
            + "are laid into the road and look worn.\n"
        );
        break;
    }

    add_item(items, desc);
}
