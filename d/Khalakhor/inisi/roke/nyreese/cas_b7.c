/*
 * cas_b7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This is a large hall in the heart of the castle. It has " +
             "probably been used for gigantic dinners with hundreds of " +
             "people. At the east wall is a huge fireplace. " +
             "This much space makes you feel a bit tiny.\n");

    add_item("fireplace",
             "It's big enough for you to stand up inside of it. " +
             "There are some ashes left here, but it appears to have " +
             "been out of use for a long time.\n");
    add_cmd_item("fireplace", "enter",
                 "You study the fireplace again and decide that it is too dirty " +
                 "to enter.\n");
    add_item("ashes", "The ashes are cold.\n");

    add_exit("cas_b6", "west");

    reset_room();
}

void
reset_room()
{
    if (!present("ironpot", TO))
    {
        tell_room(TO, "An iron pot arrives through the chimney.\n");
        clone_object(ROKEDIR + "obj/ironpot")->move(TO);
    }

    if (knight)
        return;
    knight = clone_object(ROKEDIR + "npc/knights");
    knight->equip_me();
    knight->move(TO);
    tell_room(TO, "A knight steps out of the shadows.\n");
}
