/*
 * Base file for the Vales of Anduin
 * Finwe, June 2001
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/d/Shire/anduin/base_common";
inherit "/lib/commands.c";

void create_vale_room() {}
 
public void
create_area_room()
{
    set_area("western edge");
    set_areaname("Undefined");
    set_land("Vales of the Anduin");
    set_areatype(1);
    set_areadesc("path");
    set_grass("green");
    add_item(({"path"}),
        "The path is little more than a well trodden, bare line " +
        "in the grass. On either sides of the path, tall " +
        "grasses, some flowers, and some bushes grow.\n");
    add_item(({"ground", "land", "field", "meadow","plains"}),
        "The ground is a sea of green grasses. Interspersed are " +
        "wildflowers and some bushes. The land is marshy " +
        "looking in spots from heavy rains or the occasional " +
        "flooding of the Anduin, depending on how close to the " +
        "river the land is.\n");
    add_item("sky",
        "It is @@day_desc@@. @@daylight_desc@@ fills the " +
        "sky.\n");
    add_item(({"flowers", "wildflowers"}),
        "Many different types of flowers grow here. Some are " +
        "tall, while others are short or even hidden among the " +
        "grasses, visible only when the grasses move. They are " +
        "different colors, shapes, and sizes.\n");
    add_item(({"grass", "grasses"}),
        "The grass is tall and moves about in the wind. It is a " +
        "healthy green color with various wildflowers growing " +
        "in it. Some bushes grow in the grass.\n");
    add_item(({"bushes", "bush"}),
        "The bushes grow scattered about the grass. They are " +
        "sparse, though healthy looking, and probably provide " +
        "limited protection for animals.\n");
    add_item(({"vales", "vales of anduin"}),
        "The Vales are made up of rolling hills, covered with " +
        "grasses and flowers.\n");
    add_item(({"hills", "rolling hills", "hill"}),
        "The hills are scattered about land. They are overgrown " +
        "with grass and wildflowers.\n");
    add_item(({"old forest road", "forest road", "road"}),
        "This is an ancient road that runs from the High Pass " +
        "of the Misty Mountains and across the Anduin. Brave " +
        "travellers and rumours say that the road continues " +
        "eastwards through the Mirkwood and beyond.\n");
    add_item("high pass",
        "You don't see the pass anywhere nearby.\n");
    add_item(({"grass seed heads", "seed heads"}),
        "The grass seed heads are as large as your hand, They " +
        "are ripe with seeds andcrown many of the grasses. The " +
        "heads wave gently in the breeze.\n");

    set_room_tell_time(random(ROOM_TELL_TIME) + 30);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Something rustles about in the grasses.");
    add_room_tell("Some clouds float lazily across the sky.");
    add_room_tell("A howl echos in the far distance.");
    add_room_tell("The grasses sway in the breeze.");
    add_room_tell("Some clouds drift by, blocking the " +
        "@@sun_moon@@.");
    add_room_tell("In the distance, a large bear stands up, " +
        "watches you, then disappears in the tall grass.");
    add_room_tell("A blackbird lands on a stiff grass stalk, " +
        "waving in the breeze.");
    
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

    create_vale_room();
    add_std_herbs("plain");
}

 
void
init()
{   
    ::init();
}

string road_desc1()
{
    return "The path winds its way through some bushes. ";
}

string road_desc2()
{
    return "The path wanders east and west. ";

} 

string road_desc3()
{
    return "The path crests a hill, giving a wide view of the " +
        "area. ";
} 

string road_desc4()
{
    return "The path runs east and west. ";
} 

string road_desc5()
{
    return "The bare path winds through the hills. ";
} 

string vale_desc1()
{
    return "Rolling hills stretch out in all directions, " +
        "allowing great places for wildlife and enemies to hide " +
        "behind. ";
}

string vale_desc2()
{
    return "The land is full of rolling grasslands. The land " +
        "teems with animals and life. ";
}

string vale_desc3()
{
    return "Large swathes of grass wave in the gentle breeze. " +
        "The ground is dotted with wildflowers, adding bursts " +
        "of color among the grasses. ";
}

string vale_desc4()
{
        return "The grass is a healthy color and as tall as you. " +
        "It is crowned with large seed heads that move gently " +
        "in the breeze. ";
}

string vale_desc5()
{
    return "Flowers grow scattered across the land among the " +
        "tall grasses. They provide a splash of color in the " +
        "verdant meadows here. ";
}


string vale_desc6()
{
    return "The ground is marshy this close to the river. It " +
        "teems with life that the river provides. ";
}

string vale_desc7()
{
    return "The land is a verdant green from the constant " +
        "swellings of the Anduin here. The ground is soft from " +
        "the excess water in the ground. ";
}

string vale_desc8()
{
    return "Small puddles form where you walk in this marshy " +
        "land. The ground is soaked with the recent flooding of " +
        "the Anduin. ";
}







public string
long_desc()
{
    string time;
    string desc;
    
    time  = CLOCK->query_time_of_day(),
    desc = CAP(query_short()) + ". ";

    if (!(CLOCK->query_war()))
    {
	desc += describe_time(time);
    }
    else 
    {
	desc += describe_war(time);
    }
    if (strlen(extraline))
	desc += (" " + extraline);
    if (functionp(vbfc_extra))
	desc += " " + vbfc_extra();
    return (desc);
}
