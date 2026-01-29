/*
 * Temple of Myrkul
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";
inherit "/d/Faerun/std/cmd_parse";
inherit BASE_TEMPLE;
inherit TYMORA_DIR + "info";

#define OUT_DIR ""

void
create_room()
{
    ::create_room();
    add_prop(ROOM_I_INSIDE, 1);

    donate_box("Tymora");

    set_short("Inside the temple of " + deity_name);
    set_long("This is the inside of the temple of " + deity_name +
        ", the goddess of good fortune and adventurers. A statue of the " +
        "goddess stands in the center of the temple. Dried shamrocks " +
        "decorate the walls. There is a sign on a wall to read and an " +
        "iron box next to the statue.\n");

    add_item(({"statue", "tymora"}),
        "That statue is set in the center of of the temple. It is carved of marble.\n");
    add_item(({"walls"}),
        "They are made of stone blocks. The walls are smooth and decorated with dried shamrocks.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of wood. It has been lovingly squared and polished to a deep color.\n");
    add_item(({"shamrocks", "dried shamrocks"}),
        "They are the leaves of clover. Each leaf has four segments and represent good luck. They hang on the walls, and many have dried.\n");

    add_exit(OUT_DIR + "", "out");
}


void
init()
{
    ::init();

    add_action("insert","insert");
    add_action("insert","drop");
}

int
insert(string s)
{
    object token;

    FIXEUID;

    NF("Insert what into what?\n");
    if (!s) return 0;

    if(!parse_command(s,TO,"[platinum] 'coin' 'in' / 'into' [the] [iron] 'box'"))
        return 0;

// check alignment
    switch(min_guild)
    {
        case AL_GOOD:
            if(TP->query_alignment() < min_guild)
            {
                write("\nYour alignment is too low for " + deity_name +
                ". Your request is denied.\n\n");
                return 1;
            }
        break;
        case AL_EVIL:
            if(TP->query_alignment() > min_guild)
            {
                write("\nYou are too good to be a follower of " + deity_name +
                ". Your request is denied.\n\n");
                return 1;
            }
        break;
    }


    if(present(TOKEN_NAME,TP))
    {
       if(present(god_token, TP))
        {
            write("You are already worshipping this deity.\n");
            return 1;
        }
        else
        {
            write("You can only worship one deity.\n");
            return 1;
        }
    }

    NF("You don't have any platinum coins.\n");


    if("/sys/global/money"->move_coins("platinum",1,TP,0))
        return 0;

    say(QCTNAME(TP)+" joins the the " + cult_type + " of " + deity_name + ".\n");
    write("You receive a " + adj1 + " " + adj2 + " " + emblem_name + ".\n");

    LOG_FILE("temples", "joined " + deity_name);

//    token = clone_object(emblem_file);
    token = clone_object("../base_emblem.c");
    token->set_adj(adj1);
    token->set_adj(adj2);

    token->move(TP);

    return 1;
}

