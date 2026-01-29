/* File:          /d/Khalakhor/ship/macdunn/under_pier.c
 * Creator:       Teth
 * Date:          April 22, 1997
 * Modifications: November 29, 1997, Teth, added terrain types
 * Purpose:       In this room, players are able to scrape off
 *                barnacles from the moorings. These may be used
 *                used as a component or quest item.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/barnacle.c
 *                /d/Khalakhor/common/wep/splinter.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/room";
#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
inherit HERBSEARCH;

string *herbs = HERBMASTER->query_herbs(({TERRAIN_BAY,}));

int spl, bar;
object splinter, barnacle;

public void
reset_room()
{
    spl = 0;
    bar = 0;
    set_searched(0);
}

public void
create_khalakhor_room()
{
    set_short("Under the pier");
    set_long("   The pier where the boats dock rests above you. " +
      "The water surrounding you is salty, as this is Cala " +
      "Fasgadh, an oceanic harbour. One mooring is close by, " +
      "although many support the pier. Wooden barricades prevent " +
      "movement in the north and south directions, but you can swim " +
      "east or west.\n");
    add_item("pier","The pier above you is held in place by the " +
      "moorings. It is solid in construction.\n");
    add_item("boats","There are a few boats in the harbour, but " +
      "none offer a way to board them.\n");
    add_item("boat","Each boat is different.\n");
    add_item(({"water","salt water","salty water"}),"The water, which " +
      "is the essential element of the harbour, is salty. It is " +
      "rather clean, however.\n");
    add_cmd_item(({"water","salt water","salty water","clean water",
        "the water","the salt water","the salty water",
        "the clean water","from the harbour"}), ({"drink","taste",
        "gulp","swallow"}),"The water is not potable, and you are " +
      "forced to spit it out.\n");
    add_item(({"harbour","oceanic harbour","cala","cala fasgadh"}),
      "The harbour extends to the southwest, where it meets Lear " +
      "Min, the sea, which cannot be seen from here.\n");
    add_item(({"mooring","near mooring","nearby mooring"}),"The " +
      "mooring is a long pole set in the water, and used to " +
      "support the pier. It is covered with barnacles.\n");
    add_cmd_item(({"mooring","nearby mooring","pole","long pole",
      "cedar","cedar pole","tough wood"}),"splinter","@@get_splinter");
    add_item(({"barnacles","invertebrates","crustaceans"}),"The " +
      "barnacles are invertebrates, which secure themselves tightly " +
      "to most surfaces. They are filter-feeders, perhaps a reason " +
      "why the water here is quite clean.\n");
    add_cmd_item(({"barnacles","invertebrates","crustaceans",
        "off barnacles","off invertebrates","off crustaceans","barnacle",
        "crustacean","invertebrate","off barnacle","off invertebrate",
        "off crustacean"}), ({"cut","pry","release"}),"@@get_barnacle");
    add_item(({"pole","long pole"}),"The long pole which is the " +
      "mooring is made of a tough wood.\n");
    add_item(({"wood","tough wood"}),"The wood appears to be cedar, " +
      "a tree which grows in swampy areas. With a straight grain, " +
      "cedar is easy to splinter. It is very resistant to " +
      "water rot.\n");
    add_item(({"cedar","cedar pole"}),"It stands tall and true.\n");
    add_item(({"grain","straight grain"}),"The straight grain " +
      "of the cedar makes it easy to splinter.\n");
    add_item("moorings","The moorings support the pier above you.\n");
    add_item(({"barricades","wooden barricades"}),"The barricades " +
      "are used to prevent or reduce wave action.\n");
    add_item(({"barricade","wooden barricade"}),"Both barricades " +
      "appear the same.\n");
    add_cmd_item(({"barricade","wooden barricade","barricades",
        "wooden barricades"}),({"break","destroy"}),"Nothing you " +
      "do puts a dent in either of the barricades!\n");
    add_item("sky","The semi-cloudy sky can only be seen out from " +
      "beneath the edges of the pier.\n");
    add_cmd_item("east","swim","@@go_east");
    add_cmd_item("west","swim","@@go_west");
    add_cmd_item(({"northwest","northeast","north","southeast",
        "southwest","south"}),"swim","The way is blocked by a wooden " +
      "barricade.\n");
    add_cmd_item("down",({"swim","dive"}),"You dive down into the water, " +
      "but nothing catches your attention, so you return to the " +
      "surface.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_BAY);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
      ONE_OF(herbs)}),({"water","here"}),2);

    reset_room();

    seteuid(getuid());
}

public int
get_barnacle()
{
    if (this_player()->query_weapon(-1) == ({})) 
    {
        write("You are unable to loosen any barnacles without a " +
          "tool!\n");
        say(QCTNAME(TP) + " attempts to pry off barnacles from the mooring " +
          "without a tool, and fails.\n");
        return 1;
    }

    if (bar > 4)
    {
        write("There are no barnacles that you are able to " +
          "loosen.\n");
        say(QCTNAME(TP) + " attempts to pry off a barnacle from the " +
          "mooring, but there are none that " + HE + " is able to " +
          "loosen.\n");
        return 1;
    }

    write("You are able to pry off a barnacle from the mooring!\n");
    say("With some effort, " + QCTNAME(TP) + " is able to pry off " +
      "a barnacle from the mooring!\n");
    barnacle = clone_object(MACDUNN_DIR + "barnacle");
    barnacle->move(this_player(), 1);
    bar = bar + 1;
    return 1;
}

public int
get_splinter()
{
    if (this_player()->query_weapon(-1) == ({})) 
    {
        write("You are unable to splinter the mooring without a " +
          "tool!\n");
        say(QCTNAME(TP) + " attempts to splinter wood from the mooring " +
          "without a tool, and fails.\n");
        return 1;
    }

    if (spl > 4)
    {
        write("The mooring has yielded all possible splinters already.\n");
        say(QCTNAME(TP) + " attempts to splinter the mooring, " +
          "but " + HE + " finds that the mooring will not yield any " +
          "splinters at the moment.\n");
        return 1;
    }

    write("You splinter the mooring, leaving a piece of wood " +
      "floating on the water!\n");
    say(QCTNAME(TP) + " splinters the mooring, leaving a piece of " +
      "wood floating on the water!\n");
    splinter = clone_object(COM_WEP + "splinter");
    splinter->move(this_object(), 1);
    spl = spl + 1;
    return 1;

}

public string
go_east()
{
    write("You swim towards the east shore, from under the pier.\n");
    set_dircmd("east");
    TP->move_living("swims east",MACDUNN_DIR + "tide2", 0, 0);
    return "";
}

public string
go_west()
{
    write("You swim towards the west shore, from under the pier.\n");
    set_dircmd("west");
    TP->move_living("swims west",MACDUNN_DIR + "tide1", 0, 0);
    return "";

}

