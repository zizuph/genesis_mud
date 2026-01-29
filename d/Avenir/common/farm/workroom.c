#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";

void
create_room()
{
    set_short("The workroom");
    set_long("This seems to be a workroom. Facing the northern wall " +
        "is a small desk. It's placed close to the windows at the " +
        "south and east walls, most likely to be able to use the light " +
        "they provide. Behind the desk is a chair placed on a small " +
        "carpet.\n");
    add_item("carpet","You examine the small carpet with a brief glance. " +
        "Its worn out as if the user of the chair constantly moves " +
        "while he is working.\n");
    add_item("desk","You sit down in the chair and search the desk. " +
        "Nothing can be seen on top of it and pulling out the drawer " +
        "reveals nothing as it's completely empty.\n");
    add_item("chair","You try the chair and rest your legs. It's " +
        "perfect for your size and you can relax a bit.\n");
    add_item(({"window","windows"}),"When you walk towards the windows you " +
        "have problems deciding which window to look through.\n");
    add_item(({"floor","wall","walls","ceiling"}),"The walls, floor " +
        "and ceiling have all the touch of a typical room of a " +
        "mansion like this.\n");
    add_item("east window","@@desc_east_window@@");
    add_item("south window","@@desc_south_window@@");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("hall","west");
    reset_room();
}

void
reset_room()
{

}


string
desc_east_window()
{
object *ob, east_side;
    object *liv;
    string str;

    if (LOAD_ERR(THIS_DIR + "east_side"))
        return "You look out of the window but fail to see anything of " +
        "interest.\n";


    east_side = find_object(THIS_DIR + "east_side");

    if (!east_side)
        return "You look out of the window but fail to see anything of " +
        "interest.\n";


    if (east_side->query_prop(OBJ_I_LIGHT) <= 0)
        return "You look out to the east side of the house but its dark. " +
        "You cant see anything out there.\n";

    ob = FILTER_CAN_SEE(all_inventory(east_side), TP);

    if (!sizeof(ob))
        return "You look out of the window but fail to see anything of " +
        "interest.\n";

    return "When you look out of the window you see "
        + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
}

string
desc_south_window()
{
object *ob, south_side;
    object *liv;
    string str;

    if (LOAD_ERR(THIS_DIR + "south_side"))
        return "You look out of the window but fail to see anything of " +
        "interest.\n";


    south_side = find_object(THIS_DIR + "south_side");

    if (!south_side)
        return "You look out of the window but fail to see anything of " +
        "interest.\n";


    if (south_side->query_prop(OBJ_I_LIGHT) <= 0)
        return "You look out to the south side of the house but its dark. " +
        "You cant see anything out there.\n";

    ob = FILTER_CAN_SEE(all_inventory(south_side), TP);

    if (!sizeof(ob))
        return "You look out of the window but fail to see anything of " +
        "interest.\n";

    return "When you look out of the window you see "
        + COMPOSITE_WORDS(map(ob, "desc", TO)) + ".\n";
}

string
desc(object ob)
{
    if (living(ob))
        return LANG_ADDART(ob->query_race_name());
    else
        return LANG_ADDART(ob->short());
}
