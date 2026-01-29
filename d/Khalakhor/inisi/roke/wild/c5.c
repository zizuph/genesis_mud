/*
 * c4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

int sverd_kvar;

string
bfun()
{
    return "The boulder is huge and gray. It looks like it has " +
        "been here since the beginning of times. " +
        ((sverd_kvar) ? "Someone has put a sword into it. " : "") +
        "There are stains of blood on the stone, and " +
        "around it are small bloody wads of wool.\n";
}

int
pull(string str)
{
    NF(capitalize(query_verb()) + " what?\n");
    
    if (str != "sword")
        return 0;

    if (!sverd_kvar)
        return 0;
    
    if (query_verb() == "get" && present("sword", TO))
    {
        NF("The sword is most definitely stuck.\n");
        return 0;
    }
    
    write("The sword is most definitely stuck.\n");
    say(QCTNAME(TP) +
        " pulls the sword but it does not move the slightest.\n");
    return 1;
}

void
create_room()
{
    set_short("boulder cave");
    set_long("This cave has a nasty feeling about it. " + 
             "The walls are bare, and in the middle " +
             "of the room you notice a huge granite boulder.\n");

    add_item(({"boulder", "stone"}), "@@bfun");

    add_exit("c1", "east");

    reset_room();
}

void
reset_room()
{
    if (!sverd_kvar)
    {
        sverd_kvar = 1;
        add_item(({"sword", "sword in boulder", "sword in stone"}), 
                 "It's a glass sword. You can't really get a grip on how " +
                 "it got there.\n");
        /*"Close to its handle you notice a picture of " +
          "a Jabberwock.\n";*/
    }
}

void
init()
{
    ::init();

    add_action("sacrifice", "sacrifice");
    add_action("sacrifice", "sacrify");
    add_action("pull", "pull");
    add_action("pull", "get");
}

int
sacrifice(string s)
{
    object *ob, sheep;

    NF("Sacrifice what?\n");
    if (!s || s == "")
        return 0;

    NF("As you try to sacrifice the " + s +
       " the stone glows red, making you stop.\n");
    if (s != "sheep")
        return 0;

    ob = filter(all_inventory(TP) + all_inventory(TO), &->id("sheep"));
    ob = filter(ob, &->query_npc());
    
    if (sizeof(ob) == 0 || !objectp(sheep = ob[0]))
    {
        write("You hear a dark voice telling you: " +
              "I don't see any sheep here, heretic!\n");
        return 1;
    }

    sheep->remove_object();

    write("You kill the sheep and spread its blood on the stone, then " +
          "you tear it apart and throw the pieces all over the place.\n");
    say(QCTNAME(TP) +
        " kills the sheep and spreads its blood on the stone, then " +
        "spreads parts of the sheep all over the place.\n");

    if (sverd_kvar)
    {
        tell_room(this_object(),
                  "The sword falls from the boulder, down to the floor.\n");

        sverd_kvar = 0;
        remove_item("sword");
        remove_item("sword in boulder");
        remove_item("sword in stone");

        clone_object(ROKEDIR + "wep/jabsword")->move(TO);
    }

    return 1;
}
