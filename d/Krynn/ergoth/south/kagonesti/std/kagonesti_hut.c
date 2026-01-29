#pragma strict_types

#include "local.h"
#include <ss_types.h>
#include <macros.h>
#include DEFS
#include CLOCKH

inherit R_FILE

public void create_kagonesti_hut()
{
}

string get_long_desc()
{
    string desc = "With minimal dimensions and lighting, this hut seems best "
        + "fit for sleep and privacy.";

    switch(GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            desc += " A few large furs blanket the floor, remnants of recent "
                + "sleep.";
            break;
        case TOD_TWILIGHT:
            desc += " Several furs are piled to the side, to be used in the "
                + "approaching nightfall.";
            break;
        case TOD_DAY:
            desc += " Furs have been rolled and placed out of the way while "
                + "it is daytime.";
            break;
        case TOD_NIGHT:
            desc += " Large furs are unrolled here, providing comfort and "
                + "warmth for the night.";
            break;
        default:
            break;
    }

    switch(GET_SEASON)
    {
        case WINTER:
            desc += " A small fire has been built to keep the hut warm during"
                + " these cold winter months.";
            break;
        case SPRING:
            desc += " A charred ring of dirt lies at the center of the hut, "
                + "reserved for building a fire to fend off chilly spring "
                + "mornings.";
            break;
        case SUMMER:
            desc += " The entrance is left completely uncovered, keeping the "
                + "hut cool in this scorching summer heat.";
            break;
        case AUTUMN:
            desc += " A blackened ring of dirt is all that remains from the "
                + "fires used to warm these cold autumn nights.";
        default:
            break;
    }
 
    return desc + "\n";
}

mixed get_fur_desc()
{
    switch(GET_TIMEOFDAY)
    {
        case TOD_DAWN:
            return "A few furs are spread out across the floor, used for "
                + "sleep in recent hours.\n";
        case TOD_TWILIGHT:
        case TOD_DAY:
            return "Furs are piled on the side of the hut, to be used once "
                + "darkness falls.\n";
        case TOD_NIGHT:
            return "Furs have been rolled out across the floor for the "
                + "inhabitants, keeping them cozy and off the comfortless "
                + "dirt floor.\n";
        default:
            return 0;
    }
}

mixed get_fire_desc()
{
    switch(GET_SEASON)
    {
        case WINTER:
            return "A small fire has been built in the middle of the hut. "
                + "It must burn without much smoke, else the hole above "
                + "would be quite ineffective.\n";
        case SPRING:
        case AUTUMN:
            return "The dark ring of char looks to have been formed by "
                + "several recent fires, placed in the center so smoke "
                + "could easily escape through the hole above.";
        default:
            return 0;
    }
}

mixed get_entrance_desc()
{
    if(GET_SEASON == SUMMER)
        return "The entrance is uncovered, allowing the " + GET_TIMEOFDAY
            + " air to flow freely.\n";
    
    return 0;
}

mixed get_hole_desc()
{
    if(GET_SEASON == SUMMER)
        return "The roof is completely covered with animal hide to keep "
            + "out the rain.\n";

    return "The roof is completely covered with animal hide, save a small "
        + "hole in the center to allow smoke from a fire to escape.\n";
}

void create_krynn_room()
{
    set_short("Inside a small hut");
    set_long("@@get_long_desc@@");
    add_item("furs", "@@get_fur_desc@@");
    add_item(({"fire", "ring"}), "@@get_fire_desc@@");
    add_item("entrance", "@@get_entrance_desc@@");
    add_item(({"hole", "ceiling", "roof"}), "@@get_hole_desc@@");
    INSIDE
    set_area_handler(STD + "kagonesti_placer");

    create_kagonesti_hut();
}

public int exit_move(string exit_cmd, object dest_room)
{
    object player = this_player();
    int retval;
    
    if(!(retval = ::exit_move(exit_cmd, dest_room)))
        foreach(object ob : filter(all_inventory(this_object()),
            &->query_npc()))
            ob->player_left_room(player, file_name(dest_room), exit_cmd);

    return retval;
}
