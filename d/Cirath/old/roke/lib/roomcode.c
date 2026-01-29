/*
 * roomcode.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* this is the code inherited by the rooms that are part of the
   spellpaper-quest */

#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <macros.h>

#define LOCATIONHANDLER (ROKEDIR + "obj/locationhandler")

/* a init */

void
initrc()
{
    add_action("dig", "dig");
}

int
dig(string s)
{
    NF("It is often easier to dig using a shovel.\n");
    return 0;
}

/* call this function in create_room */

void
init_sp_quest()
{
    this_object()->add_prop(ROOM_I_DIG_FUN, "diggit");
    this_object()->add_item("ground","The ground looks really soft here.\n");
}

/* xp handler */

void
expea(int i)
{
    TP->catch_msg("You feel more experienced!\n");

    if (TP->query_exp() > i)
        TP->add_exp(i);
    else
        TP->add_exp(TP->query_exp());
}

/* this is the actual dig function. it performs some checking in
   the player and determines if this is the correct room for him */

int
diggit(string s)
{
    object ppapp, hole;

    NF("Dig where?\n");
    if (s != "here")
        return 0;
    
    ppapp = present("sppapp", this_player());
    if (!ppapp || ppapp->query_nummer() < 0)
    {
        /* he doesn't even have the paper. what a sucker! */
        
        write("You dig a little, but it is quite boring, so you stop.\n");
        say(QCTNAME(TP) + " digs a little in the ground.\n");
        return 1;
    }
    else
    {
        if (LOCATIONHANDLER->give_room(ppapp->query_nummer()) != MASTER ||
            QDONE(ROKEGROUP, PAPERQUEST))
        {
	  
            write("You dig a little, but it is quite boring, so you stop.\n");
            say(QCTNAME(TP) + " digs a little in the ground.\n");
            return 1;
	}
        else
	{
            /* yes! he's done it! */

            hole = clone_object(HOLEFILE);
            hole->move(TO);
            hole->set_long("It's a rather large hole.\n");
            
            clone_object(ROKEDIR + "obj/chest2")->move(hole);
            
            write("You dig a hole.\n");
            say(QCTNAME(TP) + " digs a hole in the ground.\n");

            this_object()->remove_prop(ROOM_I_DIG_FUN);

            /* let's share the experience! */
            
            QSET(ROKEGROUP, PAPERQUEST);
            QLOG("paperquest");

            expea(PAPERQUESTXP);

            ppapp->transform_me();

            return 1;
	}
    }
}
