#pragma save_binary
#pragma strict_types

#include "local.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit OR_FILE

object ship;

void summon_ship()
{
    //seteuid(getuid(this_object()));
    if(!ship)
    {
        ship = clone_object(SHIP + "ship");
        ship->start_ship();
    }
}

void reset_krynn_room()
{
    set_alarm(1.0, 0.0, summon_ship);
}


string get_long_desc()
{
    string desc = "You are on a wooden pier on the east bank of Harkun Bay, "
        + "near the mouth of Thon-Tsalarian.";
    switch(GET_SEASON)
    {
        case WINTER:
            desc += " Snow and ice cover the planks below you. One slip could"
                + " result in a lethal dive into the winter water.";
            break;
        case SPRING:
            desc += " The planks below you have been drenched by spring "
                + "showers.";
            break;
        case SUMMER:
            desc += " The walkway is lined with cargo boxes for the summer "
                + "trade season.";
            break;
        case AUTUMN:
            desc += " Gusts of chilly autumn wind come dangerously close to "
                + "knocking you into the cold water below.";
            break;
        default:
            break;
    }

    return desc + "\n";
}

mixed examine_cargo_boxes()
{
    if(GET_SEASON != SUMMER)
        return 0;

     return "The boxes contain various goods and supplies, most likely for "
         + "trade in Silvamori or Qualimori.\n";
}

mixed examine_spring_planks()
{
    if(GET_SEASON != SPRING)
        return 0;
    
    return "The wooden planks are soaked with water from the spring rainy"
        + " season.\n";
}

mixed examine_snow()
{
    if(GET_SEASON != WINTER)
        return 0;
    
    return "The pier is covered with snow  and ice, making the waves below "
        + "look all the more treacherous.\n";
}

mixed examine_planks()
{
    if(GET_SEASON == WINTER)
        return examine_snow();
    
    if(GET_SEASON == SPRING)
        return examine_spring_planks();

    return 0;
}

void create_krynn_room()
{
    set_short("A long, wooden pier");
    set_long("@@get_long_desc@@");
    add_item(({"water", "waves"}), "The water here is not calm at all. Waves "
        + "continuously slam into the wooden joists. This certainly is not a "
        + "good place for a swim.\n");
    add_item("pier", "The pier is long and the joists below appear sturdy, "
        + "though it is certainly not wide enough for you to feel safe "
        + "standing here.\n");
    add_item(({"joists", "wooden joits"}), "The wooden joists support the "
        + "pier. They are thick and cross braced, shugging off the barrage "
        + "of waves crashing into them.\n");
    add_item(({"boxes", "cargo boxes"}), "@@examine_cargo_boxes@@");
    add_item(({"planks", "wooden planks"}), "@@examine_planks@@");
    add_item(({"snow", "ice"}), "@@examine_snow@@");
    add_prop(ROOM_I_HIDE, 1);
    add_prop(ROOM_S_DARK_LONG, "A dark stretch of a pier");
    add_prop(ROOM_I_NO_CLEANUP, 1);
    add_exit(ROOMS + "pier0", "north");

    reset_krynn_room();
}
