/*
 *  /d/Gondor/guilds/rangers/north/start.c
 *
 *  The startroom of the North Headquarters
 *
 *  Coded by Elessar
 *    Modified by Alto & Gwyneth, 14 July 2001, changed to fit revised themes
 *
 */
inherit "/d/Gondor/std/room.c";

#include "../rangers.h"
inherit RANGERS_NOR_DIR + "north_funcs.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "check_exit.c"

public string      long_desc();
static object      Tstand;
void
hideout_add_torch()
{
    object *inv;

    inv = all_inventory(this_object());

    if (!sizeof(filter(inv, &->id("torchstand"))))
    {
        Tstand = clone_object(OBJ_DIR + "torchstand");
        Tstand->set_time(1999);
        Tstand->set_lit(1);
        Tstand->set_replace_msg("An apprentice ranger slips quietly into "
            + "the room and places a new torch in the iron stand. After "
            + "lighting the new torch, the apprentice bustles away and "
            + "disappears around a corner.\n");
        Tstand->set_no_desc(1);
        Tstand->remove_prop(CONT_I_ATTACH, 1);
        Tstand->move(TO);
    }
}

/*
 * Function name: daylight
 * Description  : return lightlevel of room
 * Returns      : 0 if evening/night, 1 otherwise
 */
public int
daylight()
{
    string timestr = tod();
    if (timestr == "night" || timestr == "evening")
        return 0;
    return 1;
}


string
long_desc()
{
    return "As you enter this room, you think you have entered a forest "
        + "in moonlight. The pillars of this room have been sculpted into "
        + "the semblance of trees. Softened light from muted torches gives "
        + "the room a peaceful atmosphere. Hidden discreetly behind the "
        + "pillars are some darkened alcoves. Rangers of the North should "
        + "'start here' to sleep in this place when not on active duty. "
        + "Just east of here is a small room filled with what appear to "
        + "be numerous racks and shelves.\n";
}

public void
create_gondor()
{
    set_short("the sleeping quarters of the Northern Rangers");
    set_long(&long_desc());

    north_add_items();

    add_item(({"room", "quarters", "sleeping quarters"}), &long_desc());
    add_item(({"pillar", "pillars"}), "The pillars are beautifully sculpted, "
        + "and you almost need to touch them to realize that they are not "
        + "real trees.\n");
    add_item(({"forest"}), "Of course it is not a real forest, but so "
        + "real does it seem that you can almost hear owls calling in the "
        + "night.\n");
    add_item(({"tree", "trees"}), "On close inspection, you realize that "
        + "these are actually pillars of stone, cleverly sculpted to "
        + "resemble real trees.\n");
    add_item(({"alcove", "alcoves", "hidden alcove", "hidden alcoves",
        "form", "forms"}), "Shh! This is where the Rangers of the North "
        + "sleep when not on active duty. A number of grey-swathed "
        + "sleeping forms can be seen in some of the alcoves. Speak "
        + "quietly so they are not disturbed.\n");
    add_item(({"rack", "shelf", "racks", "shelves"}), "From here it is "
        + "difficult to make out the contents of the racks and shelves. Why "
        + "don't you walk east and investigate?\n");
    add_item(({"sentinel", "grey-cloaked sentinel"}), "You are too late! "
        + "Ranger sentinels are usually too busy with their duties to "
        + "stand around long enough to be looked at.\n");
    add_item(({"torches", "torch", "muted torches"}), "The "
        + "torches have been covered to provide enough light "
        + "to find one's way around, yet the light is soft enough "
        + "to allow sleep.\n");

    set_alarm(1.1, 0.0, &add_prop(ROOM_I_LIGHT, &daylight()));

    reset_room();

    add_exit(RANGERS_NOR_DIR + "song_room", "south");
    add_exit(RANGERS_NOR_DIR + "closet", "north");
    add_exit(RANGERS_NOR_DIR + "r_corridor", "east");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
}

int
start(string str)
{
    object tp = this_player();

    if (!strlen(str) || lower_case(str) != "here")
    {
        notify_fail("Start here?\n");
        return 0;
    }

    if (!NORTH_MEMBER(tp) && !MANAGER->query_voted_in(tp->query_real_name(),
         "north"))
    {
        notify_fail("Only Rangers of the North may sleep here!\n");
        return 0;
    }
    else if (tp->set_default_start_location(RANGERS_NOR_START))
    {
        write("You decide to start your day out here.\n");
        return 1;
    }
    else
    {
        notify_fail("Some problem prevents you from starting here.\n"
            + "Please make a bug report.\n");
        return 0;
    }
}

void
init()
{
    ::init();

    add_action(start, "start");
}


void
reset_room()
{
    set_alarm(5.0, 0.0, &hideout_add_torch());
}