
#pragma strict_types
#pragma binary_save

#include "/d/Terel/include/Terel.h"
inherit LAST_DIR+"last_room";

#include <stdproperties.h>

void
create_room()
{
    set_short("Test room");
    Extraline = "This is my test room";
    add_road();
    add_mountain();
    create_last_room();
}
