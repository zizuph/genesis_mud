/*
 * s2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

void
create_room()
{
    set_short("top of stone pillar");
    set_long("You are standing on the top of a huge stone pillar.\n" +
             "Far down below you is a sea of boiling lava, and in " +
             "front of you someone has built a stone altar. This must " +
             "be a holy place of some strange religion. There is also " +
             "a small hole in the pillar in front of the altar.\n");

    add_item("altar", "The altar is very old and made of pure mithril. " +
             "Someone has scribed an ancient legend on the top of it.\n");

    add_item("hole", "It is very deep and reaches all the way through the " +
             "pillar. Deep down you think you see some glowing lava.\n");

    add_exit("s1", "down");
}

void
summon(object tp)
{
    object spirit;
    set_this_player(tp);
    write("As the bottle hits the lava far below a strange mist is " +
          "created by the water.\n");
    say("A strange mist emerges from the hole.\n");
    spirit = clone_object(ROKEDIR + "npc/car_spirit");
    spirit->move_living("from the strange mist", TO);
    spirit->summoner(tp);
}

int
drop(string s)
{
    object b;

    NF("drop what in where?\n");

    if (s != "bottle in hole" && s != "bottle hole" && s !=
        "bottle into hole")
        return 0;

    NF("You don't have a suitable bottle to drop!");

    b = present("he-he-spirit-quest-parcel", TP);

    if (!objectp(b))
        return 0;

    write("You drop the bottle into the hole.\n");
    say(QCTNAME(TP) + " drops a bottle in the hole.\n");

    if (present("water", b))
        set_alarm(7.0, 0.0, &summon(TP));
    else
        write("Too bad it was empty.\n");
    b->remove_object();
    return 1;
}

int
read(string s)
{
    NF("read what?\n");
    if (s != "altar" && s != "legend")
        return 0;

    say(QCTNAME(TP) + " reads on the altar.\n");

    write("You read the ancient legend:\n" +
          "A bottle, blue and green, full with water to make steam,\n" +
          "raising spirit of the pole, when you drop it in the hole.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(read, "read");
    add_action(drop, "drop");
}
