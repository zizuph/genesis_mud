/*
 * cadu_m.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object mayor;

void
reset_room()
{
    if (mayor) return;

    mayor = clone_object(ROKEDIR + "npc/mayor");
    mayor->move(TO);
    tell_room(TO, "The mayor arrives from his inner chambers.\n");
}

void
create_room()
{
    set_short("The mayor's house");
    set_long("This is the house belonging to the Mayor of Cadu.\n" +
             "Here, in this room, the mayor receives hopeful " +
             "adventurers, much like yourself, that wish to work " +
             "for the city and solve various problems. A small sign " +
             "hangs on the wall.\n");

    add_item("sign", "It looks quite readable.\n");

    add_cmd_item("sign", "read",
                 "The mayor will be pleased to receive your help.\n" +
                 "Try 'ask assignment' to get an assignment. When you " +
                 "have performed your quest return to the mayor and " +
                 "'ask reward'.\n" +
                 "You can get your lost stuff back here. Type " +
                 "'restore me' to get what is rightfully yours.\n");

    add_exit("cadu_q1", "east");
    
    INSIDE;
    reset_room();
}

int
rest(string s)
{
    if (s != "me")
        return 0;

    TP->catch_msg("A weird looking spirit materializes before you. The " +
                  "spirit looks at you and suddenly it penetrates your " +
                  "skull, to search for information about your past " +
                  "inside your brain.\n");

    if (QDONE(ROKEGROUP, SKELETON) && !present("sppapp", TP))
    {
        TP->catch_msg("The spirit hands you a magic paper\n");
        clone_object(ROKEDIR + "obj/spellpaper")->move(TP);
    }

    if (QDONE(ROKEGROUP, BEGGARQUEST) && !present("ppapp",TP))
    {
        TP->catch_msg("The spirit gives you a small piece of paper, which " +
                      "looks much like the one you got from the beggar once.\n");
        clone_object(ROKEDIR + "obj/ppapp")->move(TP);
    }

    if (QDONE(ROKEGROUP, PAPERQUEST))
    {
        present("sppapp", TP)->transform_me();
        present("sppapp", TP)->fixa();
    }

    TP->catch_msg("The spirit tells you: If you still miss something that " +
                  "you have found around here, please be patient. We will " +
                  "bring it to you ASAP.\n");
    TP->catch_msg("You feel a little nauseous, and suddenly the spirit is gone.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(rest, "restore");
}
