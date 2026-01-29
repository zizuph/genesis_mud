/* File:          /d/Khalakhor/ship/macdunn/tide1.c
 * Creator:       Teth
 * Date:          April 25, 1997
 * Modifications: November 20, 1997, Teth, added drowning
 * Purpose:       This is the room that players can jump into from
 *                the western piers.
 * Related Files: /d/Khalakhor/ship/macdunn/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
#include "local.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "/d/Khalakhor/sys/paths.h"
inherit HERBSEARCH;

string *herbs = HERBMASTER->query_herbs(({TERRAIN_BAY,}));

public void do_drown(object ob);

public void
reset_room()
{
    set_searched(0);
}

public void
create_room()
{
    set_short("In the harbour, near the shore");
    set_long("Cala Fasgadh surrounds you with its salty oceanic water. " +
      "The harbour extends outward to the west and south, while to " +
      "the north it reaches a rocky shore. The pier of Port Macdunn " +
      "stands to the east, its moorings deep in the water.\n");
    add_item("pier","The pier to the east stands on moorings. Swimming " +
      "east would take you under the pier.\n");
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
    add_item("mooring","No specific mooring captures your attention.\n");
    add_item(({"shore","rocky shore"}),"The rocky shore can be " +
      "reached by swimming north. Waves splash against the rocks.\n");
    add_item("waves","The waves are unusually high for a peaceful " +
      "harbour.\n");
    add_item("sky","The semi-cloudy sky above you is a typical " +
      "coastal sky.\n");
    add_item("clouds","The clouds above are grey and streaky.\n");
    add_item("cloud","Each cloud looks about the same, although " +
      "location and size differ.\n");
    add_cmd_item("north","swim","@@go_north");
    add_cmd_item("east","swim","@@go_east");
    add_cmd_item(({"northwest","northeast","west","southeast",
        "southwest","south"}),"swim","A wave pushes you back to where " +
      "you were before.\n");
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

public string
go_east()
{
    write("You swim underneath the pier.\n");
    set_dircmd("east");
    TP->move_living("swims east",MACDUNN_DIR + "under_pier", 0, 0);
    return "";
}

public string
go_north()
{
    write("You swim towards the north shore.\n");
    set_dircmd("north");
    TP->move_living("swims north",MACDUNN_DIR + "shore1", 0, 0);
    return "";

}

public void
enter_inv(object ob,object old)
{
    ::enter_inv(ob,old);

    if (interactive(ob))
    {
        if (ob->query_skill(SS_SWIM) <= 9  &&
           (!(ob->query_prop(MAGIC_I_BREATH_WATER))))
        {
            ob->catch_msg("You drown in the deep waters of the harbour.\n");
            tell_room(environment(),QCTNAME(ob) + " struggles for a short "+
              "amount of time, but then drowns.\n,ob");
            ob = this_player();
            set_alarm(0.0,0.0,&do_drown(ob));
            return;
        }

    }
}

public void
do_drown(object ob)
{
    ob->heal_hp(-10000);
    if (ob->query_hp() <= 0)
    {
        ob->do_die();
    }
}

