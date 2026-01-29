/*
 * waiter.c
 *
 * Used in nyreese/cadu_out.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>
#include <money.h>

/* a waiter selling beer in the outdoor cafe */

int i;

int 
buybeer(string str)
{
   
    object beer;
   
    if (str != "ale" && str != "beer")
    {
        command("say Buy what? An Ale?");
        return 1;
    }
   
    if (!present("silver coin", TP))
    {
        command("say I want silver!\n");
        return 1;
    }
    if (!find_living("kalufs"))
    {
        command("say Shit, Kalufs is gone!\n");
        command("shiver");
        command("Ehh, I trust you haven't done anything " +
                "naughty with him...?\n");
        return 1;
    }
    if (!MONEY_MOVE(1, "silver", TP, TO))
    {
        write("You give the waiter one silver coin.\n");
        say(QCTNAME(TP) + " gives a silver coin to the waiter.\n");
      
        command("north");
        command("buy silly");
        command("south");
      
        present("ale", TO)->move(TP);
        write("The waiter gives you your ale.\n");
        say("The waiter gives an ale to " + QCTNAME(TP) + ".");
      
        if (!QDONE(ROKEGROUP, STATUEQUEST))
        {
            write("I will tell you the tale of the statues: \n" +
                  "The statues were built by the three powerful " +
                  "wizards they are images of. The wizards decided " +
                  "that the city needed protection from war and " +
                  "evil beings and enchanted the statues with powerful " +
                  "spells. A rumor grew among the fishermen that if you " +
                  "sacrifice fish to the statues you will get help " +
                  "from the wizards in the future. Even today, many of " +
                  "the locals sacrifice fish to prevent accidents at sea.\n");
            say("The waiter whispers something to " + QCTNAME(TP) + ".\n");
        }
      
        i++;
        if (i==5)
        {
            //FIXA snyggare reaktion
            command("say Time for an ale, mate!");
            command("north");
            command("buy silly");
            command("drink ale");
            command("south");
            command("burp");
            i=0;
        }
    } 
    return 1;
}

void
create_monster()
{
    set_name("flint");
    add_name("waiter");
    set_short("Flint the Waiter");
    set_long("The waiter sells ale. A glass of ale costs one silver coin.\n");
    set_alignment(500);
    default_config_npc(100);
   
    set_chat_time(120);
    add_chat("Yesterday evening the ground shook...it is a portent!");
    set_act_time(2);
    add_act("say Strange tales are told about the statues.");
    add_act("sing");
    add_act("say In old times, people sacrificed fish to them.");
    add_act("shout ALE! Only one silver coin!");
    ALWAYSKNOWN;
    i=0;
}

void
init_living()
{
   add_action(buybeer, "buy");
}


int query_knight_prestige(){return -1;}
