/* File:          /d/Khalakhor/ship/macdunn/shore1.c
 * Creator:       Teth
 * Date:          November 28, 1997
 * Modifications: December 5, 1997, Teth, added rocks that can be chipped
 * Purpose:       This is a room from which players can climb back
 *                up to the piers.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/common/obj/stone.c
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/room";
#include "local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
inherit HERBSEARCH;

string *herbs = HERBMASTER->query_herbs(({TERRAIN_COAST,}));

int rock;
object stone;

public void
reset_room()
{
    rock = 0;
    set_searched(0);
}

public void
create_khalakhor_room()
{
    set_short("near the rocky shore");
    set_long("   Cala Fasgadh surrounds you with its salty oceanic water. " +
      "The harbour extends outward to the west and south, while nearby to " +
      "the north is a rocky shore. The pier of Port Macdunn " +
      "stands to the east, its moorings deep in the water. One mooring " +
      "has handholds.\n");
    add_item("pier","The pier to the east stands on moorings.\n");
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
    add_item("moorings","The moorings stand tall, and support the pier. " +
      "They seem to be covered with a whitish substance, at least the " +
      "near-water portions.\n");
    add_item(({"substance","whitish substance","near-water portions",
        "portions"}),"The portions of the moorings with the whitish " +
      "substance are too far away to make out any details.\n");
    add_item("mooring","The mooring with handholds seems to present " +
      "an escape from these waters.\n");
    add_item(({"holds","handholds","grips"}),"They are present all " +
      "the way up the mooring, allowing escape from the water.\n");
    add_item(({"shore","rocky shore"}),"The rocks on the shore " +
      "prevent anyone from reaching dry land through them.\n");
    add_item("rocks","The rocks have razor-sharp edges and would " +
      "cut anyone attempting to pass through them.\n"); 
    add_item("waves","The waves are unusually high for a peaceful " +
      "harbour.\n");
    add_item("sky","The semi-cloudy sky above you is a typical " +
      "coastal sky.\n");
    add_item("clouds","The clouds above are grey and streaky.\n");
    add_item("cloud","Each cloud looks about the same, although " +
      "location and size differ.\n");
    add_cmd_item("south","swim","@@go_south");
    add_cmd_item(({"east","southeast"}),"swim","The pier prevents you " +
      "from swimming in that direction.\n");
    add_cmd_item(({"northwest","northeast","north"}),"swim","The rocky " +
      "shore prevents you from swimming in that direction.\n");
    add_cmd_item("west","swim","@@go_west");
    add_cmd_item("southwest","swim","A wave "+
      "pushes you back to where you were before.\n");
    add_cmd_item("down",({"swim","dive"}),"You dive down into the water, " +
      "but nothing catches your attention, so you return to the " +
      "surface.\n");
    add_cmd_item(({"rocks","through rocks"}),({"pass","move","climb"}),
      "@@go_rocks");
    add_cmd_item(({"holds","handholds","grips","mooring","up"}),
      ({"climb","use","scale"}),"@@go_up");
    add_cmd_item(({"rocks","sharp rocks","rock","sharp rock"}),
      ({"chip","break","crack","smash"}),"@@get_rock");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
    add_prop(OBJ_I_LIGHT, 1);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_COAST);
    set_up_herbs(({ONE_OF(herbs), ONE_OF(herbs), ONE_OF(herbs),
      ONE_OF(herbs)}),({"water","here"}),2);

    reset_room();

    seteuid(getuid());
}

public string
go_south()
{
    write("You swim towards the main harbour.\n");
    set_dircmd("south");
    TP->move_living("swims south",MACDUNN_DIR + "tide1", 0, 0);
    return "";
}

public string
go_up()
{
    write("You scale the mooring easily.\n");
    set_dircmd("up");
    TP->move_living("climbs the mooring",MACDUNN_DIR + "pier1", 0, 0);
    return "";

}

public string
go_rocks()
{
    write("You try to climb through the rocks, but find no route. " +
      "Instead, you are injured on the sharp edges.\n");
    say(QCTNAME(this_player()) + " attempts to climb through the rocks " +
      "but finds no passage.\n");
    this_player()->heal_hp(-50);
    if (this_player()->query_hp() <= 0)
    {
        this_player()->do_die();
    }
    return "";
}

public int
get_rock()
{
    if (this_player()->query_weapon(-1) == ({})) 
    {
        write("You are unable to break the rocks without a tool!\n");
        say(QCTNAME(TP) + " attempts to break the rocks lining the shore " +
          "without a tool, and fails.\n");
        return 1;
    }

    if (rock > 4)
    {
        write("Try as you might, you are unable to break any of the " +
          "rocks.\n");
        say(QCTNAME(TP) + " attempts to break the rocks lining the shore, " +
          "but " + HE + " finds that the rocks will not yield to " +
          HIS + " effort.\n");
        return 1;
    }

    write("You break a piece of stone from the rocks lining the " +
      "shore!\n");
    say(QCTNAME(TP) + " breaks a piece of stone from the rocks lining " +
      "the shore!\n");
    stone = clone_object(COM_OBJ + "stone");
    stone->move(this_object(), 1);
    rock = rock + 1;
    return 1;
}
 
public string
go_west()
{
    write("You swim out along the shoreline to the west.\n");
    set_dircmd("west");
    TP->move_living("swims west",MACDUNN_DIR + "shore0", 0, 0);
    return "";
}

