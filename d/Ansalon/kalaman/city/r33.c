#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

inherit CITY_OUT;

#define OTHER_ROOM CITY + "outside_wall"
#define SECRET_DOOR KOBJ + "secret_doora"

int dAlarm_id1;
object door;

void remove_door();

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Cobbled street by the city wall");

    add_item(({"city wall","wall"}),"@@secret_door");
    add_item(({"stone panel","panel"}),"@@see_panel");

    add_exit(CITY + "r34","east",0);
    add_exit(CITY + "r32","northwest",0);

    add_item_city();

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand on a cobbled street in the southern district of " +
    "Kalaman. " + tod_descr1() + season_road() + 
    "To the south, the great city wall rises.\n";
}

string
secret_door()
{
    if(TP->query_skill(SS_AWARENESS) < 25)
    {
	return "To the south rises the great wall that surrounds Kalaman. " +
	"\n";
    }
    return "To your south rises the great wall that surrounds Kalaman. You notice " +
    "a hidden stone panel set into the wall.\n";
}

string
see_panel()
{
    if(TP->query_skill(SS_AWARENESS) < 25)
    {
	return "You cannot find what you are looking for.\n";
    }
    return "A small stone panel has been set into the wall of the city. " +
    "You could probably push it.\n";
}

init()
{
    ::init();
    ADA("push");
}

#include "secret_door.h"
