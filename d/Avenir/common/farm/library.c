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
    set_short("The library");
    set_long("This is the library of this manor. Not much of " +
        "a library though. There is only one bookshelf placed along " +
        "the northern wall. Close to the shelf is a table with two " +
        "reading chairs on each side. The whole room is covered by a " +
        "huge red carpet of unknown design. In the south and west " +
        "walls are two small windows.\n");
    add_item("carpet","You bend down and touch the thick red carpet. " +
        "It's soft and you feel your feet sink down into it. Looking at " +
        "the pattern makes you dizzy and you take your eyes away " +
        "from it.\n");
    add_item("pattern","You try to find any symmetry with " +
        "the pattern on the carpet. Alas, even if there " +
        "was anything symmetric about it, you fail to see " +
        "it so you leave it for someone else to watch.\n");
    add_item(({"shelf","bookshelf","books"}),"You walk along the shelf " +
        "and thumb the various volumes. Most of them seem to be about " +
        "practical things like gardening, fishing and cooking. One part " +
        "of the shelf seems to contain some well thumbed books from " +
        "older days.\n");
    add_item(({"stains","oil"}), "On the table are a few old stains, " +
        "most likely made by a leaking oil lamp.\n");
    add_item(({"well thumbed books","thumbed books","volumes"}),"You " +
        "take a volume from the shelf and read:" +
        "\n\nThe complete book of knots.\n\n " +
        "You browse through a few pages and put it back on its place.\n");
    add_item("table","You look at the table and see a few stains of " +
        "oil. Most likely it is normally used for a reading lamp but " +
        "when you turn around you can't find a lamp in the room.\n");
    add_item(({"chair","chairs","reading chairs"}),"You try one of the " +
        "chairs but it is quite uncomfortable so you stand up again.\n");
    add_item(({"window","windows"}),"There is one window in the south " +
        "wall and one window in the west wall. Which window do you mean?\n");
    add_item("stains","The stains are almost gone. Probably someone " +
        "tried to remove them, but didnt completely succeed.\n");
    add_item(({"floor","wall","walls","ceiling"}),"The walls, floor " +
        "and ceiling have all the touch of a typical room of a " +
        "mansion like this.\n");
    add_item("west window","@@desc_west_window@@");
    add_item("south window","@@desc_south_window@@");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("hall","east");
    reset_room();
}

void
reset_room()
{

}

void
init()
{
    ::init();
        add_action("get_book","get");
}

string
desc_west_window()
{
object *ob, west_side;
    object *liv;
    string str;

    if (LOAD_ERR(THIS_DIR + "west_side"))
        return "You look out of the window but fail to see anything of " +
        "interest.\n";

    west_side = find_object(THIS_DIR + "west_side");

    if (!west_side)
        return "You look out of the window but fail to see anything of " +
        "interest.\n";


    if (west_side->query_prop(OBJ_I_LIGHT) <= 0)
        return "You look out to the west side of the house but its dark. " +
        "You cant see anything out there.\n";

    ob = FILTER_CAN_SEE(all_inventory(west_side), TP);

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
        return  "You look out of the window but fail to see anything of " +
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

int
get_book(string str)
{
    if (strlen(str) && ((str == "book") || (str == "thumbed book")))
    {
        write("You browse through a few pages and put it back on its place.\n");
        return 1;
    }
    return 0;

}
