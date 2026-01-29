#include "/d/Emerald/common/guild/vamp/guild.h"

inherit VAMP_ROOM_DIR + "vamp_room";

#include "defs.h"
#include <stdproperties.h>

#define OTHER_ROOM (GRAVEYARD_DIR + "under_church05")
#define TELL_OTHER(msg) tell_room(OTHER_ROOM, msg);

void open1();
void open2();
void open3();
void open4();
void open5();
void open6();
void open7();

static object door;
static int alarm_id = 0;

void
create_vamp_room()
{
    set_short("Sun chamber");
    set_long("   The walls of this small, circular chamber are covered " +
        "with a highly reflective, polished metal.  Looking up at the " +
        "ceiling, you notice that it is formed by eight wedge-shaped " +
        "panels.\n");

    add_item(({ "wall", "walls", "metal", "polished metal", "reflective metal",
                "reflective polished metal", "metal walls" }),
        "The walls are covered with sheets of polished metal.  They are " +
        "quite reflective--so much so that you can see your reflection " +
        "quite clearly.\n");

    add_item(({ "ceiling", "panels", "wedge-shaped panels",
                "wedge shaped panels", }),
        "Eight wedge-shaped panels form the ceiling.  It looks as if they " +
        "open to the outside.\n");

    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_INSIDE, 1);

    setuid();
    seteuid(getuid());

    door = clone_object(GRAVEYARD_DIR + "obj/door");
    door->set_other_room(GRAVEYARD_DIR + "under_church05");
    door->set_pass_command(({ "east", "e", "enter" }));
    door->move(this_object(), 1);
}

void
start_open()
{
    if (!alarm_id)
    {
        alarm_id = set_alarm(1.0, 0.0, open1);
    }
}

void
open1()
{
    TELL_OTHER("You hear a loud clank from behind the wall.\n");
    tell_room(this_object(), "You hear a loud clank from behind the wall.\n");
    alarm_id = set_alarm(7.0, 0.0, open2);
}

void
open2()
{
    door->auto_close();
    alarm_id = set_alarm(2.0, 0.0, open3);
}

void
open3()
{
    tell_room(this_object(), "The ceiling panels begin to open slowly, " +
        "allowing the sunlight to pour in, reflecting off the mirrored " +
        "walls, and focusing on the floor where you stand.\n");
    add_prop(ROOM_I_LIGHT, 3);
    alarm_id = set_alarm(4.0, 0.0, open4);
}

void
open4()
{
    tell_room(this_object(), "The ceiling opens up further, intensifying " +
        "the sunlight.\n");
    add_prop(ROOM_I_LIGHT, 20);
    alarm_id = set_alarm(6.0, 0.0, open5);
}

void
open5()
{
    tell_room(this_object(), "The ceiling opens completely.  Blazing " +
        "sunlight streams down on you from above.\n");
    add_prop(ROOM_I_LIGHT, 60);
    alarm_id = set_alarm(6.0, 0.0, open6);
}

void
kill_if_not_dead(object vamp)
{
    if (vamp->query_ghost() || vamp->query_wiz_level())
    {
        return;
    }

    vamp->heal_hp(-vamp->query_hp());
    vamp->vampire_death(this_object());
}

void
open6()
{
    map(VAMPS(all_inventory(this_object())), kill_if_not_dead);
    alarm_id = set_alarm(4.0, 0.0, open7);
}

void
open7()
{
    alarm_id = 0;
    tell_room(this_object(), "The ceiling panels slide back into place.\n");
    add_prop(ROOM_I_LIGHT, -2);
    door->auto_open();
    
    setuid();
    seteuid(getuid());
    OTHER_ROOM->open_complete();
}
