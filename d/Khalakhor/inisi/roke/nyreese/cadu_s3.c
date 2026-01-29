/*
 * cadu_s3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * 2018-04-16 Malus: Reset isbuilding variable when player leaves the room,
 *                   which blocked the quest until Armageddon
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object castle;
int isbuilding = 0;

void build_two(object ob);
void build_three(object ob);

void
reset_room()
{
    if (!castle) return;

    tell_room(TO, "The tide flows in, ruining the former mighty castle.\n");
    castle->remove_object();
    (NYREESEDIR + "sandcastle")->destruct_castle();
}

void
create_room()
{
    set_short("Shore");
    set_long("You are walking on the shore south of Cadu.\n" +
             "To your east you can find the harbour of Cadu. " +
             "The shore continues to the west for what seems like an eternity. " +
             "Beneath your feet you can see a thick layer of white sand. " +
             "Someone has recently built a small hut north of here.\n");

    add_item("sand", "It would be perfect to use for building a castle.\n");

    BEACH;

    add_exit("cadu_s2", "east");
    add_exit("cadu_s4", "west");
    add_exit("cadu_h3", "north");
  
    add_item("hut", "A sign on the hut says: This is the shop of Gandril the Tailor.\n");

}

int
build(string s)
{
    NF("What do you want to build?\n");
    if (s != "castle" && s != "sandcastle" && s != "sand castle")
        return 0;

    NF("Someone has already built a castle!\n");
    if (castle) return 0;

    NF("Someone is already doing that.\n");
    if (isbuilding) return 0;

    TP->catch_msg("You begin to build a castle.\n");
    say(QCTNAME(TP) + " starts to do something with the sand.\n");
    isbuilding = 1;

    set_alarm(4.0, 0.0, &build_two(TP));
    return 1;
}

void
build_two(object ob)
{
    if (!present(ob, TO))
    {
        isbuilding = 0;
        return;
    }

    ob->catch_msg("The castle starts to look good! It will most likely be "+
                  "completed soon!\n");
    set_alarm(4.0, 0.0, &build_three(ob));
}

void
build_three(object ob)
{
    isbuilding = 0;
    if (!present(ob, TO))
        return;
    set_this_player(ob);
    TP->catch_msg("You have built an extremly large castle. It is so large " +
                  "that it might just be possible to enter it!\n");
    say(QCTNAME(TP) + " has completed " + TP->query_possessive() +
        " sand castle!\n");
  
    castle = clone_object(ROKEDIR + "obj/sandcastle");
    castle->move(TO);
}

void
init()
{
    ::init();
    add_action(build, "build");
}

